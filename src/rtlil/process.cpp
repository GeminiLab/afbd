#include <rtlil/process.h>

using namespace std;
using namespace afbd;

Process::Process() {
    _type = Continuous;
	_begin = make_shared<Instruction>(InstructionType::NOOP);
}

ProcessType Process::type() const {
    return _type;
}

void Process::type(ProcessType type) {
    _type = type;
}

std::shared_ptr<Instruction> Process::begin() const {
    return _begin;
}


