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

#include <iostream>
#include <fstream>
#include <memory>
using namespace std;
using namespace afbd;

typedef initializer_list<shared_ptr<Expr>> exl;

int main() {
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
    instrXor->expr(make_shared<Expr>(ExprType::XOR, exl { make_shared<Expr>(a), make_shared<Expr>(ExprType::XOR, exl {make_shared<Expr>(t), make_shared<Expr>(b) }) }));

    p->begin()->add_succ(instrXor, 2);

    auto p2 = m->add_proc();
    p2->type(ProcessType::Nonblocking);

    auto exprx = make_shared<Expr>(ExprType::XOR, exl { make_shared<Expr>(a), make_shared<Expr>(b) });
    auto instrx = make_shared<Instruction>();
    instrx->dst(d);
    instrx->expr(exprx);

    p2->begin()->add_succ(instrx, 0);

    m->add_triggered_proc(t, p2);
    // m->add_triggered_proc(b, p2);
    //

    auto header_output = "rtl.h";
    auto fs = make_shared<fstream>();
    fs->open(header_output, ios::out | ios::trunc);

    Transpiler tr;
    auto module = tr.transpile(m, fs);

    module->print(llvm::outs(), nullptr);

    // gen
    puts("generating...");
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

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
