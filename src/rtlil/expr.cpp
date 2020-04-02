#include <rtlil/expr.h>

using namespace std;
using namespace afbd;


Expr::Expr(shared_ptr<Var> var): _type(ExprType::VAR), _var(var) {
    _constant = nullptr;
    _operands = nullptr;
}

Expr::Expr(shared_ptr<Constant> constant): _type(ExprType::CONSTANT), _constant(constant) {
    _var = nullptr;
    _operands = nullptr;
}

Expr::Expr(ExprType type, std::initializer_list<std::shared_ptr<Expr>> operands): _type(type) {
    _var = nullptr;
    _constant = nullptr;
    _operands = make_shared<std::vector<std::shared_ptr<Expr>>>(operands);
}

Expr::Expr(ExprType type, std::vector<std::shared_ptr<Expr>> operands) : _type(type) {
    _var = nullptr;
    _constant = nullptr;
    _operands = make_shared<std::vector<std::shared_ptr<Expr>>>(operands);
}

ExprType Expr::type() const {
    return _type;
}

std::shared_ptr<Var> Expr::as_var() const {
    return _type == ExprType::VAR ? _var : nullptr;
}

std::shared_ptr<Constant> Expr::as_constant() const {
    return _type == ExprType::CONSTANT ? _constant : nullptr;
}

int Expr::operand_num() const {
    return _operands->size();
}

std::shared_ptr<Expr> Expr::get_operand(int i) const {
    return _operands->at(i);
}


Constant::Constant(int bit, int value): _bit(bit), _value(value) {}

int Constant::bit() const {
    return _bit;
}

int Constant::value() const {
    return _value;
}
