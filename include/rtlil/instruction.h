#pragma once

#include <rtlil/def.h>
#include <rtlil/var.h>
#include <rtlil/module.h>

#include <vector>
#include <memory>

enum InstructionType {
	ADD,
	SUB,
	AND,
	OR,
    XOR,
	NOT,
	NOOP,
	//and so on
};


class Instruction {
    std::shared_ptr<Var> _dst;
    std::shared_ptr<VarContainer> _src;

	InstructionType _type;
	std::shared_ptr<InstrEdgeContainer> _succs;

public:
    explicit Instruction(InstructionType type);

    std::shared_ptr<Var> dst() const;
    void dst(const std::shared_ptr<Var>& dst);

    std::shared_ptr<VarContainer> src() const;
    void add_src(const std::shared_ptr<Var>& src);

    std::shared_ptr<InstrEdgeContainer> succs();
    void add_succ(const std::shared_ptr<Instruction>& dst, int delay);
};

