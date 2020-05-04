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
    auto m2 = make_shared<afbd::Module>("counter");
    auto a = m2->add_var(1, "clk");
    auto b = m2->add_var(1, "rst");
    auto t = m2->add_var(32, "o");

    auto pi = m2->add_proc();
    pi->type(ProcessType::Always);

    auto pie = make_shared<Instruction>(pi);
    pie->dst(nexpr(a));
    pie->expr(nexpr(nconst(1, 1)));

    auto pi2 = make_shared<Instruction>(pi);
    pi2->delay(3);

    auto pi3 = make_shared<Instruction>(pi);
    pi3->dst(nexpr(a));
    pi3->expr(nexpr(nconst(1, 0)));

    auto pi4 = make_shared<Instruction>(pi);
    pi4->delay(3);

    pi->begin(pie);
    pie->add_succ(pi2, nullptr);
    pi2->add_succ(pi3, nullptr);
    pi3->add_succ(pi4, nullptr);

    /*
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
