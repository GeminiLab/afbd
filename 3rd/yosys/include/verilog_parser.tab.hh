/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_FRONTEND_VERILOG_YY_FRONTENDS_VERILOG_VERILOG_PARSER_TAB_HH_INCLUDED
# define YY_FRONTEND_VERILOG_YY_FRONTENDS_VERILOG_VERILOG_PARSER_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef FRONTEND_VERILOG_YYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define FRONTEND_VERILOG_YYDEBUG 1
#  else
#   define FRONTEND_VERILOG_YYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define FRONTEND_VERILOG_YYDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined FRONTEND_VERILOG_YYDEBUG */
#if FRONTEND_VERILOG_YYDEBUG
extern int frontend_verilog_yydebug;
#endif
/* "%code requires" blocks.  */
#line 150 "frontends/verilog/verilog_parser.y" /* yacc.c:1909  */

#include <map>
#include <string>
#include "verilog_frontend.h"

#line 58 "frontends/verilog/verilog_parser.tab.hh" /* yacc.c:1909  */

/* Token type.  */
#ifndef FRONTEND_VERILOG_YYTOKENTYPE
# define FRONTEND_VERILOG_YYTOKENTYPE
  enum frontend_verilog_yytokentype
  {
    TOK_STRING = 258,
    TOK_ID = 259,
    TOK_CONSTVAL = 260,
    TOK_REALVAL = 261,
    TOK_PRIMITIVE = 262,
    TOK_SVA_LABEL = 263,
    TOK_SPECIFY_OPER = 264,
    TOK_MSG_TASKS = 265,
    TOK_ASSERT = 266,
    TOK_ASSUME = 267,
    TOK_RESTRICT = 268,
    TOK_COVER = 269,
    TOK_FINAL = 270,
    ATTR_BEGIN = 271,
    ATTR_END = 272,
    DEFATTR_BEGIN = 273,
    DEFATTR_END = 274,
    TOK_MODULE = 275,
    TOK_ENDMODULE = 276,
    TOK_PARAMETER = 277,
    TOK_LOCALPARAM = 278,
    TOK_DEFPARAM = 279,
    TOK_PACKAGE = 280,
    TOK_ENDPACKAGE = 281,
    TOK_PACKAGESEP = 282,
    TOK_INTERFACE = 283,
    TOK_ENDINTERFACE = 284,
    TOK_MODPORT = 285,
    TOK_VAR = 286,
    TOK_WILDCARD_CONNECT = 287,
    TOK_INPUT = 288,
    TOK_OUTPUT = 289,
    TOK_INOUT = 290,
    TOK_WIRE = 291,
    TOK_WAND = 292,
    TOK_WOR = 293,
    TOK_REG = 294,
    TOK_LOGIC = 295,
    TOK_INTEGER = 296,
    TOK_SIGNED = 297,
    TOK_ASSIGN = 298,
    TOK_ALWAYS = 299,
    TOK_INITIAL = 300,
    TOK_ALWAYS_FF = 301,
    TOK_ALWAYS_COMB = 302,
    TOK_ALWAYS_LATCH = 303,
    TOK_BEGIN = 304,
    TOK_END = 305,
    TOK_IF = 306,
    TOK_ELSE = 307,
    TOK_FOR = 308,
    TOK_WHILE = 309,
    TOK_REPEAT = 310,
    TOK_DPI_FUNCTION = 311,
    TOK_POSEDGE = 312,
    TOK_NEGEDGE = 313,
    TOK_OR = 314,
    TOK_AUTOMATIC = 315,
    TOK_CASE = 316,
    TOK_CASEX = 317,
    TOK_CASEZ = 318,
    TOK_ENDCASE = 319,
    TOK_DEFAULT = 320,
    TOK_FUNCTION = 321,
    TOK_ENDFUNCTION = 322,
    TOK_TASK = 323,
    TOK_ENDTASK = 324,
    TOK_SPECIFY = 325,
    TOK_IGNORED_SPECIFY = 326,
    TOK_ENDSPECIFY = 327,
    TOK_SPECPARAM = 328,
    TOK_SPECIFY_AND = 329,
    TOK_IGNORED_SPECIFY_AND = 330,
    TOK_GENERATE = 331,
    TOK_ENDGENERATE = 332,
    TOK_GENVAR = 333,
    TOK_REAL = 334,
    TOK_SYNOPSYS_FULL_CASE = 335,
    TOK_SYNOPSYS_PARALLEL_CASE = 336,
    TOK_SUPPLY0 = 337,
    TOK_SUPPLY1 = 338,
    TOK_TO_SIGNED = 339,
    TOK_TO_UNSIGNED = 340,
    TOK_POS_INDEXED = 341,
    TOK_NEG_INDEXED = 342,
    TOK_PROPERTY = 343,
    TOK_ENUM = 344,
    TOK_TYPEDEF = 345,
    TOK_RAND = 346,
    TOK_CONST = 347,
    TOK_CHECKER = 348,
    TOK_ENDCHECKER = 349,
    TOK_EVENTUALLY = 350,
    TOK_INCREMENT = 351,
    TOK_DECREMENT = 352,
    TOK_UNIQUE = 353,
    TOK_PRIORITY = 354,
    OP_LOR = 355,
    OP_LAND = 356,
    OP_NOR = 357,
    OP_XNOR = 358,
    OP_NAND = 359,
    OP_EQ = 360,
    OP_NE = 361,
    OP_EQX = 362,
    OP_NEX = 363,
    OP_LE = 364,
    OP_GE = 365,
    OP_SHL = 366,
    OP_SHR = 367,
    OP_SSHL = 368,
    OP_SSHR = 369,
    OP_POW = 370,
    UNARY_OPS = 371,
    FAKE_THEN = 372
  };
#endif

/* Value type.  */
#if ! defined FRONTEND_VERILOG_YYSTYPE && ! defined FRONTEND_VERILOG_YYSTYPE_IS_DECLARED
typedef union FRONTEND_VERILOG_YYSTYPE FRONTEND_VERILOG_YYSTYPE;
union FRONTEND_VERILOG_YYSTYPE
{
#line 156 "frontends/verilog/verilog_parser.y" /* yacc.c:1909  */

	std::string *string;
	struct YOSYS_NAMESPACE_PREFIX AST::AstNode *ast;
	std::map<std::string, YOSYS_NAMESPACE_PREFIX AST::AstNode*> *al;
	struct specify_target *specify_target_ptr;
	struct specify_triple *specify_triple_ptr;
	struct specify_rise_fall *specify_rise_fall_ptr;
	bool boolean;
	char ch;

#line 199 "frontends/verilog/verilog_parser.tab.hh" /* yacc.c:1909  */
};
# define FRONTEND_VERILOG_YYSTYPE_IS_TRIVIAL 1
# define FRONTEND_VERILOG_YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined FRONTEND_VERILOG_YYLTYPE && ! defined FRONTEND_VERILOG_YYLTYPE_IS_DECLARED
typedef struct FRONTEND_VERILOG_YYLTYPE FRONTEND_VERILOG_YYLTYPE;
struct FRONTEND_VERILOG_YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define FRONTEND_VERILOG_YYLTYPE_IS_DECLARED 1
# define FRONTEND_VERILOG_YYLTYPE_IS_TRIVIAL 1
#endif



int frontend_verilog_yyparse (void);

#endif /* !YY_FRONTEND_VERILOG_YY_FRONTENDS_VERILOG_VERILOG_PARSER_TAB_HH_INCLUDED  */
