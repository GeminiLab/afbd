#pragma once

#include <map>

#include <memory>
#include <vector>
#include <bitset>

#include "yosys/include/yosys.h"
#include "yosys/include/yosys_rtlil.h"
#include "yosys/include/ast.h"

#include "rtlil/module.h"
#include "rtlil/expr.h"
#include "rtlil/var.h"
#include "rtlil/instruction.h"

#include "libs/json11/json11.hpp"

USING_YOSYS_NAMESPACE

namespace afbd
{
	typedef std::pair<std::shared_ptr<Expr>, std::shared_ptr<Expr>> ExprPair;

	struct RTLILPass : public Pass
	{
		RTLILPass() : Pass("RTLILPass") { }

		std::map<std::string, std::shared_ptr<Module>> str2module;
		std::vector<std::shared_ptr<Module>> unfolded_modules;
		std::map<std::shared_ptr<Module>, int> module_occurence;

		std::shared_ptr<Expr> parse_identifier(AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr);
		std::shared_ptr<Expr> parse_constant(AST::AstNode* astnode);
		ExprPair parse_range(AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr);
		std::shared_ptr<Expr> parse_expr(AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr);
		std::shared_ptr<Instruction> parse_block(std::shared_ptr<Instruction> begin, std::shared_ptr<Instruction> end, AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr, std::shared_ptr<Expr> cond);
		std::shared_ptr<Instruction> parse_assign(std::shared_ptr<Instruction> begin, std::shared_ptr<Instruction> end, AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr, std::shared_ptr<Expr> cond);
		std::shared_ptr<Instruction> parse_case(std::shared_ptr<Instruction> begin, std::shared_ptr<Instruction> end, AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr, std::shared_ptr<Expr> cond);
		std::shared_ptr<Instruction> parse_statement(std::shared_ptr<Instruction> begin, std::shared_ptr<Instruction> end, AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr, std::shared_ptr<Expr> cond);

        void execute(vector<string> args, RTLIL::Design* design) override;

		void execute_cell(std::shared_ptr<Module>& curr, std::shared_ptr<std::vector<std::shared_ptr<Expr>>>& cell_vector);

        std::shared_ptr<Module> res;
	};
}