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
#include <fstream>
#include <memory>
using namespace std;
using namespace afbd;

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
    delay_struct_handler = llvm::Function::Create(dsht, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "delay_gate_handler", module);
}

llvm::StructType *st;
map<shared_ptr<Var>, int> varid;
map<shared_ptr<Var>, int> oldvarid;
map<shared_ptr<Process>, llvm::Value*> triggered;
map<pair<shared_ptr<Instruction>, shared_ptr<Var>>, int> instrid;
llvm::Function *sim;

void process_module(shared_ptr<Module> m) {
    auto header_output = "rtl.h";
    fstream fs;
    fs.open(header_output, ios::out | ios::trunc);

    fs << "struct delay_gate {" << endl;
    fs << "  int o;" << endl;
    fs << "  int n;" << endl;
    fs << "  int k;" << endl;
    fs << "};" << endl;

    //for (auto& proc: *m->procs()) process_proc(proc);

    fs << "struct sim {" << endl;

    vector<llvm::Type*> member;
    for (auto& var: *m->vars()) {
        varid[var] = member.size();
        member.push_back(i32t);
        fs << "int " << var->name()->c_str() << ";" << endl;
    }

    fs << "private:" << endl;

    for (auto& proc: *m->procs()) {
        if (proc->type() == ProcessType::Continuous) {
            for(auto& pair: *proc->begin()->succs()) {
                auto instr = pair.first;
                auto delay = pair.second;

                if (delay > 0) {
                    for (auto& v: *instr->src()) {
                        instrid[make_pair(instr, v)] = member.size();
                        fs << "delay_gate dg_" << member.size() << ";" << endl;
                        member.push_back(delay_struct);
                    }
                }
            }
        } else if (proc->type() == ProcessType::Nonblocking) {
            triggered[proc] = nullptr;
        }
    }

    for (auto& var: *m->vars()) {
        oldvarid[var] = member.size();
        member.push_back(i32t);
        fs << "int old_" << var->name()->c_str() << ";" << endl;
    }

    llvm::IRBuilder<> builder(context);
    st = llvm::StructType::create(context, llvm::ArrayRef<llvm::Type*>(member), "st");
    sim = llvm::Function::Create(
            llvm::FunctionType::get(builder.getInt8Ty(), llvm::ArrayRef<llvm::Type*> { st->getPointerTo() }, false),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "do_sim",
            module
    );

    sim->arg_begin()->setName("s");

    auto bbcheck = llvm::BasicBlock::Create(context, "", sim);
    auto bb = bbcheck;

    builder.SetInsertPoint(bb);

    for (auto& proc: *m->procs()) {
        // if (triggered.find(proc) != triggered.end()) {
            triggered[proc] = builder.CreateAlloca(i8t);
            builder.CreateStore(builder.getInt8(0), triggered[proc]);
        // }
    }

    for (auto& var: *m->vars()) {
        auto bbup = llvm::BasicBlock::Create(context, "", sim);
        auto bbnx = llvm::BasicBlock::Create(context, "", sim);

        builder.CreateCondBr(builder.CreateICmpNE(builder.CreateLoad(builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                builder.getInt32(0),
                builder.getInt32(varid[var])
        })), builder.CreateLoad(builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                builder.getInt32(0),
                builder.getInt32(oldvarid[var])
        }))), bbup, bbnx);

        builder.SetInsertPoint(bb = bbup);

        for (auto& proc: *var->sens_procs()) {
            builder.CreateStore(builder.getInt8(1), triggered[proc]);
        }

        builder.CreateBr(bbnx);
        builder.SetInsertPoint(bb = bbnx);
    }

    auto bbbegin = llvm::BasicBlock::Create(context, "", sim);
    bb = bbbegin;
    builder.CreateBr(bb);

    builder.SetInsertPoint(bb);

    for (auto& proc: *m->procs()) {
        if (proc->type() == ProcessType::Continuous) {
            for (auto& pair: *proc->begin()->succs()) {
                auto instr = pair.first;
                auto delay = pair.second;

                if (delay > 0) {
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
                        auto left = builder.CreateInBoundsGEP(
                                builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                        llvm::ConstantInt::get(i32t, 0),
                                        llvm::ConstantInt::get(i32t, instrid[make_pair(instr, instr->src()->at(0))])
                                }),
                                llvm::ArrayRef<llvm::Value*> {
                                        llvm::ConstantInt::get(i32t, 0),
                                        llvm::ConstantInt::get(i32t, 0)
                                }
                        );
                        auto righ = builder.CreateInBoundsGEP(
                                builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                        llvm::ConstantInt::get(i32t, 0),
                                        llvm::ConstantInt::get(i32t, instrid[make_pair(instr, instr->src()->at(1))])
                                }),
                                llvm::ArrayRef<llvm::Value*> {
                                        llvm::ConstantInt::get(i32t, 0),
                                        llvm::ConstantInt::get(i32t, 0)
                                }
                        );

                        builder.CreateStore(builder.CreateXor(builder.CreateLoad(left), builder.CreateLoad(righ)),builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                llvm::ConstantInt::get(i32t, 0),
                                llvm::ConstantInt::get(i32t, varid[instr->dst()])
                        }));
                    } else if (instr->type() == InstructionType::ASSIGN) {
                        auto src = builder.CreateInBoundsGEP(
                                builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                        llvm::ConstantInt::get(i32t, 0),
                                        llvm::ConstantInt::get(i32t, instrid[make_pair(instr, instr->src()->at(0))])
                                }),
                                llvm::ArrayRef<llvm::Value*> {
                                        llvm::ConstantInt::get(i32t, 0),
                                        llvm::ConstantInt::get(i32t, 0)
                                }
                        );

                        builder.CreateStore(builder.CreateLoad(src), builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                llvm::ConstantInt::get(i32t, 0),
                                llvm::ConstantInt::get(i32t, varid[instr->dst()])
                        }));
                    }

                    builder.CreateBr(bbnx);
                    builder.SetInsertPoint(bb = bbnx);
                } else {
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
                    } else if (instr->type() == InstructionType::ASSIGN) {
                        builder.CreateStore(builder.CreateLoad(builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                llvm::ConstantInt::get(i32t, 0),
                                llvm::ConstantInt::get(i32t, varid[instr->src()->at(0)])
                        })), builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                                llvm::ConstantInt::get(i32t, 0),
                                llvm::ConstantInt::get(i32t, varid[instr->dst()])
                        }));
                    }

                    auto bbnx = llvm::BasicBlock::Create(context, "", sim);
                    builder.CreateBr(bbnx);
                    builder.SetInsertPoint(bb = bbnx);
                }
            }
        } else if (proc->type() == ProcessType::Nonblocking) {
            auto bbug = llvm::BasicBlock::Create(context, "", sim);
            auto bbnx = llvm::BasicBlock::Create(context, "", sim);

            builder.CreateCondBr(builder.CreateLoad(triggered[proc]), bbug, bbnx);

            builder.SetInsertPoint(bbug);

            for (auto& pair: *proc->begin()->succs()) {
                auto instr = pair.first;
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
                } else if (instr->type() == InstructionType::ASSIGN) {
                    builder.CreateStore(builder.CreateLoad(builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                            llvm::ConstantInt::get(i32t, 0),
                            llvm::ConstantInt::get(i32t, varid[instr->src()->at(0)])
                    })), builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                            llvm::ConstantInt::get(i32t, 0),
                            llvm::ConstantInt::get(i32t, varid[instr->dst()])
                    }));
                }
            }

            builder.CreateBr(bbnx);
            builder.SetInsertPoint(bb = bbnx);
        }
    }

    for (auto& var: *m->vars()) {
        builder.CreateStore(builder.CreateLoad(builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                builder.getInt32(0),
                builder.getInt32(varid[var])
        })), builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
                builder.getInt32(0),
                builder.getInt32(oldvarid[var])
        }));
    }

    builder.CreateRet(builder.getInt8(0));
    fs << "};" << endl;
    fs << "extern \"C\" signed char do_sim(sim*);" << endl;
    fs.close();
}

int main() {
    auto m = make_shared<Module>();
    auto a = m->add_var(1, "a");
    auto b = m->add_var(1, "b");
    auto c = m->add_var(1, "c");
    auto d = m->add_var(1, "d");
    auto e = m->add_var(1, "e");

    auto a2 = m->add_var(1, "a2");
    auto f = m->add_var(1, "f");
    auto g = m->add_var(1, "g");

    auto p = m->add_proc();
    p->type(ProcessType::Continuous);

    auto instrb = make_shared<Instruction>(InstructionType::ASSIGN);
    instrb->dst(e);
    instrb->add_src(b);

    auto instr2 = make_shared<Instruction>(InstructionType::XOR);
    instr2->dst(c);
    instr2->add_src(a);
    instr2->add_src(b);

    auto instr0 = make_shared<Instruction>(InstructionType::XOR);
    instr0->dst(d);
    instr0->add_src(a);
    instr0->add_src(b);

    p->begin()->add_succ(instrb, 2);
    p->begin()->add_succ(instr2, 2);
    p->begin()->add_succ(instr0, 0);

    auto p2 = m->add_proc();
    p2->type(ProcessType::Nonblocking);

    auto instrx = make_shared<Instruction>(InstructionType::XOR);
    instrx->dst(f);
    instrx->add_src(a);
    instrx->add_src(b);

    auto instry = make_shared<Instruction>(InstructionType::XOR);
    instry->dst(g);
    instry->add_src(f);
    instry->add_src(a2);

    p2->begin()->add_succ(instrx, 0);
    p2->begin()->add_succ(instry, 0);
    m->add_triggered_proc(a2, p2);
    // m->add_triggered_proc(b, p2);
    //

    static_llvm_defs();
    process_module(m);

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
