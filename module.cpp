#include <rtlil/module.h>

using namespace std;

Module::Module() {
    _vars = make_shared<VarContainer>();
    _procs = make_shared<ProcContainer>();
}

shared_ptr<VarContainer> Module::vars() const {
    return _vars;
}

shared_ptr<ProcContainer> Module::procs() const {
    return _procs;
}

std::shared_ptr<Var> Module::add_var(int bit) {
    auto rv = make_shared<Var>(bit);
    _vars->push_back(rv);

    return rv;
}

std::shared_ptr<Process> Module::add_proc() {
    auto rv = make_shared<Process>();
    _procs->push_back(rv);

    return rv;
}
