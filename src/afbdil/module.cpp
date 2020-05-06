#include <afbdil/module.h>

using namespace std;
using namespace afbd;

Module::Module(std::string name) {
    _vars = make_shared<VarContainer>();
    _procs = make_shared<ProcContainer>();

    _name = name;
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

void Module::add_triggered_proc(shared_ptr<Var> var, shared_ptr<Process> proc) {
    var->add_sens_proc(proc);
}

std::string Module::name() const {
    return _name;
}

std::shared_ptr<Module> Module::substitute_clone(std::map<std::shared_ptr<Var>, std::shared_ptr<Expr>>& substitute_map, int occurence)
{
    std::string new_module_name = name() + "$" + std::to_string(occurence);
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
