#pragma once

#include <rtlil/def.h>
#include <rtlil/instruction.h>
#include <rtlil/var.h>
#include <rtlil/module.h>

#include <memory>
#include <set>

namespace afbd {

enum ProcessType {
    Initial,
    Always,
};

std::string proc_type_to_str(ProcessType type);

ProcessType str_to_proc_type(std::string str);

#define MAX_INST_NUM 10000

class Process {
    std::shared_ptr<Instruction> _begin;
    ProcessType _type;
public:
    Process();

    int inst_num;

    [[nodiscard]]
    ProcessType type() const;

    void type(ProcessType type);

    [[nodiscard]]
    std::shared_ptr<Instruction> begin() const;
    void begin(const std::shared_ptr<Instruction> &begin);

    std::shared_ptr<Process> substitute_clone(std::map<std::shared_ptr<Var>, std::shared_ptr<Expr>>& substitute_map);

	json11::Json to_json();
};

}
