#pragma once

#include <rtlil/def.h>
#include <rtlil/var.h>
#include <rtlil/module.h>
#include <rtlil/expr.h>

#include <vector>
#include <memory>

namespace afbd {

enum class InstructionType {
    Assign,
    Delay,
    Trigger,
};

class Instruction {
    std::shared_ptr<Process> _proc;

    std::shared_ptr<Expr> _dst;
    std::shared_ptr<Expr> _expr;

    std::shared_ptr<InstrEdgeContainer> _succs;

    int _id;

    InstructionType _type;
    int _delay;
    std::shared_ptr<TriggerContainer> _triggers;

public:
	explicit Instruction(std::shared_ptr<Process> proc);

    [[nodiscard]]
    std::shared_ptr<Expr> dst() const;
    void dst(const std::shared_ptr<Expr> &dst);

    [[nodiscard]]
    std::shared_ptr<Expr> expr() const;
    void expr(const std::shared_ptr<Expr> &expr);

    [[nodiscard]]
    int delay() const;
    void delay(int value);

    [[nodiscard]]
    std::shared_ptr<TriggerContainer> triggers() const;
    void triggers(const TriggerContainer &triggers);

    std::shared_ptr<InstrEdgeContainer> succs();

    void add_succ(const std::shared_ptr<Instruction> &dst, const std::shared_ptr<Expr> &cond);

    [[nodiscard]]
    std::shared_ptr<Process> process() const;

    [[nodiscard]]
    int id() const;

    [[nodiscard]]
    InstructionType type() const;

    json11::Json to_json();
};

}
