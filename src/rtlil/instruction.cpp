#include <rtlil/instruction.h>

using namespace std;
using namespace afbd;

Instruction::Instruction() {
    _succs = make_shared<InstrEdgeContainer>();
}

std::shared_ptr<Var> Instruction::dst() const {
    return _dst;
}

void Instruction::dst(const std::shared_ptr<Var> &dst) {
    _dst = dst;
}


shared_ptr<Expr> Instruction::expr() const {
    return _expr;
}

void Instruction::expr(const shared_ptr<Expr> &expr) {
    _expr = expr;
}

std::shared_ptr<InstrEdgeContainer> Instruction::succs() {
    return _succs;
}

void Instruction::add_succ(const std::shared_ptr<Instruction> &dst, int delay) {
    _succs->push_back(make_pair(dst, delay));
}
