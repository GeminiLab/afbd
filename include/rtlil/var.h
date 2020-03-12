#pragma once

#include <rtlil/def.h>
#include <rtlil/module.h>

#include <memory>

// now bit vector only
class Var {
	int _bit;
	std::shared_ptr<std::string> _name;
	std::shared_ptr<ProcContainer> _sens_procs;

public:
	Var(int bit, std::string name);

	int bit() const;
    std::shared_ptr<std::string> name() const;

	std::shared_ptr<ProcContainer> sens_procs() const;
	void add_sens_proc(const std::shared_ptr<Process>& proc);
};

