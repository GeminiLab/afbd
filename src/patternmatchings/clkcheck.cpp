#include "../../include/rtlil/patternmatching.h"

class ClkCheck : public PatternMatching
{
public:
	ClkCheck() : PatternMatching("ClkCheck") {}

	void checkExpr(std::shared_ptr<afbd::Instruction> instruction, std::shared_ptr<afbd::Expr> expr)
	{
		if(expr->type() == afbd::EXPR_VAR || expr->type() == afbd::EXPR_CONSTANT)
		{
			return;
		}
		if(expr->type() == afbd::EXPR_NOT && expr->get_operand(0)->type() == afbd::EXPR_VAR)
		{
			auto name = expr->get_operand(0)->as_var()->name();
			if(name.find("clk") != std::string::npos)
			{
				reportWarning("In instruction " + instruction->to_json().dump() + ", " + expr->to_json().dump() + "negates a clk");
			}
			return;
		}
		for(int i = 0; i < expr->operand_num(); i++)
			checkExpr(instruction, expr->get_operand(i));
	}

	void match(std::shared_ptr<afbd::Module> module)
	{
		for(auto process : (*module->procs()))
		{
			auto all_instructions = process->all_instructions();
			for(auto instruction : all_instructions)
			{
				auto expr = instruction->expr();
				checkExpr(instruction, expr);
			}
		}
	}
};

extern "C" PatternMatching* create()
{
	return new ClkCheck;
}