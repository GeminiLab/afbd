#pragma once

#include <rtlil/def.h>
#include <rtlil/var.h>
#include <rtlil/process.h>

#include <memory>
#include <vector>

namespace afbd {

class Module {
private:
    std::string _name;

    std::shared_ptr<VarContainer> _vars;
    std::shared_ptr<ProcContainer> _procs;

public:
    Module(std::string name);

    std::shared_ptr<VarContainer> vars() const;

    std::shared_ptr<ProcContainer> procs() const;

    std::shared_ptr<Var> add_var(int bit, std::string name, int elem_bit = -1);

    std::shared_ptr<Process> add_proc();

    void add_triggered_proc(std::shared_ptr <Var> var, std::shared_ptr <Process> proc);

    std::string name() const;

    std::vector<std::pair<std::string, std::shared_ptr<std::vector<std::shared_ptr<Expr>>>>> cells;

    std::shared_ptr<Module> substitute_clone(std::map<std::shared_ptr<Var>, std::shared_ptr<Expr>>& substitute_map, int occurence);

	void modules_in_one(std::vector<std::shared_ptr<Module>>& modules);

    json11::Json to_json();

};

}
