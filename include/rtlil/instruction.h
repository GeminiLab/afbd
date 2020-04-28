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

enum class AssignType {
	Blocking,
	Non_Blocking
};

std::string instruction_type_to_str(InstructionType type)
{
	switch(type)
	{
	case InstructionType::Assign:
		return "assign";
	case InstructionType::Delay:
		return "delay";
	case InstructionType::Trigger:
		return "trigger";
	}
}

InstructionType str_to_instruction_type(std::string str)
{
	if(str == "assign")
		return InstructionType::Assign;
	else if(str == "delay")
		return InstructionType::Delay;
	else if(str == "trigger")
		return InstructionType::Trigger;
}

class Instruction {
    std::shared_ptr<Process> _proc;

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

    [[nodiscard]]
    std::shared_ptr<Expr> dst() const;
    void dst(const std::shared_ptr<Expr> &dst);

    [[nodiscard]]
    std::shared_ptr<Expr> expr() const;
    void expr(const std::shared_ptr<Expr> &expr);

	[[nodiscard]]
	AssignType assign_type() const;
	void assign_type(const AssignType assign_type);

    [[nodiscard]]
    int delay() const;
    void delay(int value);

    [[nodiscard]]
    std::shared_ptr<TriggerContainer> triggers() const;
    void triggers(std::shared_ptr<TriggerContainer> &triggers);

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
