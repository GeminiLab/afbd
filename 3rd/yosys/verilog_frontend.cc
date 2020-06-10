/*
 *  yosys -- Yosys Open SYnthesis Suite
 *
 *  Copyright (C) 2012  Clifford Wolf <clifford@clifford.at>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *  ---
 *
 *  The Verilog frontend.
 *
 *  This frontend is using the AST frontend library (see frontends/ast/).
 *  Thus this frontend does not generate RTLIL code directly but creates an
 *  AST directly from the Verilog parse tree and then passes this AST to
 *  the AST frontend library.
 *
 */

#include "include/verilog_frontend.h"
#include "include/yosys.h"
#include "libs/sha1/sha1.h"
#include "include/register.h"
#include <stdarg.h>

YOSYS_NAMESPACE_BEGIN
using namespace VERILOG_FRONTEND;

// use the Verilog bison/flex parser to generate an AST and use AST::process() to convert it to RTLIL

static std::vector<std::string> verilog_defaults;
static std::list<std::vector<std::string>> verilog_defaults_stack;

static void error_on_dpi_function(AST::AstNode *node)
{
	if (node->type == AST::AST_DPI_FUNCTION)
		log_file_error(node->filename, node->location.first_line, "Found DPI function %s.\n", node->str.c_str());
	for (auto child : node->children)
		error_on_dpi_function(child);
}

void VerilogFrontend::execute(std::istream *&f, std::string filename, std::vector<std::string> args, RTLIL::Design *design) // YS_OVERRIDE
{
	bool flag_dump_ast1 = false;
	bool flag_dump_ast2 = false;
	bool flag_no_dump_ptr = false;
	bool flag_dump_vlog1 = false;
	bool flag_dump_vlog2 = false;
	bool flag_dump_rtlil = false;
	bool flag_nolatches = false;
	bool flag_nomeminit = false;
	bool flag_nomem2reg = false;
	bool flag_mem2reg = false;
	bool flag_ppdump = false;
	bool flag_nopp = false;
	bool flag_nodpi = false;
	bool flag_noopt = false;
	bool flag_icells = false;
	bool flag_pwires = false;
	bool flag_nooverwrite = false;
	bool flag_overwrite = false;
	bool flag_defer = false;
	bool flag_noblackbox = false;
	bool flag_nowb = false;
	std::map<std::string, std::string> defines_map;
	std::list<std::string> include_dirs;
	std::list<std::string> attributes;

	frontend_verilog_yydebug = false;
	sv_mode = false;
	formal_mode = false;
	norestrict_mode = false;
	assume_asserts_mode = false;
	lib_mode = false;
	specify_mode = false;
	default_nettype_wire = true;

	args.insert(args.begin() + 1, verilog_defaults.begin(), verilog_defaults.end());

	size_t argidx;
	for(argidx = 1; argidx < args.size(); argidx++) {
		std::string arg = args[argidx];
		if(arg == "-sv") {
			sv_mode = true;
			continue;
		}
		if(arg == "-formal") {
			formal_mode = true;
			continue;
		}
		if(arg == "-noassert") {
			noassert_mode = true;
			continue;
		}
		if(arg == "-noassume") {
			noassume_mode = true;
			continue;
		}
		if(arg == "-norestrict") {
			norestrict_mode = true;
			continue;
		}
		if(arg == "-assume-asserts") {
			assume_asserts_mode = true;
			continue;
		}
		if(arg == "-assert-assumes") {
			assert_assumes_mode = true;
			continue;
		}
		if(arg == "-debug") {
			flag_dump_ast1 = true;
			flag_dump_ast2 = true;
			flag_dump_vlog1 = true;
			flag_dump_vlog2 = true;
			frontend_verilog_yydebug = true;
			continue;
		}
		if(arg == "-dump_ast1") {
			flag_dump_ast1 = true;
			continue;
		}
		if(arg == "-dump_ast2") {
			flag_dump_ast2 = true;
			continue;
		}
		if(arg == "-no_dump_ptr") {
			flag_no_dump_ptr = true;
			continue;
		}
		if(arg == "-dump_vlog1") {
			flag_dump_vlog1 = true;
			continue;
		}
		if(arg == "-dump_vlog2") {
			flag_dump_vlog2 = true;
			continue;
		}
		if(arg == "-dump_rtlil") {
			flag_dump_rtlil = true;
			continue;
		}
		if(arg == "-yydebug") {
			frontend_verilog_yydebug = true;
			continue;
		}
		if(arg == "-nolatches") {
			flag_nolatches = true;
			continue;
		}
		if(arg == "-nomeminit") {
			flag_nomeminit = true;
			continue;
		}
		if(arg == "-nomem2reg") {
			flag_nomem2reg = true;
			continue;
		}
		if(arg == "-mem2reg") {
			flag_mem2reg = true;
			continue;
		}
		if(arg == "-ppdump") {
			flag_ppdump = true;
			continue;
		}
		if(arg == "-nopp") {
			flag_nopp = true;
			continue;
		}
		if(arg == "-nodpi") {
			flag_nodpi = true;
			continue;
		}
		if(arg == "-noblackbox") {
			flag_noblackbox = true;
			continue;
		}
		if(arg == "-lib") {
			lib_mode = true;
			defines_map["BLACKBOX"] = string();
			continue;
		}
		if(arg == "-nowb") {
			flag_nowb = true;
			continue;
		}
		if(arg == "-specify") {
			specify_mode = true;
			continue;
		}
		if(arg == "-noopt") {
			flag_noopt = true;
			continue;
		}
		if(arg == "-icells") {
			flag_icells = true;
			continue;
		}
		if(arg == "-pwires") {
			flag_pwires = true;
			continue;
		}
		if(arg == "-ignore_redef" || arg == "-nooverwrite") {
			flag_nooverwrite = true;
			flag_overwrite = false;
			continue;
		}
		if(arg == "-overwrite") {
			flag_nooverwrite = false;
			flag_overwrite = true;
			continue;
		}
		if(arg == "-defer") {
			flag_defer = true;
			continue;
		}
		if(arg == "-noautowire") {
			default_nettype_wire = false;
			continue;
		}
		if(arg == "-setattr" && argidx + 1 < args.size()) {
			attributes.push_back(RTLIL::escape_id(args[++argidx]));
			continue;
		}
		if(arg == "-D" && argidx + 1 < args.size()) {
			std::string name = args[++argidx], value;
			size_t equal = name.find('=');
			if(equal != std::string::npos) {
				value = name.substr(equal + 1);
				name = name.substr(0, equal);
			}
			defines_map[name] = value;
			continue;
		}
		if(arg.compare(0, 2, "-D") == 0) {
			size_t equal = arg.find('=', 2);
			std::string name = arg.substr(2, equal - 2);
			std::string value;
			if(equal != std::string::npos)
				value = arg.substr(equal + 1);
			defines_map[name] = value;
			continue;
		}
		if(arg == "-I" && argidx + 1 < args.size()) {
			include_dirs.push_back(args[++argidx]);
			continue;
		}
		if(arg.compare(0, 2, "-I") == 0) {
			include_dirs.push_back(arg.substr(2));
			continue;
		}
		break;
	}
	extra_args(f, filename, args, argidx);

	log_header(design, "Executing Verilog-2005 frontend: %s\n", filename.c_str());

	log("Parsing %s%s input from `%s' to AST representation.\n",
		formal_mode ? "formal " : "", sv_mode ? "SystemVerilog" : "Verilog", filename.c_str());

	AST::current_filename = filename;
	AST::set_line_num = &frontend_verilog_yyset_lineno;
	AST::get_line_num = &frontend_verilog_yyget_lineno;

	current_ast = new AST::AstNode(AST::AST_DESIGN);

	lexin = f;
	std::string code_after_preproc;

	if(!flag_nopp) {
		code_after_preproc = frontend_verilog_preproc(*f, filename, defines_map, design->verilog_defines, include_dirs);
		if(flag_ppdump)
			log("-- Verilog code after preprocessor --\n%s-- END OF DUMP --\n", code_after_preproc.c_str());
		lexin = new std::istringstream(code_after_preproc);
	}

	frontend_verilog_yyset_lineno(1);
	frontend_verilog_yyrestart(NULL);
	frontend_verilog_yyparse();
	frontend_verilog_yylex_destroy();

	for(auto &child : current_ast->children) {
		if(child->type == AST::AST_MODULE)
			for(auto &attr : attributes)
				if(child->attributes.count(attr) == 0)
					child->attributes[attr] = AST::AstNode::mkconst_int(1, false);
	}

	if(flag_nodpi)
		error_on_dpi_function(current_ast);

	AST::process(design, current_ast, flag_dump_ast1, flag_dump_ast2, flag_no_dump_ptr, flag_dump_vlog1, flag_dump_vlog2, flag_dump_rtlil, flag_nolatches,
				 flag_nomeminit, flag_nomem2reg, flag_mem2reg, flag_noblackbox, lib_mode, flag_nowb, flag_noopt, flag_icells, flag_pwires, flag_nooverwrite, flag_overwrite, flag_defer, default_nettype_wire);

	if(!flag_nopp)
		delete lexin;

	delete current_ast;
	current_ast = NULL;

	log("Successfully finished Verilog frontend.\n");
}

struct VerilogDefaults : public Pass {
	VerilogDefaults() : Pass("verilog_defaults", "set default options for read_verilog") { }
	void help() YS_OVERRIDE
	{
		//   |---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|
		log("\n");
		log("    verilog_defaults -add [options]\n");
		log("\n");
		log("Add the specified options to the list of default options to read_verilog.\n");
		log("\n");
		log("\n");
		log("    verilog_defaults -clear\n");
		log("\n");
		log("Clear the list of Verilog default options.\n");
		log("\n");
		log("\n");
		log("    verilog_defaults -push\n");
		log("    verilog_defaults -pop\n");
		log("\n");
		log("Push or pop the list of default options to a stack. Note that -push does\n");
		log("not imply -clear.\n");
		log("\n");
	}
	void execute(std::vector<std::string> args, RTLIL::Design*) YS_OVERRIDE
	{
		if (args.size() < 2)
			cmd_error(args, 1, "Missing argument.");

		if (args[1] == "-add") {
			verilog_defaults.insert(verilog_defaults.end(), args.begin()+2, args.end());
			return;
		}

		if (args.size() != 2)
			cmd_error(args, 2, "Extra argument.");

		if (args[1] == "-clear") {
			verilog_defaults.clear();
			return;
		}

		if (args[1] == "-push") {
			verilog_defaults_stack.push_back(verilog_defaults);
			return;
		}

		if (args[1] == "-pop") {
			if (verilog_defaults_stack.empty()) {
				verilog_defaults.clear();
			} else {
				verilog_defaults.swap(verilog_defaults_stack.back());
				verilog_defaults_stack.pop_back();
			}
			return;
		}
	}
} VerilogDefaults;

struct VerilogDefines : public Pass {
	VerilogDefines() : Pass("verilog_defines", "define and undefine verilog defines") { }
	void help() YS_OVERRIDE
	{
		//   |---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|---v---|
		log("\n");
		log("    verilog_defines [options]\n");
		log("\n");
		log("Define and undefine verilog preprocessor macros.\n");
		log("\n");
		log("    -Dname[=definition]\n");
		log("        define the preprocessor symbol 'name' and set its optional value\n");
		log("        'definition'\n");
		log("\n");
		log("    -Uname[=definition]\n");
		log("        undefine the preprocessor symbol 'name'\n");
		log("\n");
		log("    -reset\n");
		log("        clear list of defined preprocessor symbols\n");
		log("\n");
		log("    -list\n");
		log("        list currently defined preprocessor symbols\n");
		log("\n");
	}
	void execute(std::vector<std::string> args, RTLIL::Design *design) YS_OVERRIDE
	{
		size_t argidx;
		for (argidx = 1; argidx < args.size(); argidx++) {
			std::string arg = args[argidx];
			if (arg == "-D" && argidx+1 < args.size()) {
				std::string name = args[++argidx], value;
				size_t equal = name.find('=');
				if (equal != std::string::npos) {
					value = name.substr(equal+1);
					name = name.substr(0, equal);
				}
				design->verilog_defines[name] = std::pair<std::string, bool>(value, false);
				continue;
			}
			if (arg.compare(0, 2, "-D") == 0) {
				size_t equal = arg.find('=', 2);
				std::string name = arg.substr(2, equal-2);
				std::string value;
				if (equal != std::string::npos)
					value = arg.substr(equal+1);
				design->verilog_defines[name] = std::pair<std::string, bool>(value, false);
				continue;
			}
			if (arg == "-U" && argidx+1 < args.size()) {
				std::string name = args[++argidx];
				design->verilog_defines.erase(name);
				continue;
			}
			if (arg.compare(0, 2, "-U") == 0) {
				std::string name = arg.substr(2);
				design->verilog_defines.erase(name);
				continue;
			}
			if (arg == "-reset") {
				design->verilog_defines.clear();
				continue;
			}
			if (arg == "-list") {
				for (auto &it : design->verilog_defines) {
					log("`define %s%s %s\n", it.first.c_str(), it.second.second ? "()" : "", it.second.first.c_str());
				}
				continue;
			}
			break;
		}

		if (args.size() != argidx)
			cmd_error(args, argidx, "Extra argument.");
	}
} VerilogDefines;

YOSYS_NAMESPACE_END

// the yyerror function used by bison to report parser errors
void frontend_verilog_yyerror(char const *fmt, ...)
{
	va_list ap;
	char buffer[1024];
	char *p = buffer;
	va_start(ap, fmt);
	p += vsnprintf(p, buffer + sizeof(buffer) - p, fmt, ap);
	va_end(ap);
	p += snprintf(p, buffer + sizeof(buffer) - p, "\n");
	YOSYS_NAMESPACE_PREFIX log_file_error(YOSYS_NAMESPACE_PREFIX AST::current_filename, frontend_verilog_yyget_lineno(),
					      "%s", buffer);
	exit(1);
}
