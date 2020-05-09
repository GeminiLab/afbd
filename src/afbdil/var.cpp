#include <afbdil/var.h>

#include <utility>

using namespace std;
using namespace afbd;

extern std::string no_slash(std::string& str);

Var::Var(int bit, string name, int elem_bit): _name(make_shared<string>(move(no_slash(name)))) {
    _bit = bit;
	if(elem_bit == -1)
		_elem_bit = bit;
	else
		_elem_bit = elem_bit;
}

int Var::bit() const {
    return _bit;
}

int Var::elem_bit() const {
    return _elem_bit;
}

shared_ptr<string> Var::name() const {
    return _name;
}

void Var::add_sens_proc(const std::shared_ptr<Process>& proc) {
    _sens_procs->push_back(proc);
}

json11::Json Var::to_json()
{
	return json11::Json::object{{"name", *_name}, {"width", _bit}};
}