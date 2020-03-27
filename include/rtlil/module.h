#pragma once

#include <rtlil/def.h>
#include <rtlil/var.h>
#include <rtlil/process.h>

#include <memory>
#include <vector>

namespace afbd {

class Module {
private:
    std::shared_ptr <VarContainer> _vars;
    std::shared_ptr <ProcContainer> _procs;

public:
    Module();

    std::shared_ptr <VarContainer> vars() const;

    std::shared_ptr <ProcContainer> procs() const;

    std::shared_ptr <Var> add_var(int bit, std::string name);

    std::shared_ptr <Process> add_proc();

    void add_triggered_proc(std::shared_ptr <Var> var, std::shared_ptr <Process> proc);
};

}
