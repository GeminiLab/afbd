#include <afbdil/expr.h>
#include <afbdil/var.h>
#include <iostream>
#include <sstream>
#include <algorithm>

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
    simplify();
}

Expr::Expr(ExprType type, std::vector<std::shared_ptr<Expr>> operands) : _type(type) {
    _var = nullptr;
    _constant = nullptr;
    _operands = make_shared<std::vector<std::shared_ptr<Expr>>>(operands);
    simplify();
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

std::shared_ptr<Expr>& Expr::get_operand(int i) const {
    return _operands->at(i);
}

bool Expr::is_true() const {
    return _type == ExprType::CONSTANT && _constant->value() != 0;
}

void Expr::simplify() {
    if(_type == ExprType::VAR || _type == ExprType::CONSTANT)
        return;

    //for(auto operand : *_operands)
    //    operand->simplify();

    switch(_type)
    {
        case ExprType::ADD:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(std::max({first->bit(), second->bit()}), first->value() + second->value());
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            break;
        case ExprType::SUB:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(std::max({first->bit(), second->bit()}), first->value() - second->value());
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            break;
        case ExprType::MUL:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(std::max({first->bit(), second->bit()}), first->value() * second->value());
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(0)->as_constant()->value() == 0)
            {
                int b = bit();
                _type = ExprType::CONSTANT;
                _constant = std::make_shared<Constant>(b, 0);
                _operands->clear();
            }
            else if(_operands->at(1)->type() == ExprType::CONSTANT && _operands->at(1)->as_constant()->value() == 0)
            {
                int b = bit();
                _type = ExprType::CONSTANT;
                _constant = std::make_shared<Constant>(b, 0);
                _operands->clear();
            }
            break;
        case ExprType::DIV:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(std::max({first->bit(), second->bit()}), first->value() / second->value());
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(0)->as_constant()->value() == 0)
            {
                int b = bit();
                _type = ExprType::CONSTANT;
                _constant = std::make_shared<Constant>(b, 0);
                _operands->clear();
            }
            break;
        case ExprType::MOD:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(std::max({first->bit(), second->bit()}), first->value() % second->value());
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(0)->as_constant()->value() == 0)
            {
                int b = bit();
                _type = ExprType::CONSTANT;
                _constant = std::make_shared<Constant>(b, 0);
                _operands->clear();
            }
            break;
        case ExprType::EQ:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(1, int(first->value() == second->value()));
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0) == _operands->at(1))
            {
                _type = ExprType::CONSTANT;
                _constant = std::make_shared<Constant>(1, 1);
                _operands->clear();
            }
            break;
        case ExprType::NE:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(1, int(first->value() != second->value()));
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0) == _operands->at(1))
            {
                _type = ExprType::CONSTANT;
                _constant = std::make_shared<Constant>(1, 0);
                _operands->clear();
            }
            break;
        case ExprType::GT:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(1, int(first->value() > second->value()));
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0) == _operands->at(1))
            {
                _type = ExprType::CONSTANT;
                _constant = std::make_shared<Constant>(1, 0);
                _operands->clear();
            }
        case ExprType::GE:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(1, int(first->value() >= second->value()));
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0) == _operands->at(1))
            {
                _type = ExprType::CONSTANT;
                _constant = std::make_shared<Constant>(1, 1);
                _operands->clear();
            }
        case ExprType::LT:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(1, int(first->value() < second->value()));
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0) == _operands->at(1))
            {
                _type = ExprType::CONSTANT;
                _constant = std::make_shared<Constant>(1, 0);
                _operands->clear();
            }
        case ExprType::LE:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(1, int(first->value() <= second->value()));
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0) == _operands->at(1))
            {
                _type = ExprType::CONSTANT;
                _constant = std::make_shared<Constant>(1, 1);
                _operands->clear();
            }
        case ExprType::AND:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(std::max({first->bit(), second->bit()}), first->value() & second->value());
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0)->type() == ExprType::CONSTANT)
            {
                auto constant = _operands->at(0)->as_constant();
                int bit = constant->bit();
                int value = constant->value();
                if(value == (1 << bit) - 1)
                {
                    *this = *(_operands->at(1));
                }
                else if(value == 0)
                {
                    _type = ExprType::CONSTANT;
                    _constant = std::make_shared<Constant>(bit, 0);
                    _operands->clear();
                }
            }
            else if(_operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto constant = _operands->at(1)->as_constant();
                int bit = constant->bit();
                int value = constant->value();
                if(value == (1 << bit) - 1)
                {
                    *this = *(_operands->at(0));
                }
                else if(value == 0)
                {
                    _type = ExprType::CONSTANT;
                    _constant = std::make_shared<Constant>(bit, 0);
                    _operands->clear();
                }
            }
            break;
        case ExprType::OR:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(std::max({first->bit(), second->bit()}), first->value() | second->value());
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            else if(_operands->at(0)->type() == ExprType::CONSTANT)
            {
                auto constant = _operands->at(0)->as_constant();
                int bit = constant->bit();
                int value = constant->value();
                if(value == 0)
                {
                    *this = *(_operands->at(1));
                }
                else if(value == (1 << bit) - 1)
                {
                    _type = ExprType::CONSTANT;
                    _constant = std::make_shared<Constant>(bit, (1 << bit) - 1);
                    _operands->clear();
                }
            }
            else if(_operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto constant = _operands->at(1)->as_constant();
                int bit = constant->bit();
                int value = constant->value();
                if(value == 0)
                {
                    *this = *(_operands->at(0));
                }
                else if(value == (1 << bit) - 1)
                {
                    _type = ExprType::CONSTANT;
                    _constant = std::make_shared<Constant>(bit, (1 << bit) - 1);
                    _operands->clear();
                }
            }
            break;
        case ExprType::NOT:
            if(_operands->at(0)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto constant = std::make_shared<Constant>(first->bit(), (first->value() ^ ((1 << bit()) - 1)));
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
        case ExprType::SHL:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(std::max({first->bit(), second->bit()}), first->value() << second->value());
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            break;
        case ExprType::LSHR:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(std::max({first->bit(), second->bit()}), unsigned(first->value()) >> second->value());
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            break;
        case ExprType::ASHR:
            if(_operands->at(0)->type() == ExprType::CONSTANT && _operands->at(1)->type() == ExprType::CONSTANT)
            {
                auto first = _operands->at(0)->as_constant();
                auto second = _operands->at(1)->as_constant();
                auto constant = std::make_shared<Constant>(std::max({first->bit(), second->bit()}), first->value() >> second->value());
                _type = ExprType::CONSTANT;
                _constant = constant;
                _operands->clear();
            }
            break;
    }

    std::shared_ptr<Expr> var_expr;
    std::shared_ptr<Expr> constant_expr;

    switch(_type)
    {
        case ExprType::ADD:
        case ExprType::SUB:
        case ExprType::MUL:
        case ExprType::DIV:
        case ExprType::MOD:
        case ExprType::AND:
        case ExprType::OR:
        case ExprType::XOR:
        case ExprType::EQ:
        case ExprType::NE:
        case ExprType::GT:
        case ExprType::GE:
        case ExprType::LT:
        case ExprType::LE:
            if(get_operand(0)->type() == ExprType::VAR && get_operand(1)->type() == ExprType::CONSTANT)
            {
                var_expr = get_operand(0);
                constant_expr = get_operand(1);
            }
            else if(get_operand(1)->type() == ExprType::VAR && get_operand(0)->type() == ExprType::CONSTANT)
            {
                var_expr = get_operand(1);
                constant_expr = get_operand(0);
            }
            break;
        case ExprType::COND:
            if(get_operand(1)->type() == ExprType::VAR && get_operand(2)->type() == ExprType::CONSTANT)
            {
                var_expr = get_operand(1);
                constant_expr = get_operand(2);
            }
            else if(get_operand(2)->type() == ExprType::VAR && get_operand(1)->type() == ExprType::CONSTANT)
            {
                var_expr = get_operand(2);
                constant_expr = get_operand(1);
            }
            break;
        default:
            break;
    }

    //make room for pattern matching
    if(var_expr && constant_expr && constant_expr->bit() != -1 && constant_expr->bit() != var_expr->bit())
    {
        auto old_constant = constant_expr->as_constant();
        auto new_constant = std::make_shared<Constant>(var_expr->bit(), old_constant->value());
        constant_expr->_constant = new_constant;
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

namespace afbd {
    std::string to_string(ExprType type) {
        switch (type) {
            case ExprType::VAR:
                return "var";
            case ExprType::CONSTANT:
                return "constant";

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
    switch(_type)
    {
    case ExprType::CONSTANT:
    {
        auto constant = as_constant();
        return std::make_shared<Expr>(std::make_shared<Constant>(constant->bit(), constant->value()));
    }
    case ExprType::VAR:
        return substitute_map[_var];
    default:
        std::vector<std::shared_ptr<Expr>> operands;
        for(auto operand : *_operands)
            operands.push_back(operand->substitute_clone(substitute_map));
        return std::make_shared<Expr>(_type, operands);
    }
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
    auto opl = get_operand(0);
    auto opr = get_operand(1);

    //std::cout << "binary_to_smv called opl is " << to_string(opl->type()) << " opr is " << to_string(opr->type()) << "\n";
    //std::cout << to_json().dump() << "\n";

    if(opr->type() == ExprType::CONSTANT)
    {
        while(opl->type() == ExprType::REDUCE_BOOL)
            opl = opl->get_operand(0);

        if(opl->type() >= ExprType::EQ && opr->type() <= ExprType::LE)
            return std::string("(") + opl->to_smv() + " " + delim + " " + opr->to_smv(true) + ")";
    }
    if(opl->type() == ExprType::CONSTANT)
    {
        while(opr->type() == ExprType::REDUCE_BOOL)
            opr = opr->get_operand(0);

        if(opr->type() >= ExprType::EQ && opr->type() <= ExprType::LE)
            return std::string("(") + opl->to_smv(true) + " " + delim + " " + opr->to_smv() + ")";
    }

    return std::string("(") + opl->to_smv() + " " + delim + " " + opr->to_smv() + ")";
}

std::string constant_to_smv(std::shared_ptr<Constant> constant)
{
    int bit = constant->bit();
    int value = constant->value();

    if(bit == -1)
        return std::to_string(value);

    std::stringstream smv_stream;
    smv_stream << "0b" << constant->bit() << "_";
    for(int i = bit - 1; i >= 0; i--)
        smv_stream << ((value >> i) & 1);
    return smv_stream.str();
}

std::string Expr::to_smv(bool as_bool)
{
    switch(type())
    {
        case ExprType::VAR:
            return *(as_var()->name());
        case ExprType::CONSTANT:
            if(as_bool)
                return as_constant()->value() != 0 ? "TRUE" : "FALSE";
            return constant_to_smv(as_constant());
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
            return std::string("!") + get_operand(0)->to_smv();
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
        case ExprType::REDUCE_BOOL:
            return get_operand(0)->to_smv();
        default:
            return std::string("(") + to_string(type()) + std::to_string(int(type())) + " is not supported)";
    }
}

bool Expr::operator==(const Expr& right) const
{
    if(_type != right._type)
        return false;

    if(_type == ExprType::CONSTANT)
        return _constant->bit() == right._constant->bit() && _constant->value() == right._constant->value();

    if(_type == ExprType::VAR)
        return _var->bit() == right._var->bit() && *(_var->name()) == *(right._var->name());

    if(_operands->size() != right._operands->size())
        return false;

    for(int i = 0; i < _operands->size(); i++)
        if(!(_operands->at(i) == right._operands->at(i)))
            return false;

    return true;
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

    std::shared_ptr<Constant> constant_nobit_zero = std::make_shared<Constant>(-1, 0);
    std::shared_ptr<Expr> expr_nobit_zero = std::make_shared<Expr>(constant_nobit_zero);

    std::shared_ptr<Constant> constant_nobit_one = std::make_shared<Constant>(-1, 1);
    std::shared_ptr<Expr> expr_nobit_one = std::make_shared<Expr>(constant_nobit_one);

    std::shared_ptr<Constant> constant_nobit_minus_one = std::make_shared<Constant>(-1, -1);
    std::shared_ptr<Expr> expr_nobit_minus_one = std::make_shared<Expr>(constant_nobit_minus_one);

    std::shared_ptr<Expr> double_fold(ExprType type, std::vector<std::shared_ptr<Expr>>& operands)
    {
        if(operands.size() == 1)
            return operands[0];
        if(operands.size() >= 2)
        {
            std::shared_ptr<Expr> curr = std::make_shared<Expr>(type, exl{operands[0], operands[1]});
            for(int i = 2; i < operands.size(); i++)
            {
                auto next = curr;
                curr = std::make_shared<Expr>(type, exl{next, operands[i]});
            }
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
