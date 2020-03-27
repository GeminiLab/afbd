#include <transpiler/transpiler.h>

using namespace std;
using namespace afbd;

void print_common_header(fstream &fs) {
    fs << "struct delay_gate {" << endl;
    fs << "  int o;" << endl;
    fs << "  int n;" << endl;
    fs << "  int k;" << endl;
    fs << "};" << endl;
}

llvm::Module *Transpiler::transpile(shared_ptr<Module> module, shared_ptr<fstream> fs) {
    print_common_header(*fs);

    auto var_idx = make_shared<map<shared_ptr<Var>, int>>();
    auto old_var_idx = make_shared<map<shared_ptr<Var>, int>>();
    auto delay_gate_idx = make_shared<map<pair<shared_ptr<Instruction>, shared_ptr<Var>>, int>>();


    map<shared_ptr<Process>, llvm::Value*> triggered;

    return nullptr;
}
