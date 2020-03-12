#include <rtlil/instruction.h>

using namespace std;

Instruction::Instruction(InstructionType type) {
    _type = type;
    _src = make_shared<VarContainer>();
    _succs = make_shared<InstrEdgeContainer>();
}

InstructionType Instruction::type() const {
    return _type;
}

std::shared_ptr<Var> Instruction::dst() const {
    return _dst;
}

void Instruction::dst(const std::shared_ptr<Var> &dst) {
    _dst = dst;
}

std::shared_ptr<VarContainer> Instruction::src() const {
    return _src;
}

void Instruction::add_src(const std::shared_ptr<Var> &src) {
    _src->push_back(src);
}

std::shared_ptr<InstrEdgeContainer> Instruction::succs() {
    return _succs;
}

void Instruction::add_succ(const std::shared_ptr<Instruction> &dst, int delay) {
    _succs->push_back(make_pair(dst, delay));
}
