#pragma once

#include <rtlil/def.h>
#include <rtlil/module.h>

#include <memory>

// now bit vector only
class Var {
	int _bit;

	std::shared_ptr<ProcContainer> _sens_procs;

public:
	explicit Var(int bit);

	int bit() const;

	std::shared_ptr<ProcContainer> sens_procs() const;
	void add_sens_proc(const std::shared_ptr<Process>& proc);
};

