#pragma once

#include "module.h"

#include <memory>
#include <iostream>

namespace afbd {

class ModuleSerializer {
public:
    static void serialize(std::shared_ptr<std::ostream> dest, std::shared_ptr<Module> module);
    static void deserialize(std::shared_ptr<std::istream> source, std::shared_ptr<Module> module);
};

}
