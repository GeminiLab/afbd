#pragma once

#include <afbdil/def.h>

#include <memory>

namespace afbd {

enum class ExprType {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    EQ,
    NE,
    GT,
    GE,
    LT,
    LE,

    SUBVEC,
    CONCAT,
    REDUCE_BOOL,

    AND,
    OR,
    XOR,
    NOT,

//and so on
    CONSTANT,
    VAR,

    DEFAULT,
    UNKNOWN,
};

class Expr {
    ExprType _type;
    std::shared_ptr<std::vector<std::shared_ptr<Expr>>> _operands;
    std::shared_ptr<Var> _var;
    std::shared_ptr<Constant> _constant;

public:
    Expr(std::shared_ptr<Var> var);
    Expr(std::shared_ptr<Constant> constant);
    Expr(ExprType type, std::initializer_list<std::shared_ptr<Expr>> operands);
    Expr(ExprType type, std::vector<std::shared_ptr<Expr>> operands);

    ExprType type() const;
    std::shared_ptr<Var> as_var() const;
    std::shared_ptr<Constant> as_constant() const;
    int operand_num() const;
    std::shared_ptr<Expr> get_operand(int i) const;
    inline void add_operand(std::shared_ptr<Expr> operand) { _operands->push_back(operand); }

    bool is_true() const;

	std::shared_ptr<Expr> substitute_clone(std::map<std::shared_ptr<Var>, std::shared_ptr<Expr>>& substitute_map);

    void simplify();

    int bit() const;

    json11::Json to_json();

    void all_as_sens(std::shared_ptr<Module>& module, std::shared_ptr<Process>& proc);
};

class Constant {
    int _bit;
    int _value;
public:
    Constant(int bit, int value);

    int bit() const;
    inline void bit(int v) { _bit = v; }
    int value() const;
};

typedef std::initializer_list<std::shared_ptr<Expr>> exl;
}
