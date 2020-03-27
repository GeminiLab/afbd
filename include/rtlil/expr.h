#include <rtlil/def.h>

#include <memory>

namespace afbd {

enum class ExprType {
    ADD,
    SUB,
    AND,
    OR,
    XOR,
    NOT,
//and so on
    CONSTANT,
    VAR,
};

class Expr {
    ExprType _type;
    std::shared_ptr<std::vector<std::shared_ptr<Expr>>> _operands;
    std::shared_ptr<Var> _var;
    std::shared_ptr<Constant> _constant;

public:
    Expr(std::shared_ptr<Var> var);
    Expr(std::shared_ptr<Constant> constant);
    Expr(ExprType type);

    ExprType type() const;
    std::shared_ptr<Var> as_var() const;
    std::shared_ptr<Constant> as_constant() const;
    int operand_num() const;
    std::shared_ptr<Expr> get_operand(int i) const;
    void add_operand(std::shared_ptr<Expr> operand);
};

class Constant {
    int _bit;
    int _value;
public:
    Constant(int bit, int value);

    int bit() const;
    int value() const;
};

}
