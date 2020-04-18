#pragma once

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
//#include "llvm/IR/TypeBuilder.h"

#include <rtlil/rtlil>

#include <fstream>

class Transpiler {
private:
    llvm::LLVMContext context;
public:
    llvm::Module* transpile(std::shared_ptr<afbd::Module> module, std::shared_ptr<std::fstream> fs);
};
