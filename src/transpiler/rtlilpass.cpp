#include <map>

#include <memory>
#include <vector>
#include <bitset>

#include "yosys/include/yosys.h"
#include "transpiler/rtlilpass.h"
#include "libs/json11/json11.hpp"

#include "yosys/include/yosys_rtlil.h"
#include "yosys/include/ast.h"

#include "rtlil/module.h"
#include "rtlil/expr.h"
#include "rtlil/var.h"
#include "rtlil/instruction.h"
#include "rtlil/patternmatching.h"

#ifdef linux
#include <dlfcn.h>
#endif //linux

USING_YOSYS_NAMESPACE

namespace afbd
{
	extern std::shared_ptr<Expr> expr_true;
	extern std::shared_ptr<Expr> expr_int_zero;
	extern std::shared_ptr<Expr> expr_default;

	std::shared_ptr<Expr> RTLILPass::parse_identifier(AST::AstNode * astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr)
	{
		std::string identifier = astnode->str;
		auto identifierExpr = str2expr[identifier];

		if(astnode->children.empty())
			return identifierExpr;
		else
		{
			std::shared_ptr<Expr> singleExpr;
			std::shared_ptr<Expr> doubleExprLeft;
			std::shared_ptr<Expr> doubleExprRight;

			std::shared_ptr<Expr> elemBit;
			if(identifierExpr->type() == ExprType::VAR)
				elemBit = std::make_shared<Expr>(std::make_shared<Constant>(32, identifierExpr->as_var()->elem_bit()));
			else
				elemBit = std::make_shared<Expr>(std::make_shared<Constant>(32, identifierExpr->as_constant()->bit()));

			for(auto child : astnode->children)
			{
				if(child->type != AST::AST_RANGE)
				{
					std::cout << "found a non-AST_RANGE node under AST_IDENTIFIER!\n";
					continue;
				}
				
				auto range = parse_range(child, str2expr);
				if(range.second)
				{
					doubleExprLeft = range.first;
					doubleExprRight = range.second;
				}
				else
				{
					singleExpr = range.first;
				}
			}

			if(!singleExpr)
			{
				singleExpr = expr_int_zero;
			}
			if(!doubleExprLeft)
			{
				doubleExprLeft = std::make_shared<Expr>(std::make_shared<Constant>(32, identifierExpr->as_var()->elem_bit() - 1));
				doubleExprRight = expr_int_zero;
			}

			auto ret = std::make_shared<Expr>(ExprType::SUBVEC, exl{});
			ret->add_operand(identifierExpr);

			std::shared_ptr<Expr> offset = std::make_shared<Expr>(ExprType::MUL, exl{singleExpr, elemBit});
			std::shared_ptr<Expr> leftBound = std::make_shared<Expr>(ExprType::ADD, exl{offset, doubleExprLeft});
			std::shared_ptr<Expr> rightBound = std::make_shared<Expr>(ExprType::ADD, exl{offset, doubleExprRight});

			ret->add_operand(leftBound);
			ret->add_operand(rightBound);
			ret->simplify();
			return ret;
		}
	}

	std::shared_ptr<Expr> RTLILPass::parse_constant(AST::AstNode* astnode)
	{
		int bits = astnode->range_left - astnode->range_right + 1;
		unsigned long long value = astnode->asInt(false);
		auto constant = std::make_shared<Constant>(bits, value);
		return std::make_shared<Expr>(constant);
	}

	ExprPair RTLILPass::parse_range(AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr)
	{
		if(astnode->children.size() < 2)
			return std::make_pair(parse_expr(astnode->children[0], str2expr), nullptr);
		else
			return std::make_pair(parse_expr(astnode->children[0], str2expr), parse_expr(astnode->children[1], str2expr));
	}

	std::shared_ptr<Expr> RTLILPass::parse_expr(AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr)
	{
		ExprType type;
		switch(astnode->type)
		{
		case AST::AST_IDENTIFIER:
		{
			return parse_identifier(astnode, str2expr);
		}
		case AST::AST_CONSTANT:
		{
			return parse_constant(astnode);
		}
		case AST::AST_ADD:
			type = ExprType::ADD;
			break;
		case AST::AST_SUB:
			type = ExprType::SUB;
			break;
		case AST::AST_MUL:
			type = ExprType::MUL;
			break;
		case AST::AST_DIV:
			type = ExprType::DIV;
			break;
		case AST::AST_MOD:
			type = ExprType::MOD;
			break;
		case AST::AST_LOGIC_AND:
		case AST::AST_BIT_AND:
			type = ExprType::AND;
			break;
		case AST::AST_LOGIC_OR:
		case AST::AST_BIT_OR:
			type = ExprType::OR;
			break;
		case AST::AST_LOGIC_NOT:
		case AST::AST_BIT_NOT:
			type = ExprType::NOT;
			break;
		case AST::AST_BIT_XOR:
			type = ExprType::XOR;
			break;
		case AST::AST_CONCAT:
			type = ExprType::CONCAT;
			break;
		case AST::AST_EQ:
			type = ExprType::EQ;
			break;
		case AST::AST_NE:
			type = ExprType::NE;
			break;
		case AST::AST_GT:
			type = ExprType::GT;
			break;
		case AST::AST_GE:
			type = ExprType::GE;
			break;
		case AST::AST_LT:
			type = ExprType::LT;
			break;
		case AST::AST_LE:
			type = ExprType::LE;
			break;
		case AST::AST_REDUCE_BOOL:
			type = ExprType::REDUCE_BOOL;
			break;
		default:
			type = ExprType::UNKNOWN;
			std::cout << AST::type2str(astnode->type) << " is not supported, currently.\n";
		}
		auto expr = std::make_shared<Expr>(type, exl{});
		for(auto child : astnode->children)
		{
			expr->add_operand(parse_expr(child, str2expr));
		}
		return expr;
	}

	std::shared_ptr<Instruction> RTLILPass::parse_block(std::shared_ptr<Instruction> begin, AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr, std::shared_ptr<Expr> cond)
	{
		auto curr = begin;
		for(auto child : astnode->children)
		{
			curr = parse_statement(curr, child, str2expr, cond);
			cond = expr_true;
		}
		return curr;
	}

	std::shared_ptr<Instruction> RTLILPass::parse_assign(std::shared_ptr<Instruction> begin, AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr, std::shared_ptr<Expr> cond, bool is_blocking)
	{
		auto inst = std::make_shared<Instruction>(begin->process());

		if(!begin)
			std::cout << "shit!begin is nullptr\n";

		begin->add_succ(inst, cond);

		inst->dst(parse_identifier(astnode->children[0], str2expr));
		inst->expr(parse_expr(astnode->children[1], str2expr));
		inst->assign_type(is_blocking ? AssignType::Blocking : AssignType::NonBlocking);

		return inst;
	}

	std::shared_ptr<Instruction> RTLILPass::parse_case(std::shared_ptr<Instruction> begin, AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr, std::shared_ptr<Expr> cond)
	{
		auto leftExpr = parse_expr(astnode->children[0], str2expr);

		auto this_begin = std::make_shared<Instruction>(begin->process());
		auto this_end = std::make_shared<Instruction>(begin->process());

		begin->add_succ(this_begin, cond);

		bool has_default = false;
		int cond_num = 0;

		for(int i = 1; i < astnode->children.size(); i++)
		{
			auto child = astnode->children[i];
			if(child->type != AST::AST_COND)
			{
				std::cout << "assertion failed! not an AST_COND\n";
			}

			std::shared_ptr<Expr> new_cond;
			auto cond_node = child->children[0];

			if(cond_node->type == AST::AST_DEFAULT)
			{
				new_cond = expr_default;
				has_default = true;
			}
			else if(cond_node->type == AST::AST_CONSTANT)
			{
				auto cond_const = parse_constant(cond_node);
				new_cond = std::make_shared<Expr>(ExprType::EQ, exl{leftExpr, cond_const});
				cond_num++;
			}
			else
			{
				std::cout << "assertion failed! cond not an AST_CONSTANT\n";
			}

			auto block_node = child->children[1];
			auto block = parse_block(this_begin, block_node, str2expr, new_cond);
			block->add_succ(this_end, expr_true);
		}

		if(!has_default && cond_num < (1 << leftExpr->bit()))
			this_begin->add_succ(this_end, expr_default);

		return this_end;
	}

	std::shared_ptr<Instruction> RTLILPass::parse_statement(std::shared_ptr<Instruction> begin, AST::AstNode* astnode, std::map<std::string, std::shared_ptr<Expr>>& str2expr, std::shared_ptr<Expr> cond)
	{
		switch(astnode->type)
		{
		case AST::AST_BLOCK:
			return parse_block(begin, astnode, str2expr, cond);
		case AST::AST_ASSIGN_LE:
			return parse_assign(begin, astnode, str2expr, cond, false);
		case AST::AST_ASSIGN:
		case AST::AST_ASSIGN_EQ:
			return parse_assign(begin, astnode, str2expr, cond, true);
		case AST::AST_CASE:
			return parse_case(begin, astnode, str2expr, cond);
		default:
			std::cout << AST::type2str(astnode->type) << " is not supported as a statement, currently.\n";
			return begin;
		}
	}

	void RTLILPass::execute(vector<string> args, RTLIL::Design* design)
	{
		std::cout << "Hello World!\n";

		auto current_modules = design->modules();
		for(auto current_module : current_modules)
		{
			AST::AstNode* current_ast = ((AST::AstModule*)(current_module))->ast;

			current_ast->dumpAst(stdout, "    ");

			std::string name = current_module->name.c_str();
			std::cout << name << "\n";

			std::shared_ptr<Module> myModule = std::make_shared<Module>(name);
			str2module[name] = myModule;

			std::map<std::string, std::shared_ptr<Expr>> str2expr;

			int temp_var_num = 0;

			for(auto child : current_ast->children)
			{
				switch(child->type)
				{
				case AST::AST_WIRE:
				{
					int bits = 1;
					for(auto range: child->children)
					{
						if(range->type != AST::AST_RANGE)
						{
							continue;
						}
						auto bounds = parse_range(range, str2expr);
						bounds.first->simplify();
						bounds.second->simplify();
						if(bounds.first->type() != ExprType::CONSTANT || bounds.second->type() != ExprType::CONSTANT)
						{
							std::cout << "error: bounds of range are not AST_CONSTANT.\n";
							std::cout << bounds.first->to_json().dump() << "\n" << bounds.second->to_json().dump() << "\n";
							std::exit(0);
						}
						bits = bounds.first->as_constant()->value() - bounds.second->as_constant()->value() + 1;
					}
					std::string wire_name = child->str;
					str2expr[wire_name] = std::make_shared<Expr>(myModule->add_var(bits, wire_name));
					break;
				}
				case AST::AST_PARAMETER:
				case AST::AST_LOCALPARAM:
				{
					std::string wire_name = child->str;
					std::shared_ptr<Expr> param_expr;
					int bits = 1;
					for(auto& grandchild : child->children)
					{
						if(grandchild->type == AST::AST_RANGE)
						{
							auto bounds = parse_range(grandchild, str2expr);
							bounds.first->simplify();
							bounds.second->simplify();
							if(bounds.first->type() != ExprType::CONSTANT || bounds.second->type() != ExprType::CONSTANT)
							{
								std::cout << "error: bounds of range are not AST_CONSTANT.\n";
								std::cout << bounds.first->to_json().dump() << "\n" << bounds.second->to_json().dump() << "\n";
								std::exit(0);
							}
							bits = bounds.first->as_constant()->value() - bounds.second->as_constant()->value() + 1;
						}
						else
						{
							param_expr = parse_expr(grandchild, str2expr);
							param_expr->simplify();
							if(param_expr->type() != ExprType::CONSTANT)
							{
								std::cout << "error! param is not a constant\n";
								std::exit(0);
							}
						}
					}
					param_expr->as_constant()->bit(bits);
					str2expr[wire_name] = param_expr;
					break;
				}
				case AST::AST_MEMORY:
				{
					auto range = child->children[0];
					if(range->type != AST::AST_RANGE)
					{
						std::cout << "error: range not found.\n";
						std::exit(0);
					}
					auto bounds = parse_range(range, str2expr);
					bounds.first->simplify();
					bounds.second->simplify();
					if(bounds.first->type() != ExprType::CONSTANT || bounds.second->type() != ExprType::CONSTANT)
					{
						std::cout << "error: bounds of range are not AST_CONSTANT.\n";
						std::exit(0);
					}
					int arraySize = bounds.first->as_constant()->value() - bounds.second->as_constant()->value() + 1;

					int bits;
					if(child->children.size() < 2)
					{
						bits = 1;
					}
					else
					{
						auto range = child->children[1];
						if(range->type != AST::AST_RANGE)
						{
							std::cout << "error: range not found.\n";
							std::exit(0);
						}
						auto bounds = parse_range(range, str2expr);
						bounds.first->simplify();
						bounds.second->simplify();
						if(bounds.first->type() != ExprType::CONSTANT || bounds.second->type() != ExprType::CONSTANT)
						{
							std::cout << "error: bounds of range are not AST_CONSTANT.\n";
							std::exit(0);
						}
						bits = bounds.first->as_constant()->value() - bounds.second->as_constant()->value() + 1;
					}
					std::string wire_name = child->str;
					str2expr[wire_name] = std::make_shared<Expr>(myModule->add_var(bits * arraySize, wire_name, bits));

					break;
				}
				case AST::AST_ALWAYS:
				{
					auto myProc = myModule->add_proc();
					auto triggers = std::make_shared<TriggerContainer>();
					auto begin = std::make_shared<Instruction>(myProc);
					begin->triggers(triggers);
					myProc->begin(begin);

					for(auto grandchild : child->children)
					{
						if(grandchild->type == AST::AST_EDGE || grandchild->type == AST::AST_POSEDGE || grandchild->type == AST::AST_NEGEDGE)
						{
							std::string identifier = grandchild->children[0]->str;
							auto identifierExpr = str2expr[identifier];

							if(identifierExpr->type() != ExprType::VAR)
							{
								std::cout << "error! edge is not a var\n";
								std::exit(0);
							}

							auto identifierVar = identifierExpr->as_var();
							myModule->add_triggered_proc(identifierVar, myProc);
							
							Trigger sensitive_var;
							sensitive_var.first = identifierVar;
							switch(grandchild->type)
							{
							case AST::AST_EDGE:
								sensitive_var.second = Edge::EDGE;
								break;
							case AST::AST_POSEDGE:
								sensitive_var.second = Edge::POSEDGE;
								break;
							case AST::AST_NEGEDGE:
								sensitive_var.second = Edge::NEGEDGE;
								break;
							}
							// TODO:
							triggers->push_back(sensitive_var);
						}
						if(grandchild->type == AST::AST_BLOCK)
						{
							parse_block(myProc->begin(), grandchild, str2expr, expr_true);
						}
					}
					break;
				}
				case AST::AST_CELL:
				{
					std::string cellname;
					auto cell_vector = std::make_shared<std::vector<std::shared_ptr<Expr>>>();
					for(auto& grandchild : child->children)
					{
						if(grandchild->type == AST::AST_CELLTYPE)
							cellname = grandchild->str;//cellname = no_slash(grandchild->str);
						if(grandchild->type == AST::AST_ARGUMENT)
						{
							auto expr = parse_expr(grandchild->children[0], str2expr);
							if(expr->type() != ExprType::VAR && expr->type() != ExprType::CONSTANT)
							{
								//generate new temp var

								std::string wire_name = "$temp_var_" + std::to_string(temp_var_num);
								temp_var_num++;

								auto temp_var = myModule->add_var(expr->bit(), wire_name);
								str2expr[wire_name] = std::make_shared<Expr>(temp_var);
								cell_vector->push_back(std::make_shared<Expr>(temp_var));

								auto dst_expr = std::make_shared<Expr>(ExprType::VAR, exl{});
								dst_expr->add_operand(std::make_shared<Expr>(temp_var));

								auto myProc = myModule->add_proc();
								auto inst = std::make_shared<Instruction>(myProc);
								myProc->begin()->add_succ(inst, expr_true);
								inst->dst(dst_expr);
								inst->expr(expr);

								expr->all_as_sens(myModule, myProc);

							}
							else
								cell_vector->push_back(expr);
						}
					}
					myModule->cells.push_back(std::make_pair(cellname, cell_vector));
					//std::cout << myModule->name() << "has a new cell " << cellname << "\n";
					//std::cout << myModule->name() << "has a new cell " << str2module[cellname]->name() << "\n";
					break;
				}
				case AST::AST_ASSIGN:
				{
					auto myProc = myModule->add_proc();

					auto inst = parse_assign(myProc->begin(), child, str2expr, expr_true, true);

					inst->expr()->all_as_sens(myModule, myProc);
					break;
				}
				default:
					std::cout << AST::type2str(child->type) << "is not supported in a module, currently.\n";
				}
			}
		}

		//for(auto& mpair : str2module)
		//{
		//	std::cout << mpair.second->to_json().dump() << "\n";
		//}

		if(args.size() < 3)
		{
			std::cout << "No top module\n";
			return;
		}

		std::string top_module_name = "\\" + args[2];

		std::shared_ptr<Module> top_module = str2module[top_module_name];

		std::cout << "top module is " << top_module->name() << "\n";

		auto empty_vector = std::make_shared<std::vector<std::shared_ptr<Expr>>>();
		execute_cell(top_module, empty_vector);

		std::cout << "generate unfolded_modules ok\n";

		res = std::make_shared<Module>("");
		res->modules_in_one(unfolded_modules);

		std::cout << "generating json:\n" << res->to_json().dump() << "\n";

#ifdef linux
		std::cout << "It is linux! We can do PatternMatching!\n";

		std::vector<PatternMatching*> patterns;

		for(auto& arg : args)
		{
			if(arg.substr(arg.size() - 3) != ".so")
				continue;

			std::cout << arg << " is a so name!\n";
			void *so_handle = dlopen(arg£¬ RTLD_LAZY);
			if(so_handle == NULL)
			{
				std::cout << arg << " install failed...\n";
				continue;
			}

			PatternMatching* (*create)();
			create = dlsym(so_handle£¬ "create");
			if(dlerror() != NULL)
			{
				std::cout << dlerror() << "\n";
				dlclose(so_handle);
				continue;
			}

			patterns.push_back((*create)());
			dlclose(so_handle);
		}

		for(auto pattern : patterns)
		{
			pattern->match();
			delete pattern;
		}

#endif //linux
	}

	void RTLILPass::execute_cell(std::shared_ptr<Module>& curr, std::shared_ptr<std::vector<std::shared_ptr<Expr>>>& cell_vector)
	{
		std::map<std::shared_ptr<Var>, std::shared_ptr<Expr>> substitute_map;
		int occurence_id = module_occurence[curr];

		for(int i = 0; i < curr->vars()->size(); i++)
		{
			auto curr_var = (*curr->vars())[i];
			if(i < cell_vector->size())
			{
				substitute_map[curr_var] = (*cell_vector)[i];
			}
			else
			{
				std::string new_var_name = *(curr_var->name()) + "$" + std::to_string(occurence_id);
				auto new_var = std::make_shared<Var>(curr_var->bit(), new_var_name);
				substitute_map[curr_var] = std::make_shared<Expr>(new_var);
			}
		}

		unfolded_modules.push_back(curr->substitute_clone(substitute_map, occurence_id));

		module_occurence[curr]++;

		for(auto& cell : curr->cells)
		{
			auto& succ = str2module[cell.first];
			auto new_cell_vector = cell.second;

			auto new_cell_vector_substitute = std::make_shared<std::vector<std::shared_ptr<Expr>>>();

			//std::cout << "cell succ is " << succ->name() << "\n";

			for(auto& new_cell_elem : *new_cell_vector)
			{
				/*std::cout << to_string(new_cell_elem->type()) << " ";
				if(new_cell_elem->type() == EXPR_VAR)
					std::cout << new_cell_elem->as_var()->name() << " ";

				std::cout << " -> ";*/

				auto new_cell_elem_substitute = new_cell_elem->substitute_clone(substitute_map);
				new_cell_vector_substitute->push_back(new_cell_elem_substitute);

				/*std::cout << to_string(new_cell_elem_substitute->type()) << " ";
				if(new_cell_elem_substitute->type() == EXPR_VAR)
					std::cout << new_cell_elem_substitute->as_var()->name() << " ";

				std::cout << "\n";*/
			}

			execute_cell(succ, new_cell_vector_substitute);
		}
	}
}
