/*
#include <rtlil/module_serializer.h>

#include <json/json.hpp>

#include <map>
#include <vector>

using namespace std;
using namespace afbd;
using json = nlohmann::json;

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

ExprType str_to_op(string s) {
    if (s == "add") return ExprType::ADD;
    if (s == "sub") return ExprType::SUB;
    if (s == "and") return ExprType::AND;
    if (s == "or") return ExprType::OR;
    if (s == "xor") return ExprType::XOR;
    if (s == "not") return ExprType::NOT;
    return ExprType::ADD;
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

shared_ptr<Expr> json_to_expr(json j, map<string, shared_ptr<Var>> &vars) {
    string op = j["op"];

    if (op == "var") {
        return make_shared<Expr>(vars[j["var"]]);
    } else if (op == "const") {
        return make_shared<Expr>(make_shared<Constant>((int)j["width"], (int)j["value"]));
    } else {
        auto o = str_to_op(op);
        vector<shared_ptr<Expr>> e;

        for (auto& v: j["operands"]) {
           e.push_back(json_to_expr(v, vars));
        }

        return make_shared<Expr>(o, e);
    }
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

			in["type"] = instruction_type_to_str(i->type());

            json succs = json::array();
            for (auto& e: *i->succs()) {
                json edge = json::object();

                if (e.second == nullptr) {
                    edge["cond"] = nullptr;
                } else {
                    edge["cond"] = expr_to_json(e.second);
                }

                edge["instr"] = itoa(iid[e.first]);

                succs.push_back(edge);
            }
            in["succs"] = succs;

            if(i->dst())
				in["dest"] = expr_to_json(i->dst());
			if(i->expr())
                in["expr"] = expr_to_json(i->expr());
            
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

    map<string, shared_ptr<Var>> vars;

    auto vs = j["vars"];
    for (auto& v: vs) {
        std::string name = v["name"];
        int width = v["width"];

        vars[name] = module->add_var(width, name);
    }

    auto ps = j["procs"];
    for (auto& p: ps) {
        map<string, shared_ptr<Instruction>> instrs;

        auto proc = module->add_proc();
        proc->type(str_to_proc_type(p["type"]));

        auto sen = p["sen"];
        for (auto& s: sen) {
            module->add_triggered_proc(vars[s], proc);
        }

        auto is = p["instrs"];
        for (auto iter = is.begin(); iter != is.end(); ++iter) {
            auto name = iter.key();
            instrs[name] = make_shared<Instruction>(&(*proc));
        }

        for (auto iter = is.begin(); iter != is.end(); ++iter) {
            auto name = iter.key();
            auto i = iter.value();

            auto instr = instrs[name];

            if (i["type"] != "pseudo_begin" && i["type"] != "pseudo_end") {
                instr->dst(json_to_expr(i["dest"], vars));
                instr->expr(json_to_expr(i["expr"], vars));
            }

            for (auto s: i["succs"]) {
                auto d = instrs[s["instr"]];
                if (s["cond"].is_null()) {
                    instr->add_succ(d, nullptr);
                    break;
                } else {
                    instr->add_succ(d, json_to_expr(s["cond"], vars));
                }
            }
        }
    }
}
*/