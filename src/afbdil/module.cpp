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
    std::map<std::shared_ptr<Expr>, int> expr2id;
    std::map<std::shared_ptr<Var>, int> vars_next;
    std::map<std::shared_ptr<Var>, int> vars_init;
    std::set<std::shared_ptr<Var>> edge_vars;

    for(auto proc: *_procs)
    {
        proc->to_smv(expressions, expr2id, vars_next, vars_init, edge_vars);
    }

    std::stringstream smv_stream;

    smv_stream << "generate by afbd Verilog compiler!\n\n";
    smv_stream << "MODULE " << name() << "\n\n";

    smv_stream << "VAR\n";
    smv_stream << " -- original vars --\n";
    for(auto var: *_vars)
    {
        smv_stream << "\t\"" << *(var->name()) << "\" : word[" << var->bit() << "];\n";
    }
    /*smv_stream << " -- edge vars --\n";
    for(auto edge_var: edge_vars)
    {
        smv_stream << "\t\"" << edge_var->name() << "\" : -1, 0, 1;\n";
    }
    smv_stream << "\n";*/

    smv_stream << "DEFINE\n";
    for(int i = 0; i < expressions.size(); i++)
    {
        auto expr = expressions[i];
        smv_stream << "\t__expr" << i << " := " << expr->to_smv() << ";\n";
    }

    smv_stream << "\n -- initialization --\n";
    for(auto var: *_vars)
        if(vars_init.find(var) != vars_init.end())
            smv_stream << "\tinit(\"" << *(var->name()) << "\") = __expr" << vars_init[var] << ";\n";

    smv_stream << "\n -- transformation --\n";
    for(auto var: *_vars)
        if(vars_next.find(var) != vars_next.end())
            smv_stream << "\tnext(\"" << *(var->name()) << "\") = __expr" << vars_next[var] << ";\n";

    return smv_stream.str();
}