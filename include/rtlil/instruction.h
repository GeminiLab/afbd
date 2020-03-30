#pragma once

#include <rtlil/def.h>
#include <rtlil/var.h>
#include <rtlil/module.h>
#include <rtlil/expr.h>

#include <vector>
#include <memory>

namespace afbd {

class Instruction {
    std::shared_ptr<Var> _dst;
    std::shared_ptr<Expr> _expr;

    std::shared_ptr<InstrEdgeContainer> _succs;

    bool _pseudo_begin;
    bool _pseudo_end;

public:
    explicit Instruction();

    [[nodiscard]]
    std::shared_ptr<Var> dst() const;

    void dst(const std::shared_ptr<Var> &dst);

    [[nodiscard]]
    std::shared_ptr<Expr> expr() const;

    void expr(const std::shared_ptr<Expr> &expr);

    std::shared_ptr<InstrEdgeContainer> succs();

    void add_succ(const std::shared_ptr<Instruction> &dst, const std::shared_ptr<Expr> &cond);

    [[nodiscard]]
    bool pseudo_begin() const;

    void pseudo_begin(bool value);

    [[nodiscard]]
    bool pseudo_end() const;

    void pseudo_end(bool value);
};

}
