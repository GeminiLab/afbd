#pragma once

#include <rtlil/def.h>
#include <rtlil/instruction.h>
#include <rtlil/var.h>
#include <rtlil/module.h>

#include <memory>
#include <set>

namespace afbd {

enum ProcessType {
    Blocking,
    Nonblocking,
    Continuous,
};

#define MAX_INST_NUM 10000

class Process {
    std::shared_ptr<Instruction> _begin;
    std::shared_ptr<Instruction> _end;
    ProcessType _type;
    std::set<Sen> _sensitive_vars;
public:
    Process();

    int inst_num;

    [[nodiscard]]
    ProcessType type() const;

    void type(ProcessType type);

    [[nodiscard]]
    std::shared_ptr<Instruction> begin() const;
    [[nodiscard]]
    std::shared_ptr<Instruction> end() const;

    std::shared_ptr<Process> substitute_clone(std::map<std::shared_ptr<Var>, std::shared_ptr<Expr>>& substitute_map);

	void add_sensitive_var(Sen sensitive_var);

	json11::Json to_json();
};

}
