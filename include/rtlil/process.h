#pragma once

#include <rtlil/def.h>
#include <rtlil/instruction.h>
#include <rtlil/var.h>
#include <rtlil/module.h>

#include <memory>

namespace afbd {

enum ProcessType {
    Blocking,
    Nonblocking,
    Continuous,
};

class Process {
    std::shared_ptr<Instruction> _begin;
    std::shared_ptr<Instruction> _end;
    ProcessType _type;

public:
    Process();

    [[nodiscard]]
    ProcessType type() const;

    void type(ProcessType type);

    [[nodiscard]]
    std::shared_ptr<Instruction> begin() const;
    [[nodiscard]]
    std::shared_ptr<Instruction> end() const;
};

}
