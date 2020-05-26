#pragma once

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
//#include "llvm/IR/TypeBuilder.h"

#include <afbdil/afbdil>

#include <fstream>

class Transpiler {
private:
    llvm::LLVMContext context;

    std::shared_ptr<std::map<std::shared_ptr<afbd::Var>, int>> var_id;

    llvm::Module *m;
    llvm::StructType *sim_type;
    llvm::FunctionType *process_type;

    llvm::Function *set_var_count;

    llvm::Function *push_process;
    llvm::Function *process_end;
    llvm::Function *exec_until;
    llvm::Function *reset;

    llvm::Function *delay;
    llvm::Function *delay_for_explicit_zero_delay;
    llvm::Function *delay_for_nonblocking_assign_update;
    llvm::Function *delayed_nonblocking_assign_update;
    llvm::Function *prepare_wait;
    llvm::Function *add_wait;
    llvm::Function *do_wait;

    llvm::Function *update;
    llvm::Function *mark_updated;

    void load_static_functions();


    llvm::Value *eval_expr(llvm::IRBuilder<> &builder, std::shared_ptr<afbd::Expr> expr);
    llvm::Function *transpile_process(std::shared_ptr<afbd::Process> proc);
public:
    llvm::Module* transpile(std::shared_ptr<afbd::Module> module, std::shared_ptr<std::fstream> fs);
};
