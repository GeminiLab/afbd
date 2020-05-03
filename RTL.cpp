#include <rtlil/rtlil>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/TypeBuilder.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#include <transpiler/transpiler.h>
#include <rtlil/module_serializer.h>
#include <yosys/include/verilog_frontend.h>
#include <transpiler/rtlilpass.h>

#include <iostream>
#include <fstream>
#include <memory>
using namespace std;
using namespace afbd;

USING_YOSYS_NAMESPACE

typedef initializer_list<shared_ptr<Expr>> exl;
#define lexpr(...) initializer_list<shared_ptr<Expr>> { __VA_ARGS__ }
#define nexpr(...) make_shared<Expr>(__VA_ARGS__)
#define nconst(...) make_shared<Constant>(__VA_ARGS__)

int main(int argc, char** argv) {
    /*
    auto m = make_shared<Module>();
    auto a = m->add_var(1, "a");
    auto b = m->add_var(1, "b");
    auto t = m->add_var(1, "t");

    auto c = m->add_var(1, "c");
    auto d = m->add_var(1, "d");


    auto p = m->add_proc();
    p->type(ProcessType::Continuous);

    auto instrXor = make_shared<Instruction>();
    instrXor->dst(c);
    instrXor->expr(nexpr(ExprType::XOR, lexpr(nexpr(a), nexpr(ExprType::XOR, lexpr(nexpr(t), nexpr(b))))));

    p->begin()->add_succ(instrXor, nullptr);
    instrXor->add_succ(p->end(), nullptr);


    auto p2 = m->add_proc();
    p2->type(ProcessType::Nonblocking);

    auto instrx = make_shared<Instruction>();
    instrx->dst(d);
    instrx->expr(nexpr(ExprType::XOR, lexpr(nexpr(a), nexpr(b))));

    auto instry = make_shared<Instruction>();
    instry->dst(d);
    instry->expr(nexpr(nconst(1, 0)));

    p2->begin()->add_succ(instrx, nexpr(t));
    p2->begin()->add_succ(instry, nullptr);
    instrx->add_succ(p2->end(), nullptr);
    instry->add_succ(p2->end(), nullptr);

    m->add_triggered_proc(t, p2);
    // m->add_triggered_proc(b, p2);
    //

    auto v = make_shared<ofstream>("con");
    ModuleSerializer::serialize(v, m);
    v->close();
*/
    // args hack
    const char *fin = "/home/gemini/source/repos/rtlil/example/example.v";
    const char *mon = "counter";

    argc = 3;
    char* new_argv[3] = { argv[0], const_cast<char*>(fin), const_cast<char*>(mon) };
    argv = new_argv;

    // begin
    if(argc < 2)
    {
        std::cout << "no filename\n";
        return 0;
    }

    std::vector<std::string> args;
    for(int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    std::istream* f = nullptr;

    RTLIL::Design* design = new RTLIL::Design;

    VerilogFrontend frontend;
    frontend.execute(f, args[1], args, design);

    afbd::RTLILPass p;
    p.execute(args, design);
    auto m2 = p.res;

    /*
    auto v2 = make_shared<ifstream>("../example/example.json");
    auto m2 = make_shared<Module>();
    ModuleSerializer::deserialize(v2, m2);
*/

    auto header_output = "rtl.h";
    auto fs = make_shared<fstream>();
    fs->open(header_output, ios::out | ios::trunc);

    /*
    for (auto var: *m2->vars()) {
        cout << *var->name() << endl;
    }
     */

    Transpiler tr;
    auto module = tr.transpile(m2, fs);

    module->print(llvm::outs(), nullptr);

    // gen
    puts("generating...");
    LLVMInitializeX86TargetInfo();
    LLVMInitializeX86Target();
    LLVMInitializeX86TargetMC();
    LLVMInitializeX86AsmParser();
    LLVMInitializeX86AsmPrinter();

    auto targetTriple = llvm::sys::getDefaultTargetTriple();
    module->setTargetTriple(targetTriple);

    std::string err;
    auto target = llvm::TargetRegistry::lookupTarget(targetTriple, err);

    if (!target) {
        llvm::errs() << err;
        return 1;
    }

    auto CPU = "generic";
    auto Features = "";

    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto targetMachine = target->createTargetMachine(targetTriple, CPU, Features, opt, RM);

    module->setDataLayout(targetMachine->createDataLayout());

    auto Filename = "rtl.o";
    std::error_code EC;
    llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OpenFlags::OF_None);

    if (EC) {
        llvm::errs() << "Could not open file: " << EC.message();
        return 1;
    }

    llvm::legacy::PassManager pass;
    auto FileType = llvm::LLVMTargetMachine::CGFT_ObjectFile;

    if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        llvm::errs() << "TheTargetMachine can't emit a file of this type";
        return 1;
    }

    puts("emitting...");
    pass.run(*module);
    puts("generated.");
    dest.flush();

    llvm::outs() << "Wrote " << Filename << "\n";
    return 0;
}
