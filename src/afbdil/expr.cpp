#include <afbdil/expr.h>
#include <afbdil/var.h>
#include <iostream>
#include <sstream>

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

        case ExprType::DEFAULT:
            return "default";

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
        case ExprType::COND:
            return "cond";
        case ExprType::SHL:
            return "shl";
        case ExprType::LSHR:
            return "lshr";
        case ExprType::ASHR:
            return "ashr";
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
    auto begin = proc->begin();
    if(begin->type() != InstructionType::Trigger)
    {
        std::cout << "shit! begin of a process is not a trigger, during all_as_sens\n";
        return;
    }

    switch(_type)
    {
        case ExprType::VAR:
            begin->triggers()->push_back(std::make_pair(as_var(), Edge::EDGE));
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

std::string Expr::children_to_smv(std::string delim)
{
    std::stringstream smv_stream;
    smv_stream << "(";
    for(auto& operand: *_operands)
    {
        smv_stream << operand->to_smv();
        if(operand != _operands->back())
            smv_stream << " " << delim << " ";
    }
    smv_stream << ")";
    return smv_stream.str();
}

std::string Expr::binary_to_smv(std::string delim)
{
    return std::string("(") + get_operand(0)->to_smv() + " " + delim + " " + get_operand(1)->to_smv() + ")";
}

std::string Expr::to_smv()
{
    switch(type())
    {
        case ExprType::VAR:
            return *(as_var()->name());
        case ExprType::CONSTANT:
            return std::to_string(as_constant()->value());
        case ExprType::ADD:
            return children_to_smv("+");
        case ExprType::SUB:
            return children_to_smv("-");
        case ExprType::MUL:
            return children_to_smv("*");
        case ExprType::DIV:
            return children_to_smv("/");
        case ExprType::MOD:
            return children_to_smv("%");
        case ExprType::AND:
            return children_to_smv("&");
        case ExprType::OR:
            return children_to_smv("|");
        case ExprType::NOT:
            return std::string("~") + get_operand(0)->to_smv();
        case ExprType::XOR:
            return children_to_smv("^");
        case ExprType::EQ:
            return binary_to_smv("=");
        case ExprType::NE:
            return binary_to_smv("!=");
        case ExprType::GT:
            return binary_to_smv(">");
        case ExprType::GE:
            return binary_to_smv(">=");
        case ExprType::LT:
            return binary_to_smv("<");
        case ExprType::LE:
            return binary_to_smv("<=");
        case ExprType::COND:
            return std::string("(") + get_operand(0)->to_smv() + " ? " + get_operand(1)->to_smv() + " : " + get_operand(2)->to_smv() + ")";
        default:
            return std::string("(") + to_string(type()) + std::to_string(int(type())) + " is not supported)";
    }
}

namespace afbd {


    std::shared_ptr<Constant> constant_true = std::make_shared<Constant>(1, 1);
    std::shared_ptr<Expr> expr_true = std::make_shared<Expr>(constant_true);

    std::shared_ptr<Constant> constant_int_zero = std::make_shared<Constant>(32, 0);
    std::shared_ptr<Expr> expr_int_zero = std::make_shared<Expr>(constant_int_zero);

    std::shared_ptr<Constant> constant_int_one = std::make_shared<Constant>(32, 1);
    std::shared_ptr<Expr> expr_int_one = std::make_shared<Expr>(constant_int_one);

    std::shared_ptr<Constant> constant_int_minus_one = std::make_shared<Constant>(32, -1);
    std::shared_ptr<Expr> expr_int_minus_one = std::make_shared<Expr>(constant_int_minus_one);

    std::shared_ptr<Expr> double_fold(ExprType type, std::vector<std::shared_ptr<Expr>>& operands)
    {
        if(operands.size() == 1)
            return operands[0];
        if(operands.size() >= 2)
        {
            std::shared_ptr<Expr> curr = std::make_shared<Expr>(type, exl{operands[0], operands[1]});
            for(int i = 2; i < operands.size(); i++)
                curr = std::make_shared<Expr>(type, exl{curr, operands[i]});
            return curr;
        }
    }
}

Constant::Constant(int bit, int value): _bit(bit), _value(value) {}

int Constant::bit() const {
    return _bit;
}

int Constant::value() const {
    return _value;
}
