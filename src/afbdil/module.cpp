#include <afbdil/module.h>
#include <iostream>
#include <sstream>

using namespace std;
using namespace afbd;

extern std::string no_slash(std::string& str);

Module::Module(std::string name) {
    _vars = make_shared<VarContainer>();
    _procs = make_shared<ProcContainer>();

    _name = no_slash(name);
    _has_error = false;
}

shared_ptr<VarContainer> Module::vars() const {
    return _vars;
}

shared_ptr<ProcContainer> Module::procs() const {
    return _procs;
}

std::shared_ptr<Var> Module::add_var(int bit, string name, int elem_bit) {
    auto rv = make_shared<Var>(bit, move(name), elem_bit);
    _vars->push_back(rv);

    return rv;
}

std::shared_ptr<Process> Module::add_proc() {
    auto rv = make_shared<Process>();
    _procs->push_back(rv);

    return rv;
}

std::string Module::name() const {
    return _name;
}

std::shared_ptr<Module> Module::substitute_clone(std::map<std::shared_ptr<Var>, std::shared_ptr<Expr>>& substitute_map, int occurence)
{
    std::string new_module_name = name() + "_" + std::to_string(occurence);
    auto new_module = std::make_shared<Module>(new_module_name);

    for(auto var : *_vars)
    {
        auto substitute = substitute_map[var];
        if(substitute->type() == ExprType::VAR)
            new_module->_vars->push_back(substitute->as_var());
    }

    for(auto proc : *_procs)
    {
        std::shared_ptr<Process> new_proc = proc->substitute_clone(substitute_map);
        new_module->_procs->push_back(new_proc);
    }

    return new_module;
}

void Module::modules_in_one(std::vector<std::shared_ptr<Module>>& modules)
{
    _name = modules[0]->name();
    for(auto m : modules)
    {
        for(auto v : *(m->_vars))
            _vars->push_back(v);
        for(auto p : *(m->_procs))
            _procs->push_back(p);
    }

}

json11::Json Module::to_json()
{
    std::map<std::string, json11::Json> ret_map;

    ret_map["name"] = _name;

    std::vector<json11::Json> vars_vec;
    for(auto& var : *_vars)
        vars_vec.push_back(var->to_json());
    ret_map["vars"] = json11::Json(vars_vec);

    std::vector<json11::Json> procs_vec;
    for(auto& proc : *_procs)
        procs_vec.push_back(proc->to_json());
    ret_map["procs"] = json11::Json(procs_vec);

    return json11::Json(ret_map);
}

std::string Module::to_smv()
{
    std::vector<std::shared_ptr<Expr>> expressions;
    std::map<std::shared_ptr<Var>, int> vars_next;
    std::map<std::shared_ptr<Var>, int> vars_init;
    std::set<std::shared_ptr<Var>> edge_vars;
    std::vector<std::pair<int, std::shared_ptr<Expr>>> countdowns;
    std::set<std::string> conditions;
    int temp_var_num = 0;

    for(auto proc: *_procs)
    {
        proc->to_smv(expressions, vars_next, vars_init, edge_vars, countdowns, *_vars, temp_var_num, conditions);
    }

    std::stringstream smv_stream;

    smv_stream << " -- generate by afbd Verilog compiler!\n\n";
    smv_stream << "MODULE main\n\n";

    smv_stream << "VAR\n";
    smv_stream << " -- original vars --\n";
    for(auto var: *_vars)
    {
        smv_stream << "\t" << *(var->name()) << " : word[" << var->bit() << "];\n";
    }
    smv_stream << " -- edge vars --\n";
    for(auto edge_var: edge_vars)
    {
        auto edge_var_name = *(edge_var->name());
        smv_stream << "\t" << edge_var_name << "_last : word[" << edge_var->bit() << "];\n";
        smv_stream << "\t" << edge_var_name << "_edge : -1 .. 1;\n";
    }
    smv_stream << "\n";
    smv_stream << " -- countdown vars --\n";
    for(int countdown_id = 0; countdown_id < countdowns.size(); countdown_id++)
    {
        auto countdown_max = countdowns[countdown_id].first;
        smv_stream << "\t__countdown_" << countdown_id << " : 0 .. " << countdown_max << ";\n";
        smv_stream << "\t__countdown_" << countdown_id << "_last : 0 .. " << countdown_max << ";\n";
        smv_stream << "\t__countdown_" << countdown_id << "_ok : boolean;\n";
    }

    smv_stream << "DEFINE\n";
    for(int i = 0; i < expressions.size(); i++)
    {
        auto expr = expressions[i];
        smv_stream << "\t__expr" << i << " := " << expr->to_smv() << ";\n";
    }

    smv_stream << "ASSIGN\n";
    smv_stream << "\n -- initialization --\n";
    for(auto var: *_vars)
        if(vars_init.find(var) != vars_init.end())
        {
            smv_stream << "\tinit(" << *(var->name()) << ") := __expr" << vars_init[var] << ";\n";
            if(edge_vars.find(var) != edge_vars.end())
                smv_stream << "\tinit(" << *(var->name()) << "_last) := __expr" << vars_init[var] << ";\n";
        }

    smv_stream << "\n -- transformation --\n";
    for(auto var: *_vars)
        if(vars_next.find(var) != vars_next.end())
        {
            smv_stream << "\tnext(" << *(var->name()) << ") := __expr" << vars_next[var] << ";\n";
            if(edge_vars.find(var) != edge_vars.end())
                smv_stream << "\tnext(" << *(var->name()) << "_last) := " << *(var->name()) << ";\n";
        }

    smv_stream << "\n -- edge calculation --\n";
    for(auto edge_var: edge_vars)
    {
        std::string name = *(edge_var->name());
        std::string name_last = name + "_last";

        smv_stream << name << "_edge := (" << name << " > " << name_last << ") ? 1 : ((" << name << " < " << name_last << ") ? -1 : 0);\n";
    }

    smv_stream << "\n -- countdown calculation --\n";
    for(int countdown_id = 0; countdown_id < countdowns.size(); countdown_id++)
    {
        auto countdown_max = countdowns[countdown_id].first;
        auto countdown_expr = countdowns[countdown_id].second;

        auto countdown_name = std::string("__countdown_") + std::to_string(countdown_id);
        smv_stream << "next(" << countdown_name << ") := " << countdown_expr->to_smv() << " ? " << countdown_max << " : (" << countdown_name << " > 0 ? " << countdown_name << " - 1 : 0);\n";

        auto countdown_last_name = std::string("__countdown_") + std::to_string(countdown_id) + "_last";
        smv_stream << "next(" << countdown_last_name << ") := " << countdown_name << ";\n";

        auto countdown_ok_name = std::string("__countdown_") + std::to_string(countdown_id) + "_ok";
        smv_stream << "next(" << countdown_ok_name << ") := (" << countdown_last_name << " = 1);\n";
    }

    smv_stream << "SPEC\n";

    smv_stream << "-- all states can lead to initial state --\n";
    smv_stream << "    AG(EF(";
    for(auto var_init = vars_init.begin(); var_init != vars_init.end(); var_init++)
    {
        if(var_init != vars_init.begin())
            smv_stream << " & ";
        auto name = *(var_init->first->name());
        auto expr = expressions[var_init->second];
        smv_stream << name << " = " << expr->to_smv();
    }
    smv_stream << "));\n";

    smv_stream << "-- all statements are reachable --\n";
    for(auto condition_it = conditions.begin(); condition_it != conditions.end(); condition_it++)
    {
        if(condition_it != conditions.begin())
            smv_stream << " & ";
        else
            smv_stream << "    ";

        auto condition = *condition_it;
        if(condition[0] == '(')
            smv_stream << "EF" << condition;
        else
            smv_stream << "EF(" << condition <<  ")";
    }
    smv_stream << ";\n";

    return smv_stream.str();
}