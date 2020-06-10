#pragma once

#include <afbdil/def.h>
#include <afbdil/instruction.h>
#include <afbdil/var.h>
#include <afbdil/module.h>

#include <memory>
#include <set>

namespace afbd {

enum ProcessType {
    Initial,
    Always,
};

//std::string proc_type_to_str(ProcessType type);

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

    std::vector<std::shared_ptr<Instruction>> all_instructions();

    void to_smv(std::vector<std::shared_ptr<Expr>>& expressions, std::map<std::shared_ptr<Var>, int>& vars_next, std::map<std::shared_ptr<Var>, int>& vars_init, std::set<std::shared_ptr<Var>>& edge_vars, std::vector<std::pair<int, std::shared_ptr<Expr>>>& countdowns, std::vector<std::shared_ptr<Var>>& vars, int& temp_var_num, std::set<std::string>& conditions);
};

}
