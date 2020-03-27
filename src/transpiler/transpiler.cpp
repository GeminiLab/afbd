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

struct TranspilerValues {
    llvm::LLVMContext *context;
    llvm::IRBuilder<> *builder;
    llvm::Function *func;
    shared_ptr<map<shared_ptr<Var>, llvm::Value*>> var_ptr;
    shared_ptr<map<shared_ptr<Var>, llvm::Value*>> last_var_ptr;
    shared_ptr<map<shared_ptr<Var>, llvm::Value*>> orig_var_ptr;
    shared_ptr<map<shared_ptr<Process>, llvm::Value*>> triggered_ptr;
};

llvm::Value* eval_expr(llvm::IRBuilder<> &builder, bool use_orig, shared_ptr<Expr> expr, TranspilerValues values) {
    auto type = expr->type();

    if (type == ExprType::VAR) {
        return builder.CreateLoad((use_orig ? values.orig_var_ptr : values.var_ptr)->at(expr->as_var()));
    } else if (type == ExprType::CONSTANT) {
        return builder.getInt32(expr->as_constant()->value());
    } else {
        if (type == ExprType::NOT) {
            return builder.CreateNot(eval_expr(builder, use_orig, expr->get_operand(0), values));
        } else {
            auto opl = eval_expr(builder, use_orig, expr->get_operand(0), values);
            auto opr = eval_expr(builder, use_orig, expr->get_operand(1), values);

            switch (type) {
                case ExprType::ADD:
                    return builder.CreateAdd(opl, opr);
                case ExprType::SUB:
                    return builder.CreateSub(opl, opr);
                case ExprType::AND:
                    return builder.CreateAnd(opl, opr);
                case ExprType::OR:
                    return builder.CreateOr(opl, opr);
                case ExprType::XOR:
                    return builder.CreateXor(opl, opr);
            }
        }
    }
}

void process_continuous(shared_ptr<Instruction> pseudo_root, TranspilerValues values) {
    auto& builder = *values.builder;
    auto& context = *values.context;
    auto func = values.func;

    for (auto& pair: *pseudo_root->succs()) {
        auto instr = pair.first;
        auto delay = pair.second;

        /*
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
        } else */ {
            builder.CreateStore(eval_expr(builder, true, instr->expr(), values), (*values.var_ptr).at(instr->dst()));

            auto bbnx = llvm::BasicBlock::Create(context, "", func);
            builder.CreateBr(bbnx);
            builder.SetInsertPoint(bbnx);
        }
    }
}

void process_nonblock(shared_ptr<Instruction> root, TranspilerValues values) {
    auto& builder = *values.builder;
    auto& context = *values.context;
    auto func = values.func;

    auto instr = root->succs()->at(0).first;

    builder.CreateStore(eval_expr(builder, true, instr->expr(), values), (*values.var_ptr).at(instr->dst()));

    auto bbnx = llvm::BasicBlock::Create(context, "", func);
    builder.CreateBr(bbnx);
    builder.SetInsertPoint(bbnx);
}

void process_block(shared_ptr<Instruction> root, TranspilerValues values) {
    auto& builder = *values.builder;
    auto& context = *values.context;
    auto func = values.func;

    builder.CreateStore(eval_expr(builder, false, root->expr(), values), (*values.var_ptr).at(root->dst()));

    auto bbnx = llvm::BasicBlock::Create(context, "", func);
    builder.CreateBr(bbnx);
    builder.SetInsertPoint(bbnx);
}

void process_process(shared_ptr<Process> proc, TranspilerValues values) {
    auto& builder = *values.builder;
    auto& context = *values.context;
    auto func = values.func;

    if (proc->type() == ProcessType::Continuous) {
        process_continuous(proc->begin(), values);
    } else if (proc->type() == ProcessType::Nonblocking) {
        auto bbug = llvm::BasicBlock::Create(context, "", func);
        auto bbnx = llvm::BasicBlock::Create(context, "", func);

        builder.CreateCondBr(builder.CreateLoad(values.triggered_ptr->at(proc)), bbug, bbnx);
        builder.SetInsertPoint(bbug);

        process_nonblock(proc->begin(), values);

        builder.CreateBr(bbnx);
        builder.SetInsertPoint(bbnx);
    } else if (proc->type() == ProcessType::Blocking) {
        auto bbug = llvm::BasicBlock::Create(context, "", func);
        auto bbnx = llvm::BasicBlock::Create(context, "", func);

        builder.CreateCondBr(builder.CreateLoad(values.triggered_ptr->at(proc)), bbug, bbnx);
        builder.SetInsertPoint(bbug);

        process_block(proc->begin(), values);

        builder.CreateBr(bbnx);
        builder.SetInsertPoint(bbnx);
    }
}

llvm::Module *Transpiler::transpile(shared_ptr<Module> module, shared_ptr<fstream> fs) {
    print_common_header(*fs);

    auto m = new llvm::Module("sim", context);

    auto var_idx = make_shared<map<shared_ptr<Var>, int>>();
    auto old_var_idx = make_shared<map<shared_ptr<Var>, int>>();
    // auto delay_gate_idx = make_shared<map<pair<shared_ptr<Instruction>, shared_ptr<Var>>, int>>();

    *fs << "struct sim {" << endl;

    llvm::IRBuilder<> builder(context);

    vector<llvm::Type*> member;
    for (auto& var: *module->vars()) {
        (*var_idx)[var] = member.size();
        member.push_back(builder.getInt32Ty());
        *fs << "int " << var->name()->c_str() << ";" << endl;
    }

    *fs << "private:" << endl;

    for (auto& var: *module->vars()) {
        (*old_var_idx)[var] = member.size();
        member.push_back(builder.getInt32Ty());
        *fs << "int old_" << var->name()->c_str() << ";" << endl;
    }

    *fs << "};" << endl;

    auto simSt = llvm::StructType::create(context, llvm::ArrayRef<llvm::Type*>(member), "sim");
    auto sim = llvm::Function::Create(
        llvm::FunctionType::get(builder.getInt8Ty(), llvm::ArrayRef<llvm::Type*> { simSt->getPointerTo() }, false),
        llvm::GlobalValue::LinkageTypes::ExternalLinkage,
        "do_sim",
        m
    );

    auto bb = llvm::BasicBlock::Create(context, "", sim);
    builder.SetInsertPoint(bb);

    auto var_ptr = make_shared<map<shared_ptr<Var>, llvm::Value*>>();
    auto last_var_ptr = make_shared<map<shared_ptr<Var>, llvm::Value*>>();
    auto orig_var_ptr = make_shared<map<shared_ptr<Var>, llvm::Value*>>();
    auto triggered_ptr = make_shared<map<shared_ptr<Process>, llvm::Value*>>();

    sim->arg_begin()->setName("s");

    for (auto& var: *module->vars()) {
        (*var_ptr)[var] = builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
            builder.getInt32(0),
            builder.getInt32(var_idx->at(var))
        });
        (*last_var_ptr)[var] = builder.CreateInBoundsGEP(sim->arg_begin(), llvm::ArrayRef<llvm::Value*> {
            builder.getInt32(0),
            builder.getInt32(old_var_idx->at(var))
        });
        builder.CreateStore(builder.CreateLoad((*var_ptr)[var]), (*orig_var_ptr)[var] = builder.CreateAlloca(builder.getInt32Ty()));
    }

    for (auto& proc: *module->procs()) {
        // if (triggered.find(proc) != triggered.end()) {
        (*triggered_ptr)[proc] = builder.CreateAlloca(builder.getInt8Ty());
        builder.CreateStore(builder.getInt8(0), triggered_ptr->at(proc));
        // }
    }

    for (auto& var: *module->vars()) {
        auto bbup = llvm::BasicBlock::Create(context, "", sim);
        auto bbnx = llvm::BasicBlock::Create(context, "", sim);

        builder.CreateCondBr(builder.CreateICmpNE(builder.CreateLoad(var_ptr->at(var)), builder.CreateLoad(last_var_ptr->at(var))), bbup, bbnx);

        builder.SetInsertPoint(bb = bbup);

        for (auto& proc: *var->sens_procs()) {
            builder.CreateStore(builder.getInt8(1), triggered_ptr->at(proc));
        }

        builder.CreateBr(bbnx);
        builder.SetInsertPoint(bb = bbnx);
    }

    TranspilerValues values;
    values.context = &context;
    values.builder = &builder;
    values.func = sim;
    values.var_ptr = var_ptr;
    values.last_var_ptr = last_var_ptr;
    values.orig_var_ptr = orig_var_ptr;
    values.triggered_ptr = triggered_ptr;
    for (auto& proc: *module->procs()) {
        process_process(proc, values);
    }

    for (auto& var: *module->vars()) {
        builder.CreateStore(builder.CreateLoad((*var_ptr)[var]), (*last_var_ptr)[var]);
    }

    builder.CreateRet(builder.getInt8(0));

    *fs << "extern \"C\" signed char do_sim(sim*);" << endl;
    fs->close();

    return m;
}
