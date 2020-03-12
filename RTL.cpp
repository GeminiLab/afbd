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

#include <iostream>
#include <memory>
using namespace std;

llvm::LLVMContext context;
llvm::Module *module;
llvm::StructType *delay_struct;
llvm::Function *delay_struct_handler;
llvm::Type *i8t, *i32t;

void static_llvm_defs() {
    module = new llvm::Module("sim", context);
    i8t = llvm::TypeBuilder<int8_t, false>::get(context);
    i32t = llvm::TypeBuilder<int32_t, false>::get(context);

    delay_struct = llvm::StructType::create(context, llvm::ArrayRef<llvm::Type*> {
            i32t, // active value
            i32t, // current value
            i32t, // keep time
    }, "delay_gate");

    // i8 delay_handler (delay_gate* st, int delay, int current)
    auto dsht = llvm::FunctionType::get(i8t, llvm::ArrayRef<llvm::Type*> { delay_struct->getPointerTo(), i32t, i32t }, false);
    delay_struct_handler = llvm::Function::Create(dsht, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "delay_handler", module);

    llvm::IRBuilder<> builder(context);

    auto bb = llvm::BasicBlock::Create(context, "entry", delay_struct_handler);
    builder.SetInsertPoint(bb);

    auto ds = delay_struct_handler->arg_begin();
    ds->setName("ds");
    auto actvValue = builder.CreateInBoundsGEP(delay_struct,  ds, llvm::ArrayRef<llvm::Value*> {
            llvm::ConstantInt::get(i32t, 0),
            llvm::ConstantInt::get(i32t, 0),
    });
    auto currValue = builder.CreateInBoundsGEP(delay_struct,  ds, llvm::ArrayRef<llvm::Value*> {
            llvm::ConstantInt::get(i32t, 0),
            llvm::ConstantInt::get(i32t, 1),
    });
    auto keepTime = builder.CreateInBoundsGEP(delay_struct,  ds, llvm::ArrayRef<llvm::Value*> {
            llvm::ConstantInt::get(i32t, 0),
            llvm::ConstantInt::get(i32t, 2),
    });
    auto delay = delay_struct_handler->arg_begin() + 1;
    auto curr = delay + 1;

    delay->setName("delay");
    curr->setName("curr");

    auto rv = builder.CreateAlloca(i8t, llvm::ConstantInt::get(i8t, 0));
    auto bbfl = llvm::BasicBlock::Create(context, "flip", delay_struct_handler);
    auto bbup = llvm::BasicBlock::Create(context, "upgr", delay_struct_handler);

    builder.CreateCondBr(builder.CreateICmpSGE(builder.CreateLoad(keepTime), delay), bbfl, bbup);

    builder.SetInsertPoint(bbfl);
    builder.CreateStore(llvm::ConstantInt::get(i8t, 1), rv);
    builder.CreateStore(builder.CreateLoad(currValue), actvValue);
    builder.CreateStore(curr, currValue);
    builder.CreateStore(llvm::ConstantInt::get(i32t, 0), keepTime);

    builder.CreateBr(bbup);

    auto bbbkc = llvm::BasicBlock::Create(context, "back_cond", delay_struct_handler);
    auto bbbke = llvm::BasicBlock::Create(context, "back_exec", delay_struct_handler);
    auto bbkpc = llvm::BasicBlock::Create(context, "keep_cond", delay_struct_handler);
    auto bbkpe = llvm::BasicBlock::Create(context, "keep_exec", delay_struct_handler);
    auto bbnv = llvm::BasicBlock::Create(context, "new_value", delay_struct_handler);
    auto bbend = llvm::BasicBlock::Create(context, "end", delay_struct_handler);

    builder.SetInsertPoint(bbup);
    builder.CreateBr(bbbkc);

    builder.SetInsertPoint(bbbkc);
    builder.CreateCondBr(builder.CreateICmpEQ(builder.CreateLoad(actvValue), curr), bbbke, bbkpc);

    builder.SetInsertPoint(bbbke);
    builder.CreateStore(llvm::ConstantInt::get(i32t, 0), keepTime);
    builder.CreateStore(curr, currValue);
    builder.CreateBr(bbend);

    builder.SetInsertPoint(bbkpc);
    builder.CreateCondBr(builder.CreateICmpEQ(builder.CreateLoad(currValue), curr), bbkpe, bbnv);

    builder.SetInsertPoint(bbkpe);
    builder.CreateStore(builder.CreateAdd(builder.CreateLoad(keepTime), llvm::ConstantInt::get(i32t, 1)), keepTime);
    builder.CreateBr(bbend);

    builder.SetInsertPoint(bbnv);
    builder.CreateStore(llvm::ConstantInt::get(i32t, 1), keepTime);
    builder.CreateStore(curr, currValue);
    builder.CreateBr(bbend);

    builder.SetInsertPoint(bbend);
    builder.CreateRet(rv);
}

llvm::StructType *st;
map<shared_ptr<Var>, int> varid;
map<pair<shared_ptr<Instruction>, shared_ptr<Var>>, int> instrid;
llvm::Function *sim;

void process_module(shared_ptr<Module> m) {


    //for (auto& proc: *m->procs()) process_proc(proc);

    vector<llvm::Type*> member;
    for (auto& var: *m->vars()) {
        varid[var] = member.size();
        member.push_back(i32t);
    }


    for (auto& proc: *m->procs()) {
        if (proc->type() == ProcessType::Continuous) {
            for(auto& pair: *proc->begin()->succs()) {
                auto instr = pair.first;
                for (auto& v: *instr->src()) {
                    instrid[make_pair(instr, v)] = member.size();
                    member.push_back(delay_struct);
                }
            }
        }
    }

    llvm::IRBuilder<> builder(context);
    st = llvm::StructType::create(context, llvm::ArrayRef<llvm::Type*>(member), "st");
    sim = llvm::Function::Create(
            llvm::FunctionType::get(builder.getVoidTy(), llvm::ArrayRef<llvm::Type*> { st->getPointerTo() }, false),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "do_sim",
            module
    );

    sim->arg_begin()->setName("s");

    auto bbbegin = llvm::BasicBlock::Create(context, "", sim);
    auto bb = bbbegin;

    builder.SetInsertPoint(bb);

    for (auto& proc: *m->procs()) {
        if (proc->type() == ProcessType::Continuous) {
            for (auto& pair: *proc->begin()->succs()) {
                auto instr = pair.first;
                auto delay = pair.second;

                llvm::Value *cond = nullptr;
                for (auto& var: *instr->src()) {
                    if (cond == nullptr) {
                        cond = builder.CreateCall(delay_struct_handler, llvm::ArrayRef<llvm::Value*> {
                            builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                llvm::ConstantInt::get(i32t, 0),
                                llvm::ConstantInt::get(i32t, instrid[make_pair(instr, var)])
                            }),
                            llvm::ConstantInt::get(i32t, delay),
                            builder.CreateLoad(builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                llvm::ConstantInt::get(i32t, 0),
                                llvm::ConstantInt::get(i32t, varid[var])
                            })),
                        });
                    } else {
                        cond = builder.CreateOr(cond, builder.CreateCall(delay_struct_handler, llvm::ArrayRef<llvm::Value*> {
                            builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                llvm::ConstantInt::get(i32t, 0),
                                llvm::ConstantInt::get(i32t, instrid[make_pair(instr, var)])
                            }),
                            llvm::ConstantInt::get(i32t, delay),
                            builder.CreateLoad(builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                llvm::ConstantInt::get(i32t, 0),
                                llvm::ConstantInt::get(i32t, varid[var])
                            })),
                        }));
                    }
                }

                auto bbug = llvm::BasicBlock::Create(context, "", sim);
                auto bbnx = llvm::BasicBlock::Create(context, "", sim);

                builder.CreateCondBr(cond, bbug, bbnx);

                builder.SetInsertPoint(bbug);

                if (instr->type() == InstructionType::XOR) {
                    builder.CreateStore(builder.CreateXor(builder.CreateLoad(builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                            llvm::ConstantInt::get(i32t, 0),
                            llvm::ConstantInt::get(i32t, varid[instr->src()->at(0)])
                    })),builder.CreateLoad(builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                            llvm::ConstantInt::get(i32t, 0),
                            llvm::ConstantInt::get(i32t, varid[instr->src()->at(1)])
                    }))),builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                            llvm::ConstantInt::get(i32t, 0),
                            llvm::ConstantInt::get(i32t, varid[instr->dst()])
                    }));
                }

                builder.CreateBr(bbnx);
                builder.SetInsertPoint(bb = bbnx);
            }
        }
    }
}

int main() {
    auto m = make_shared<Module>();
    auto a = m->add_var(1, "a");
    auto b = m->add_var(1, "b");
    auto c = m->add_var(1, "c");
    auto d = m->add_var(1, "d");
    auto p = m->add_proc();
    p->type(ProcessType::Continuous);

    auto instr2 = make_shared<Instruction>(InstructionType::XOR);
    instr2->dst(c);
    instr2->add_src(a);
    instr2->add_src(b);

    auto instr0 = make_shared<Instruction>(InstructionType::XOR);
    instr0->dst(d);
    instr0->add_src(a);
    instr0->add_src(b);

    p->begin()->add_succ(instr2, 2);
    p->begin()->add_succ(instr0, 0);

    //

    static_llvm_defs();
    process_module(m);

    module->print(llvm::outs(), nullptr);

    return 0;
}
