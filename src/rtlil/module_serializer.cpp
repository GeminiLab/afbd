#include <rtlil/module_serializer.h>

#include <json/json.hpp>

#include <map>
#include <vector>

using namespace std;
using namespace afbd;
using json = nlohmann::json;

const char* proc_type_to_str(ProcessType pt) {
    if (pt == ProcessType::Continuous) return "continuous";
    else if (pt == ProcessType::Blocking) return "blocking";
    else if (pt == ProcessType::Nonblocking) return "nonblocking";
    return "continuous";
}

char __itoa[20];
const char* itoa(int i) {
    sprintf(__itoa, "%d", i);
    return __itoa;
}

void number_instrs(shared_ptr<Instruction> u, map<shared_ptr<Instruction>, int> &m) {
    if (m.find(u) != m.end()) {
        return;
    }

    m[u] = m.size();

    for (auto& e: *u->succs()) {
        number_instrs(e.first, m);
    }
}

const char* op_to_str(ExprType et) {
    if (et == ExprType::ADD) return "add";
    else if (et == ExprType::SUB) return "sub";
    else if (et == ExprType::AND) return "and";
    else if (et == ExprType::OR) return "or";
    else if (et == ExprType::XOR) return "xor";
    else if (et == ExprType::NOT) return "not";
    return "add";
}

json expr_to_json(shared_ptr<Expr> expr) {
    json e;

    if (expr->type() == ExprType::CONSTANT) {
        e["op"] = "const";
        e["width"] = expr->as_constant()->bit();
        e["value"] = expr->as_constant()->value();
    } else if (expr->type() == ExprType::VAR) {
        e["op"] = "var";
        e["var"] = expr->as_var()->name()->c_str();
    } else {
        e["op"] = op_to_str(expr->type());

        json operands = json::array();
        int opn = expr->operand_num();
        for (int i = 0; i < opn; ++i) {
            auto o = expr->get_operand(i);

            operands.push_back(expr_to_json(o));
        }

        e["operands"] = operands;
    }

    return e;
}

void ModuleSerializer::serialize(shared_ptr<ostream> dest, shared_ptr<Module> module) {
    map<shared_ptr<Process>, vector<shared_ptr<Var>>> sens;

    json j = json::object();
    j["name"] = "module";


    json vars = json::array();
    for (auto& v: *module->vars()) {
        json var = json::object();
        var["name"] = v->name()->c_str();
        var["width"] = v->bit();

        vars.push_back(var);

        for (auto& p: *v->sens_procs()) {
            if (sens.find(p) == sens.end()) {
                sens[p] = vector<shared_ptr<Var>>();
            }

            sens[p].push_back(v);
        }
    }

    j["vars"] = vars;


    json procs = json::array();
    for (auto& p: *module->procs()) {
        json proc;
        proc["type"] = proc_type_to_str(p->type());

        json s = json::array();
        for (auto& ss: sens[p]) {
            s.push_back(ss->name()->c_str());
        }

        proc["sen"] = s;

        map<shared_ptr<Instruction>, int> iid;
        number_instrs(p->begin(), iid);

        json instrs = json::object();
        for (auto& inn: iid) {
            json in;
            auto i = inn.first;
            auto num = inn.second;

            in["type"] =
                    i->pseudo_begin() ? "pseudo_begin"
                    : i->pseudo_end() ? "pseudo_end"
                    : "normal";

            json succs = json::array();
            for (auto& e: *i->succs()) {
                json edge = json::object();

                if (e.second == nullptr) {
                    edge["cond"] = json();
                } else {
                    edge["cond"] = expr_to_json(e.second);
                }

                edge["instr"] = itoa(iid[e.first]);

                succs.push_back(edge);
            }
            in["succs"] = succs;

            if (!i->pseudo_begin() && !i->pseudo_end()) {
                in["dest"] = i->dst()->name()->c_str();
                in["expr"] = expr_to_json(i->expr());
            }

            instrs[itoa(num)]  = in;
        }
        proc["instrs"] = instrs;

        procs.push_back(proc);
    }

    j["procs"] = procs;


    *dest << j;
}

void ModuleSerializer::deserialize(shared_ptr<istream> source, shared_ptr<Module> module) {
    json j;
    *source >> j;
}
