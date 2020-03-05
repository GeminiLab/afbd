#pragma once

#include <rtlil/def.h>
#include <rtlil/instruction.h>
#include <rtlil/var.h>
#include <rtlil/module.h>

#include <memory>

enum ProcessType {
	Blocking,
	Nonblocking,
	Continuous,
};

class Process {
    std::shared_ptr<Instruction> _begin;
	ProcessType _type;

public:
    Process();

	ProcessType type() const;
	void type(ProcessType type);

	std::shared_ptr<Instruction> begin() const;
};

