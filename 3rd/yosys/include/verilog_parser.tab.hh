/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
    TOK_USELESS = 263,
    TOK_SVA_LABEL = 264,
    TOK_SPECIFY_OPER = 265,
    TOK_MSG_TASKS = 266,
    TOK_ASSERT = 267,
    TOK_ASSUME = 268,
    TOK_RESTRICT = 269,
    TOK_COVER = 270,
    TOK_FINAL = 271,
    ATTR_BEGIN = 272,
    ATTR_END = 273,
    DEFATTR_BEGIN = 274,
    DEFATTR_END = 275,
    TOK_MODULE = 276,
    TOK_ENDMODULE = 277,
    TOK_PARAMETER = 278,
    TOK_LOCALPARAM = 279,
    TOK_DEFPARAM = 280,
    TOK_PACKAGE = 281,
    TOK_ENDPACKAGE = 282,
    TOK_PACKAGESEP = 283,
    TOK_INTERFACE = 284,
    TOK_ENDINTERFACE = 285,
    TOK_MODPORT = 286,
    TOK_VAR = 287,
    TOK_WILDCARD_CONNECT = 288,
    TOK_INPUT = 289,
    TOK_OUTPUT = 290,
    TOK_INOUT = 291,
    TOK_WIRE = 292,
    TOK_WAND = 293,
    TOK_WOR = 294,
    TOK_REG = 295,
    TOK_LOGIC = 296,
    TOK_INTEGER = 297,
    TOK_SIGNED = 298,
    TOK_ASSIGN = 299,
    TOK_ALWAYS = 300,
    TOK_INITIAL = 301,
    TOK_ALWAYS_FF = 302,
    TOK_ALWAYS_COMB = 303,
    TOK_ALWAYS_LATCH = 304,
    TOK_BEGIN = 305,
    TOK_END = 306,
    TOK_IF = 307,
    TOK_ELSE = 308,
    TOK_FOR = 309,
    TOK_WHILE = 310,
    TOK_REPEAT = 311,
    TOK_DPI_FUNCTION = 312,
    TOK_POSEDGE = 313,
    TOK_NEGEDGE = 314,
    TOK_OR = 315,
    TOK_AUTOMATIC = 316,
    TOK_CASE = 317,
    TOK_CASEX = 318,
    TOK_CASEZ = 319,
    TOK_ENDCASE = 320,
    TOK_DEFAULT = 321,
    TOK_FUNCTION = 322,
    TOK_ENDFUNCTION = 323,
    TOK_TASK = 324,
    TOK_ENDTASK = 325,
    TOK_SPECIFY = 326,
    TOK_IGNORED_SPECIFY = 327,
    TOK_ENDSPECIFY = 328,
    TOK_SPECPARAM = 329,
    TOK_SPECIFY_AND = 330,
    TOK_IGNORED_SPECIFY_AND = 331,
    TOK_GENERATE = 332,
    TOK_ENDGENERATE = 333,
    TOK_GENVAR = 334,
    TOK_REAL = 335,
    TOK_SYNOPSYS_FULL_CASE = 336,
    TOK_SYNOPSYS_PARALLEL_CASE = 337,
    TOK_SUPPLY0 = 338,
    TOK_SUPPLY1 = 339,
    TOK_TO_SIGNED = 340,
    TOK_TO_UNSIGNED = 341,
    TOK_POS_INDEXED = 342,
    TOK_NEG_INDEXED = 343,
    TOK_PROPERTY = 344,
    TOK_ENUM = 345,
    TOK_TYPEDEF = 346,
    TOK_RAND = 347,
    TOK_CONST = 348,
    TOK_CHECKER = 349,
    TOK_ENDCHECKER = 350,
    TOK_EVENTUALLY = 351,
    TOK_INCREMENT = 352,
    TOK_DECREMENT = 353,
    TOK_UNIQUE = 354,
    TOK_PRIORITY = 355,
    OP_LOR = 356,
    OP_LAND = 357,
    OP_NOR = 358,
    OP_XNOR = 359,
    OP_NAND = 360,
    OP_EQ = 361,
    OP_NE = 362,
    OP_EQX = 363,
    OP_NEX = 364,
    OP_LE = 365,
    OP_GE = 366,
    OP_SHL = 367,
    OP_SHR = 368,
    OP_SSHL = 369,
    OP_SSHR = 370,
    OP_POW = 371,
    UNARY_OPS = 372,
    FAKE_THEN = 373
  };
#endif

/* Value type.  */
#if ! defined FRONTEND_VERILOG_YYSTYPE && ! defined FRONTEND_VERILOG_YYSTYPE_IS_DECLARED

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

#line 200 "frontends/verilog/verilog_parser.tab.hh" /* yacc.c:1909  */
};

typedef union FRONTEND_VERILOG_YYSTYPE FRONTEND_VERILOG_YYSTYPE;
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
