#pragma once

#include <afbdil/def.h>
#include <afbdil/var.h>
#include <afbdil/module.h>
#include <afbdil/expr.h>

#include <vector>
#include <memory>

namespace afbd {

enum class InstructionType {
    Assign,
    Delay,
    Trigger,
};

enum class AssignType {
	Blocking,
	NonBlocking
};

std::string instruction_type_to_str(InstructionType type);
InstructionType str_to_instruction_type(std::string str);

class Instruction {
    Process* _proc;

    std::shared_ptr<Expr> _dst;
    std::shared_ptr<Expr> _expr;

    std::shared_ptr<InstrEdgeContainer> _succs;

    int _id;

    InstructionType _type;

	//For assign
	AssignType _assign_type;

	//For delay
    int _delay;

	//For trigger
    std::shared_ptr<TriggerContainer> _triggers;

public:
	explicit Instruction(std::shared_ptr<Process> proc);
	explicit Instruction(Process* proc);

    [[nodiscard]]
    std::shared_ptr<Expr> dst() const;
    void dst(const std::shared_ptr<Expr> &dst);

    [[nodiscard]]
    std::shared_ptr<Expr> expr() const;
    void expr(const std::shared_ptr<Expr> &expr);

	[[nodiscard]]
	AssignType assign_type() const;
	void assign_type(AssignType assign_type);

    [[nodiscard]]
    int delay() const;
    void delay(int value);

    void assign_delay(int value);

    [[nodiscard]]
    std::shared_ptr<TriggerContainer> triggers() const;
    void triggers(std::shared_ptr<TriggerContainer> &triggers);

    std::shared_ptr<InstrEdgeContainer> succs();

    void add_succ(const std::shared_ptr<Instruction> &dst, const std::shared_ptr<Expr> &cond);

    [[nodiscard]]
    Process* process() const;

    [[nodiscard]]
    int id() const;

    [[nodiscard]]
    InstructionType type() const;

    json11::Json to_json();
};

}
