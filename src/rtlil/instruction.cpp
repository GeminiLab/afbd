#include <rtlil/instruction.h>

using namespace std;
using namespace afbd;

Instruction::Instruction() {
    _succs = make_shared<InstrEdgeContainer>();
    _pseudo_begin = false;
    _pseudo_end = false;
}

std::shared_ptr<Var> Instruction::dst() const {
    return _dst;
}

void Instruction::dst(const shared_ptr<Var> &dst) {
    _dst = dst;
}

shared_ptr<Expr> Instruction::expr() const {
    return _expr;
}

void Instruction::expr(const shared_ptr<Expr> &expr) {
    _expr = expr;
}

shared_ptr<InstrEdgeContainer> Instruction::succs() {
    return _succs;
}

void Instruction::add_succ(const shared_ptr<Instruction> &dst, const shared_ptr<Expr> &cond) {
    _succs->push_back(make_pair(dst, cond));
}

bool Instruction::pseudo_begin() const {
    return _pseudo_begin;
}

void Instruction::pseudo_begin(bool value) {
    _pseudo_begin = value;
}

bool Instruction::pseudo_end() const {
    return _pseudo_end;
}

void Instruction::pseudo_end(bool value) {
    _pseudo_end = value;
}
