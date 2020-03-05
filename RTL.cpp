#include <rtlil/rtlil>

#include <iostream>
#include <memory>
using namespace std;

int main() {
    Module m;
    auto a = m.add_var(1);
    auto b = m.add_var(1);
    auto c = m.add_var(1);
    auto proc = m.add_proc();
    proc->type(ProcessType::Continuous);

    auto instr = make_shared<Instruction>(InstructionType::XOR);
    instr->dst(c);
    instr->add_src(a);
    instr->add_src(b);

    proc->begin()->add_succ(instr, 2);

    return 0;
}
