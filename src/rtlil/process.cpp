#include <rtlil/process.h>

using namespace std;
using namespace afbd;

Process::Process() {
    _type = Continuous;
    auto this_shared = shared_ptr<Process>(this);
	_begin = make_shared<Instruction>(this_shared);
	_end = make_shared<Instruction>(this_shared);

	_begin->pseudo_begin(true);
	_end->pseudo_end(true);
}

ProcessType Process::type() const {
    return _type;
}

void Process::type(ProcessType type) {
    _type = type;
}

shared_ptr<Instruction> Process::begin() const {
    return _begin;
}

shared_ptr<Instruction> Process::end() const {
    return _end;
}
