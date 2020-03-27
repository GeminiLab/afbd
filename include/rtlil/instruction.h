#pragma once

#include <rtlil/def.h>
#include <rtlil/var.h>
#include <rtlil/module.h>
#include <rtlil/expr.h>

#include <vector>
#include <memory>

namespace afbd {

enum class InstructionType {
    ADD,
    SUB,
    AND,
    OR,
    XOR,
    NOT,
    ASSIGN,
    NOOP,
    //and so on
};


class Instruction {
    std::shared_ptr<Var> _dst;
    std::shared_ptr<Expr> _expr;

    std::shared_ptr<InstrEdgeContainer> _succs;

public:
    explicit Instruction();

    std::shared_ptr<Var> dst() const;

    void dst(const std::shared_ptr<Var> &dst);

    std::shared_ptr<Expr> expr() const;

    void expr(const std::shared_ptr<Expr> &expr);

    std::shared_ptr<InstrEdgeContainer> succs();

    void add_succ(const std::shared_ptr<Instruction> &dst, int delay);
};

}
