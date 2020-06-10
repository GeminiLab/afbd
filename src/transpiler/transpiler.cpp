#include <transpiler/transpiler.h>
#include <llvm/IR/TypeBuilder.h>

#include <queue>
#include <set>
#include <sstream>
#include <iostream>

using namespace std;
using namespace afbd;

void print_common_header(fstream &fs) {
    /*
    fs << "struct delay_gate {" << endl;
    fs << "  int o;" << endl;
    fs << "  int n;" << endl;
    fs << "  int k;" << endl;
    fs << "};" << endl;
     */
}

shared_ptr<set<shared_ptr<Instruction>>> get_all_instrs(shared_ptr<Instruction> root) {
    auto _instrs = make_shared<set<shared_ptr<Instruction>>>();
    queue<shared_ptr<Instruction>> _instr_to_visit;

    _instrs->insert(root);
    _instr_to_visit.push(root);
    while (!_instr_to_visit.empty()) {
        auto u = _instr_to_visit.front();
        _instr_to_visit.pop();

        for (auto& e: *u->succs()) {
            auto nx = e.first;

            if (_instrs->find(nx) == _instrs->end()) {
                _instrs->insert(nx);
                _instr_to_visit.push(nx);
            }
        }
    }

    return _instrs;
}

llvm::Function *Transpiler::transpile_process(shared_ptr<Process> proc) {
    std::ostringstream ss;
    ss << "process_" << rand() << "_" << time(nullptr);
    auto process = llvm::Function::Create(
            process_type,
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            ss.str(),
            m
    );

    llvm::IRBuilder<> builder(context);

    auto bbEntry = llvm::BasicBlock::Create(context, "", process);
    auto bbLoop = llvm::BasicBlock::Create(context, "", process);
    llvm::BasicBlock* bbEnd;

    if (proc->type() == ProcessType::Always) {
        bbEnd = bbLoop;
    } else {
        bbEnd = llvm::BasicBlock::Create(context, "", process);
    }

    builder.SetInsertPoint(bbEntry);

    auto sim = process->arg_begin();
    map<shared_ptr<Var>, llvm::Value*> varAddr;
    for (auto &v: *var_id) {
        varAddr[v.first] = builder.CreateInBoundsGEP(sim, llvm::ArrayRef<llvm::Value*> {
                builder.getInt32(0),
                builder.getInt32(v.second)
        });
    }

    function<llvm::Value*(shared_ptr<Expr>)> eval = [&](shared_ptr<Expr> expr) -> llvm::Value* {
        auto type = expr->type();

        if (type == ExprType::VAR) {
            return builder.CreateLoad(varAddr[expr->as_var()]);
        } else if (type == ExprType::CONSTANT) {
            return builder.getInt32(expr->as_constant()->value());
        } else {
            if (type == ExprType::NOT) {
                return builder.CreateNot(eval(expr->get_operand(0)));
            } else if (type == ExprType::REDUCE_BOOL) {
                return builder.CreateIntCast(eval(expr->get_operand(0)), builder.getInt32Ty(), false);
            } else if (type == ExprType::COND) {
                return builder.CreateSelect(eval(expr->get_operand(0)), eval(expr->get_operand(1)), eval(expr->get_operand(2)));
            } else {
                auto opl = eval(expr->get_operand(0));
                auto opr = eval(expr->get_operand(1));

                /*std::cout << "dump when eval: " << expr->get_operand(0)->to_json().dump() << " " << expr->get_operand(1)->to_json().dump() << "\n";
                std::cout << "their types are " << opl->getType()->getTypeID() << " " << opr->getType()->getTypeID() << "\n";*/

                switch (type) {
                    case ExprType::ADD:
                        return builder.CreateAdd(opl, opr);
                    case ExprType::SUB:
                        return builder.CreateSub(opl, opr);
                    case ExprType::MUL:
                        return builder.CreateMul(opl, opr);
                    case ExprType::DIV:
                        return builder.CreateUDiv(opl, opr);
                    case ExprType::MOD:
                        return builder.CreateURem(opl, opr);
                    case ExprType::EQ:
                        return builder.CreateICmpEQ(opl, opr);
                    case ExprType::NE:
                        return builder.CreateICmpNE(opl, opr);
                    case ExprType::GT:
                        return builder.CreateICmpUGT(opl, opr);
                    case ExprType::GE:
                        return builder.CreateICmpUGE(opl, opr);
                    case ExprType::LT:
                        return builder.CreateICmpULT(opl, opr);
                    case ExprType::LE:
                        return builder.CreateICmpULE(opl, opr);
                    case ExprType::AND:
                        return builder.CreateAnd(opl, opr);
                    case ExprType::OR:
                        return builder.CreateOr(opl, opr);
                    case ExprType::XOR:
                        return builder.CreateXor(opl, opr);
                    case ExprType::SHL:
                        return builder.CreateShl(opl, opr);
                    case ExprType::LSHR:
                        return builder.CreateLShr(opl, opr);
                    case ExprType::ASHR:
                        return builder.CreateAShr(opl, opr);
                }
            }
        }
    };

    function<llvm::Value*(llvm::Value*, int32_t)> shrink_to_width = [&](llvm::Value *v, int32_t width) -> llvm::Value* {
        return builder.CreateAnd(v, builder.getInt32((uint32_t)((1ull << width) - 1)));
    };

    auto instrs = get_all_instrs(proc->begin());
    map<shared_ptr<Instruction>, llvm::BasicBlock*> instr_bb;
    for (auto &x: *instrs) {
        instr_bb[x] = llvm::BasicBlock::Create(context, "", process);
    }

    builder.CreateBr(bbLoop);
    builder.SetInsertPoint(bbLoop);
    builder.CreateBr(instr_bb[proc->begin()]);

    for (auto &x: *instrs) {
        builder.SetInsertPoint(instr_bb[x]);

        auto type = x->type();
        auto instr_delay = x->delay();
        auto has_delay = instr_delay >= 0;
        instr_delay = has_delay ? instr_delay : 0;

        if (type == InstructionType::Delay) {
            if (instr_delay > 0) {
                builder.CreateCall(delay, llvm::ArrayRef<llvm::Value*> { builder.getInt32(instr_delay) });
            }
        } else if (type == InstructionType::Trigger) {
            if (x->triggers()->size() > 0) {
                builder.CreateCall(prepare_wait);
                for (auto &w: *x->triggers()) {
                    builder.CreateCall(
                            add_wait,
                            llvm::ArrayRef<llvm::Value*> {
                                    builder.getInt32(var_id->at(w.first)),
                                    builder.getInt32((int32_t)w.second),
                            }
                    );
                }
                builder.CreateCall(do_wait);
            }
        } else {
            auto assign_type = x->assign_type();
            auto dst = x->dst()->as_var();

            if (assign_type == AssignType::Blocking) {
                if (has_delay) {
                    auto temp = builder.CreateAlloca(builder.getInt32Ty());
                    builder.CreateStore(shrink_to_width(eval(x->expr()), dst->bit()), temp);
                    if (instr_delay == 0) {
                        builder.CreateCall(delay_for_explicit_zero_delay);
                    } else {
                        builder.CreateCall(delay, llvm::ArrayRef<llvm::Value*> { builder.getInt32(instr_delay) });
                    }
                    builder.CreateCall(
                            update,
                            llvm::ArrayRef<llvm::Value*> {
                                    varAddr[x->dst()->as_var()],
                                    builder.CreateLoad(temp),
                                    builder.getInt32(var_id->at(dst)),
                            }
                    );
                } else {
                    builder.CreateCall(
                            update,
                            llvm::ArrayRef<llvm::Value*> {
                                    varAddr[x->dst()->as_var()],
                                    shrink_to_width(eval(x->expr()), dst->bit()),
                                    builder.getInt32(var_id->at(dst)),
                            }
                    );
                }
            } else {
                builder.CreateCall(
                        delayed_nonblocking_assign_update,
                        llvm::ArrayRef<llvm::Value*> {
                                varAddr[x->dst()->as_var()],
                                shrink_to_width(eval(x->expr()), dst->bit()),
                                builder.getInt32(var_id->at(dst)),
                                builder.getInt32(instr_delay),
                        }
                );
            }
        }

        auto bbcd = llvm::BasicBlock::Create(context, "", process);
        builder.CreateBr(bbcd);
        builder.SetInsertPoint(bbcd);

        bool end = false;
        for (auto &s: *x->succs()) {
            auto instr = s.first;
            auto cond = s.second;

            if (cond == nullptr) { // || cond->type() == ExprType::DEFAULT) {
                builder.CreateBr(instr_bb[instr]);
                end = true;
                break;
            } else {
                bbcd = llvm::BasicBlock::Create(context, "", process);
                builder.CreateCondBr(eval(cond), instr_bb[instr], bbcd);
                builder.SetInsertPoint(bbcd);
            }
        }

        if (!end) builder.CreateBr(bbEnd);
    }

    if (bbEnd != bbLoop) {
        builder.SetInsertPoint(bbEnd);
        builder.CreateCall(process_end);
        builder.CreateRetVoid();
    }

    return process;
}

void Transpiler::load_static_functions() {
    auto voidTy = llvm::TypeBuilder<void, false>::get(context);
    auto tickTy = llvm::TypeBuilder<int32_t, false>::get(context);
    auto valTy = llvm::TypeBuilder<int32_t, false>::get(context);
    auto valPtrTy = valTy->getPointerTo();
    auto varIdTy = llvm::TypeBuilder<int32_t, false>::get(context);
    auto edgeTy = llvm::TypeBuilder<int32_t, false>::get(context);

    process_type = llvm::FunctionType::get(
            voidTy,
            llvm::ArrayRef<llvm::Type *>{sim_type->getPointerTo()},
            false
    );

    set_var_count = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type *>{varIdTy},
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "set_var_count",
            m
    );

    push_process = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type *>{process_type->getPointerTo(), sim_type->getPointerTo()},
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "push_process",
            m
    );

    process_end = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type *>{},
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "process_end",
            m
    );

    reset = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type *>{},
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "reset",
            m
    );


    delay = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type*> { tickTy },
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "delay",
            m
    );

    delay_for_explicit_zero_delay = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type *>{},
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "delay_for_explicit_zero_delay",
            m
    );

    delay_for_nonblocking_assign_update = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type*> { tickTy },
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "delay_for_nonblocking_assign_update",
            m
    );

    delayed_nonblocking_assign_update = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type*> { valPtrTy, valTy, varIdTy, tickTy },
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "delayed_nonblocking_assign_update",
            m
    );

    prepare_wait = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type *>{},
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "prepare_wait",
            m
    );

    add_wait = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type *>{ varIdTy, edgeTy },
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "add_wait",
            m
    );

    do_wait = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type *>{},
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "do_wait",
            m
    );

    update = llvm::Function::Create(
            llvm::FunctionType::get(
                    voidTy,
                    llvm::ArrayRef<llvm::Type*> { valPtrTy, valTy, varIdTy },
                    false
            ),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "update",
            m
    );
}

llvm::Module *Transpiler::transpile(shared_ptr<Module> module, shared_ptr<fstream> fs) {
    auto simName = "sim_" + module->name();
    m = new llvm::Module("sim_" + simName, context);
    llvm::IRBuilder<> builder(context);

    print_common_header(*fs);

    var_id = make_shared<map<shared_ptr<Var>, int>>();

    *fs << "struct " << simName << " {" << endl;

    vector<llvm::Type *> member;
    for (auto &var: *module->vars()) {
        (*var_id)[var] = member.size();
        member.push_back(builder.getInt32Ty());
        *fs << "int " << *var->name() << ";" << endl;
    }

    *fs << "};" << endl;

    sim_type = llvm::StructType::create(context, llvm::ArrayRef<llvm::Type *>(member), simName);
    auto initializer = llvm::Function::Create(
            llvm::FunctionType::get(builder.getVoidTy(), llvm::ArrayRef<llvm::Type *>{sim_type->getPointerTo()}, false),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "initialize_sim",
            m
    );

    *fs << "extern \"C\" void initialize_sim(" << simName << "*);" << endl;

    load_static_functions();

    auto bb = llvm::BasicBlock::Create(context, "", initializer);
    builder.SetInsertPoint(bb);

    initializer->arg_begin()->setName("s");

    builder.CreateCall(set_var_count, llvm::ArrayRef<llvm::Value*> { builder.getInt32(module->vars()->size()) });

    for (auto &proc: *module->procs()) {
        builder.CreateCall(push_process, llvm::ArrayRef<llvm::Value*> { transpile_process(proc), initializer->arg_begin() });
    }

    builder.CreateRetVoid();

    fs->close();

    return m;
}
