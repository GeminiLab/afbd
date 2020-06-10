#include <memory>

#include "../../include/afbdil/patternmatching.h"
#include "../../include/afbdil/expr.h"
#include "../../include/afbdil/instruction.h"

using namespace afbd;

void reportDefect(std::shared_ptr<Module> module, std::string str, bool is_error, int line)
{
    if(is_error)
    {
        std::cout << "Error: ";
        module->set_error();
    }
    else
        std::cout << "Warning: ";
	std::cout << str << " in line " << line << ".\n";
}

void clkCheck(std::shared_ptr<afbd::Module> module)
{
	std::set<std::shared_ptr<Var>> clk_vars;

	for(auto process : (*module->procs()))
	{
		auto begin = process->begin();
		auto triggers = begin->triggers();
		if(triggers)
		{
			for(auto trigger: *triggers)
			{
				if(trigger.second != Edge::EDGE)
					clk_vars.insert(trigger.first);
			}
		}
	}

	for(auto process : (*module->procs()))
	{
		auto all_instructions = process->all_instructions();
		for(auto instruction : all_instructions)
		{
			if(instruction->type() != InstructionType::Assign)
				continue;
			auto expr = instruction->expr();
			if(expr && expr->type() == ExprType::VAR && clk_vars.find(expr->as_var()) != clk_vars.end())
			{
				std::string str = "buf on clock signal ";
				str += *(expr->as_var()->name());
				reportDefect(module, str, false, instruction->line());
			}
			else if(expr && expr->type() == ExprType::NOT)
			{
				auto subexpr = expr->get_operand(0);
				if(subexpr->type() == ExprType::VAR && clk_vars.find(subexpr->as_var()) != clk_vars.end())
				{
					std::string str = "not on clock signal ";
                    str += *(subexpr->as_var()->name());
                    reportDefect(module, str, false, instruction->line());
				}
			}
		}
	}
}

int exprCheck(std::shared_ptr<afbd::Module> module, std::shared_ptr<Expr> expr, int line)
{
	int op0_len, op1_len, op2_len;
	std::string str;
	switch(expr->type())
	{
		case ExprType::VAR:
			return expr->as_var()->bit();
		case ExprType::CONSTANT:
			return expr->as_constant()->bit();
		case ExprType::NOT:
			op0_len = exprCheck(module, expr->get_operand(0), line);
			return op0_len;
		case ExprType::ADD:
		case ExprType::SUB:
		case ExprType::MUL:
		case ExprType::DIV:
		case ExprType::MOD:
		case ExprType::SHL:
		case ExprType::LSHR:
		case ExprType::ASHR:
		case ExprType::AND:
		case ExprType::OR:
		case ExprType::XOR:
			op0_len = exprCheck(module, expr->get_operand(0), line);
			op1_len = exprCheck(module, expr->get_operand(1), line);
			if(op0_len != -1 && op1_len != -1)
			{
				if(op0_len == op1_len)
					return op0_len;
				else
				{
					str += "type mismatch in ";
                    str += expr->to_json().dump();
					reportDefect(module, str, false, line);
					return -1;
				}
			}
			else
				return -1;
		case ExprType::EQ:
		case ExprType::NE:
		case ExprType::GT:
		case ExprType::GE:
		case ExprType::LT:
		case ExprType::LE:
			op0_len = exprCheck(module, expr->get_operand(0), line);
			op1_len = exprCheck(module, expr->get_operand(1), line);
			if(op0_len != -1 && op1_len != -1)
			{
				if(op0_len == op1_len)
					return 1;
				else
				{
                    str += "type mismatch in ";
                    str += expr->to_json().dump();
					reportDefect(module, str, false, line);
					return -1;
				}
			}
			else
				return -1;
		case ExprType::COND:
			op0_len = exprCheck(module, expr->get_operand(0), line);
			op1_len = exprCheck(module, expr->get_operand(1), line);
			op2_len = exprCheck(module, expr->get_operand(2), line);
			if(op0_len != -1 && op1_len != -1 && op2_len != -1)
			{
				if(op0_len == 1 && op1_len == op2_len)
					return op1_len;
				else
				{
                    str += "type mismatch in ";
                    str += expr->to_json().dump();
					reportDefect(module, str, false, line);
					return -1;
				}
			}
			else
				return -1;
		case ExprType::SUBVEC:
			op1_len = exprCheck(module, expr->get_operand(1), line);
			op2_len = exprCheck(module, expr->get_operand(2), line);
			if(op1_len != -1 && op2_len != -1)
			{
				if(op1_len != op2_len)
				{
                    str += "type mismatch in ";
                    str += expr->to_json().dump();
					reportDefect(module, str, false, line);
				}
			} else{}
			if(expr->get_operand(1)->type() == ExprType::CONSTANT && expr->get_operand(2)->type() == ExprType::CONSTANT)
			{
				int constant1 = expr->get_operand(1)->as_constant()->value();
				int constant2 = expr->get_operand(2)->as_constant()->value();
				if(constant1 > constant2)
					return constant1 - constant2 + 1;
				else
					return constant2 - constant1 + 1;
			}
			else
				return -1;
		case ExprType::CONCAT:

			op0_len = exprCheck(module, expr->get_operand(0), line);
			op1_len = exprCheck(module, expr->get_operand(1), line);
			return op0_len + op1_len;
		case ExprType::REDUCE_BOOL:
			return 1;
		default:
			std::cout << to_string(expr->type()) << " not supported in exprCheck, currently\n";
			return -1;
	}
}

void typeCheck(std::shared_ptr<afbd::Module> module)
{
	for(auto process: *(module->procs()))
	{
		auto instructions = process->all_instructions();
		for(auto instruction: instructions)
		{
			auto expr = instruction->expr();
			auto dst = instruction->dst();
			if(expr)
			{
				int expr_len = exprCheck(module, expr, instruction->line());
				if(expr_len != -1 && dst && dst->type() == ExprType::VAR)
				{
					int dst_len = dst->as_var()->bit();
					if(dst_len != expr_len)
					{
						std::string str = "type mismatch in assign ";
                        str += expr->to_json().dump();
                        str += " to ";
                        str += dst->to_json().dump();
						reportDefect(module, str, false, instruction->line());
					}
				}
			}

			for(auto succ : *(instruction->succs()))
				exprCheck(module, succ.second, instruction->line());
		}
	}
}

void passCheck(std::shared_ptr<afbd::Module> module)
{
	for(auto process: *(module->procs()))
	{
		auto instructions = process->all_instructions();

		for(auto instruction: instructions)
		{
			if(instruction->succs()->size() <= 1)
				continue;

            for(int succ_id = 0; succ_id < instruction->succs()->size(); succ_id++)
            {
                auto succ = (*instruction->succs())[succ_id];
                if (succ.first->pred_num() > 1) {
                    std::string str = "case ";
                    str += std::to_string(succ_id);
                    str += " of a if/case statement does nothing";
                    reportDefect(module, str, false, instruction->line());
                }
            }

		}
	}
}

void blockCheck(std::shared_ptr<afbd::Module> module)
{
	for(auto process: *(module->procs()))
	{
		bool is_temporal = false;
		auto begin = process->begin();
		if(begin->type() == InstructionType::Trigger)
		{
			for(auto trigger: *(begin->triggers()))
				if(trigger.second != Edge::EDGE)
				{
					is_temporal = true;
					break;
				}
		}

		bool is_blocking;

		auto instructions = process->all_instructions();
		for(auto instruction: instructions)
		{
			if(instruction->type() == InstructionType::Assign && instruction->dst())
			{
				is_blocking = (instruction->assign_type() == AssignType::Blocking);
				break;
			}
		}

		if(is_blocking == is_temporal)
		{
			std::string str;
			if(is_blocking)
				str += "a process is blocking and temporal ";
			else
				str += "a process is non-blocking and combinational ";
            reportDefect(module, str, false, begin->line());
		}

	}
}