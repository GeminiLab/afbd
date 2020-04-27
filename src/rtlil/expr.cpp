#include <rtlil/expr.h>
#include <rtlil/var.h>

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

bool Expr::is_true() const {
    return _type == ExprType::CONSTANT && _constant->value() != 0;
}

void Expr::simplify() {
    if(_type == ExprType::VAR || _type == ExprType::CONSTANT)
        return;

    for(auto operand : *_operands)
        operand->simplify();

    int bits = -1;
    for(auto operand : *_operands)
    {
        if(operand->_type != ExprType::CONSTANT)
            return;
        int operand_bits = operand->bit();
        if(operand_bits > bits)
            bits = operand_bits;
    }

    switch(_type)
    {
        case ExprType::ADD:
            _type = ExprType::CONSTANT;
            _constant = std::make_shared<Constant>(bits, _operands->at(0)->as_constant()->value() + _operands->at(1)->as_constant()->value());
            _operands->clear();
            break;
        case ExprType::SUB:
            _type = ExprType::CONSTANT;
            _constant = std::make_shared<Constant>(bits, _operands->at(0)->as_constant()->value() - _operands->at(1)->as_constant()->value());
            _operands->clear();
            break;
        case ExprType::MUL:
            _type = ExprType::CONSTANT;
            _constant = std::make_shared<Constant>(bits, _operands->at(0)->as_constant()->value() * _operands->at(1)->as_constant()->value());
            _operands->clear();
            break;
    }
}

int Expr::bit() const {
    if(_type == ExprType::VAR)
        return _var->bit();
    if(_type == ExprType::CONSTANT)
        return _constant->bit();

    int ret = 0;
    for(auto& child : *_operands)
    {
        int child_bit = child->bit();
        if(child_bit > ret)
            ret = child_bit;
    }
    return ret;
}

std::string to_string(ExprType type) {
    switch(type)
    {
        case ExprType::VAR:
            return "var";
        case ExprType::CONSTANT:
            return "constant";
            /*
        case ExprType::DEFAULT:
            return "default";
             */
        case ExprType::ADD:
            return "add";
        case ExprType::SUB:
            return "sub";
        case ExprType::MUL:
            return "mul";
        case ExprType::DIV:
            return "div";
        case ExprType::MOD:
            return "mod";
        case ExprType::AND:
            return "and";
        case ExprType::OR:
            return "or";
        case ExprType::XOR:
            return "xor";
        case ExprType::NOT:
            return "not";
        case ExprType::CONCAT:
            return "concat";
        case ExprType::SUBVEC:
            return "subvec";
        case ExprType::EQ:
            return "eq";
        case ExprType::NE:
            return "ne";
        case ExprType::LT:
            return "lt";
        case ExprType::LE:
            return "le";
        case ExprType::GT:
            return "gt";
        case ExprType::GE:
            return "ge";
        case ExprType::REDUCE_BOOL:
            return "reduce_bool";
        default:
            return "unknown";
    }
}

json11::Json Expr::to_json() {
    switch(_type)
    {
        case ExprType::VAR:
            return json11::Json::object{{"op", "var"}, {"var", *as_var()->name()}};
        case ExprType::CONSTANT:
            return json11::Json::object{{"op", "const"}, {"width", as_constant()->bit()}, {"value", int(as_constant()->value())}};
        default:
            std::map<std::string, json11::Json> ret_map;
            ret_map["op"] = to_string(_type);
            std::vector<json11::Json> operands_vec;
            for(auto& operand : *_operands)
                operands_vec.push_back(operand->to_json());
            ret_map["operands"] = json11::Json(operands_vec);
            return json11::Json(ret_map);
    }
}

void Expr::all_as_sens(std::shared_ptr<Module>& module, std::shared_ptr<Process>& proc)
{
    switch(_type)
    {
        case ExprType::VAR:
            module->add_triggered_proc(_var, proc);
            // proc->add_sensitive_var(std::make_pair(_var, EDGE));
            module->add_triggered_proc(_var, proc);
            return;
        case ExprType::CONSTANT:
            return;
        default:
            for(auto& child : *_operands)
                child->all_as_sens(module, proc);
            return;
    }
}

std::shared_ptr<Expr> Expr::substitute_clone(std::map<std::shared_ptr<Var>, std::shared_ptr<Expr>>& substitute_map)
{
    std::shared_ptr<Expr> ret;
    switch(_type)
    {
    case ExprType::CONSTANT:
    {
        auto constant = as_constant();
        ret = std::make_shared<Expr>(std::make_shared<Constant>(constant->bit(), constant->value()));
        break;
    }
    case ExprType::VAR:
        ret = substitute_map[_var];
        break;
    default:
        ret = std::make_shared<Expr>(_type, exl{});
        for(auto operand : *_operands)
            ret->_operands->push_back(operand->substitute_clone(substitute_map));
        break;
    }
    return ret;
}

namespace afbd {


    std::shared_ptr<Constant> constant_true = std::make_shared<Constant>(1, 1);
    std::shared_ptr<Expr> expr_true = std::make_shared<Expr>(constant_true);

    std::shared_ptr<Constant> constant_int_zero = std::make_shared<Constant>(32, 0);
    std::shared_ptr<Expr> expr_int_zero = std::make_shared<Expr>(constant_int_zero);

    std::shared_ptr<Expr> expr_default = std::make_shared<Expr>(ExprType::DEFAULT, exl{});
}

Constant::Constant(int bit, int value): _bit(bit), _value(value) {}

int Constant::bit() const {
    return _bit;
}

int Constant::value() const {
    return _value;
}
