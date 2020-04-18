#include <rtlil/instruction.h>

using namespace std;
using namespace afbd;

Instruction::Instruction(Process* proc) {
    _succs = make_shared<InstrEdgeContainer>();
    _pseudo_begin = false;
    _pseudo_end = false;

    _proc = proc;
    _id = proc->inst_num;
	proc->inst_num++;
}

Instruction::Instruction(std::shared_ptr<Process> proc) {
	_succs = make_shared<InstrEdgeContainer>();
	_pseudo_begin = false;
	_pseudo_end = false;

	_proc = &(*proc);
	_id = proc->inst_num;
	proc->inst_num++;
}

std::shared_ptr<Expr> Instruction::dst() const {
    return _dst;
}

void Instruction::dst(const shared_ptr<Expr> &dst) {
    _dst = dst;
}

shared_ptr<Expr> Instruction::expr() const {
    return _expr;
}

void Instruction::expr(const shared_ptr<Expr> &expr) {
    _expr = expr;
}

shared_ptr<InstrEdgeContainer> Instruction::succs() {
    return _succs;
}

void Instruction::add_succ(const shared_ptr<Instruction> &dst, const shared_ptr<Expr> &cond) {
    _succs->push_back(make_pair(dst, cond));
}

bool Instruction::pseudo_begin() const {
    return _pseudo_begin;
}

void Instruction::pseudo_begin(bool value) {
    _pseudo_begin = value;
}

bool Instruction::pseudo_end() const {
    return _pseudo_end;
}

void Instruction::pseudo_end(bool value) {
    _pseudo_end = value;
}

Process* Instruction::process() const {
    return _proc;
}

int Instruction::id() const {
    return _id;
}

json11::Json Instruction::to_json()
{
    std::map<std::string, json11::Json> ret_map;

    if(pseudo_begin())
        ret_map["type"] = "pseudo_begin";
    else if(pseudo_end())
        ret_map["type"] = "pseudo_end";
    else
        ret_map["type"] = "normal";

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

    return ret_map;
}