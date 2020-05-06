#pragma once

#include <afbdil/def.h>
#include <afbdil/module.h>

#include <memory>

namespace afbd {

// now bit vector only
class Var {
    int _bit;
    int _elem_bit;
    std::shared_ptr <std::string> _name;
    std::shared_ptr <ProcContainer> _sens_procs;

public:
    Var(int bit, std::string name, int elem_bit = -1);

    int bit() const;

    int elem_bit() const;

    std::shared_ptr <std::string> name() const;

    std::shared_ptr <ProcContainer> sens_procs() const;

    void add_sens_proc(const std::shared_ptr <Process> &proc);

	json11::Json to_json();
};

}
