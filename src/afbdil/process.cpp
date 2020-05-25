#include <afbdil/process.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <set>

using namespace std;
using namespace afbd;

namespace afbd {
	extern std::shared_ptr<Expr> expr_true;
    extern std::shared_ptr<Expr> expr_int_zero;
    extern std::shared_ptr<Expr> expr_int_one;
    extern std::shared_ptr<Expr> expr_int_minus_one;
    extern std::shared_ptr<Expr> expr_nobit_zero;
    extern std::shared_ptr<Expr> expr_nobit_one;
    extern std::shared_ptr<Expr> expr_nobit_minus_one;
}

std::string proc_type_to_str(ProcessType type)
{
	switch(type)
	{
	case ProcessType::Initial:
		return "initial";
	case ProcessType::Always:
		return "always";
	}
}

ProcessType str_to_proc_type(std::string str)
{
	if(str == "initial")
		return ProcessType::Initial;
	else if(str == "always")
		return ProcessType::Always;
}

Process::Process() {
    inst_num = 0;
    _type = Always;
	_begin = nullptr;

}

ProcessType Process::type() const {
    return _type;
}

void Process::type(ProcessType type) {
    _type = type;
}

shared_ptr<Instruction> Process::begin() const {
    return _begin;
}

void Process::begin(const std::shared_ptr<Instruction> &begin) {
    _begin = begin;
}

// NEED REWRITE
std::shared_ptr<Process> Process::substitute_clone(std::map<std::shared_ptr<Var>, std::shared_ptr<Expr>>& substitute_map)
{
    auto new_process = std::make_shared<Process>();
    new_process->_type = _type;

    std::vector<std::shared_ptr<Instruction>> tovisits_old;
    std::vector<std::shared_ptr<Instruction>> tovisits_new;

    tovisits_old.push_back(begin());
    //tovisits_new.push_back(new_process->begin());

    std::vector<std::shared_ptr<Instruction>> created_insts;

    static bool visited[MAX_INST_NUM];

    memset(visited, 0, sizeof(bool) * inst_num);
    visited[0] = true;
    while(!tovisits_old.empty())
    {
        auto tovisit_old = tovisits_old.back();
		tovisits_old.pop_back();

		std::shared_ptr<Instruction> tovisit_new;

		if(!tovisits_new.empty())
		{
			tovisit_new = tovisits_new.back();
			tovisits_new.pop_back();
		}
		else
		{
			auto tovisit_begin = std::make_shared<Instruction>(new_process);
			created_insts.push_back(tovisit_begin);
			new_process->begin(tovisit_begin);
			tovisit_new = tovisit_begin;
		}

		//For delay
		tovisit_new->delay(tovisit_old->delay());

		//For assign
		if(tovisit_old->expr())
		{
			tovisit_new->expr(tovisit_old->expr()->substitute_clone(substitute_map));
			tovisit_new->assign_type(tovisit_old->assign_type());
		}

        if(tovisit_old->dst())
        {
            auto dst = tovisit_old->dst()->substitute_clone(substitute_map);
            if(dst->type() != ExprType::VAR && (dst->type() != ExprType::SUBVEC))
                std::cout << "error! dst must be a VAR\n";
            tovisit_new->dst(dst);
			tovisit_new->assign_type(tovisit_old->assign_type());
        }

		//For trigger
		if(tovisit_old->triggers())
		{
			auto new_triggers = std::make_shared<TriggerContainer>();
			for(auto trigger : *(tovisit_old->triggers()))
			{
				Trigger new_trigger = std::make_pair(substitute_map[trigger.first]->as_var(), trigger.second);
				new_triggers->push_back(new_trigger);
			}
			tovisit_new->triggers(new_triggers);
		}

        for(auto& succ : *(tovisit_old->succs()))
        {
            //if(new_process->inst_num != created_insts.size())
            //   std::cout << "error! size not match " << new_process->inst_num << " " << created_insts.size();

            while(succ.first->id() >= created_insts.size())
            {
                created_insts.push_back(std::make_shared<Instruction>(new_process));

                //if(new_process->inst_num != created_insts.size())
                //    std::cout << "error! size not match " << new_process->inst_num << " " << created_insts.size();
            }

            auto& new_succ = created_insts[succ.first->id()];
            tovisit_new->add_succ(new_succ, succ.second->substitute_clone(substitute_map));

            if(!visited[succ.first->id()])
            {
                tovisits_old.push_back(succ.first);
                tovisits_new.push_back(new_succ);
                visited[succ.first->id()] = true;
            }
        }

        /*if(tovisit_old->succs()->empty() && type() == ProcessType::Always) //link to begin
        {
            tovisit_new->add_succ(new_process->begin(), afbd::expr_true);
        }*/
    }
    return new_process;
}

json11::Json Process::to_json()
{
    std::map<std::string, json11::Json> ret_map;
    ret_map["type"] = proc_type_to_str(_type);
    //ret_map["sen"] = json11::Json::array(); //todo
        
    std::map<std::string, json11::Json> instr_map;

    static bool visited_instr[MAX_INST_NUM];
    memset(visited_instr, 0, sizeof(bool) * inst_num);
    std::vector<std::shared_ptr<Instruction>> tovisit;
    tovisit.push_back(begin());
    visited_instr[0] = true;
    while(!tovisit.empty())
    {
        auto curr = tovisit.back();
        tovisit.pop_back();
        int id = curr->id();

        visited_instr[id] = true;
        instr_map[std::to_string(id)] = curr->to_json();

        for(auto succ_edge : *(curr->succs()))
        {
            auto succ = succ_edge.first;
            int succ_id = succ->id();
            if(!visited_instr[succ_id])
            {
                tovisit.push_back(succ);
                visited_instr[succ_id] = true;
            }
        }

    }
    ret_map["instrs"] = instr_map;
    return ret_map;
}

std::vector<std::shared_ptr<Instruction>> Process::all_instructions() //topological order
{
    std::vector<std::shared_ptr<Instruction>> ret;

    bool added[MAX_INST_NUM];
    memset(added, 0, MAX_INST_NUM * sizeof(bool));

    int visited_pred_num[MAX_INST_NUM];
    memset(visited_pred_num, 0, MAX_INST_NUM * sizeof(int));

    std::list<std::shared_ptr<Instruction>> tovisit{begin()};
    added[begin()->id()] = true;
    ret.push_back(begin());
    while(!tovisit.empty())
    {
        for(auto curr = tovisit.begin(); curr != tovisit.end();)
        {
            auto curr_shared = *curr;

            if(curr_shared->pred_num() != visited_pred_num[curr_shared->id()])
            {
                curr++;
                continue;
            }
            ret.push_back(curr_shared);
            for (auto succ : *(curr_shared->succs())) {
                auto succ_inst = succ.first;
                visited_pred_num[succ_inst->id()]++;
                if (!added[succ_inst->id()]) {
                    added[succ_inst->id()] = true;
                    tovisit.push_back(succ_inst);
                }
            }

            curr = tovisit.erase(curr);
        }
    }
    return ret;
}

std::shared_ptr<Expr> generate_condition(Trigger trigger, std::set<std::shared_ptr<Var>>& edge_vars)
{
    auto var = trigger.first;
    //auto expr = std::make_shared<Expr>(var);
    auto edge = trigger.second;

    edge_vars.insert(var);

    std::string edge_var_name = (*var->name()) + "_edge";
    std::shared_ptr<Var> edge_var = std::make_shared<Var>(32, edge_var_name, 32);
    std::shared_ptr<Expr> edge_expr = std::make_shared<Expr>(edge_var);

    if(edge == Edge::EDGE)
        //return nullptr;
        return std::make_shared<Expr>(ExprType::NE, exl{edge_expr, expr_nobit_zero});
    else if(edge == Edge::POSEDGE)
        //return std::make_shared<Expr>(ExprType::EQ, exl{expr, expr_int_one});
        return std::make_shared<Expr>(ExprType::EQ, exl{edge_expr, expr_nobit_one});
    else if(edge == Edge::NEGEDGE)
        //return std::make_shared<Expr>(ExprType::EQ, exl{expr, expr_int_zero});
        return std::make_shared<Expr>(ExprType::EQ, exl{edge_expr, expr_nobit_minus_one});
    else
    {
        std::cout << "Illegal trigger\n";
        return nullptr;
    }
}

void Process::to_smv(std::vector<std::shared_ptr<Expr>>& expressions, std::map<std::shared_ptr<Var>, int>& vars_next, std::map<std::shared_ptr<Var>, int>& vars_init, std::set<std::shared_ptr<Var>>& edge_vars, std::vector<std::pair<int, std::shared_ptr<Expr>>>& countdowns, std::vector<std::shared_ptr<Var>>& vars, int& temp_var_num, std::set<std::string>& conditions)
{
    std::vector<std::shared_ptr<Expr>> condition_vec(inst_num, nullptr);

    auto instructions = all_instructions();
    for(auto inst: instructions)
    {
        std::shared_ptr<Expr> inherit_condition;
        std::vector<std::shared_ptr<Expr>> pred_conditions;
        for(auto pred: inst->preds())
        {
            auto pred_id = pred.first;
            auto pred_to_curr = pred.second;
            auto pred_condition = condition_vec[pred_id];
            if(!pred_condition)
                std::cout << "error! one instruction is processed before all its preds\n";
            pred_conditions.push_back(std::make_shared<Expr>(ExprType::AND, exl{pred_to_curr, pred_condition}));
        }

        if(pred_conditions.empty())
            inherit_condition = expr_true;
        else
            inherit_condition = double_fold(ExprType::OR, pred_conditions);

        std::shared_ptr<Expr> new_condition = inherit_condition;

        if(inst->type() == InstructionType::Trigger)
        {
            auto triggers = begin()->triggers();
            switch (triggers->size()) {
                case 0:
                    new_condition = expr_true;
                    break;
                case 1:
                    new_condition = generate_condition((*triggers)[0], edge_vars);
                    break;
                default:
                {
                    std::vector<std::shared_ptr<Expr>> operands;
                    for (auto trigger: *triggers)
                    {
                        auto one_cond = generate_condition(trigger, edge_vars);
                        if (one_cond)
                            operands.push_back(one_cond);
                    }
                    if (operands.size() == 0)
                        new_condition = expr_true;
                    else
                        new_condition = double_fold(ExprType::OR, operands);
                    break;
                }
            }
        }
        if(inst->type() == InstructionType::Delay && inst->delay() > 0)
        {
            int countdown_id = countdowns.size();
            countdowns.push_back(std::make_pair(inst->delay(), inherit_condition));
            std::string countdown_ok_name = std::string("__countdown_") + std::to_string(countdown_id) + std::string("_ok");
            std::shared_ptr<Var> countdown_ok_var = std::make_shared<Var>(1, countdown_ok_name);
            new_condition = std::make_shared<Expr>(countdown_ok_var);
        }

        if(inst->type() == InstructionType::Assign && inst->dst())
        {
            if(inst->dst()->type() == ExprType::VAR)
            {
                if(inst->delay() <= 0)
                {
                    auto var = inst->dst()->as_var();

                    std::shared_ptr<Expr> src;
                    if (!inherit_condition->is_true())
                    {
                        conditions.insert(inherit_condition->to_smv());
                        src = std::make_shared<Expr>(ExprType::COND, exl{inherit_condition, inst->expr(), inst->dst()});
                    }
                    else
                        src = inst->expr();

                    if (type() == ProcessType::Initial)
                    {
                        if (vars_init.find(var) != vars_init.end())
                            std::cout << "Warning, " << *(var->name()) << " has been initialized\n";
                        else
                        {
                            int src_id = expressions.size();
                            expressions.push_back(src);
                            vars_init[var] = src_id;
                        }
                    }
                    else
                    {
                        if (vars_next.find(var) != vars_next.end()) {
                            auto old_id = vars_next[var];
                            auto old_src = expressions[old_id];
                            if (old_src->type() != ExprType::COND || src->type() != ExprType::COND)
                                std::cout << "Warning! A conditional assignment and an unconditional one conflict\n";
                            else
                            {
                                auto curr = old_src;
                                while (curr->type() == ExprType::COND && curr->get_operand(2)->type() == ExprType::COND)
                                    curr = curr->get_operand(2);
                                curr->get_operand(2) = src;
                            }
                        }
                        else
                        {
                            int src_id = expressions.size();
                            expressions.push_back(src);
                            vars_next[var] = src_id;
                        }
                    }
                }
                else
                {
                    auto var = inst->dst()->as_var();

                    auto temp_var_name = std::string("__temp_var_") + std::to_string(temp_var_num);
                    temp_var_num++;
                    auto temp_var = std::make_shared<Var>(var->bit(), temp_var_name);
                    auto temp_var_expr = std::make_shared<Expr>(temp_var);

                    std::shared_ptr<Expr> src;

                    if (!inherit_condition->is_true())
                    {
                        conditions.insert(inherit_condition->to_smv());
                        src = std::make_shared<Expr>(ExprType::COND, exl{inherit_condition, inst->expr(), temp_var_expr});
                    }
                    else
                        src = inst->expr();

                    int src_id = expressions.size();
                    expressions.push_back(src);
                    vars.push_back(temp_var);
                    vars_next[temp_var] = src_id;

                    int countdown_id = countdowns.size();
                    countdowns.push_back(std::make_pair(inst->delay(), inherit_condition));
                    std::string countdown_ok_name = std::string("__countdown_") + std::to_string(countdown_id) + std::string("_ok");
                    std::shared_ptr<Var> countdown_ok_var = std::make_shared<Var>(1, countdown_ok_name);
                    new_condition = std::make_shared<Expr>(countdown_ok_var);

                    conditions.insert(new_condition->to_smv());
                    auto src2 = std::make_shared<Expr>(ExprType::COND, exl{new_condition, temp_var_expr, inst->dst()});

                    if (vars_next.find(var) != vars_next.end())
                    {
                        auto old_id = vars_next[var];
                        auto old_src = expressions[old_id];
                        if (old_src->type() != ExprType::COND || src->type() != ExprType::COND)
                            std::cout << "Warning! A conditional assignment and an unconditional one conflict\n";
                        else
                        {
                            auto curr = old_src;
                            while (curr->type() == ExprType::COND && curr->get_operand(2)->type() == ExprType::COND)
                                curr = curr->get_operand(2);
                            curr->get_operand(2) = src2;
                        }
                    }
                    else
                    {
                        int temp_var_id = expressions.size();
                        expressions.push_back(src2);
                        vars_next[var] = temp_var_id;
                    }
                }
            }
        }
        condition_vec[inst->id()] = new_condition;
    }

}