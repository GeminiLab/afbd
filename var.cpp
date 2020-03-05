#include <rtlil/var.h>

using namespace std;

Var::Var(int bit) {
    _bit = bit;
    _sens_procs = make_shared<ProcContainer>();
}

int Var::bit() const {
    return _bit;
}

std::shared_ptr<ProcContainer> Var::sens_procs() const {
    return _sens_procs;
}

void Var::add_sens_proc(const std::shared_ptr<Process>& proc) {
    _sens_procs->push_back(proc);
}
