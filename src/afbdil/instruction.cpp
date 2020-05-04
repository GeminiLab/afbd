#include <afbdil/instruction.h>

using namespace std;
using namespace afbd;

std::string instruction_type_to_str(InstructionType type)
{
	switch(type)
	{
	case InstructionType::Assign:
		return "assign";
	case InstructionType::Delay:
		return "delay";
	case InstructionType::Trigger:
		return "trigger";
	}
}

InstructionType str_to_instruction_type(std::string str)
{
	if(str == "assign")
		return InstructionType::Assign;
	else if(str == "delay")
		return InstructionType::Delay;
	else if(str == "trigger")
		return InstructionType::Trigger;
}

Instruction::Instruction(std::shared_ptr<Process> proc) {
	_succs = make_shared<InstrEdgeContainer>();

	_proc = &(*proc);
	_id = proc->inst_num;
	proc->inst_num++;

	_type = InstructionType::Assign;
	_delay = -1;
	_triggers = nullptr;
}

Instruction::Instruction(Process* proc)
{
	_succs = make_shared<InstrEdgeContainer>();

	_proc = proc;
	_id = proc->inst_num;
	proc->inst_num++;

	_type = InstructionType::Assign;
	_delay = -1;
	_triggers = nullptr;
}

std::shared_ptr<Expr> Instruction::dst() const {
    return _dst;
}

void Instruction::dst(const shared_ptr<Expr> &dst) {
    _type = InstructionType::Assign;
    _dst = dst;
}

shared_ptr<Expr> Instruction::expr() const {
    return _expr;
}

void Instruction::expr(const shared_ptr<Expr> &expr) {
    _type = InstructionType::Assign;
    _expr = expr;
}

AssignType Instruction::assign_type() const {
	return _assign_type;
}

void Instruction::assign_type(AssignType assign_type) {
	_type = InstructionType::Assign;
	_assign_type = assign_type;
}

int Instruction::delay() const {
    return _delay;
}

void Instruction::delay(int value) {
    _type = InstructionType::Delay;
    _delay = value;
}

void Instruction::assign_delay(int value) {
    _type = InstructionType::Assign;
    _delay = value;
}

shared_ptr<TriggerContainer> Instruction::triggers() const {
    return _triggers;
}

void Instruction::triggers(std::shared_ptr<TriggerContainer> &triggers) {
    _type = InstructionType::Trigger;
    _triggers = triggers;
}

shared_ptr<InstrEdgeContainer> Instruction::succs() {
    return _succs;
}

void Instruction::add_succ(const shared_ptr<Instruction> &dst, const shared_ptr<Expr> &cond) {
    _succs->push_back(make_pair(dst, cond));
}

Process* Instruction::process() const {
    return _proc;
}

int Instruction::id() const {
    return _id;
}

InstructionType Instruction::type() const {
    return _type;
}

json11::Json Instruction::to_json() {
    std::map<std::string, json11::Json> ret_map;

    if (_type == InstructionType::Assign)
        ret_map["type"] = "assign";
    else if (_type == InstructionType::Delay)
        ret_map["type"] = "delay";
    else if (_type == InstructionType::Trigger)
        ret_map["type"] = "trigger";

    std::vector<json11::Json> succs_vec;
    for(auto& edge : *_succs)
    {
        auto succ_id = edge.first->id();
        auto cond = edge.second;
        if(cond->is_true())
            succs_vec.push_back(json11::Json::object{{"instr", succ_id}});
        else
            succs_vec.push_back(json11::Json::object{{"instr", succ_id}, {"cond", cond->to_json()}});
    }
    ret_map["succs"] = succs_vec;

    if(_dst)
        ret_map["dest"] = _dst->to_json();

    if(_expr)
        ret_map["expr"] = _expr->to_json();

	if(_delay != 0)
		ret_map["delay"] = _delay;

	if(_triggers)
	{
		std::vector<json11::Json> triggers_vec;
		for(auto& trigger : *_triggers)
			triggers_vec.push_back(json11::Json::object{{"var", *(trigger.first->name())}, {"edge", int(trigger.second)}});
		ret_map["triggers"] = triggers_vec;
	}

    return ret_map;
}