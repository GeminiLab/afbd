#include <rtlil/process.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;
using namespace afbd;

namespace afbd {
	extern std::shared_ptr<Expr> expr_true;
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
    tovisits_new.push_back(new_process->begin());

    std::vector<std::shared_ptr<Instruction>> created_insts;
    created_insts.push_back(new_process->begin());

    static bool visited[MAX_INST_NUM];

    memset(visited, 0, sizeof(bool) * inst_num);
    visited[0] = true;
    while(!tovisits_old.empty())
    {
        auto tovisit_old = tovisits_old.back();
        auto tovisit_new = tovisits_new.back();

        tovisits_old.pop_back();
        tovisits_new.pop_back();

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

		//For delay
		if(tovisit_old->delay() != 0)
			tovisit_new->delay(tovisit_old->delay());

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
            if(new_process->inst_num != created_insts.size())
                std::cout << "error! size not match " << new_process->inst_num << " " << created_insts.size();

            while(succ.first->id() >= new_process->inst_num)
            {
                created_insts.push_back(std::make_shared<Instruction>(new_process));

                if(new_process->inst_num != created_insts.size())
                    std::cout << "error! size not match " << new_process->inst_num << " " << created_insts.size();
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

        if(tovisit_old->succs()->empty() && type() == ProcessType::Always) //link to begin
        {
            tovisit_new->add_succ(new_process->begin(), afbd::expr_true);
        }
    }
    return new_process;
}

json11::Json Process::to_json()
{
    std::map<std::string, json11::Json> ret_map;
    ret_map["type"] = "continues"; //todo
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