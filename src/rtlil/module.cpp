#include <rtlil/module.h>

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

