#include <afbdil/afbdil>

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
#include <afbdil/module_serializer.h>
#include <yosys/include/verilog_frontend.h>
#include <transpiler/afbdilpass.h>

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
    auto m2 = make_shared<afbd::Module>("counter");
    auto a = m2->add_var(1, "clk");
    auto b = m2->add_var(1, "rst");
    auto t = m2->add_var(32, "cnt");
    auto t2 = m2->add_var(32, "cn2");

    auto pi = m2->add_proc();
    pi->type(ProcessType::Always);

    auto pie = make_shared<Instruction>(pi);
    pie->dst(nexpr(a));
    pie->expr(nexpr(nconst(1, 0)));

    auto pi2 = make_shared<Instruction>(pi);
    pi2->delay(3);

    auto pi3 = make_shared<Instruction>(pi);
    pi3->dst(nexpr(a));
    pi3->expr(nexpr(nconst(1, 1)));

    auto pi4 = make_shared<Instruction>(pi);
    pi4->delay(3);

    pi->begin(pie);
    pie->add_succ(pi2, nullptr);
    pi2->add_succ(pi3, nullptr);
    pi3->add_succ(pi4, nullptr);

    auto po = m2->add_proc();
    po->type(ProcessType::Always);

    auto poe = make_shared<Instruction>(po);
    auto trigger = make_shared<TriggerContainer>(initializer_list<Trigger>{ { a, Edge::POSEDGE } });
    poe->triggers(trigger);

    auto po2 = make_shared<Instruction>(po);
    po2->dst(nexpr(t));
    po2->expr(nexpr(ExprType::ADD, lexpr(nexpr(t), nexpr(nconst(32, 1)))));
    po2->assign_type(AssignType::NonBlocking);
    po2->assign_delay(1);

    po->begin(poe);
    poe->add_succ(po2, nullptr);

    auto pop = m2->add_proc();
    pop->type(ProcessType::Always);

    auto pope = make_shared<Instruction>(pop);
    auto triggerp = make_shared<TriggerContainer>(initializer_list<Trigger>{ { a, Edge::EDGE } });
    pope->triggers(triggerp);

    auto pop2 = make_shared<Instruction>(pop);
    pop2->dst(nexpr(t2));
    pop2->expr(nexpr(ExprType::ADD, lexpr(nexpr(t2), nexpr(nconst(32, 1)))));
    pop2->assign_type(AssignType::NonBlocking);
    pop2->assign_delay(2);

    pop->begin(pope);
    pope->add_succ(pop2, nullptr);
*/

    /*
    // args hack
    */
#ifdef ARGS_HACK
    const char *fin = "/home/gemini/source/bachelor/afbd/example/example.v";
    const char *mon = "counter";

    argc = 3;
    char* new_argv[3] = { argv[0], const_cast<char*>(fin), const_cast<char*>(mon) };
    argv = new_argv;
#endif

    // begin
    if(argc < 2) {
        std::cout << "no filename\n";
        return 0;
    }

    std::vector<std::string> args;
    for(int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    std::istream* f = nullptr;

    RTLIL::Design* design = new RTLIL::Design;

    cout << "parsing..." << endl;

    VerilogFrontend frontend;
    frontend.execute(f, args[1], args, design);

    cout << "analyzing..." << endl;

    afbd::afbdilPass p;
    p.execute(args, design);
    auto m2 = p.res;


    auto header_output = m2->name() + ".h";
    auto object_output = m2->name() + ".o";
    auto fs = make_shared<fstream>();
    fs->open(header_output, ios::out | ios::trunc);

    /*
    for (auto var: *m2->vars()) {
        cout << *var->name() << endl;
    }
     */

    cout << "generating llvm ir..." << endl;

    for (auto &v: *m2->vars()) {
        cout << *v->name() << " " << v->bit() << endl;
    }

    Transpiler tr;
    auto module = tr.transpile(m2, fs);

    cout << "writing " << header_output << " ..." << endl;
    // module->print(llvm::outs(), nullptr);

    // gen
    puts("generating object file...");
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

    std::error_code EC;
    llvm::raw_fd_ostream dest(object_output, EC, llvm::sys::fs::OpenFlags::OF_None);

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

    pass.run(*module);
    puts("generated.");
    dest.flush();

    llvm::outs() << "written to " << object_output << "\n";
    return 0;
}
