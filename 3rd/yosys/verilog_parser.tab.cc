/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         FRONTEND_VERILOG_YYSTYPE
#define YYLTYPE         FRONTEND_VERILOG_YYLTYPE
/* Substitute the variable and function names.  */
#define yyparse         frontend_verilog_yyparse
#define yylex           frontend_verilog_yylex
#define yyerror         frontend_verilog_yyerror
#define yydebug         frontend_verilog_yydebug
#define yynerrs         frontend_verilog_yynerrs


/* Copy the first part of user declarations.  */
#line 36 "frontends/verilog/verilog_parser.y" /* yacc.c:339  */

#include <list>
#include <stack>
#include <string.h>
#include "include/verilog_frontend.h"
#include "include/verilog_parser.tab.hh"
#include "include/log.h"

#define YYLEX_PARAM &yylval, &yylloc

USING_YOSYS_NAMESPACE
using namespace AST;
using namespace VERILOG_FRONTEND;

YOSYS_NAMESPACE_BEGIN
namespace VERILOG_FRONTEND {
	int port_counter;
	std::map<std::string, int> port_stubs;
	std::map<std::string, AstNode*> *attr_list, default_attr_list;
	std::stack<std::map<std::string, AstNode*> *> attr_list_stack;
	std::map<std::string, AstNode*> *albuf;
	std::vector<AstNode*> ast_stack;
	struct AstNode *astbuf1, *astbuf2, *astbuf3;
	struct AstNode *current_function_or_task;
	struct AstNode *current_ast, *current_ast_mod;
	int current_function_or_task_port_id;
	std::vector<char> case_type_stack;
	bool do_not_require_port_stubs;
	bool default_nettype_wire;
	bool sv_mode, formal_mode, lib_mode, specify_mode;
	bool noassert_mode, noassume_mode, norestrict_mode;
	bool assume_asserts_mode, assert_assumes_mode;
	bool current_wire_rand, current_wire_const;
	bool current_modport_input, current_modport_output;
	std::istream *lexin;
}
YOSYS_NAMESPACE_END

#define SET_AST_NODE_LOC(WHICH, BEGIN, END) \
    do { (WHICH)->location.first_line = (BEGIN).first_line; \
    (WHICH)->location.first_column = (BEGIN).first_column; \
    (WHICH)->location.last_line = (END).last_line; \
    (WHICH)->location.last_column = (END).last_column; } while(0)

#define SET_RULE_LOC(LHS, BEGIN, END) \
    do { (LHS).first_line = (BEGIN).first_line; \
    (LHS).first_column = (BEGIN).first_column; \
    (LHS).last_line = (END).last_line; \
    (LHS).last_column = (END).last_column; } while(0)

int frontend_verilog_yylex(YYSTYPE *yylval_param, YYLTYPE *yyloc_param);

static void append_attr(AstNode *ast, std::map<std::string, AstNode*> *al)
{
	for (auto &it : *al) {
		if (ast->attributes.count(it.first) > 0)
			delete ast->attributes[it.first];
		ast->attributes[it.first] = it.second;
	}
	delete al;
}

static void append_attr_clone(AstNode *ast, std::map<std::string, AstNode*> *al)
{
	for (auto &it : *al) {
		if (ast->attributes.count(it.first) > 0)
			delete ast->attributes[it.first];
		ast->attributes[it.first] = it.second->clone();
	}
}

static void free_attr(std::map<std::string, AstNode*> *al)
{
	for (auto &it : *al)
		delete it.second;
	delete al;
}

struct specify_target {
	char polarity_op;
	AstNode *dst, *dat;
};

struct specify_triple {
	AstNode *t_min, *t_avg, *t_max;
};

struct specify_rise_fall {
	specify_triple rise;
	specify_triple fall;
};

static AstNode *makeRange(int msb = 31, int lsb = 0, bool isSigned = true)
{
	auto range = new AstNode(AST_RANGE);
	range->children.push_back(AstNode::mkconst_int(msb, true));
	range->children.push_back(AstNode::mkconst_int(lsb, true));
	range->is_signed = isSigned;
	return range;
}

static void addRange(AstNode *parent, int msb = 31, int lsb = 0, bool isSigned = true)
{
	auto range = makeRange(msb, lsb, isSigned);
	parent->children.push_back(range);
}

#line 182 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "verilog_parser.tab.hh".  */
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
#line 150 "frontends/verilog/verilog_parser.y" /* yacc.c:355  */

#include <map>
#include <string>
#include "frontends/verilog/verilog_frontend.h"

#line 226 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:355  */

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
#line 156 "frontends/verilog/verilog_parser.y" /* yacc.c:355  */

	std::string *string;
	struct YOSYS_NAMESPACE_PREFIX AST::AstNode *ast;
	std::map<std::string, YOSYS_NAMESPACE_PREFIX AST::AstNode*> *al;
	struct specify_target *specify_target_ptr;
	struct specify_triple *specify_triple_ptr;
	struct specify_rise_fall *specify_rise_fall_ptr;
	bool boolean;
	char ch;

#line 367 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 395 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined FRONTEND_VERILOG_YYLTYPE_IS_TRIVIAL && FRONTEND_VERILOG_YYLTYPE_IS_TRIVIAL \
             && defined FRONTEND_VERILOG_YYSTYPE_IS_TRIVIAL && FRONTEND_VERILOG_YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2306

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  144
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  245
/* YYNRULES -- Number of rules.  */
#define YYNRULES  553
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1138

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   372

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   143,     2,   134,     2,   124,   106,     2,
     131,   132,   122,   120,   128,   121,   130,   123,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   135,   133,
     112,   129,   115,   141,   140,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   136,     2,   137,   104,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   138,   102,   139,   142,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   103,   105,   107,
     108,   109,   110,   111,   113,   114,   116,   117,   118,   119,
     125,   126,   127
};

#if FRONTEND_VERILOG_YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   227,   227,   227,   239,   240,   241,   242,   243,   244,
     245,   246,   246,   250,   250,   266,   268,   272,   279,   272,
     290,   290,   293,   294,   297,   303,   311,   314,   322,   332,
     335,   335,   357,   357,   357,   357,   360,   360,   362,   364,
     364,   370,   370,   376,   379,   379,   379,   382,   382,   385,
     385,   388,   404,   408,   408,   422,   427,   422,   437,   437,
     452,   457,   457,   470,   471,   475,   476,   479,   479,   499,
     499,   502,   502,   502,   502,   502,   502,   502,   503,   506,
     507,   508,   509,   510,   513,   513,   516,   516,   526,   527,
     528,   529,   536,   539,   542,   548,   550,   553,   556,   559,
     562,   565,   571,   578,   581,   584,   589,   594,   600,   606,
     612,   615,   621,   624,   629,   630,   633,   636,   644,   646,
     646,   650,   650,   650,   650,   650,   650,   650,   650,   650,
     650,   651,   652,   652,   652,   652,   652,   652,   655,   655,
     666,   666,   676,   676,   687,   687,   699,   699,   711,   711,
     735,   740,   746,   746,   750,   751,   752,   752,   756,   756,
     760,   763,   768,   768,   768,   772,   768,   780,   780,   783,
     783,   804,   807,   807,   813,   816,   816,   820,   903,   974,
     977,   982,   985,   990,   993,   998,  1004,  1010,  1016,  1024,
    1025,  1026,  1029,  1037,  1044,  1053,  1065,  1085,  1091,  1101,
    1102,  1105,  1106,  1109,  1112,  1113,  1117,  1118,  1124,  1127,
    1127,  1130,  1133,  1133,  1136,  1142,  1143,  1147,  1148,  1149,
    1153,  1154,  1158,  1158,  1161,  1162,  1163,  1166,  1167,  1168,
    1172,  1173,  1176,  1177,  1180,  1181,  1184,  1185,  1186,  1190,
    1194,  1197,  1200,  1201,  1202,  1205,  1206,  1207,  1214,  1217,
    1218,  1225,  1225,  1231,  1233,  1236,  1243,  1246,  1250,  1253,
    1262,  1263,  1270,  1270,  1279,  1279,  1288,  1288,  1291,  1309,
    1312,  1312,  1315,  1324,  1324,  1345,  1346,  1347,  1350,  1353,
    1354,  1358,  1359,  1363,  1377,  1378,  1382,  1383,  1386,  1397,
    1404,  1419,  1404,  1425,  1425,  1433,  1433,  1442,  1444,  1455,
    1455,  1458,  1500,  1528,  1581,  1584,  1584,  1587,  1594,  1631,
    1638,  1638,  1647,  1647,  1657,  1660,  1665,  1666,  1669,  1669,
    1678,  1678,  1690,  1691,  1694,  1695,  1695,  1701,  1701,  1704,
    1704,  1706,  1708,  1713,  1722,  1749,  1749,  1752,  1757,  1763,
    1771,  1778,  1787,  1794,  1797,  1802,  1805,  1810,  1817,  1810,
    1830,  1830,  1846,  1846,  1860,  1861,  1862,  1863,  1864,  1864,
    1868,  1869,  1870,  1873,  1878,  1883,  1890,  1893,  1898,  1901,
    1906,  1909,  1912,  1917,  1923,  1917,  1929,  1929,  1932,  1932,
    1935,  1936,  1939,  1949,  1949,  1952,  1964,  1976,  1988,  2000,
    2008,  2016,  2024,  2038,  2054,  2061,  2068,  2075,  2082,  2089,
    2100,  2113,  2117,  2121,  2125,  2132,  2132,  2132,  2132,  2132,
    2132,  2133,  2134,  2134,  2135,  2135,  2145,  2145,  2155,  2155,
    2171,  2176,  2178,  2171,  2187,  2187,  2201,  2201,  2215,  2226,
    2215,  2233,  2233,  2246,  2249,  2252,  2257,  2263,  2266,  2269,
    2274,  2278,  2281,  2285,  2285,  2289,  2289,  2300,  2303,  2303,
    2307,  2313,  2307,  2326,  2326,  2330,  2336,  2330,  2344,  2345,
    2348,  2351,  2356,  2359,  2364,  2369,  2378,  2385,  2388,  2393,
    2397,  2403,  2403,  2407,  2407,  2411,  2412,  2415,  2420,  2420,
    2424,  2424,  2428,  2432,  2428,  2437,  2437,  2445,  2445,  2453,
    2453,  2465,  2465,  2476,  2476,  2485,  2485,  2488,  2488,  2491,
    2494,  2503,  2506,  2516,  2528,  2535,  2541,  2552,  2556,  2556,
    2566,  2570,  2574,  2577,  2582,  2585,  2588,  2592,  2596,  2600,
    2604,  2608,  2612,  2616,  2620,  2625,  2629,  2634,  2638,  2642,
    2646,  2650,  2654,  2658,  2662,  2666,  2670,  2674,  2678,  2682,
    2686,  2690,  2694,  2698,  2702,  2706,  2710,  2714,  2718,  2722,
    2726,  2730,  2736,  2739
};
#endif

#if FRONTEND_VERILOG_YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_STRING", "TOK_ID", "TOK_CONSTVAL",
  "TOK_REALVAL", "TOK_PRIMITIVE", "TOK_SVA_LABEL", "TOK_SPECIFY_OPER",
  "TOK_MSG_TASKS", "TOK_ASSERT", "TOK_ASSUME", "TOK_RESTRICT", "TOK_COVER",
  "TOK_FINAL", "ATTR_BEGIN", "ATTR_END", "DEFATTR_BEGIN", "DEFATTR_END",
  "TOK_MODULE", "TOK_ENDMODULE", "TOK_PARAMETER", "TOK_LOCALPARAM",
  "TOK_DEFPARAM", "TOK_PACKAGE", "TOK_ENDPACKAGE", "TOK_PACKAGESEP",
  "TOK_INTERFACE", "TOK_ENDINTERFACE", "TOK_MODPORT", "TOK_VAR",
  "TOK_WILDCARD_CONNECT", "TOK_INPUT", "TOK_OUTPUT", "TOK_INOUT",
  "TOK_WIRE", "TOK_WAND", "TOK_WOR", "TOK_REG", "TOK_LOGIC", "TOK_INTEGER",
  "TOK_SIGNED", "TOK_ASSIGN", "TOK_ALWAYS", "TOK_INITIAL", "TOK_ALWAYS_FF",
  "TOK_ALWAYS_COMB", "TOK_ALWAYS_LATCH", "TOK_BEGIN", "TOK_END", "TOK_IF",
  "TOK_ELSE", "TOK_FOR", "TOK_WHILE", "TOK_REPEAT", "TOK_DPI_FUNCTION",
  "TOK_POSEDGE", "TOK_NEGEDGE", "TOK_OR", "TOK_AUTOMATIC", "TOK_CASE",
  "TOK_CASEX", "TOK_CASEZ", "TOK_ENDCASE", "TOK_DEFAULT", "TOK_FUNCTION",
  "TOK_ENDFUNCTION", "TOK_TASK", "TOK_ENDTASK", "TOK_SPECIFY",
  "TOK_IGNORED_SPECIFY", "TOK_ENDSPECIFY", "TOK_SPECPARAM",
  "TOK_SPECIFY_AND", "TOK_IGNORED_SPECIFY_AND", "TOK_GENERATE",
  "TOK_ENDGENERATE", "TOK_GENVAR", "TOK_REAL", "TOK_SYNOPSYS_FULL_CASE",
  "TOK_SYNOPSYS_PARALLEL_CASE", "TOK_SUPPLY0", "TOK_SUPPLY1",
  "TOK_TO_SIGNED", "TOK_TO_UNSIGNED", "TOK_POS_INDEXED", "TOK_NEG_INDEXED",
  "TOK_PROPERTY", "TOK_ENUM", "TOK_TYPEDEF", "TOK_RAND", "TOK_CONST",
  "TOK_CHECKER", "TOK_ENDCHECKER", "TOK_EVENTUALLY", "TOK_INCREMENT",
  "TOK_DECREMENT", "TOK_UNIQUE", "TOK_PRIORITY", "OP_LOR", "OP_LAND",
  "'|'", "OP_NOR", "'^'", "OP_XNOR", "'&'", "OP_NAND", "OP_EQ", "OP_NE",
  "OP_EQX", "OP_NEX", "'<'", "OP_LE", "OP_GE", "'>'", "OP_SHL", "OP_SHR",
  "OP_SSHL", "OP_SSHR", "'+'", "'-'", "'*'", "'/'", "'%'", "OP_POW",
  "UNARY_OPS", "FAKE_THEN", "','", "'='", "'.'", "'('", "')'", "';'",
  "'#'", "':'", "'['", "']'", "'{'", "'}'", "'@'", "'?'", "'~'", "'!'",
  "$accept", "input", "$@1", "design", "attr", "$@2", "attr_opt",
  "defattr", "$@3", "$@4", "opt_attr_list", "attr_list", "attr_assign",
  "hierarchical_id", "hierarchical_type_id", "module", "$@5",
  "module_para_opt", "$@6", "$@7", "module_para_list",
  "single_module_para", "$@8", "$@9", "module_args_opt", "module_args",
  "optional_comma", "module_arg_opt_assignment", "module_arg", "$@10",
  "$@11", "$@12", "$@13", "package", "$@14", "package_body",
  "package_body_stmt", "interface", "$@15", "interface_body",
  "interface_body_stmt", "non_opt_delay", "delay", "wire_type", "$@16",
  "wire_type_token_list", "wire_type_token_io", "wire_type_token",
  "non_opt_range", "non_opt_multirange", "range", "range_or_multirange",
  "range_or_signed_int", "module_body", "module_body_stmt", "checker_decl",
  "$@17", "task_func_decl", "$@18", "$@19", "$@20", "$@21", "$@22",
  "dpi_function_arg", "opt_dpi_function_args", "dpi_function_args",
  "opt_automatic", "opt_signed", "task_func_args_opt", "$@23", "$@24",
  "task_func_args", "task_func_port", "$@25", "task_func_body",
  "specify_block", "specify_item_list", "specify_item",
  "specify_opt_triple", "specify_if", "specify_condition",
  "specify_target", "specify_edge", "specify_rise_fall", "specify_triple",
  "ignored_specify_block", "ignored_specify_item_opt",
  "ignored_specify_item", "specparam_declaration", "specparam_range",
  "list_of_specparam_assignments", "specparam_assignment",
  "ignspec_opt_cond", "path_declaration", "simple_path_declaration",
  "path_delay_value", "list_of_path_delay_extra_expressions",
  "specify_edge_identifier", "parallel_path_description",
  "full_path_description", "list_of_path_inputs", "more_path_inputs",
  "list_of_path_outputs", "opt_polarity_operator",
  "specify_input_terminal_descriptor",
  "specify_output_terminal_descriptor", "system_timing_declaration",
  "system_timing_arg", "system_timing_args", "ignspec_constant_expression",
  "ignspec_expr", "ignspec_id", "$@26", "param_signed", "param_integer",
  "param_real", "param_range", "param_type", "param_decl", "$@27",
  "localparam_decl", "$@28", "param_decl_list", "single_param_decl",
  "defparam_decl", "defparam_decl_list", "single_defparam_decl",
  "enum_type", "$@29", "enum_base_type", "int_atom", "int_vec",
  "enum_name_list", "enum_name_decl", "opt_enum_init", "enum_var_list",
  "enum_var", "enum_decl", "wire_decl", "$@30", "$@31", "$@32", "$@33",
  "opt_supply_wires", "wire_name_list", "wire_name_and_opt_assign",
  "wire_name", "assign_stmt", "assign_expr_list", "assign_expr",
  "typedef_decl", "cell_stmt", "$@34", "$@35", "tok_prim_wrapper",
  "cell_list", "single_cell", "$@36", "$@37", "prim_list", "single_prim",
  "$@38", "cell_parameter_list_opt", "cell_parameter_list",
  "cell_parameter", "cell_port_list", "cell_port_list_rules", "cell_port",
  "always_comb_or_latch", "always_or_always_ff", "always_stmt", "$@39",
  "$@40", "$@41", "$@42", "always_cond", "always_events", "always_event",
  "opt_label", "opt_sva_label", "opt_property", "modport_stmt", "$@43",
  "$@44", "modport_args_opt", "modport_args", "modport_arg",
  "modport_member", "modport_type_token", "assert", "assert_property",
  "simple_behavioral_stmt", "behavioral_stmt", "$@45", "$@46", "$@47",
  "$@48", "$@49", "$@50", "$@51", "$@52", "$@53", "$@54", "$@55",
  "unique_case_attr", "case_attr", "case_type", "opt_synopsys_attr",
  "behavioral_stmt_list", "optional_else", "$@56", "case_body",
  "case_item", "$@57", "$@58", "gen_case_body", "gen_case_item", "$@59",
  "$@60", "case_select", "case_expr_list", "rvalue", "lvalue",
  "lvalue_concat_list", "opt_arg_list", "arg_list", "arg_list2",
  "single_arg", "module_gen_body", "gen_stmt_or_module_body_stmt",
  "gen_stmt", "$@61", "$@62", "$@63", "$@64", "$@65", "$@66",
  "gen_stmt_block", "$@67", "gen_stmt_or_null", "opt_gen_else", "expr",
  "basic_expr", "$@68", "concat_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   124,   357,    94,   358,    38,   359,   360,   361,
     362,   363,    60,   364,   365,    62,   366,   367,   368,   369,
      43,    45,    42,    47,    37,   370,   371,   372,    44,    61,
      46,    40,    41,    59,    35,    58,    91,    93,   123,   125,
      64,    63,   126,    33
};
# endif

#define YYPACT_NINF -796

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-796)))

#define YYTABLE_NINF -461

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -796,    40,   163,  -796,  -796,    81,   -10,  -796,   466,  -796,
     163,   163,   163,   163,   163,   163,   163,   163,   117,  -796,
    -796,   -30,  1060,   137,   173,  -796,  -796,   189,   198,   201,
     201,   207,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,   153,  -796,   115,   205,   308,  1575,  -796,   348,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,   117,  -796,  1044,  -796,  -796,   232,
    -796,    66,    66,  -796,    39,  -796,   340,   354,   117,   407,
     117,   384,  1575,   430,   306,   342,  -796,   503,  -796,   474,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  1575,  1575,  -796,  -796,   102,  -796,   196,  2030,   -30,
      41,  -796,  -796,   205,  -796,   449,   488,   488,   351,  -796,
     494,   519,  -796,    43,  -796,   535,  -796,  -796,  -796,  -796,
    -796,  -796,    54,   451,  -796,  -796,  -796,   431,  -796,   -30,
    -796,   405,   462,  1575,  1575,  1575,  1575,  1575,  1575,  1575,
    1575,   311,   -27,   459,  1575,  1575,  -796,  1575,  -796,   -30,
     -30,  -796,  1575,  1575,  1575,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,   -30,  -796,   472,  -796,   342,  -796,   527,
     453,    47,  -796,   267,  -796,   482,   607,   493,  -796,  -796,
     620,   501,  -796,    96,   630,   507,  -796,  -796,   511,  -796,
    -796,   636,  -796,  -796,  1575,  1575,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,   637,  1575,  1575,  1575,  -796,  -796,
    -796,   257,   510,  -796,  -796,   508,   509,   514,  1575,  1575,
    1575,  1575,  1575,  1575,  1575,  1575,  1575,  1575,  1575,  1575,
    1575,  1575,  1575,  1575,  1575,  1575,  1575,  1575,  1575,  1575,
    1575,  1575,  1575,  1575,  1575,  -796,   520,  -796,   -30,  1575,
     488,  -796,  -796,    56,   643,   522,  -796,   648,  -796,   524,
     526,    75,   529,  -796,  -796,   531,   659,   534,   -30,    79,
     536,   377,   538,    50,  -796,   537,   539,  -796,   540,   544,
    -796,   541,   546,  1575,  -796,  -796,  -796,  2097,  2121,  2143,
    2143,  2163,  2163,  2181,  2181,  1102,  1102,  1102,  1102,   673,
     673,   673,   673,   426,   426,   426,   426,   433,   433,   549,
     549,   549,  -796,   542,  -796,  -796,  -796,  -796,  -796,   655,
    -796,  -796,  -796,   678,  -796,    -9,  -796,   482,   679,   501,
    -796,   681,  -796,  -796,  -796,    96,   554,  1575,  -796,  -796,
    -796,   683,  -796,  -796,   -30,  -796,   684,   555,   471,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  1575,  -796,
     636,  -796,  -796,  -796,  1575,   556,   117,   565,  -796,  -796,
    -796,  1575,  1848,  -796,   643,  -796,   561,  -796,   564,   -30,
    -796,   571,  -796,  -796,   141,    66,    66,  -796,  -796,  -796,
     531,  -796,   117,   281,  -796,  -796,   110,  -796,    22,  -796,
    -796,  -796,  -796,  -796,   696,   697,   -30,  -796,  -796,  2072,
    -796,   570,  -796,    14,  -796,  1575,   572,  -796,   568,  -796,
    -796,   578,   574,   583,  -796,  -796,  -796,   118,   197,    21,
    -796,   711,  2046,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,   713,  -796,  -796,  -796,  -796,  -796,  -796,
     553,  -796,   587,  -796,  -796,  -796,   482,  -796,  -796,   -30,
      38,  -796,  -796,  -796,  -796,  1575,   812,  -796,   305,   373,
    -796,  -796,  -796,  -796,   589,  -796,   586,  -796,   525,  -796,
     302,   488,   488,  -796,   531,   591,   -30,  -796,   594,  -796,
    -796,  -796,  1575,   312,  -796,   598,   373,  -796,  -796,  -796,
     373,   590,  -796,  -796,  -796,  -796,   600,   725,  -796,  1575,
    -796,   601,   602,   662,   118,   604,  -796,   606,  -796,   199,
    -796,  -796,   608,  -796,   605,  -796,   609,  1575,   739,   316,
    -796,   615,  1882,   612,  -796,  -796,  -796,   555,  -796,   322,
    -796,   658,   661,   664,   665,  1575,   614,   362,  -796,  -796,
     618,  -796,   616,   629,   578,   627,   628,   631,   632,  -796,
    -796,  -796,  -796,  -796,   146,   146,   146,    97,  -796,   635,
    -796,  -796,   555,   555,  -796,  -796,  -796,  1575,  -796,    62,
    -796,   378,    22,  -796,  1575,  -796,  -796,  -796,   555,  -796,
      61,  -796,  1575,   634,  -796,  -796,   641,    22,   399,  1575,
    -796,  -796,   399,   -30,  1575,  -796,  -796,   202,   639,   640,
    -796,   523,   625,  -796,   326,   739,  -796,  1575,  -796,  -796,
    -796,  -796,  -796,   644,  -796,   713,  -796,   646,   649,   650,
     651,   642,  -796,  -796,   681,  -796,   600,  -796,  1575,  -796,
    1575,  -796,  1575,  1575,   406,  -796,  -796,   600,  -796,  -796,
     652,   654,   671,  -796,   674,  1575,  1575,  1575,  -796,  -796,
    -796,  -796,  -796,   633,  -796,  -796,   771,   675,  -796,  1575,
    -796,  -796,   336,   343,   681,   647,  -796,  1128,   373,   565,
    -796,  1952,  -796,   676,  -796,  -796,  1575,   672,  1575,  -796,
     685,   680,  -796,  -796,   739,   689,   145,  -796,  1618,  1618,
     739,   739,  -796,   130,  -796,  1575,  -796,  -796,  -796,  -796,
     682,   802,   802,  -796,  1234,  1240,  1296,  1575,  -796,  -796,
     687,  -796,  -796,   695,    22,   698,   699,   688,  1345,  1389,
    1419,  1464,   700,  -796,  -796,   321,   704,  -796,  -796,   702,
     803,  -796,  -796,   710,  -796,   712,  -796,  -796,  1575,  1575,
     707,   -15,  -796,  -796,  -796,   715,   578,  -796,  1575,   742,
    -796,   833,  -796,  1575,   721,   304,   729,  -796,  -796,   739,
     225,   716,  1575,  -796,   720,  -796,  -796,  -796,   523,   523,
     724,   722,  1781,  1513,   -30,   344,  -796,  -796,   347,  -796,
     727,  1575,   730,  1575,   732,  1575,   736,   738,  -796,  -796,
     842,  -796,   744,  -796,  -796,  -796,  1575,   740,  1575,   759,
    1575,   765,   766,   768,  -796,  -796,  -796,  1575,  -796,   681,
     769,  1575,  -796,  -796,  -796,  1184,  1184,  -796,  -796,  -796,
     849,  1986,  -796,  1575,   778,  1624,   772,   794,   797,  -796,
     739,  -796,   739,  -796,   798,   720,   398,  1575,  -796,  -796,
    -796,  -796,  -796,  -796,   911,   152,  -796,  -796,  -796,   785,
     802,  -796,   802,  -796,  -796,   786,   784,   787,   795,   799,
     796,   800,   866,   578,  -796,   373,  1575,   373,   373,   804,
     805,   809,   810,   813,   811,  -796,   814,  -796,   820,  -796,
    -796,  -796,  -796,  -796,   822,  -796,  -796,   823,  -796,   399,
    1575,   827,  -796,  1575,   829,   832,   369,  -796,  -796,  -796,
     739,   835,  1575,   720,   834,  1513,  -796,   837,  -796,  -796,
    -796,   819,   838,   807,  -796,   836,  -796,   839,  -796,   840,
    -796,  -796,  -796,  -796,  1190,  -796,  -796,  -796,  -796,  -796,
     841,  -796,   844,  -796,   845,  -796,  -796,   480,  -796,  -796,
    -796,  -796,    22,  1575,   191,   850,  -796,   739,   739,   739,
    -796,   856,  -796,   846,  -796,  1575,  -796,  -796,   857,  -796,
     938,  -796,  -796,  -796,  -796,  -796,  -796,  -796,   128,  -796,
     221,  -796,   919,   858,  -796,  -796,  -796,  -796,  -796,   918,
     860,   742,  1575,  1575,  1575,  1680,   241,   166,  -796,  -796,
    1575,   863,   864,  -796,   859,  -796,   822,  1575,  -796,  -796,
    -796,    22,  -796,  -796,  1190,  -796,   870,   865,   867,   436,
    1575,   868,  -796,   873,  1575,   874,  1575,   875,   570,  -796,
    -796,  1569,  -796,  -796,   373,   871,  -796,  -796,  1575,  -796,
    -796,  -796,   876,   443,  -796,  1575,   879,  1575,   880,  1575,
    -796,   882,  -796,  -796,   373,   877,  1575,  1575,   886,   894,
     898,   900,   902,  -796,   373,  -796,  1575,   903,   371,   901,
    1575,  -796,   905,  -796,   907,  -796,  -796,   908,  1575,  -796,
    1575,  -796,  -796,  -796,  -796,   393,   570,  1575,  -796,   915,
    1575,   916,  1575,   403,  1575,  -796,   917,  1575,   920,  1575,
     921,  1575,   923,  1575,   924,  1575,   929,  -796
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,    13,     1,    17,     0,    86,     3,     0,    16,
      13,    13,    13,    13,    13,    13,    13,    13,    21,    67,
     273,   113,     0,     0,     0,   262,   264,     0,     0,   159,
     159,    14,     5,     4,    10,    11,     6,     7,     8,     9,
      26,    18,    20,    22,    24,    35,   254,     0,   112,     0,
     100,    92,    93,    94,    95,    97,    96,    98,    99,   101,
     103,   102,   104,   105,     0,    91,    87,    90,    88,     0,
      30,   254,   254,    61,     0,   158,   161,     0,    21,     0,
       0,     0,     0,     0,     0,    45,   253,   277,   507,   505,
     506,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,     0,     0,    13,    13,   113,   501,     0,   499,   113,
       0,    89,   309,    35,   261,   256,     0,     0,     0,   140,
       0,     0,   160,   113,   146,     0,    19,    23,    27,    25,
      28,    32,    13,     0,   279,   280,   278,     0,   276,   113,
     504,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   552,     0,     0,     0,   503,     0,   508,   112,
     466,   465,     0,     0,     0,   109,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,   115,   114,     0,    29,    45,   255,   258,
       0,     0,   266,     0,    64,   153,     0,     0,   117,   116,
       0,   163,    15,    13,    53,     0,    44,    86,    50,    47,
      70,     0,   259,   275,     0,     0,   525,   526,   527,   528,
     523,   524,   547,   548,   512,     0,     0,     0,   514,   516,
     551,     0,     0,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   308,     0,   257,   113,     0,
       0,   263,   265,    13,   157,     0,   142,     0,   148,   164,
       0,     0,    33,    36,    43,    52,     0,     0,   113,    13,
       0,    13,   285,     0,   281,     0,     0,   502,     0,   552,
     553,     0,   109,   474,   107,   108,   106,   550,   549,   519,
     520,   521,   522,   517,   518,   535,   536,   537,   538,   533,
     534,   539,   540,   529,   530,   531,   532,   541,   542,   543,
     544,   545,   546,     0,   120,   260,   268,   267,    62,     0,
      63,    66,    65,   151,   156,     0,   141,   153,     0,   163,
     162,    13,   173,    39,    41,    13,     0,     0,    54,    56,
      60,     0,    48,    46,   113,    68,     0,    85,    86,    69,
      71,    72,    74,    75,    77,    73,    76,    78,     0,   283,
       0,   274,   510,   511,     0,     0,     0,    50,   473,   475,
     477,     0,    13,   150,   155,   152,     0,   144,     0,   113,
      86,    50,   167,   171,    13,   254,   254,    37,    34,    51,
      52,    58,     0,     0,   270,   373,     0,    84,     0,   345,
     352,   346,   343,   344,     0,     0,   113,   350,   347,   284,
     282,     0,   515,   113,   464,    49,     0,   500,     0,   491,
      31,   367,     0,     0,   437,   438,   439,   176,   213,     0,
     479,     0,    86,   134,   118,   136,   121,   122,   137,   127,
     123,   124,   126,     0,   131,   128,   129,   125,   130,   132,
       0,   135,     0,   119,   154,   143,   153,   173,   303,   113,
      13,   165,    13,   147,   413,     0,    86,   405,   113,    13,
     408,   409,   407,   410,     0,   406,     0,   172,     0,   467,
       0,     0,     0,    57,    52,     0,   113,   269,     0,    79,
      80,    81,     0,     0,   305,     0,    13,   293,   295,   290,
      13,   359,   513,   476,   509,   368,   472,     0,   489,     0,
     482,     0,     0,     0,   176,     0,   251,     0,   200,   213,
     202,   203,     0,   204,     0,   205,     0,     0,     0,     0,
     209,     0,    13,     0,   310,   314,   315,    85,   288,     0,
     286,     0,     0,     0,     0,     0,     0,    13,   169,   168,
       0,   416,     0,   469,   367,     0,     0,     0,     0,    13,
      13,   436,   414,   411,   372,   372,   372,   372,   412,     0,
     402,   403,    85,    85,    40,    42,    59,     0,   271,     0,
     374,     0,     0,   304,     0,   353,   297,   297,    85,   351,
       0,   348,   474,     0,   366,   479,     0,     0,   191,     0,
     174,   175,   191,   113,     0,   199,   201,     0,     0,     0,
     214,     0,     0,   248,     0,     0,   206,     0,   133,   481,
     478,   480,   138,   328,   312,     0,   289,     0,     0,     0,
       0,     0,   145,   149,     0,   166,   472,   468,     0,   418,
       0,   420,     0,     0,   433,   435,   434,   472,   371,   370,
       0,     0,     0,   391,     0,     0,     0,     0,   272,   382,
     383,   384,   376,    50,   378,   381,     0,     0,    82,     0,
     306,   307,     0,     0,     0,     0,   358,     0,    13,    50,
     492,    13,   485,     0,   189,   190,     0,     0,     0,   252,
       0,   249,   222,   223,     0,     0,   238,   239,     0,     0,
       0,     0,   245,     0,   244,     0,   207,   210,   211,   120,
       0,     0,   325,   287,     0,     0,     0,     0,   487,   170,
       0,   470,   444,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   404,   401,    49,     0,   380,   375,     0,
       0,   294,   296,   291,   299,   301,   356,   357,     0,     0,
       0,     0,   360,   365,   349,     0,   367,   493,     0,   184,
     181,     0,   212,     0,     0,   238,     0,   236,   237,     0,
     238,   230,     0,   215,   218,   216,   242,   243,     0,     0,
       0,     0,    13,   331,   318,     0,   316,   324,     0,   322,
       0,     0,     0,     0,     0,     0,     0,     0,   454,   417,
      13,   428,     0,   424,   426,   415,     0,     0,     0,     0,
       0,     0,     0,     0,   431,   379,   377,     0,   298,     0,
       0,     0,   363,   364,   355,     0,     0,   354,   471,   490,
     498,    13,   483,     0,     0,     0,     0,     0,     0,   230,
       0,   232,     0,   231,     0,     0,   249,     0,   219,   246,
     247,   241,   208,   139,     0,     0,   329,   332,   320,     0,
       0,   311,   325,   313,    13,     0,     0,     0,     0,     0,
       0,     0,   455,   367,   443,    13,     0,    13,    13,     0,
       0,     0,     0,     0,     0,   390,     0,   442,     0,   300,
     292,   302,   361,   362,   493,   486,   494,     0,   183,   191,
       0,     0,   185,     0,     0,     0,     0,   234,   240,   233,
       0,     0,     0,   220,     0,   331,   327,     0,    13,   317,
     323,   337,     0,   334,   335,     0,   394,     0,   395,     0,
     399,   398,   488,   453,     0,   419,   429,   421,   425,   427,
       0,   385,     0,   386,     0,   392,   389,   449,    83,   496,
     495,   497,     0,     0,     0,     0,   250,     0,     0,     0,
     227,     0,   217,     0,   221,     0,   330,    13,     0,   342,
       0,   338,   326,    13,   396,   397,   400,   461,   459,   456,
       0,   462,   447,     0,   387,   388,   393,   440,   441,   450,
       0,   184,     0,     0,     0,     0,   238,   238,   235,   224,
       0,     0,     0,   319,   341,   336,   493,     0,   458,   445,
     430,     0,   432,   448,     0,   493,     0,     0,     0,     0,
       0,     0,   192,   197,     0,     0,     0,     0,   250,   333,
     321,     0,   457,   463,    13,     0,   451,   484,     0,   188,
     187,   186,     0,   197,   177,     0,     0,     0,     0,     0,
     340,     0,   446,   422,    13,   180,     0,     0,     0,     0,
       0,     0,     0,   339,    13,   452,     0,     0,     0,     0,
       0,   229,     0,   226,     0,   423,   179,     0,     0,   193,
       0,   198,   228,   225,   178,     0,   198,     0,   194,     0,
       0,     0,     0,     0,     0,   195,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   196
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -796,  -796,  -796,   869,   122,  -796,  -796,    76,  -796,  -796,
     969,  -796,   922,   -18,  1040,  -796,  -796,   954,  -796,  -796,
    -796,   703,  -796,  -796,   872,  -796,  -330,  -384,   773,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -363,  -200,    12,  -796,  -796,  -796,  1005,   -50,   -92,
      73,  -397,  -796,   335,  -401,  -796,  -796,  -396,  -796,  -796,
    -796,  -796,  -796,   686,  -322,  -796,  1047,  -796,   719,  -796,
    -796,  -796,   599,  -796,   592,  -796,   548,  -796,  -796,  -796,
      67,  -796,  -610,  -796,  -102,  -796,  -796,   557,  -421,  -796,
     545,   460,  -796,  -796,  -796,   375,  -795,  -796,  -796,  -796,
     383,  -796,   121,  -780,  -700,  -599,  -796,  -235,  -796,   374,
    -626,  -402,  -796,  1065,  -796,  -796,   843,   -68,    17,  -796,
      37,  -796,   995,  -175,   815,  -796,   597,  1108,  -796,  -796,
    -796,  -796,  -796,   728,  -796,  -796,   465,  -796,  -298,  -796,
    -796,  -796,  -796,   498,  -796,   268,  -641,   825,  -796,   512,
      59,  -796,  -796,  -796,  -796,  -796,  -725,  -796,  -796,  -796,
     231,  -796,  -796,  -796,   182,  -663,  -796,   125,  -796,  -796,
     828,  -796,  -796,  -796,  -796,  -796,  -796,  -265,  -579,  -395,
      20,  -796,  -796,  -796,  -796,  -796,   372,   445,  -796,  -796,
    -796,  -614,  -368,  -796,  -796,  -796,  -796,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,     6,   638,  -796,  -796,  -796,
    -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,  -796,    95,
    -796,    46,  -417,   475,  -409,   528,  -796,   708,   517,   283,
    -400,  -796,  -796,  -796,  -796,  -796,  -796,  -778,  -796,   111,
    -796,   -37,   910,  -796,   382
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,   496,     9,    31,   497,    18,    79,
      41,    42,    43,   105,   114,    11,   113,    85,   213,   366,
     292,   293,   415,   416,   133,   218,   300,   368,   219,   295,
     296,   420,   514,    12,   118,   283,   350,    13,    45,   301,
     379,   499,   428,   436,    22,    66,    67,    68,    48,   160,
     161,   195,   210,   402,   649,   465,   739,    14,   205,   357,
     486,   211,   359,   354,   285,   355,    76,   123,   290,   361,
     580,   411,   412,   664,   414,   467,   543,   544,  1097,   545,
     864,   931,   716,  1051,  1052,   468,   549,   550,   469,   558,
     559,   560,   552,   553,   554,   803,   878,   724,   638,   639,
     725,   800,   936,   801,   726,   937,   555,   732,   733,   642,
     734,   938,   633,   115,   199,   278,   223,   116,   500,    71,
     501,    72,   201,   202,   472,   423,   424,   473,    46,   137,
     138,   139,   303,   304,   389,   569,   570,   474,   502,   618,
     850,   616,   617,   702,   773,   774,   413,   476,   523,   524,
     503,   478,   653,   742,   567,   815,   817,   889,   947,   818,
     819,   820,   741,   885,   886,   952,   953,   954,   437,   438,
     479,   531,   708,   530,   526,   621,   781,   782,   538,   504,
     680,   387,   518,   697,   610,   693,   694,   695,   696,   505,
     481,   506,   507,   677,   666,   752,   754,  1013,  1094,   907,
     908,   905,  1012,   917,   591,   508,   482,   977,   830,  1040,
    1064,  1019,  1043,  1044,  1084,   902,   963,   964,  1036,  1009,
    1010,   106,   510,   582,   623,   397,   398,   399,   562,   650,
     651,   627,   927,   787,   828,   625,   536,   980,   861,   981,
     925,  1053,   108,   242,   153
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,   464,   483,   383,   117,   669,   466,   480,   720,   860,
     107,   525,   488,   713,   427,   869,   816,   193,    21,    15,
     873,   738,   718,   749,   795,   546,    40,    15,    15,    15,
      15,    15,    15,    15,    15,   406,   513,   551,   294,    16,
       3,    81,   409,   119,   855,   129,   110,    16,    16,    16,
      16,    16,    16,    16,    16,   159,   556,   561,   214,   159,
      44,    17,    44,   775,   151,   152,   689,   446,    81,    17,
      17,    17,    17,    17,    17,    17,    17,   705,    10,    20,
     941,   491,   348,   214,   208,    19,    10,    10,    10,    10,
      10,    10,    10,    10,    49,   690,   691,   363,   364,   871,
     200,   236,   804,   804,   475,   347,    47,   156,    86,   243,
     244,   237,   678,   856,   519,   520,   521,   857,   -13,   404,
     241,    40,   541,   405,     8,   245,   246,   247,   551,    81,
     606,   593,     8,     8,     8,     8,     8,     8,     8,     8,
     832,    69,    81,   244,    83,    40,     6,   556,   994,   448,
     157,   492,  -369,  -369,  -369,  -369,   561,   557,   615,     4,
     495,   678,   619,   -12,   576,   949,   466,   480,   120,   542,
     -49,    83,   939,   196,   121,   280,   875,    70,   390,    47,
     281,     4,   194,   706,   215,   679,   216,   305,   306,   391,
     294,     5,   707,    73,   692,   525,   209,    64,   308,   309,
     309,   546,    74,   546,   427,   808,   546,   859,   775,   215,
     493,   -49,   222,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,    78,   -38,   154,   155,   158,   -38,   298,
     683,     6,    83,   -13,   679,   727,   719,   343,   157,   427,
     427,   522,   346,   561,    82,    83,  1055,  1057,   547,  -182,
     547,   943,  1056,     6,   217,   427,  -460,   750,   809,   722,
     723,    75,   810,  -460,   475,   797,   798,  1067,   757,   548,
     459,   635,   459,   799,   494,   426,   400,  1022,  1023,   495,
     945,    80,   162,   163,   946,   998,   797,   798,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   466,   480,   193,   380,   983,
     351,   -13,   727,   234,   965,   689,  1024,  1054,   806,   807,
     419,   164,    81,   165,  1032,   291,   604,   605,   381,    84,
     784,   991,   352,   162,   163,   797,   798,   511,   512,  1037,
      86,   222,   109,   872,   690,   691,  1038,   441,   124,   159,
     385,   797,   798,   766,   447,   112,    40,   654,  1020,   989,
     448,   371,   492,  -369,  -369,  -369,  -369,    40,   443,   785,
       4,   448,   122,   492,  -369,  -369,  -369,  -369,   128,  1027,
    1028,     4,   164,   159,   312,   280,   498,   727,   600,   601,
     282,   374,   686,   687,   443,   349,   375,   376,   400,   516,
     443,   464,   483,   475,   517,   602,   466,   480,   704,   470,
     377,   217,   489,   378,   797,   798,   126,  1065,  1076,   663,
    1078,   603,   799,   868,   130,    83,   -13,   131,   -13,   471,
     612,   157,   444,   234,   645,   613,   235,   422,   159,   646,
     655,  1090,     6,  1092,   645,   656,   714,   715,   583,   736,
     509,   477,   904,     6,   770,   466,   480,     6,   515,   771,
     727,   770,   890,   132,   509,   892,   772,   891,   463,   140,
     893,   498,   194,   410,   204,   611,    24,   291,    25,    26,
     198,    27,   200,    25,    26,   494,   426,   989,   206,  1108,
     495,   990,   626,  1109,   589,   590,   494,   426,   498,   529,
     698,   495,   498,   699,   475,   429,   430,   431,   432,   433,
     643,  1117,    28,   207,   462,  1118,    88,    40,    89,    90,
     234,  1124,    29,   942,    30,  1125,   224,   966,   661,   968,
     969,   193,   134,   135,   136,   509,   186,   187,   188,   189,
     190,   191,   212,   434,   435,   188,   189,   190,   191,   498,
    1017,  1018,   578,   475,   571,   572,   573,   574,  1071,   221,
     688,   394,   509,   879,   880,   234,   509,   701,  1087,   470,
     730,   731,   279,   159,   220,   400,   454,   455,   456,   422,
     922,   923,   717,   225,   443,   675,   676,   721,   238,   471,
     594,   595,   596,   597,   721,   275,   277,    91,    92,   443,
     721,   286,   410,   284,   581,   681,   682,   684,   310,   311,
     592,   477,   287,   509,   288,    93,    94,    95,    96,    97,
      98,   583,   289,   753,   -55,   755,   756,   297,   463,   299,
     302,   313,   307,    99,   100,   314,   315,   353,   762,   763,
     764,   316,   358,   344,   101,   356,   360,   365,   509,   362,
     367,   102,   769,   369,   370,   103,   104,   388,   373,   392,
     783,   393,   236,   509,   191,   394,   396,   401,    26,   789,
     395,   791,   403,   407,   462,   409,   418,   421,   425,   426,
     498,   721,   721,   445,   485,   442,  1082,   487,   643,   490,
     527,   528,   532,   535,   534,   539,   194,   822,   824,   826,
     827,   674,   674,   537,   540,   563,  1095,   568,   575,   598,
     607,   837,   839,   841,   843,   609,  1105,   614,   470,   624,
     620,   622,   628,   629,   630,   632,   443,   634,   640,   637,
     641,   852,   853,   546,   647,   652,   657,   662,   471,   658,
     665,   862,   659,   660,   509,   667,   866,   668,   670,   671,
     735,   765,   672,   673,   888,   876,   685,   710,   728,   729,
     477,   721,   721,   712,   748,   689,   887,   744,   740,   776,
     745,   746,   747,   758,   895,   759,   897,   463,   899,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   909,
     509,   911,   760,   913,   790,   761,   814,   848,   768,   788,
     918,   796,   498,   813,   921,   793,   863,   792,   783,   783,
     829,   835,    88,    40,    89,    90,   928,   831,   932,   470,
     833,   834,   844,   462,    25,    26,   846,   847,   849,   854,
     721,   851,   865,   867,   870,   874,    40,   858,   877,   471,
     448,   999,   492,  -369,  -369,  -369,  -369,   881,   894,   882,
       4,   584,   896,   585,   898,   586,   587,   588,   900,   967,
     901,   477,   910,  -433,  -433,  -433,   509,   906,   470,    32,
      33,    34,    35,    36,    37,    38,    39,   498,   463,   498,
     498,   912,   903,   984,   434,   435,   986,   914,   471,   915,
     916,   924,   920,    91,    92,   993,   929,   933,   887,   934,
     589,   590,   935,   940,  1001,   944,   948,   956,   955,   957,
     477,    93,    94,    95,    96,    97,    98,  1011,   958,   960,
     962,   959,     6,   961,   462,  1003,   970,   463,   971,    99,
     100,   972,  1034,   973,   975,   974,  1021,   976,  1072,  1000,
     101,   509,   978,   509,   509,   979,   982,   102,  1031,   985,
     987,   103,   104,   988,   443,   995,  1085,   992,   997,  1004,
    1002,  1039,  1005,  1006,  1014,   494,   426,  1015,  1016,  1025,
     495,  1030,  1042,   462,  1098,  1047,  1048,  1049,  1029,  1033,
    1061,  1041,  1045,  1058,  1106,  1059,  1060,  1069,  1068,  1070,
    1063,  1074,   127,  1083,  1086,  1096,  1115,  1011,  1075,  1077,
    1079,  1089,  1091,  1073,  1093,  1119,   951,   721,  1121,   721,
    1123,  1100,  1126,   443,  1081,  1128,  1101,  1130,   509,  1132,
    1102,  1134,  1103,  1136,  1104,  1107,  1110,  1112,  1088,  1113,
     721,  1114,   721,  1120,  1122,  1127,   498,   125,  1129,  1131,
    1099,  1133,  1135,   226,   227,   228,   229,   230,   231,   232,
     233,  1137,    65,  1111,   239,   240,   498,   197,   417,   276,
     951,   111,   372,  1116,   812,    50,   498,    77,   408,   577,
      54,    55,    56,    57,    58,    59,    60,   509,  1046,   579,
     484,    50,   631,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,   644,   805,   737,   636,   794,  1026,   811,
     509,    87,   203,   608,    23,   703,   382,   919,   440,   951,
     743,   345,    61,   950,   700,   951,   384,   996,  1035,   386,
     509,    88,    40,    89,    90,    62,    63,   845,    61,  1066,
     509,   767,   711,   751,   926,   777,   599,  1062,     0,     0,
     709,    62,    63,   533,     0,     0,     0,     0,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,     0,   778,   779,    88,    40,    89,
      90,    64,     0,    88,    40,    89,    90,     0,  1007,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    91,    92,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,     0,     0,
      93,    94,    95,    96,    97,    98,     0,    88,    40,    89,
      90,   778,   779,    88,    40,    89,    90,     0,    99,   100,
     780,     0,     0,     0,     0,  1008,     0,     0,     0,   101,
       0,     0,     0,     0,     0,     0,   102,     0,    91,    92,
     103,   104,     0,     0,    91,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    96,
      97,    98,    93,    94,    95,    96,    97,    98,   439,    88,
      40,    89,    90,     0,    99,   100,     0,     0,     0,     0,
      99,   100,     0,     0,     0,   101,     0,     0,    91,    92,
       0,   101,   102,     0,    91,    92,   103,   104,   102,   821,
       0,     0,   103,   104,     0,   823,    93,    94,    95,    96,
      97,    98,    93,    94,    95,    96,    97,    98,    88,    40,
      89,    90,     0,     0,    99,   100,     0,     0,     0,     0,
      99,   100,     0,     0,     0,   101,     0,     0,     0,     0,
       0,   101,   102,     0,     0,     0,   103,   104,   102,     0,
      91,    92,   103,   104,     0,     0,     0,     0,     0,     0,
       0,   825,    88,    40,    89,    90,     0,     0,    93,    94,
      95,    96,    97,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    99,   100,     0,     0,
       0,     0,    88,    40,    89,    90,     0,   101,     0,    91,
      92,     0,     0,     0,   102,     0,     0,     0,   103,   104,
     836,     0,     0,     0,     0,     0,     0,    93,    94,    95,
      96,    97,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,   100,    88,    40,    89,
      90,     0,     0,    91,    92,     0,   101,     0,     0,     0,
       0,     0,     0,   102,   838,     0,     0,   103,   104,     0,
       0,    93,    94,    95,    96,    97,    98,     0,     0,     0,
       0,     0,     0,    91,    92,     0,     0,     0,     0,    99,
     100,     0,     0,     0,   840,     0,    88,    40,    89,    90,
     101,    93,    94,    95,    96,    97,    98,   102,     0,     0,
       0,   103,   104,     0,     0,     0,     0,     0,     0,    99,
     100,     0,     0,     0,     0,     0,     0,     0,    91,    92,
     101,     0,     0,     0,     0,     0,     0,   102,     0,     0,
       0,   103,   104,     0,     0,     0,    93,    94,    95,    96,
      97,    98,    88,    40,    89,    90,     0,     0,    88,    40,
      89,    90,     0,     0,    99,   100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   101,   842,    91,    92,     0,
       0,     0,   102,     0,     0,     0,   103,   104,     0,     0,
       0,     0,     0,     0,     0,    93,    94,    95,    96,    97,
      98,    88,    40,    89,    90,     0,     0,    88,    40,    89,
      90,     0,     0,    99,   100,     0,     0,     0,     0,     0,
       0,     0,     0,   884,   101,     0,     0,     0,     0,     0,
       0,   102,     0,    91,    92,   103,   104,     0,     0,    91,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    93,    94,    95,    96,    97,    98,    93,    94,    95,
      96,    97,    98,    88,    40,    89,    90,     0,     0,    99,
     100,     0,     0,     0,     0,    99,   100,     0,     0,     0,
     101,  1080,    91,    92,     0,     0,   101,   102,    91,    92,
       0,   103,   104,   102,     0,     0,     0,   103,   104,     0,
      93,    94,    95,    96,    97,    98,    93,    94,    95,    96,
      97,    98,     0,     0,     0,     0,     0,     0,    99,   100,
       0,     0,     0,     0,    99,   100,     0,     0,     0,   802,
       0,     0,     0,     0,     0,   930,   102,     0,     0,     0,
     103,   104,   102,     0,    91,    92,   103,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,    94,    95,    96,    97,    98,     0,   448,
       0,   449,  -369,  -369,  -369,  -369,     0,     0,     0,     4,
      99,   100,     0,     0,     0,   374,     0,     0,     0,     0,
       0,  1050,     0,     0,     0,     0,     0,     0,   102,     0,
       0,     0,   103,   104,   377,     0,     0,     0,     0,     0,
     451,     0,   452,     0,   453,     0,     0,     0,     0,     0,
       0,     0,   454,   455,   456,     0,     0,     0,     0,     0,
       0,   457,   458,     0,   459,     0,   448,   460,   449,  -369,
    -369,  -369,  -369,     0,     0,     0,     4,     0,     0,   450,
      20,     6,   374,     0,   461,   883,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     448,   377,   449,  -369,  -369,  -369,  -369,   451,     0,   452,
       4,   453,     0,     0,     0,     0,   374,     0,     0,   454,
     455,   456,     0,     0,     0,     0,     0,     0,   457,   458,
       0,   459,     0,     0,   460,   377,     0,     0,     0,     0,
       0,   451,     0,   452,     0,   453,     0,    20,     6,     0,
       0,   461,     0,   454,   455,   456,     0,     0,     0,     0,
       0,     0,   457,   458,     0,   459,     0,     0,   460,   648,
     448,     0,   449,  -369,  -369,  -369,  -369,     0,     0,     0,
       4,    20,     6,     0,     0,   461,   374,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   448,   377,   449,  -369,  -369,  -369,
    -369,   451,   786,   452,     4,   453,     0,     0,     0,     0,
     374,     0,     0,   454,   455,   456,     0,     0,     0,     0,
       0,     0,   457,   458,     0,   459,     0,     0,   460,   377,
       0,     0,     0,     0,     0,   451,     0,   452,     0,   453,
       0,    20,     6,     0,     0,   461,     0,   454,   455,   456,
     564,     0,     0,   565,     0,     0,   457,   458,     0,   459,
       0,     0,   460,     0,     0,     0,     0,     0,    25,    26,
       0,     0,     0,     0,     0,    20,     6,     0,     0,   461,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     429,   430,   431,   432,   433,     0,     0,     0,     0,     0,
       0,     0,    28,     0,     0,   566,     0,     0,     0,     0,
       0,     0,    29,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   434,   435,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   192,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191
};

static const yytype_int16 yycheck[] =
{
      18,   402,   402,   301,    72,   584,   402,   402,   634,   787,
      47,   428,   409,   627,   377,   795,   741,   109,     6,     2,
     800,   647,   632,   664,   724,     4,     4,    10,    11,    12,
      13,    14,    15,    16,    17,   357,   420,   458,   213,     2,
       0,    27,     4,     4,    59,    82,    64,    10,    11,    12,
      13,    14,    15,    16,    17,   105,   458,   459,     4,   109,
      78,     2,    80,   704,   101,   102,     4,   397,    27,    10,
      11,    12,    13,    14,    15,    16,    17,    16,     2,    89,
     875,   411,    26,     4,    41,     4,    10,    11,    12,    13,
      14,    15,    16,    17,    21,    33,    34,    22,    23,   799,
       4,   128,   728,   729,   402,   280,   136,     5,    42,   159,
     160,   138,    15,   128,     4,     5,     6,   132,    16,   128,
     157,     4,     4,   132,     2,   162,   163,   164,   549,    27,
     514,   499,    10,    11,    12,    13,    14,    15,    16,    17,
     754,     4,    27,   193,   130,     4,    90,   549,   943,     8,
     136,    10,    11,    12,    13,    14,   558,   136,   526,    18,
     138,    15,   530,     0,   486,   890,   562,   562,   129,    51,
     132,   130,   872,   132,   135,   128,   802,     4,   128,   136,
     133,    18,   109,   122,   130,    88,   132,   224,   225,   139,
     365,    28,   131,     4,   132,   612,   123,   131,   235,   236,
     237,     4,     4,     4,   567,    75,     4,   786,   849,   130,
      69,   132,   139,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    16,   128,   103,   104,   105,   132,   217,
     133,    90,   130,   131,    88,   637,   633,   274,   136,   602,
     603,   131,   279,   645,   129,   130,  1026,  1027,    51,   131,
      51,   877,    86,    90,   132,   618,   128,   666,   128,    57,
      58,    60,   132,   135,   562,   120,   121,  1045,   677,    72,
      73,    72,    73,   128,   133,   134,   313,    86,    87,   138,
     128,   128,    86,    87,   132,   948,   120,   121,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   711,   711,   409,   301,   929,
     283,    16,   724,   132,   903,     4,   135,    86,   730,   731,
     367,   135,    27,   137,   997,   213,   511,   512,   301,   134,
     708,   940,   283,    86,    87,   120,   121,   415,   416,   128,
      42,   278,     4,   128,    33,    34,   135,   394,     4,   409,
     301,   120,   121,   693,   401,   133,     4,   567,   982,   128,
       8,   298,    10,    11,    12,    13,    14,     4,   396,   709,
      18,     8,    42,    10,    11,    12,    13,    14,     4,   988,
     989,    18,   135,   443,   137,   128,   414,   799,    96,    97,
     133,    24,   602,   603,   422,   283,    29,    30,   445,   128,
     428,   812,   812,   711,   133,   113,   812,   812,   618,   402,
      43,   299,   410,   301,   120,   121,    19,  1041,  1054,    67,
    1056,   129,   128,   129,     4,   130,   131,   131,   133,   402,
     128,   136,   396,   132,   128,   133,   135,   374,   498,   133,
     128,  1077,    90,  1079,   128,   133,    57,    58,   495,   133,
     414,   402,   830,    90,   128,   861,   861,    90,   422,   133,
     872,   128,   128,   131,   428,   128,   133,   133,   402,     5,
     133,   499,   409,   361,   133,   522,    20,   365,    22,    23,
      41,    25,     4,    22,    23,   133,   134,   128,     4,   128,
     138,   132,   539,   132,    98,    99,   133,   134,   526,   436,
     132,   138,   530,   135,   812,    44,    45,    46,    47,    48,
     557,   128,    56,     4,   402,   132,     3,     4,     5,     6,
     132,   128,    66,   135,    68,   132,   131,   905,   575,   907,
     908,   633,    39,    40,    41,   499,   120,   121,   122,   123,
     124,   125,    17,    82,    83,   122,   123,   124,   125,   577,
      80,    81,   489,   861,    11,    12,    13,    14,   132,   138,
     607,   135,   526,   808,   809,   132,   530,   614,   135,   562,
      57,    58,   129,   633,   133,   622,    61,    62,    63,   516,
     855,   856,   629,   131,   612,   589,   590,   634,   139,   562,
      11,    12,    13,    14,   641,   133,    79,    84,    85,   627,
     647,     4,   490,   131,   492,   595,   596,   597,   236,   237,
     498,   562,   129,   577,     4,   102,   103,   104,   105,   106,
     107,   668,   131,   670,     4,   672,   673,   130,   562,   128,
       4,   131,     5,   120,   121,   137,   137,     4,   685,   686,
     687,   137,     4,   133,   131,   133,   132,   128,   612,   133,
     129,   138,   699,     4,   130,   142,   143,   129,   132,   132,
     707,   132,   128,   627,   125,   135,   130,   135,    23,   716,
     139,   718,     4,     4,   562,     4,   132,     4,     4,   134,
     708,   728,   729,   128,   133,   139,  1064,   133,   735,   128,
       4,     4,   132,   135,   132,   131,   633,   744,   745,   746,
     747,   589,   590,   135,   131,     4,  1084,     4,   131,   133,
     129,   758,   759,   760,   761,   131,  1094,   129,   711,     4,
     140,   131,   131,   131,    72,   131,   754,   131,   133,   131,
     131,   778,   779,     4,   129,   133,    88,   133,   711,    88,
     132,   788,    88,    88,   708,   139,   793,   128,   131,   131,
     135,   128,   131,   131,   814,   802,   131,   133,   129,   129,
     711,   808,   809,   132,   132,     4,   813,   131,   134,   132,
     131,   131,   131,   131,   821,   131,   823,   711,   825,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   836,
     754,   838,   131,   840,   132,   131,     4,     4,   133,   133,
     847,   122,   830,   131,   851,   135,    74,   132,   855,   856,
     133,   133,     3,     4,     5,     6,   863,   132,   865,   812,
     132,   132,   132,   711,    22,    23,   132,   135,   128,   132,
     877,   129,     9,   122,   115,   129,     4,   132,   128,   812,
       8,    32,    10,    11,    12,    13,    14,   133,   131,   137,
      18,    49,   132,    51,   132,    53,    54,    55,   132,   906,
     132,   812,   132,    61,    62,    63,   830,   133,   861,    10,
      11,    12,    13,    14,    15,    16,    17,   905,   812,   907,
     908,   132,    50,   930,    82,    83,   933,   132,   861,   133,
     132,    52,   133,    84,    85,   942,   128,   135,   945,   115,
      98,    99,   115,   115,   951,     4,   131,   133,   132,   132,
     861,   102,   103,   104,   105,   106,   107,   964,   133,   133,
      64,   132,    90,   133,   812,   128,   132,   861,   133,   120,
     121,   132,     4,   133,   133,   132,   983,   133,  1050,   130,
     131,   905,   132,   907,   908,   133,   133,   138,   995,   132,
     131,   142,   143,   131,   982,   131,  1068,   132,   131,   133,
     132,    52,   133,   133,   133,   133,   134,   133,   133,   129,
     138,   135,    64,   861,  1086,  1022,  1023,  1024,   132,   132,
     131,   133,   132,  1030,  1096,   132,   132,   132,   128,   132,
    1037,   133,    80,   132,   128,   128,  1108,  1044,   135,   135,
     135,   132,   132,  1050,   132,  1117,   894,  1054,  1120,  1056,
    1122,   135,  1124,  1041,  1061,  1127,   132,  1129,   982,  1131,
     132,  1133,   132,  1135,   132,   132,   135,   132,  1075,   132,
    1077,   133,  1079,   128,   128,   128,  1064,    78,   128,   128,
    1087,   128,   128,   143,   144,   145,   146,   147,   148,   149,
     150,   132,    22,  1100,   154,   155,  1084,   113,   365,   197,
     948,    66,   299,  1110,   739,    31,  1094,    30,   359,   487,
      36,    37,    38,    39,    40,    41,    42,  1041,  1021,   490,
     404,    31,   544,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,   558,   729,   645,   549,   724,   987,   735,
    1064,    46,   117,   516,     6,   617,   301,   849,   390,   997,
     655,   278,    78,   892,   612,  1003,   301,   945,  1003,   301,
    1084,     3,     4,     5,     6,    91,    92,   765,    78,  1044,
    1094,   696,   625,   668,   861,    17,   508,  1036,    -1,    -1,
     622,    91,    92,   445,    -1,    -1,    -1,    -1,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,    -1,    57,    58,     3,     4,     5,
       6,   131,    -1,     3,     4,     5,     6,    -1,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    -1,    -1,
     102,   103,   104,   105,   106,   107,    -1,     3,     4,     5,
       6,    57,    58,     3,     4,     5,     6,    -1,   120,   121,
     122,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,   131,
      -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    84,    85,
     142,   143,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   102,   103,   104,   105,   106,   107,   388,     3,
       4,     5,     6,    -1,   120,   121,    -1,    -1,    -1,    -1,
     120,   121,    -1,    -1,    -1,   131,    -1,    -1,    84,    85,
      -1,   131,   138,    -1,    84,    85,   142,   143,   138,    95,
      -1,    -1,   142,   143,    -1,    95,   102,   103,   104,   105,
     106,   107,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,    -1,    -1,   120,   121,    -1,    -1,    -1,    -1,
     120,   121,    -1,    -1,    -1,   131,    -1,    -1,    -1,    -1,
      -1,   131,   138,    -1,    -1,    -1,   142,   143,   138,    -1,
      84,    85,   142,   143,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,     3,     4,     5,     6,    -1,    -1,   102,   103,
     104,   105,   106,   107,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   120,   121,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    -1,   131,    -1,    84,
      85,    -1,    -1,    -1,   138,    -1,    -1,    -1,   142,   143,
      95,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,   121,     3,     4,     5,
       6,    -1,    -1,    84,    85,    -1,   131,    -1,    -1,    -1,
      -1,    -1,    -1,   138,    95,    -1,    -1,   142,   143,    -1,
      -1,   102,   103,   104,   105,   106,   107,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,   120,
     121,    -1,    -1,    -1,    95,    -1,     3,     4,     5,     6,
     131,   102,   103,   104,   105,   106,   107,   138,    -1,    -1,
      -1,   142,   143,    -1,    -1,    -1,    -1,    -1,    -1,   120,
     121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
     131,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,    -1,
      -1,   142,   143,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,     3,     4,     5,     6,    -1,    -1,     3,     4,
       5,     6,    -1,    -1,   120,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   131,   132,    84,    85,    -1,
      -1,    -1,   138,    -1,    -1,    -1,   142,   143,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,     3,     4,     5,     6,    -1,    -1,     3,     4,     5,
       6,    -1,    -1,   120,   121,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   130,   131,    -1,    -1,    -1,    -1,    -1,
      -1,   138,    -1,    84,    85,   142,   143,    -1,    -1,    84,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,    -1,    -1,   120,
     121,    -1,    -1,    -1,    -1,   120,   121,    -1,    -1,    -1,
     131,   132,    84,    85,    -1,    -1,   131,   138,    84,    85,
      -1,   142,   143,   138,    -1,    -1,    -1,   142,   143,    -1,
     102,   103,   104,   105,   106,   107,   102,   103,   104,   105,
     106,   107,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,
      -1,    -1,    -1,    -1,   120,   121,    -1,    -1,    -1,   131,
      -1,    -1,    -1,    -1,    -1,   131,   138,    -1,    -1,    -1,
     142,   143,   138,    -1,    84,    85,   142,   143,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,    -1,     8,
      -1,    10,    11,    12,    13,    14,    -1,    -1,    -1,    18,
     120,   121,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,    -1,    -1,    -1,   138,    -1,
      -1,    -1,   142,   143,    43,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    -1,    73,    -1,     8,    76,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,
      89,    90,    24,    -1,    93,    94,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       8,    43,    10,    11,    12,    13,    14,    49,    -1,    51,
      18,    53,    -1,    -1,    -1,    -1,    24,    -1,    -1,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      -1,    73,    -1,    -1,    76,    43,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    51,    -1,    53,    -1,    89,    90,    -1,
      -1,    93,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    -1,    73,    -1,    -1,    76,    77,
       8,    -1,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      18,    89,    90,    -1,    -1,    93,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,    43,    10,    11,    12,    13,
      14,    49,    50,    51,    18,    53,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    -1,    73,    -1,    -1,    76,    43,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    -1,    53,
      -1,    89,    90,    -1,    -1,    93,    -1,    61,    62,    63,
       4,    -1,    -1,     7,    -1,    -1,    70,    71,    -1,    73,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    83,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   145,   146,     0,    18,    28,    90,   147,   148,   149,
     151,   159,   177,   181,   201,   262,   264,   294,   152,     4,
      89,   187,   188,   271,    20,    22,    23,    25,    56,    66,
      68,   150,   147,   147,   147,   147,   147,   147,   147,   147,
       4,   154,   155,   156,   157,   182,   272,   136,   192,   194,
      31,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    78,    91,    92,   131,   158,   189,   190,   191,     4,
       4,   263,   265,     4,     4,    60,   210,   210,    16,   153,
     128,    27,   129,   130,   134,   161,    42,   257,     3,     5,
       6,    84,    85,   102,   103,   104,   105,   106,   107,   120,
     121,   131,   138,   142,   143,   157,   365,   385,   386,     4,
     157,   191,   133,   160,   158,   257,   261,   261,   178,     4,
     129,   135,    42,   211,     4,   154,    19,   156,     4,   385,
       4,   131,   131,   168,    39,    40,    41,   273,   274,   275,
       5,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   385,   385,   388,   148,   148,     5,   136,   148,   192,
     193,   194,    86,    87,   135,   137,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   141,   193,   194,   195,   132,   161,    41,   258,
       4,   266,   267,   266,   133,   202,     4,     4,    41,   194,
     196,   205,    17,   162,     4,   130,   132,   148,   169,   172,
     133,   138,   194,   260,   131,   131,   386,   386,   386,   386,
     386,   386,   386,   386,   132,   135,   128,   138,   139,   386,
     386,   385,   387,   192,   192,   385,   385,   385,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   133,   168,    79,   259,   129,
     128,   133,   133,   179,   131,   208,     4,   129,     4,   131,
     212,   148,   164,   165,   267,   173,   174,   130,   187,   128,
     170,   183,     4,   276,   277,   385,   385,     5,   385,   385,
     388,   388,   137,   131,   137,   137,   137,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   385,   133,   260,   385,   267,    26,   148,
     180,   264,   294,     4,   207,   209,   133,   203,     4,   206,
     132,   213,   133,    22,    23,   128,   163,   129,   171,     4,
     130,   194,   172,   132,    24,    29,    30,    43,   148,   184,
     262,   264,   268,   282,   291,   294,   314,   325,   129,   278,
     128,   139,   132,   132,   135,   139,   130,   369,   370,   371,
     385,   135,   197,     4,   128,   132,   208,     4,   212,     4,
     148,   215,   216,   290,   218,   166,   167,   165,   132,   385,
     175,     4,   194,   269,   270,     4,   134,   185,   186,    44,
      45,    46,    47,    48,    82,    83,   187,   312,   313,   386,
     277,   385,   139,   157,   365,   128,   170,   385,     8,    10,
      21,    49,    51,    53,    61,    62,    63,    70,    71,    73,
      76,    93,   148,   151,   198,   199,   201,   219,   229,   232,
     262,   264,   268,   271,   281,   282,   291,   294,   295,   314,
     323,   334,   350,   374,   207,   133,   204,   133,   195,   187,
     128,   170,    10,    69,   133,   138,   148,   151,   157,   185,
     262,   264,   282,   294,   323,   333,   335,   336,   349,   365,
     366,   261,   261,   171,   176,   365,   128,   133,   326,     4,
       5,     6,   131,   292,   293,   366,   318,     4,     4,   194,
     317,   315,   132,   371,   132,   135,   380,   135,   322,   131,
     131,     4,    51,   220,   221,   223,     4,    51,    72,   230,
     231,   232,   236,   237,   238,   250,   255,   136,   233,   234,
     235,   255,   372,     4,     4,     7,    59,   298,     4,   279,
     280,    11,    12,    13,    14,   131,   208,   218,   194,   216,
     214,   148,   367,   385,    49,    51,    53,    54,    55,    98,
      99,   348,   148,   336,    11,    12,    13,    14,   133,   350,
      96,    97,   113,   129,   267,   267,   171,   129,   270,   131,
     328,   385,   128,   133,   129,   336,   285,   286,   283,   336,
     140,   319,   131,   368,     4,   379,   385,   375,   131,   131,
      72,   220,   131,   256,   131,    72,   231,   131,   242,   243,
     133,   131,   253,   385,   234,   128,   133,   129,    77,   198,
     373,   374,   133,   296,   186,   128,   133,    88,    88,    88,
      88,   385,   133,    67,   217,   132,   338,   139,   128,   322,
     131,   131,   131,   131,   148,   349,   349,   337,    15,    88,
     324,   324,   324,   133,   324,   131,   186,   186,   385,     4,
      33,    34,   132,   329,   330,   331,   332,   327,   132,   135,
     293,   385,   287,   287,   186,    16,   122,   131,   316,   369,
     133,   372,   132,   335,    57,    58,   226,   385,   226,   195,
     254,   385,    57,    58,   241,   244,   248,   255,   129,   129,
      57,    58,   251,   252,   254,   135,   133,   235,   254,   200,
     134,   306,   297,   280,   131,   131,   131,   131,   132,   290,
     368,   367,   339,   385,   340,   385,   385,   368,   131,   131,
     131,   131,   385,   385,   385,   128,   170,   331,   133,   385,
     128,   133,   133,   288,   289,   290,   132,    17,    57,    58,
     122,   320,   321,   385,   336,   170,    50,   377,   133,   385,
     132,   385,   132,   135,   244,   248,   122,   120,   121,   128,
     245,   247,   131,   239,   254,   239,   255,   255,    75,   128,
     132,   253,   197,   131,     4,   299,   300,   300,   303,   304,
     305,    95,   385,    95,   385,    95,   385,   385,   378,   133,
     352,   132,   335,   132,   132,   133,    95,   385,    95,   385,
      95,   385,   132,   385,   132,   330,   132,   135,     4,   128,
     284,   129,   385,   385,   132,    59,   128,   132,   132,   322,
     381,   382,   385,    74,   224,     9,   385,   122,   129,   247,
     115,   248,   128,   247,   129,   254,   385,   128,   240,   251,
     251,   133,   137,    94,   130,   307,   308,   385,   192,   301,
     128,   133,   128,   133,   131,   385,   132,   385,   132,   385,
     132,   132,   359,    50,   336,   345,   133,   343,   344,   385,
     132,   385,   132,   385,   132,   133,   132,   347,   385,   289,
     133,   385,   321,   321,    52,   384,   373,   376,   385,   128,
     131,   225,   385,   135,   115,   115,   246,   249,   255,   248,
     115,   240,   135,   254,     4,   128,   132,   302,   131,   300,
     304,   148,   309,   310,   311,   132,   133,   132,   133,   132,
     133,   133,    64,   360,   361,   322,   336,   385,   336,   336,
     132,   133,   132,   133,   132,   133,   133,   351,   132,   133,
     381,   383,   133,   226,   385,   132,   385,   131,   131,   128,
     132,   249,   132,   385,   240,   131,   308,   131,   309,    32,
     130,   385,   132,   128,   133,   133,   133,     8,    65,   363,
     364,   385,   346,   341,   133,   133,   133,    80,    81,   355,
     335,   385,    86,    87,   135,   129,   246,   249,   249,   132,
     135,   385,   309,   132,     4,   311,   362,   128,   135,    52,
     353,   133,    64,   356,   357,   132,   224,   385,   385,   385,
     131,   227,   228,   385,    86,   247,    86,   247,   385,   132,
     132,   131,   383,   385,   354,   335,   363,   381,   128,   132,
     132,   132,   228,   385,   133,   135,   254,   135,   254,   135,
     132,   385,   336,   132,   358,   228,   128,   135,   385,   132,
     254,   132,   254,   132,   342,   336,   128,   222,   228,   385,
     135,   132,   132,   132,   132,   336,   228,   132,   128,   132,
     135,   385,   132,   132,   133,   228,   385,   128,   132,   228,
     128,   228,   128,   228,   128,   132,   228,   128,   228,   128,
     228,   128,   228,   128,   228,   128,   228,   132
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   144,   146,   145,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   149,   148,   150,   150,   152,   153,   151,
     154,   154,   155,   155,   156,   156,   157,   157,   157,   158,
     160,   159,   162,   163,   161,   161,   164,   164,   165,   166,
     165,   167,   165,   165,   168,   168,   168,   169,   169,   170,
     170,   171,   171,   173,   172,   174,   175,   172,   176,   172,
     172,   178,   177,   179,   179,   180,   180,   182,   181,   183,
     183,   184,   184,   184,   184,   184,   184,   184,   184,   185,
     185,   185,   185,   185,   186,   186,   188,   187,   189,   189,
     189,   189,   190,   190,   190,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   192,   192,   192,   192,
     193,   193,   194,   194,   195,   195,   196,   196,   197,   197,
     197,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   200,   199,
     202,   201,   203,   201,   204,   201,   205,   201,   206,   201,
     207,   207,   208,   208,   209,   209,   209,   209,   210,   210,
     211,   211,   212,   212,   213,   214,   212,   215,   215,   217,
     216,   216,   218,   218,   219,   220,   220,   221,   221,   222,
     222,   223,   223,   224,   224,   225,   225,   225,   225,   226,
     226,   226,   227,   227,   227,   227,   227,   228,   228,   229,
     229,   230,   230,   231,   231,   231,   232,   232,   233,   234,
     234,   235,   236,   236,   237,   238,   238,   239,   239,   239,
     240,   240,   241,   241,   242,   242,   242,   243,   243,   243,
     244,   244,   245,   245,   246,   246,   247,   247,   247,   248,
     249,   250,   251,   251,   251,   252,   252,   252,   253,   254,
     254,   256,   255,   257,   257,   258,   258,   259,   259,   260,
     261,   261,   263,   262,   265,   264,   266,   266,   267,   268,
     269,   269,   270,   272,   271,   273,   273,   273,   274,   275,
     275,   276,   276,   277,   278,   278,   279,   279,   280,   281,
     283,   284,   282,   285,   282,   286,   282,   287,   287,   288,
     288,   289,   289,   290,   291,   292,   292,   293,   294,   294,
     296,   295,   297,   295,   298,   298,   299,   299,   301,   300,
     302,   300,   303,   303,   304,   305,   304,   306,   306,   307,
     307,   308,   308,   308,   309,   310,   310,   311,   311,   311,
     311,   311,   311,   312,   312,   313,   313,   315,   316,   314,
     317,   314,   318,   314,   319,   319,   319,   319,   319,   319,
     320,   320,   320,   321,   321,   321,   322,   322,   323,   323,
     324,   324,   324,   326,   327,   325,   328,   328,   329,   329,
     330,   330,   331,   332,   332,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   334,   334,   334,   334,   334,   334,
     334,   335,   335,   335,   335,   336,   336,   336,   336,   336,
     336,   336,   336,   336,   337,   336,   338,   336,   339,   336,
     340,   341,   342,   336,   343,   336,   344,   336,   345,   346,
     336,   347,   336,   348,   348,   348,   349,   350,   350,   350,
     351,   351,   351,   352,   352,   354,   353,   353,   355,   355,
     357,   358,   356,   359,   359,   361,   362,   360,   363,   363,
     364,   364,   364,   364,   365,   365,   365,   366,   366,   367,
     367,   368,   368,   369,   369,   370,   370,   371,   372,   372,
     373,   373,   375,   376,   374,   377,   374,   378,   374,   379,
     374,   380,   374,   382,   381,   383,   383,   384,   384,   385,
     385,   386,   386,   386,   386,   386,   386,   386,   387,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   388,   388
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     0,     0,     2,     4,     0,     0,     0,     5,
       1,     0,     1,     3,     1,     3,     1,     3,     3,     3,
       0,     9,     0,     0,     6,     0,     1,     3,     0,     0,
       5,     0,     5,     1,     2,     0,     4,     1,     3,     1,
       0,     2,     0,     0,     3,     0,     0,     5,     0,     6,
       3,     0,     7,     2,     0,     1,     1,     0,     8,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     4,     8,     1,     0,     0,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     5,     5,     3,
       2,     2,     1,     0,     1,     1,     1,     1,     2,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     0,     6,
       0,     7,     0,     9,     0,    11,     0,     9,     0,    11,
       2,     1,     3,     0,     3,     2,     1,     0,     1,     0,
       1,     0,     2,     0,     0,     0,     6,     1,     3,     0,
       5,     1,     2,     0,     3,     2,     0,    10,    14,     2,
       0,     4,     0,     2,     0,     1,     5,     5,     5,     1,
       1,     0,     1,     5,     7,    13,    25,     1,     5,     3,
       2,     2,     1,     1,     1,     1,     3,     4,     5,     1,
       3,     3,     4,     0,     2,     4,     4,     4,     1,     2,
       2,     3,     1,     1,     7,    12,    11,     6,    12,    11,
       2,     3,     2,     3,     1,     3,     1,     1,     0,     1,
       1,     5,     2,     2,     1,     1,     3,     3,     1,     1,
       5,     0,     3,     1,     0,     1,     0,     1,     0,     1,
       4,     1,     0,     6,     0,     6,     1,     3,     3,     3,
       1,     3,     4,     0,     7,     2,     1,     0,     1,     1,
       1,     1,     3,     2,     2,     0,     1,     3,     1,     3,
       0,     0,     8,     0,     6,     0,     6,     0,     3,     1,
       3,     1,     3,     2,     4,     1,     3,     3,     6,     4,
       0,     6,     0,     6,     1,     1,     1,     3,     0,     5,
       0,     6,     1,     3,     1,     0,     4,     4,     0,     1,
       3,     0,     1,     5,     1,     1,     3,     1,     2,     6,
       5,     3,     2,     1,     1,     1,     1,     0,     0,     6,
       0,     4,     0,     4,     4,     4,     3,     3,     2,     0,
       1,     3,     3,     2,     2,     1,     2,     0,     2,     0,
       1,     1,     0,     0,     0,     6,     2,     4,     1,     3,
       2,     1,     1,     1,     1,     7,     7,     8,     8,     7,
       6,     3,     7,     8,     7,     7,     8,     8,     7,     7,
       8,     4,     2,     2,     4,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     0,     5,     0,     5,     0,     7,
       0,     0,     0,    13,     0,     7,     0,     7,     0,     0,
       9,     0,     9,     0,     2,     2,     2,     1,     1,     1,
       2,     2,     0,     2,     0,     0,     3,     0,     2,     0,
       0,     0,     4,     2,     0,     0,     0,     4,     2,     1,
       1,     1,     1,     3,     6,     2,     2,     1,     3,     1,
       3,     4,     0,     1,     0,     1,     3,     1,     2,     0,
       1,     1,     0,     0,    11,     0,     7,     0,     7,     0,
       6,     0,     4,     0,     2,     1,     1,     2,     0,     1,
       6,     1,     4,     2,     2,     1,     1,     1,     0,     7,
       5,     5,     3,     7,     3,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     3,     3,     3,     3,     3,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,     3,     4,
       4,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      YY_LAC_DISCARD ("YYBACKUP");                              \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if FRONTEND_VERILOG_YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined FRONTEND_VERILOG_YYLTYPE_IS_TRIVIAL && FRONTEND_VERILOG_YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !FRONTEND_VERILOG_YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !FRONTEND_VERILOG_YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if FRONTEND_VERILOG_YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if FRONTEND_VERILOG_YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if FRONTEND_VERILOG_YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
# if FRONTEND_VERILOG_YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined FRONTEND_VERILOG_YYLTYPE_IS_TRIVIAL && FRONTEND_VERILOG_YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
          case 2:
#line 227 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
	ast_stack.clear();
	ast_stack.push_back(current_ast);
}
#line 2920 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 230 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
	ast_stack.pop_back();
	log_assert(GetSize(ast_stack) == 0);
	for (auto &it : default_attr_list)
		delete it.second;
	default_attr_list.clear();
}
#line 2932 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 250 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (attr_list != nullptr)
			attr_list_stack.push(attr_list);
		attr_list = new std::map<std::string, AstNode*>;
		for (auto &it : default_attr_list)
			(*attr_list)[it.first] = it.second->clone();
	}
#line 2944 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 256 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.al) = attr_list;
		if (!attr_list_stack.empty()) {
			attr_list = attr_list_stack.top();
			attr_list_stack.pop();
		} else
			attr_list = nullptr;
	}
#line 2957 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 266 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_RULE_LOC((yyloc), (yylsp[-2]), (yyloc));
	}
#line 2965 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 272 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (attr_list != nullptr)
			attr_list_stack.push(attr_list);
		attr_list = new std::map<std::string, AstNode*>;
		for (auto &it : default_attr_list)
			delete it.second;
		default_attr_list.clear();
	}
#line 2978 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 279 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		attr_list->swap(default_attr_list);
		delete attr_list;
		if (!attr_list_stack.empty()) {
			attr_list = attr_list_stack.top();
			attr_list_stack.pop();
		} else
			attr_list = nullptr;
	}
#line 2992 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 297 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (attr_list->count(*(yyvsp[0].string)) != 0)
			delete (*attr_list)[*(yyvsp[0].string)];
		(*attr_list)[*(yyvsp[0].string)] = AstNode::mkconst_int(1, false);
		delete (yyvsp[0].string);
	}
#line 3003 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 303 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (attr_list->count(*(yyvsp[-2].string)) != 0)
			delete (*attr_list)[*(yyvsp[-2].string)];
		(*attr_list)[*(yyvsp[-2].string)] = (yyvsp[0].ast);
		delete (yyvsp[-2].string);
	}
#line 3014 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 311 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = (yyvsp[0].string);
	}
#line 3022 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 314 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].string)->compare(0, 1, "\\") == 0)
			*(yyvsp[-2].string) += "::" + (yyvsp[0].string)->substr(1);
		else
			*(yyvsp[-2].string) += "::" + *(yyvsp[0].string);
		delete (yyvsp[0].string);
		(yyval.string) = (yyvsp[-2].string);
	}
#line 3035 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 322 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].string)->compare(0, 1, "\\") == 0)
			*(yyvsp[-2].string) += "." + (yyvsp[0].string)->substr(1);
		else
			*(yyvsp[-2].string) += "." + *(yyvsp[0].string);
		delete (yyvsp[0].string);
		(yyval.string) = (yyvsp[-2].string);
	}
#line 3048 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 332 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[-1].string); }
#line 3054 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 335 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		do_not_require_port_stubs = false;
		AstNode *mod = new AstNode(AST_MODULE);
		ast_stack.back()->children.push_back(mod);
		ast_stack.push_back(mod);
		current_ast_mod = mod;
		port_stubs.clear();
		port_counter = 0;
		mod->str = *(yyvsp[0].string);
		append_attr(mod, (yyvsp[-2].al));
		delete (yyvsp[0].string);
	}
#line 3071 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 346 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (port_stubs.size() != 0)
			frontend_verilog_yyerror("Missing details for module port `%s'.",
					port_stubs.begin()->first.c_str());
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[-7]), (yyloc));
		ast_stack.pop_back();
		log_assert(ast_stack.size() == 1);
		current_ast_mod = NULL;
	}
#line 3085 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 357 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { astbuf1 = nullptr; }
#line 3091 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 357 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { if (astbuf1) delete astbuf1; }
#line 3097 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 364 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (astbuf1) delete astbuf1;
		astbuf1 = new AstNode(AST_PARAMETER);
		astbuf1->children.push_back(AstNode::mkconst_int(0, true));
		append_attr(astbuf1, (yyvsp[-1].al));
	}
#line 3108 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 370 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (astbuf1) delete astbuf1;
		astbuf1 = new AstNode(AST_LOCALPARAM);
		astbuf1->children.push_back(AstNode::mkconst_int(0, true));
		append_attr(astbuf1, (yyvsp[-1].al));
	}
#line 3119 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 388 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (ast_stack.back()->children.size() > 0 && ast_stack.back()->children.back()->type == AST_WIRE) {
			AstNode *wire = new AstNode(AST_IDENTIFIER);
			wire->str = ast_stack.back()->children.back()->str;
			if (ast_stack.back()->children.back()->is_input) {
				AstNode *n = ast_stack.back()->children.back();
				if (n->attributes.count("\\defaultvalue"))
					delete n->attributes.at("\\defaultvalue");
				n->attributes["\\defaultvalue"] = (yyvsp[0].ast);
			} else
			if (ast_stack.back()->children.back()->is_reg || ast_stack.back()->children.back()->is_logic)
				ast_stack.back()->children.push_back(new AstNode(AST_INITIAL, new AstNode(AST_BLOCK, new AstNode(AST_ASSIGN_LE, wire, (yyvsp[0].ast)))));
			else
				ast_stack.back()->children.push_back(new AstNode(AST_ASSIGN, wire, (yyvsp[0].ast)));
		} else
			frontend_verilog_yyerror("SystemVerilog interface in module port list cannot have a default value.");
	}
#line 3141 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 408 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (ast_stack.back()->children.size() > 0 && ast_stack.back()->children.back()->type == AST_WIRE) {
			AstNode *node = ast_stack.back()->children.back()->clone();
			node->str = *(yyvsp[0].string);
			node->port_id = ++port_counter;
			ast_stack.back()->children.push_back(node);
			SET_AST_NODE_LOC(node, (yylsp[0]), (yylsp[0]));
		} else {
			if (port_stubs.count(*(yyvsp[0].string)) != 0)
				frontend_verilog_yyerror("Duplicate module port `%s'.", (yyvsp[0].string)->c_str());
			port_stubs[*(yyvsp[0].string)] = ++port_counter;
		}
		delete (yyvsp[0].string);
	}
#line 3160 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 422 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = new AstNode(AST_INTERFACEPORT);
		astbuf1->children.push_back(new AstNode(AST_INTERFACEPORTTYPE));
		astbuf1->children[0]->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 3171 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 427 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {  /* SV interfaces */
		if (!sv_mode)
			frontend_verilog_yyerror("Interface found in port list (%s). This is not supported unless read_verilog is called with -sv!", (yyvsp[0].string)->c_str());
		astbuf2 = astbuf1->clone(); // really only needed if multiple instances of same type.
		astbuf2->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
		astbuf2->port_id = ++port_counter;
		ast_stack.back()->children.push_back(astbuf2);
		delete astbuf1; // really only needed if multiple instances of same type.
	}
#line 3186 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 437 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = (yyvsp[-2].ast);
		node->str = *(yyvsp[0].string);
		SET_AST_NODE_LOC(node, (yylsp[0]), (yylsp[0]));
		node->port_id = ++port_counter;
		if ((yyvsp[-1].ast) != NULL)
			node->children.push_back((yyvsp[-1].ast));
		if (!node->is_input && !node->is_output)
			frontend_verilog_yyerror("Module port `%s' is neither input nor output.", (yyvsp[0].string)->c_str());
		if (node->is_reg && node->is_input && !node->is_output && !sv_mode)
			frontend_verilog_yyerror("Input port `%s' is declared as register.", (yyvsp[0].string)->c_str());
		ast_stack.back()->children.push_back(node);
		append_attr(node, (yyvsp[-3].al));
		delete (yyvsp[0].string);
	}
#line 3206 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 452 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		do_not_require_port_stubs = true;
	}
#line 3214 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 457 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *mod = new AstNode(AST_PACKAGE);
		ast_stack.back()->children.push_back(mod);
		ast_stack.push_back(mod);
		current_ast_mod = mod;
		mod->str = *(yyvsp[0].string);
		append_attr(mod, (yyvsp[-2].al));
	}
#line 3227 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 464 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
		current_ast_mod = NULL;
	}
#line 3236 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 479 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		do_not_require_port_stubs = false;
		AstNode *intf = new AstNode(AST_INTERFACE);
		ast_stack.back()->children.push_back(intf);
		ast_stack.push_back(intf);
		current_ast_mod = intf;
		port_stubs.clear();
		port_counter = 0;
		intf->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 3252 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 489 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (port_stubs.size() != 0)
			frontend_verilog_yyerror("Missing details for module port `%s'.",
				port_stubs.begin()->first.c_str());
		ast_stack.pop_back();
		log_assert(ast_stack.size() == 1);
		current_ast_mod = NULL;
	}
#line 3265 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 506 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].string); }
#line 3271 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 507 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].string); }
#line 3277 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 508 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].string); }
#line 3283 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 509 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[-1].ast); }
#line 3289 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 510 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[-5].ast); delete (yyvsp[-3].ast); delete (yyvsp[-1].ast); }
#line 3295 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 516 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3 = new AstNode(AST_WIRE);
		current_wire_rand = false;
		current_wire_const = false;
	}
#line 3305 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 520 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = astbuf3;
		SET_RULE_LOC((yyloc), (yylsp[0]), (yyloc));
	}
#line 3314 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 529 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_custom_type = true;
		astbuf3->children.push_back(new AstNode(AST_WIRETYPE));
		astbuf3->children.back()->str = *(yyvsp[0].string);
	}
#line 3324 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 536 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_input = true;
	}
#line 3332 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 539 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_output = true;
	}
#line 3340 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 542 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_input = true;
		astbuf3->is_output = true;
	}
#line 3349 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 548 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
	}
#line 3356 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 550 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_wor = true;
	}
#line 3364 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 553 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_wand = true;
	}
#line 3372 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 556 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_reg = true;
	}
#line 3380 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 559 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_logic = true;
	}
#line 3388 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 562 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_logic = true;
	}
#line 3396 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 565 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_reg = true;
		astbuf3->range_left = 31;
		astbuf3->range_right = 0;
		astbuf3->is_signed = true;
	}
#line 3407 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 571 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->type = AST_GENVAR;
		astbuf3->is_reg = true;
		astbuf3->is_signed = true;
		astbuf3->range_left = 31;
		astbuf3->range_right = 0;
	}
#line 3419 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 578 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_signed = true;
	}
#line 3427 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 581 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_wire_rand = true;
	}
#line 3435 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 584 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_wire_const = true;
	}
#line 3443 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 589 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_RANGE);
		(yyval.ast)->children.push_back((yyvsp[-3].ast));
		(yyval.ast)->children.push_back((yyvsp[-1].ast));
	}
#line 3453 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 594 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_RANGE);
		AstNode *expr = new AstNode(AST_CONCAT, (yyvsp[-3].ast));
		(yyval.ast)->children.push_back(new AstNode(AST_SUB, new AstNode(AST_ADD, expr->clone(), (yyvsp[-1].ast)), AstNode::mkconst_int(1, true)));
		(yyval.ast)->children.push_back(new AstNode(AST_ADD, expr, AstNode::mkconst_int(0, true)));
	}
#line 3464 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 600 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_RANGE);
		AstNode *expr = new AstNode(AST_CONCAT, (yyvsp[-3].ast));
		(yyval.ast)->children.push_back(new AstNode(AST_ADD, expr, AstNode::mkconst_int(0, true)));
		(yyval.ast)->children.push_back(new AstNode(AST_SUB, new AstNode(AST_ADD, expr->clone(), AstNode::mkconst_int(1, true)), (yyvsp[-1].ast)));
	}
#line 3475 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 606 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_RANGE);
		(yyval.ast)->children.push_back((yyvsp[-1].ast));
	}
#line 3484 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 612 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_MULTIRANGE, (yyvsp[-1].ast), (yyvsp[0].ast));
	}
#line 3492 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 615 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
		(yyval.ast)->children.push_back((yyvsp[0].ast));
	}
#line 3501 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 621 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 3509 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 624 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = NULL;
	}
#line 3517 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 629 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 3523 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 630 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 3529 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 633 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 3537 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 636 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_RANGE);
		(yyval.ast)->children.push_back(AstNode::mkconst_int(31, true));
		(yyval.ast)->children.push_back(AstNode::mkconst_int(0, true));
		(yyval.ast)->is_signed = true;
	}
#line 3548 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 655 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENBLOCK);
		node->str = *(yyvsp[-1].string);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 3559 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 660 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete (yyvsp[-4].string);
		ast_stack.pop_back();
	}
#line 3568 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 666 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = new AstNode(AST_DPI_FUNCTION, AstNode::mkconst_str(*(yyvsp[-1].string)), AstNode::mkconst_str(*(yyvsp[0].string)));
		current_function_or_task->str = *(yyvsp[0].string);
		append_attr(current_function_or_task, (yyvsp[-3].al));
		ast_stack.back()->children.push_back(current_function_or_task);
		delete (yyvsp[-1].string);
		delete (yyvsp[0].string);
	}
#line 3581 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 673 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = NULL;
	}
#line 3589 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 676 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = new AstNode(AST_DPI_FUNCTION, AstNode::mkconst_str(*(yyvsp[-1].string)), AstNode::mkconst_str(*(yyvsp[-3].string)));
		current_function_or_task->str = *(yyvsp[0].string);
		append_attr(current_function_or_task, (yyvsp[-5].al));
		ast_stack.back()->children.push_back(current_function_or_task);
		delete (yyvsp[-3].string);
		delete (yyvsp[-1].string);
		delete (yyvsp[0].string);
	}
#line 3603 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 684 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = NULL;
	}
#line 3611 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 687 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = new AstNode(AST_DPI_FUNCTION, AstNode::mkconst_str(*(yyvsp[-1].string)), AstNode::mkconst_str(*(yyvsp[-5].string) + ":" + RTLIL::unescape_id(*(yyvsp[-3].string))));
		current_function_or_task->str = *(yyvsp[0].string);
		append_attr(current_function_or_task, (yyvsp[-7].al));
		ast_stack.back()->children.push_back(current_function_or_task);
		delete (yyvsp[-5].string);
		delete (yyvsp[-3].string);
		delete (yyvsp[-1].string);
		delete (yyvsp[0].string);
	}
#line 3626 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 696 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = NULL;
	}
#line 3634 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 699 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = new AstNode(AST_TASK);
		current_function_or_task->str = *(yyvsp[0].string);
		append_attr(current_function_or_task, (yyvsp[-3].al));
		ast_stack.back()->children.push_back(current_function_or_task);
		ast_stack.push_back(current_function_or_task);
		current_function_or_task_port_id = 1;
		delete (yyvsp[0].string);
	}
#line 3648 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 707 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = NULL;
		ast_stack.pop_back();
	}
#line 3657 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 711 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = new AstNode(AST_FUNCTION);
		current_function_or_task->str = *(yyvsp[0].string);
		append_attr(current_function_or_task, (yyvsp[-5].al));
		ast_stack.back()->children.push_back(current_function_or_task);
		ast_stack.push_back(current_function_or_task);
		AstNode *outreg = new AstNode(AST_WIRE);
		outreg->str = *(yyvsp[0].string);
		outreg->is_signed = (yyvsp[-2].boolean);
		outreg->is_reg = true;
		if ((yyvsp[-1].ast) != NULL) {
			outreg->children.push_back((yyvsp[-1].ast));
			outreg->is_signed = (yyvsp[-2].boolean) || (yyvsp[-1].ast)->is_signed;
			(yyvsp[-1].ast)->is_signed = false;
		}
		current_function_or_task->children.push_back(outreg);
		current_function_or_task_port_id = 1;
		delete (yyvsp[0].string);
	}
#line 3681 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 729 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = NULL;
		ast_stack.pop_back();
	}
#line 3690 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 735 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task->children.push_back(AstNode::mkconst_str(*(yyvsp[-1].string)));
		delete (yyvsp[-1].string);
		delete (yyvsp[0].string);
	}
#line 3700 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 740 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task->children.push_back(AstNode::mkconst_str(*(yyvsp[0].string)));
		delete (yyvsp[0].string);
	}
#line 3709 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 160:
#line 760 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = true;
	}
#line 3717 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 161:
#line 763 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 3725 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 768 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		albuf = nullptr;
		astbuf1 = nullptr;
		astbuf2 = nullptr;
	}
#line 3735 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 165:
#line 772 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
		if (astbuf2 != NULL)
			delete astbuf2;
		free_attr(albuf);
	}
#line 3746 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 783 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (albuf) {
			delete astbuf1;
			if (astbuf2 != NULL)
				delete astbuf2;
			free_attr(albuf);
		}
		albuf = (yyvsp[-2].al);
		astbuf1 = (yyvsp[-1].ast);
		astbuf2 = (yyvsp[0].ast);
		if (astbuf1->range_left >= 0 && astbuf1->range_right >= 0) {
			if (astbuf2) {
				frontend_verilog_yyerror("integer/genvar types cannot have packed dimensions (task/function arguments)");
			} else {
				astbuf2 = new AstNode(AST_RANGE);
				astbuf2->children.push_back(AstNode::mkconst_int(astbuf1->range_left, true));
				astbuf2->children.push_back(AstNode::mkconst_int(astbuf1->range_right, true));
			}
		}
		if (astbuf2 && astbuf2->children.size() != 2)
			frontend_verilog_yyerror("task/function argument range must be of the form: [<expr>:<expr>], [<expr>+:<expr>], or [<expr>-:<expr>]");
	}
#line 3773 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 177:
#line 820 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *en_expr = (yyvsp[-9].ast);
		char specify_edge = (yyvsp[-7].ch);
		AstNode *src_expr = (yyvsp[-6].ast);
		string *oper = (yyvsp[-5].string);
		specify_target *target = (yyvsp[-4].specify_target_ptr);
		specify_rise_fall *timing = (yyvsp[-1].specify_rise_fall_ptr);

		if (specify_edge != 0 && target->dat == nullptr)
			frontend_verilog_yyerror("Found specify edge but no data spec.\n");

		AstNode *cell = new AstNode(AST_CELL);
		ast_stack.back()->children.push_back(cell);
		cell->str = stringf("$specify$%d", autoidx++);
		cell->children.push_back(new AstNode(AST_CELLTYPE));
		cell->children.back()->str = target->dat ? "$specify3" : "$specify2";

		char oper_polarity = 0;
		char oper_type = oper->at(0);

		if (oper->size() == 3) {
			oper_polarity = oper->at(0);
			oper_type = oper->at(1);
		}

		cell->children.push_back(new AstNode(AST_PARASET, AstNode::mkconst_int(oper_type == '*', false, 1)));
		cell->children.back()->str = "\\FULL";

		cell->children.push_back(new AstNode(AST_PARASET, AstNode::mkconst_int(oper_polarity != 0, false, 1)));
		cell->children.back()->str = "\\SRC_DST_PEN";

		cell->children.push_back(new AstNode(AST_PARASET, AstNode::mkconst_int(oper_polarity == '+', false, 1)));
		cell->children.back()->str = "\\SRC_DST_POL";

		cell->children.push_back(new AstNode(AST_PARASET, timing->rise.t_min));
		cell->children.back()->str = "\\T_RISE_MIN";

		cell->children.push_back(new AstNode(AST_PARASET, timing->rise.t_avg));
		cell->children.back()->str = "\\T_RISE_TYP";

		cell->children.push_back(new AstNode(AST_PARASET, timing->rise.t_max));
		cell->children.back()->str = "\\T_RISE_MAX";

		cell->children.push_back(new AstNode(AST_PARASET, timing->fall.t_min));
		cell->children.back()->str = "\\T_FALL_MIN";

		cell->children.push_back(new AstNode(AST_PARASET, timing->fall.t_avg));
		cell->children.back()->str = "\\T_FALL_TYP";

		cell->children.push_back(new AstNode(AST_PARASET, timing->fall.t_max));
		cell->children.back()->str = "\\T_FALL_MAX";

		cell->children.push_back(new AstNode(AST_ARGUMENT, en_expr ? en_expr : AstNode::mkconst_int(1, false, 1)));
		cell->children.back()->str = "\\EN";

		cell->children.push_back(new AstNode(AST_ARGUMENT, src_expr));
		cell->children.back()->str = "\\SRC";

		cell->children.push_back(new AstNode(AST_ARGUMENT, target->dst));
		cell->children.back()->str = "\\DST";

		if (target->dat)
		{
			cell->children.push_back(new AstNode(AST_PARASET, AstNode::mkconst_int(specify_edge != 0, false, 1)));
			cell->children.back()->str = "\\EDGE_EN";

			cell->children.push_back(new AstNode(AST_PARASET, AstNode::mkconst_int(specify_edge == 'p', false, 1)));
			cell->children.back()->str = "\\EDGE_POL";

			cell->children.push_back(new AstNode(AST_PARASET, AstNode::mkconst_int(target->polarity_op != 0, false, 1)));
			cell->children.back()->str = "\\DAT_DST_PEN";

			cell->children.push_back(new AstNode(AST_PARASET, AstNode::mkconst_int(target->polarity_op == '+', false, 1)));
			cell->children.back()->str = "\\DAT_DST_POL";

			cell->children.push_back(new AstNode(AST_ARGUMENT, target->dat));
			cell->children.back()->str = "\\DAT";
		}

		delete oper;
		delete target;
		delete timing;
	}
#line 3861 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 178:
#line 903 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (*(yyvsp[-13].string) != "$setup" && *(yyvsp[-13].string) != "$hold" && *(yyvsp[-13].string) != "$setuphold" && *(yyvsp[-13].string) != "$removal" && *(yyvsp[-13].string) != "$recovery" &&
				*(yyvsp[-13].string) != "$recrem" && *(yyvsp[-13].string) != "$skew" && *(yyvsp[-13].string) != "$timeskew" && *(yyvsp[-13].string) != "$fullskew" && *(yyvsp[-13].string) != "$nochange")
			frontend_verilog_yyerror("Unsupported specify rule type: %s\n", (yyvsp[-13].string)->c_str());

		AstNode *src_pen = AstNode::mkconst_int((yyvsp[-11].ch) != 0, false, 1);
		AstNode *src_pol = AstNode::mkconst_int((yyvsp[-11].ch) == 'p', false, 1);
		AstNode *src_expr = (yyvsp[-10].ast), *src_en = (yyvsp[-9].ast) ? (yyvsp[-9].ast) : AstNode::mkconst_int(1, false, 1);

		AstNode *dst_pen = AstNode::mkconst_int((yyvsp[-7].ch) != 0, false, 1);
		AstNode *dst_pol = AstNode::mkconst_int((yyvsp[-7].ch) == 'p', false, 1);
		AstNode *dst_expr = (yyvsp[-6].ast), *dst_en = (yyvsp[-5].ast) ? (yyvsp[-5].ast) : AstNode::mkconst_int(1, false, 1);

		specify_triple *limit = (yyvsp[-3].specify_triple_ptr);
		specify_triple *limit2 = (yyvsp[-2].specify_triple_ptr);

		AstNode *cell = new AstNode(AST_CELL);
		ast_stack.back()->children.push_back(cell);
		cell->str = stringf("$specify$%d", autoidx++);
		cell->children.push_back(new AstNode(AST_CELLTYPE));
		cell->children.back()->str = "$specrule";

		cell->children.push_back(new AstNode(AST_PARASET, AstNode::mkconst_str(*(yyvsp[-13].string))));
		cell->children.back()->str = "\\TYPE";

		cell->children.push_back(new AstNode(AST_PARASET, limit->t_min));
		cell->children.back()->str = "\\T_LIMIT_MIN";

		cell->children.push_back(new AstNode(AST_PARASET, limit->t_avg));
		cell->children.back()->str = "\\T_LIMIT_TYP";

		cell->children.push_back(new AstNode(AST_PARASET, limit->t_max));
		cell->children.back()->str = "\\T_LIMIT_MAX";

		cell->children.push_back(new AstNode(AST_PARASET, limit2 ? limit2->t_min : AstNode::mkconst_int(0, true)));
		cell->children.back()->str = "\\T_LIMIT2_MIN";

		cell->children.push_back(new AstNode(AST_PARASET, limit2 ? limit2->t_avg : AstNode::mkconst_int(0, true)));
		cell->children.back()->str = "\\T_LIMIT2_TYP";

		cell->children.push_back(new AstNode(AST_PARASET, limit2 ? limit2->t_max : AstNode::mkconst_int(0, true)));
		cell->children.back()->str = "\\T_LIMIT2_MAX";

		cell->children.push_back(new AstNode(AST_PARASET, src_pen));
		cell->children.back()->str = "\\SRC_PEN";

		cell->children.push_back(new AstNode(AST_PARASET, src_pol));
		cell->children.back()->str = "\\SRC_POL";

		cell->children.push_back(new AstNode(AST_PARASET, dst_pen));
		cell->children.back()->str = "\\DST_PEN";

		cell->children.push_back(new AstNode(AST_PARASET, dst_pol));
		cell->children.back()->str = "\\DST_POL";

		cell->children.push_back(new AstNode(AST_ARGUMENT, src_en));
		cell->children.back()->str = "\\SRC_EN";

		cell->children.push_back(new AstNode(AST_ARGUMENT, src_expr));
		cell->children.back()->str = "\\SRC";

		cell->children.push_back(new AstNode(AST_ARGUMENT, dst_en));
		cell->children.back()->str = "\\DST_EN";

		cell->children.push_back(new AstNode(AST_ARGUMENT, dst_expr));
		cell->children.back()->str = "\\DST";

		delete (yyvsp[-13].string);
	}
#line 3935 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 179:
#line 974 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_triple_ptr) = (yyvsp[0].specify_triple_ptr);
	}
#line 3943 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 180:
#line 977 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_triple_ptr) = nullptr;
	}
#line 3951 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 181:
#line 982 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 3959 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 182:
#line 985 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
	}
#line 3967 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 183:
#line 990 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 3975 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 184:
#line 993 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
	}
#line 3983 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 185:
#line 998 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_target_ptr) = new specify_target;
		(yyval.specify_target_ptr)->polarity_op = 0;
		(yyval.specify_target_ptr)->dst = (yyvsp[0].ast);
		(yyval.specify_target_ptr)->dat = nullptr;
	}
#line 3994 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 186:
#line 1004 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_target_ptr) = new specify_target;
		(yyval.specify_target_ptr)->polarity_op = 0;
		(yyval.specify_target_ptr)->dst = (yyvsp[-3].ast);
		(yyval.specify_target_ptr)->dat = (yyvsp[-1].ast);
	}
#line 4005 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 187:
#line 1010 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_target_ptr) = new specify_target;
		(yyval.specify_target_ptr)->polarity_op = '-';
		(yyval.specify_target_ptr)->dst = (yyvsp[-3].ast);
		(yyval.specify_target_ptr)->dat = (yyvsp[-1].ast);
	}
#line 4016 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 188:
#line 1016 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_target_ptr) = new specify_target;
		(yyval.specify_target_ptr)->polarity_op = '+';
		(yyval.specify_target_ptr)->dst = (yyvsp[-3].ast);
		(yyval.specify_target_ptr)->dat = (yyvsp[-1].ast);
	}
#line 4027 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 189:
#line 1024 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ch) = 'p'; }
#line 4033 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 190:
#line 1025 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ch) = 'n'; }
#line 4039 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 191:
#line 1026 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ch) = 0; }
#line 4045 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 192:
#line 1029 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_rise_fall_ptr) = new specify_rise_fall;
		(yyval.specify_rise_fall_ptr)->rise = *(yyvsp[0].specify_triple_ptr);
		(yyval.specify_rise_fall_ptr)->fall.t_min = (yyvsp[0].specify_triple_ptr)->t_min->clone();
		(yyval.specify_rise_fall_ptr)->fall.t_avg = (yyvsp[0].specify_triple_ptr)->t_avg->clone();
		(yyval.specify_rise_fall_ptr)->fall.t_max = (yyvsp[0].specify_triple_ptr)->t_max->clone();
		delete (yyvsp[0].specify_triple_ptr);
	}
#line 4058 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 193:
#line 1037 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_rise_fall_ptr) = new specify_rise_fall;
		(yyval.specify_rise_fall_ptr)->rise = *(yyvsp[-3].specify_triple_ptr);
		(yyval.specify_rise_fall_ptr)->fall = *(yyvsp[-1].specify_triple_ptr);
		delete (yyvsp[-3].specify_triple_ptr);
		delete (yyvsp[-1].specify_triple_ptr);
	}
#line 4070 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 194:
#line 1044 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_rise_fall_ptr) = new specify_rise_fall;
		(yyval.specify_rise_fall_ptr)->rise = *(yyvsp[-5].specify_triple_ptr);
		(yyval.specify_rise_fall_ptr)->fall = *(yyvsp[-3].specify_triple_ptr);
		delete (yyvsp[-5].specify_triple_ptr);
		delete (yyvsp[-3].specify_triple_ptr);
        delete (yyvsp[-1].specify_triple_ptr);
        log_file_warning(current_filename, get_line_num(), "Path delay expressions beyond rise/fall not currently supported. Ignoring.\n");
	}
#line 4084 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 195:
#line 1053 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_rise_fall_ptr) = new specify_rise_fall;
		(yyval.specify_rise_fall_ptr)->rise = *(yyvsp[-11].specify_triple_ptr);
		(yyval.specify_rise_fall_ptr)->fall = *(yyvsp[-9].specify_triple_ptr);
		delete (yyvsp[-11].specify_triple_ptr);
		delete (yyvsp[-9].specify_triple_ptr);
        delete (yyvsp[-7].specify_triple_ptr);
        delete (yyvsp[-5].specify_triple_ptr);
        delete (yyvsp[-3].specify_triple_ptr);
        delete (yyvsp[-1].specify_triple_ptr);
        log_file_warning(current_filename, get_line_num(), "Path delay expressions beyond rise/fall not currently supported. Ignoring.\n");
	}
#line 4101 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 196:
#line 1065 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_rise_fall_ptr) = new specify_rise_fall;
		(yyval.specify_rise_fall_ptr)->rise = *(yyvsp[-23].specify_triple_ptr);
		(yyval.specify_rise_fall_ptr)->fall = *(yyvsp[-21].specify_triple_ptr);
		delete (yyvsp[-23].specify_triple_ptr);
		delete (yyvsp[-21].specify_triple_ptr);
        delete (yyvsp[-19].specify_triple_ptr);
        delete (yyvsp[-17].specify_triple_ptr);
        delete (yyvsp[-15].specify_triple_ptr);
        delete (yyvsp[-13].specify_triple_ptr);
        delete (yyvsp[-11].specify_triple_ptr);
        delete (yyvsp[-9].specify_triple_ptr);
        delete (yyvsp[-7].specify_triple_ptr);
        delete (yyvsp[-5].specify_triple_ptr);
        delete (yyvsp[-3].specify_triple_ptr);
        delete (yyvsp[-1].specify_triple_ptr);
        log_file_warning(current_filename, get_line_num(), "Path delay expressions beyond rise/fall not currently supported. Ignoring.\n");
	}
#line 4124 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 197:
#line 1085 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_triple_ptr) = new specify_triple;
		(yyval.specify_triple_ptr)->t_min = (yyvsp[0].ast);
		(yyval.specify_triple_ptr)->t_avg = (yyvsp[0].ast)->clone();
		(yyval.specify_triple_ptr)->t_max = (yyvsp[0].ast)->clone();
	}
#line 4135 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 198:
#line 1091 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_triple_ptr) = new specify_triple;
		(yyval.specify_triple_ptr)->t_min = (yyvsp[-4].ast);
		(yyval.specify_triple_ptr)->t_avg = (yyvsp[-2].ast);
		(yyval.specify_triple_ptr)->t_max = (yyvsp[0].ast);
	}
#line 4146 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 248:
#line 1214 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].ast); }
#line 4152 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 249:
#line 1217 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].ast); }
#line 4158 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 250:
#line 1218 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete (yyvsp[-4].ast);
		delete (yyvsp[-2].ast);
		delete (yyvsp[0].ast);
	}
#line 4168 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 251:
#line 1225 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].string); }
#line 4174 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 252:
#line 1226 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].ast); }
#line 4180 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 253:
#line 1231 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1->is_signed = true;
	}
#line 4188 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 255:
#line 1236 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (astbuf1->children.size() != 1)
			frontend_verilog_yyerror("Internal error in param_integer - should not happen?");
		astbuf1->children.push_back(new AstNode(AST_RANGE));
		astbuf1->children.back()->children.push_back(AstNode::mkconst_int(31, true));
		astbuf1->children.back()->children.push_back(AstNode::mkconst_int(0, true));
		astbuf1->is_signed = true;
	}
#line 4201 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 257:
#line 1246 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (astbuf1->children.size() != 1)
			frontend_verilog_yyerror("Parameter already declared as integer, cannot set to real.");
		astbuf1->children.push_back(new AstNode(AST_REALVALUE));
	}
#line 4211 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 259:
#line 1253 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].ast) != NULL) {
			if (astbuf1->children.size() != 1)
				frontend_verilog_yyerror("integer/real parameters should not have a range.");
			astbuf1->children.push_back((yyvsp[0].ast));
		}
	}
#line 4223 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 261:
#line 1263 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1->is_custom_type = true;
		astbuf1->children.push_back(new AstNode(AST_WIRETYPE));
		astbuf1->children.back()->str = *(yyvsp[0].string);
	}
#line 4233 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 262:
#line 1270 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = new AstNode(AST_PARAMETER);
		astbuf1->children.push_back(AstNode::mkconst_int(0, true));
		append_attr(astbuf1, (yyvsp[-1].al));
	}
#line 4243 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 263:
#line 1274 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
	}
#line 4251 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 264:
#line 1279 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = new AstNode(AST_LOCALPARAM);
		astbuf1->children.push_back(AstNode::mkconst_int(0, true));
		append_attr(astbuf1, (yyvsp[-1].al));
	}
#line 4261 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 265:
#line 1283 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
	}
#line 4269 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 268:
#line 1291 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node;
		if (astbuf1 == nullptr) {
			if (!sv_mode)
				frontend_verilog_yyerror("In pure Verilog (not SystemVerilog), parameter/localparam with an initializer must use the parameter/localparam keyword");
			node = new AstNode(AST_PARAMETER);
			node->children.push_back(AstNode::mkconst_int(0, true));
		} else {
			node = astbuf1->clone();
		}
		node->str = *(yyvsp[-2].string);
		delete node->children[0];
		node->children[0] = (yyvsp[0].ast);
		ast_stack.back()->children.push_back(node);
		delete (yyvsp[-2].string);
	}
#line 4290 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 272:
#line 1315 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_DEFPARAM);
		node->children.push_back((yyvsp[-2].ast));
		node->children.push_back((yyvsp[0].ast));
		if ((yyvsp[-3].ast) != NULL)
			node->children.push_back((yyvsp[-3].ast));
		ast_stack.back()->children.push_back(node);
	}
#line 4303 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 273:
#line 1324 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		static int enum_count;
		// create parent node for the enum
		astbuf2 = new AstNode(AST_ENUM);
		ast_stack.back()->children.push_back(astbuf2);
		astbuf2->str = std::string("$enum");
		astbuf2->str += std::to_string(enum_count++);
		// create the template for the names
		astbuf1 = new AstNode(AST_ENUM_ITEM);
		astbuf1->children.push_back(AstNode::mkconst_int(0, true));
	 }
#line 4319 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 274:
#line 1334 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {  // create template for the enum vars
								auto tnode = astbuf1->clone();
								delete astbuf1;
								astbuf1 = tnode;
								tnode->type = AST_WIRE;
								tnode->attributes["\\enum_type"] = AstNode::mkconst_str(astbuf2->str);
								// drop constant but keep any range
								delete tnode->children[0];
								tnode->children.erase(tnode->children.begin()); }
#line 4333 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 277:
#line 1347 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {astbuf1->is_reg = true; addRange(astbuf1); }
#line 4339 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 278:
#line 1350 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {astbuf1->is_reg=true; addRange(astbuf1); }
#line 4345 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 279:
#line 1353 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {astbuf1->is_reg = true;}
#line 4351 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 280:
#line 1354 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {astbuf1->is_logic = true;}
#line 4357 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 283:
#line 1363 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		// put in fn
		log_assert(astbuf1);
		log_assert(astbuf2);
		auto node = astbuf1->clone();
		node->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		delete node->children[0];
		node->children[0] = (yyvsp[0].ast) ? (yyvsp[0].ast) : new AstNode(AST_NONE);
		astbuf2->children.push_back(node);
	}
#line 4373 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 284:
#line 1377 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 4379 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 285:
#line 1378 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = NULL; }
#line 4385 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 288:
#line 1386 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		log_assert(astbuf1);
		log_assert(astbuf2);
		auto node = astbuf1->clone();
		ast_stack.back()->children.push_back(node);
		node->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
		node->is_enum = true;
	}
#line 4399 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 289:
#line 1397 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		//enum_type creates astbuf1 for use by typedef only
		delete astbuf1;
	}
#line 4408 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 290:
#line 1404 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		albuf = (yyvsp[-2].al);
		astbuf1 = (yyvsp[-1].ast);
		astbuf2 = (yyvsp[0].ast);
		if (astbuf1->range_left >= 0 && astbuf1->range_right >= 0) {
			if (astbuf2) {
				frontend_verilog_yyerror("integer/genvar types cannot have packed dimensions.");
			} else {
				astbuf2 = new AstNode(AST_RANGE);
				astbuf2->children.push_back(AstNode::mkconst_int(astbuf1->range_left, true));
				astbuf2->children.push_back(AstNode::mkconst_int(astbuf1->range_right, true));
			}
		}
		if (astbuf2 && astbuf2->children.size() != 2)
			frontend_verilog_yyerror("wire/reg/logic packed dimension must be of the form: [<expr>:<expr>], [<expr>+:<expr>], or [<expr>-:<expr>]");
	}
#line 4429 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 291:
#line 1419 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
		if (astbuf2 != NULL)
			delete astbuf2;
		free_attr(albuf);
	}
#line 4440 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 293:
#line 1425 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_WIRE));
		ast_stack.back()->children.back()->str = *(yyvsp[0].string);
		append_attr(ast_stack.back()->children.back(), (yyvsp[-2].al));
		ast_stack.back()->children.push_back(new AstNode(AST_ASSIGN, new AstNode(AST_IDENTIFIER), AstNode::mkconst_int(0, false, 1)));
		ast_stack.back()->children.back()->children[0]->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 4453 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 295:
#line 1433 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_WIRE));
		ast_stack.back()->children.back()->str = *(yyvsp[0].string);
		append_attr(ast_stack.back()->children.back(), (yyvsp[-2].al));
		ast_stack.back()->children.push_back(new AstNode(AST_ASSIGN, new AstNode(AST_IDENTIFIER), AstNode::mkconst_int(1, false, 1)));
		ast_stack.back()->children.back()->children[0]->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 4466 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 298:
#line 1444 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *wire_node = ast_stack.back()->children.at(GetSize(ast_stack.back()->children)-2)->clone();
		AstNode *assign_node = ast_stack.back()->children.at(GetSize(ast_stack.back()->children)-1)->clone();
		wire_node->str = *(yyvsp[0].string);
		assign_node->children[0]->str = *(yyvsp[0].string);
		ast_stack.back()->children.push_back(wire_node);
		ast_stack.back()->children.push_back(assign_node);
		delete (yyvsp[0].string);
	}
#line 4480 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 301:
#line 1458 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		bool attr_anyconst = false;
		bool attr_anyseq = false;
		bool attr_allconst = false;
		bool attr_allseq = false;
		if (ast_stack.back()->children.back()->get_bool_attribute("\\anyconst")) {
			delete ast_stack.back()->children.back()->attributes.at("\\anyconst");
			ast_stack.back()->children.back()->attributes.erase("\\anyconst");
			attr_anyconst = true;
		}
		if (ast_stack.back()->children.back()->get_bool_attribute("\\anyseq")) {
			delete ast_stack.back()->children.back()->attributes.at("\\anyseq");
			ast_stack.back()->children.back()->attributes.erase("\\anyseq");
			attr_anyseq = true;
		}
		if (ast_stack.back()->children.back()->get_bool_attribute("\\allconst")) {
			delete ast_stack.back()->children.back()->attributes.at("\\allconst");
			ast_stack.back()->children.back()->attributes.erase("\\allconst");
			attr_allconst = true;
		}
		if (ast_stack.back()->children.back()->get_bool_attribute("\\allseq")) {
			delete ast_stack.back()->children.back()->attributes.at("\\allseq");
			ast_stack.back()->children.back()->attributes.erase("\\allseq");
			attr_allseq = true;
		}
		if (current_wire_rand || attr_anyconst || attr_anyseq || attr_allconst || attr_allseq) {
			AstNode *wire = new AstNode(AST_IDENTIFIER);
			AstNode *fcall = new AstNode(AST_FCALL);
			wire->str = ast_stack.back()->children.back()->str;
			fcall->str = current_wire_const ? "\\$anyconst" : "\\$anyseq";
			if (attr_anyconst)
				fcall->str = "\\$anyconst";
			if (attr_anyseq)
				fcall->str = "\\$anyseq";
			if (attr_allconst)
				fcall->str = "\\$allconst";
			if (attr_allseq)
				fcall->str = "\\$allseq";
			fcall->attributes["\\reg"] = AstNode::mkconst_str(RTLIL::unescape_id(wire->str));
			ast_stack.back()->children.push_back(new AstNode(AST_ASSIGN, wire, fcall));
		}
	}
#line 4527 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 302:
#line 1500 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *wire = new AstNode(AST_IDENTIFIER);
		wire->str = ast_stack.back()->children.back()->str;
		if (astbuf1->is_input) {
			if (astbuf1->attributes.count("\\defaultvalue"))
				delete astbuf1->attributes.at("\\defaultvalue");
			astbuf1->attributes["\\defaultvalue"] = (yyvsp[0].ast);
		}
		else if (astbuf1->is_reg || astbuf1->is_logic){
			AstNode *assign = new AstNode(AST_ASSIGN_LE, wire, (yyvsp[0].ast));
			AstNode *block = new AstNode(AST_BLOCK, assign);
			AstNode *init = new AstNode(AST_INITIAL, block);

			SET_AST_NODE_LOC(assign, (yylsp[-2]), (yylsp[0]));
			SET_AST_NODE_LOC(block, (yylsp[-2]), (yylsp[0]));
			SET_AST_NODE_LOC(init, (yylsp[-2]), (yylsp[0]));

			ast_stack.back()->children.push_back(init);
		}
		else {
			AstNode *assign = new AstNode(AST_ASSIGN, wire, (yyvsp[0].ast));
			SET_AST_NODE_LOC(assign, (yylsp[-2]), (yylsp[0]));
			ast_stack.back()->children.push_back(assign);
		}

	}
#line 4558 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 303:
#line 1528 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (astbuf1 == nullptr)
			frontend_verilog_yyerror("Internal error - should not happen - no AST_WIRE node.");
		AstNode *node = astbuf1->clone();
		node->str = *(yyvsp[-1].string);
		append_attr_clone(node, albuf);
		if (astbuf2 != NULL)
			node->children.push_back(astbuf2->clone());
		if ((yyvsp[0].ast) != NULL) {
			if (node->is_input || node->is_output)
				frontend_verilog_yyerror("input/output/inout ports cannot have unpacked dimensions.");
			if (!astbuf2 && !node->is_custom_type) {
				AstNode *rng = new AstNode(AST_RANGE);
				rng->children.push_back(AstNode::mkconst_int(0, true));
				rng->children.push_back(AstNode::mkconst_int(0, true));
				node->children.push_back(rng);
			}
			node->type = AST_MEMORY;
			auto *rangeNode = (yyvsp[0].ast);
			if (rangeNode->type == AST_RANGE && rangeNode->children.size() == 1) {
				// SV array size [n], rewrite as [n-1:0]
				rangeNode->children[0] = new AstNode(AST_SUB, rangeNode->children[0], AstNode::mkconst_int(1, true));
				rangeNode->children.push_back(AstNode::mkconst_int(0, false));
			}
			node->children.push_back(rangeNode);
		}
		if (current_function_or_task == NULL) {
			if (do_not_require_port_stubs && (node->is_input || node->is_output) && port_stubs.count(*(yyvsp[-1].string)) == 0) {
				port_stubs[*(yyvsp[-1].string)] = ++port_counter;
			}
			if (port_stubs.count(*(yyvsp[-1].string)) != 0) {
				if (!node->is_input && !node->is_output)
					frontend_verilog_yyerror("Module port `%s' is neither input nor output.", (yyvsp[-1].string)->c_str());
				if (node->is_reg && node->is_input && !node->is_output && !sv_mode)
					frontend_verilog_yyerror("Input port `%s' is declared as register.", (yyvsp[-1].string)->c_str());
				node->port_id = port_stubs[*(yyvsp[-1].string)];
				port_stubs.erase(*(yyvsp[-1].string));
			} else {
				if (node->is_input || node->is_output)
					frontend_verilog_yyerror("Module port `%s' is not declared in module header.", (yyvsp[-1].string)->c_str());
			}
		} else {
			if (node->is_input || node->is_output)
				node->port_id = current_function_or_task_port_id++;
		}
		//FIXME: for some reason, TOK_ID has a location which always points to one column *after* the real last column...
		SET_AST_NODE_LOC(node, (yylsp[-1]), (yylsp[-1]));
		ast_stack.back()->children.push_back(node);

		delete (yyvsp[-1].string);
	}
#line 4614 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 307:
#line 1587 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ASSIGN, (yyvsp[-2].ast), (yyvsp[0].ast));
		SET_AST_NODE_LOC(node, (yyloc), (yyloc));
		ast_stack.back()->children.push_back(node);
	}
#line 4624 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 308:
#line 1594 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = (yyvsp[-4].ast);
		astbuf2 = (yyvsp[-3].ast);
		if (astbuf1->range_left >= 0 && astbuf1->range_right >= 0) {
			if (astbuf2) {
				frontend_verilog_yyerror("integer/genvar types cannot have packed dimensions.");
			} else {
				astbuf2 = new AstNode(AST_RANGE);
				astbuf2->children.push_back(AstNode::mkconst_int(astbuf1->range_left, true));
				astbuf2->children.push_back(AstNode::mkconst_int(astbuf1->range_right, true));
			}
		}
		if (astbuf2 && astbuf2->children.size() != 2)
			frontend_verilog_yyerror("wire/reg/logic packed dimension must be of the form: [<expr>:<expr>], [<expr>+:<expr>], or [<expr>-:<expr>]");
		if (astbuf2)
			astbuf1->children.push_back(astbuf2);

		if ((yyvsp[-1].ast) != NULL) {
			if (!astbuf2) {
				AstNode *rng = new AstNode(AST_RANGE);
				rng->children.push_back(AstNode::mkconst_int(0, true));
				rng->children.push_back(AstNode::mkconst_int(0, true));
				astbuf1->children.push_back(rng);
			}
			astbuf1->type = AST_MEMORY;
			auto *rangeNode = (yyvsp[-1].ast);
			if (rangeNode->type == AST_RANGE && rangeNode->children.size() == 1) {
				// SV array size [n], rewrite as [n-1:0]
				rangeNode->children[0] = new AstNode(AST_SUB, rangeNode->children[0], AstNode::mkconst_int(1, true));
				rangeNode->children.push_back(AstNode::mkconst_int(0, false));
			}
			astbuf1->children.push_back(rangeNode);
		}

		ast_stack.back()->children.push_back(new AstNode(AST_TYPEDEF, astbuf1));
		ast_stack.back()->children.back()->str = *(yyvsp[-2].string);
	}
#line 4666 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 309:
#line 1631 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_TYPEDEF, astbuf1));
		ast_stack.back()->children.back()->str = *(yyvsp[-1].string);
	}
#line 4675 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 310:
#line 1638 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = new AstNode(AST_CELL);
		append_attr(astbuf1, (yyvsp[-1].al));
		astbuf1->children.push_back(new AstNode(AST_CELLTYPE));
		astbuf1->children[0]->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 4687 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 311:
#line 1644 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
	}
#line 4695 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 312:
#line 1647 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = new AstNode(AST_PRIMITIVE);
		astbuf1->str = *(yyvsp[-1].string);
		append_attr(astbuf1, (yyvsp[-2].al));
		delete (yyvsp[-1].string);
	}
#line 4706 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 313:
#line 1652 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
	}
#line 4714 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 314:
#line 1657 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = (yyvsp[0].string);
	}
#line 4722 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 315:
#line 1660 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = new std::string("or");
	}
#line 4730 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 318:
#line 1669 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf2 = astbuf1->clone();
		if (astbuf2->type != AST_PRIMITIVE)
			astbuf2->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
		ast_stack.back()->children.push_back(astbuf2);
	}
#line 4742 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 319:
#line 1675 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(astbuf2, (yylsp[-4]), (yyloc));
	}
#line 4750 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 320:
#line 1678 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf2 = astbuf1->clone();
		if (astbuf2->type != AST_PRIMITIVE)
			astbuf2->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		ast_stack.back()->children.push_back(new AstNode(AST_CELLARRAY, (yyvsp[0].ast), astbuf2));
	}
#line 4762 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 321:
#line 1684 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(astbuf2, (yylsp[-5]), (yyloc));
		SET_AST_NODE_LOC(astbuf3, (yylsp[-5]), (yyloc));
	}
#line 4771 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 325:
#line 1695 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf2 = astbuf1->clone();
		ast_stack.back()->children.push_back(astbuf2);
	}
#line 4780 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 332:
#line 1708 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_PARASET);
		astbuf1->children.push_back(node);
		node->children.push_back((yyvsp[0].ast));
	}
#line 4790 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 333:
#line 1713 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_PARASET);
		node->str = *(yyvsp[-3].string);
		astbuf1->children.push_back(node);
		node->children.push_back((yyvsp[-1].ast));
		delete (yyvsp[-3].string);
	}
#line 4802 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 334:
#line 1722 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		// remove empty args from end of list
		while (!astbuf2->children.empty()) {
			AstNode *node = astbuf2->children.back();
			if (node->type != AST_ARGUMENT) break;
			if (!node->children.empty()) break;
			if (!node->str.empty()) break;
			astbuf2->children.pop_back();
			delete node;
		}

		// check port types
		bool has_positional_args = false;
		bool has_named_args = false;
		for (auto node : astbuf2->children) {
			if (node->type != AST_ARGUMENT) continue;
			if (node->str.empty())
				has_positional_args = true;
			else
				has_named_args = true;
		}

		if (has_positional_args && has_named_args)
			frontend_verilog_yyerror("Mix of positional and named cell ports.");
	}
#line 4832 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 337:
#line 1752 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ARGUMENT);
		astbuf2->children.push_back(node);
		free_attr((yyvsp[0].al));
	}
#line 4842 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 338:
#line 1757 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ARGUMENT);
		astbuf2->children.push_back(node);
		node->children.push_back((yyvsp[0].ast));
		free_attr((yyvsp[-1].al));
	}
#line 4853 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 339:
#line 1763 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ARGUMENT);
		node->str = *(yyvsp[-3].string);
		astbuf2->children.push_back(node);
		node->children.push_back((yyvsp[-1].ast));
		delete (yyvsp[-3].string);
		free_attr((yyvsp[-5].al));
	}
#line 4866 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 340:
#line 1771 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ARGUMENT);
		node->str = *(yyvsp[-2].string);
		astbuf2->children.push_back(node);
		delete (yyvsp[-2].string);
		free_attr((yyvsp[-4].al));
	}
#line 4878 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 341:
#line 1778 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ARGUMENT);
		node->str = *(yyvsp[0].string);
		astbuf2->children.push_back(node);
		node->children.push_back(new AstNode(AST_IDENTIFIER));
		node->children.back()->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
		free_attr((yyvsp[-2].al));
	}
#line 4892 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 342:
#line 1787 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (!sv_mode)
			frontend_verilog_yyerror("Wildcard port connections are only supported in SystemVerilog mode.");
		astbuf2->attributes[ID(wildcard_port_conns)] = AstNode::mkconst_int(1, false);
	}
#line 4902 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 343:
#line 1794 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 4910 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 344:
#line 1797 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = true;
	}
#line 4918 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 345:
#line 1802 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 4926 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 346:
#line 1805 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = true;
	}
#line 4934 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 347:
#line 1810 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ALWAYS);
		append_attr(node, (yyvsp[-1].al));
		if ((yyvsp[0].boolean))
			node->attributes[ID(always_ff)] = AstNode::mkconst_int(1, false);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 4947 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 348:
#line 1817 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
	}
#line 4957 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 349:
#line 1821 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
		ast_stack.pop_back();

		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[-4]), (yyloc));
		ast_stack.pop_back();

		SET_RULE_LOC((yyloc), (yylsp[-4]), (yyloc));
	}
#line 4971 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 350:
#line 1830 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ALWAYS);
		append_attr(node, (yyvsp[-1].al));
		if ((yyvsp[0].boolean))
			node->attributes[ID(always_latch)] = AstNode::mkconst_int(1, false);
		else
			node->attributes[ID(always_comb)] = AstNode::mkconst_int(1, false);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
	}
#line 4989 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 351:
#line 1842 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 4998 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 352:
#line 1846 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_INITIAL);
		append_attr(node, (yyvsp[-1].al));
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
	}
#line 5012 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 353:
#line 1854 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5021 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 363:
#line 1873 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_POSEDGE);
		ast_stack.back()->children.push_back(node);
		node->children.push_back((yyvsp[0].ast));
	}
#line 5031 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 364:
#line 1878 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_NEGEDGE);
		ast_stack.back()->children.push_back(node);
		node->children.push_back((yyvsp[0].ast));
	}
#line 5041 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 365:
#line 1883 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_EDGE);
		ast_stack.back()->children.push_back(node);
		node->children.push_back((yyvsp[0].ast));
	}
#line 5051 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 366:
#line 1890 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = (yyvsp[0].string);
	}
#line 5059 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 367:
#line 1893 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = NULL;
	}
#line 5067 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 368:
#line 1898 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = (yyvsp[-1].string);
	}
#line 5075 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 369:
#line 1901 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = NULL;
	}
#line 5083 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 370:
#line 1906 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = true;
	}
#line 5091 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 371:
#line 1909 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 5099 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 372:
#line 1912 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 5107 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 373:
#line 1917 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
        AstNode *modport = new AstNode(AST_MODPORT);
        ast_stack.back()->children.push_back(modport);
        ast_stack.push_back(modport);
        modport->str = *(yyvsp[0].string);
        delete (yyvsp[0].string);
    }
#line 5119 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 374:
#line 1923 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
        ast_stack.pop_back();
        log_assert(ast_stack.size() == 2);
    }
#line 5128 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 382:
#line 1939 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
        AstNode *modport_member = new AstNode(AST_MODPORTMEMBER);
        ast_stack.back()->children.push_back(modport_member);
        modport_member->str = *(yyvsp[0].string);
        modport_member->is_input = current_modport_input;
        modport_member->is_output = current_modport_output;
        delete (yyvsp[0].string);
    }
#line 5141 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 383:
#line 1949 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {current_modport_input = 1; current_modport_output = 0;}
#line 5147 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 384:
#line 1949 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {current_modport_input = 0; current_modport_output = 1;}
#line 5153 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 385:
#line 1952 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (noassert_mode) {
			delete (yyvsp[-2].ast);
		} else {
			AstNode *node = new AstNode(assume_asserts_mode ? AST_ASSUME : AST_ASSERT, (yyvsp[-2].ast));
			if ((yyvsp[-6].string) != nullptr)
				node->str = *(yyvsp[-6].string);
			ast_stack.back()->children.push_back(node);
		}
		if ((yyvsp[-6].string) != nullptr)
			delete (yyvsp[-6].string);
	}
#line 5170 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 386:
#line 1964 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (noassume_mode) {
			delete (yyvsp[-2].ast);
		} else {
			AstNode *node = new AstNode(assert_assumes_mode ? AST_ASSERT : AST_ASSUME, (yyvsp[-2].ast));
			if ((yyvsp[-6].string) != nullptr)
				node->str = *(yyvsp[-6].string);
			ast_stack.back()->children.push_back(node);
		}
		if ((yyvsp[-6].string) != nullptr)
			delete (yyvsp[-6].string);
	}
#line 5187 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 387:
#line 1976 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (noassert_mode) {
			delete (yyvsp[-2].ast);
		} else {
			AstNode *node = new AstNode(assume_asserts_mode ? AST_FAIR : AST_LIVE, (yyvsp[-2].ast));
			if ((yyvsp[-7].string) != nullptr)
				node->str = *(yyvsp[-7].string);
			ast_stack.back()->children.push_back(node);
		}
		if ((yyvsp[-7].string) != nullptr)
			delete (yyvsp[-7].string);
	}
#line 5204 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 388:
#line 1988 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (noassume_mode) {
			delete (yyvsp[-2].ast);
		} else {
			AstNode *node = new AstNode(assert_assumes_mode ? AST_LIVE : AST_FAIR, (yyvsp[-2].ast));
			if ((yyvsp[-7].string) != nullptr)
				node->str = *(yyvsp[-7].string);
			ast_stack.back()->children.push_back(node);
		}
		if ((yyvsp[-7].string) != nullptr)
			delete (yyvsp[-7].string);
	}
#line 5221 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 389:
#line 2000 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_COVER, (yyvsp[-2].ast));
		if ((yyvsp[-6].string) != nullptr) {
			node->str = *(yyvsp[-6].string);
			delete (yyvsp[-6].string);
		}
		ast_stack.back()->children.push_back(node);
	}
#line 5234 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 390:
#line 2008 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_COVER, AstNode::mkconst_int(1, false));
		if ((yyvsp[-5].string) != nullptr) {
			node->str = *(yyvsp[-5].string);
			delete (yyvsp[-5].string);
		}
		ast_stack.back()->children.push_back(node);
	}
#line 5247 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 391:
#line 2016 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_COVER, AstNode::mkconst_int(1, false));
		if ((yyvsp[-2].string) != nullptr) {
			node->str = *(yyvsp[-2].string);
			delete (yyvsp[-2].string);
		}
		ast_stack.back()->children.push_back(node);
	}
#line 5260 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 392:
#line 2024 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (norestrict_mode) {
			delete (yyvsp[-2].ast);
		} else {
			AstNode *node = new AstNode(AST_ASSUME, (yyvsp[-2].ast));
			if ((yyvsp[-6].string) != nullptr)
				node->str = *(yyvsp[-6].string);
			ast_stack.back()->children.push_back(node);
		}
		if (!(yyvsp[-4].boolean))
			log_file_warning(current_filename, get_line_num(), "SystemVerilog does not allow \"restrict\" without \"property\".\n");
		if ((yyvsp[-6].string) != nullptr)
			delete (yyvsp[-6].string);
	}
#line 5279 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 393:
#line 2038 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (norestrict_mode) {
			delete (yyvsp[-2].ast);
		} else {
			AstNode *node = new AstNode(AST_FAIR, (yyvsp[-2].ast));
			if ((yyvsp[-7].string) != nullptr)
				node->str = *(yyvsp[-7].string);
			ast_stack.back()->children.push_back(node);
		}
		if (!(yyvsp[-5].boolean))
			log_file_warning(current_filename, get_line_num(), "SystemVerilog does not allow \"restrict\" without \"property\".\n");
		if ((yyvsp[-7].string) != nullptr)
			delete (yyvsp[-7].string);
	}
#line 5298 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 394:
#line 2054 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(assume_asserts_mode ? AST_ASSUME : AST_ASSERT, (yyvsp[-2].ast)));
		if ((yyvsp[-6].string) != nullptr) {
			ast_stack.back()->children.back()->str = *(yyvsp[-6].string);
			delete (yyvsp[-6].string);
		}
	}
#line 5310 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 395:
#line 2061 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_ASSUME, (yyvsp[-2].ast)));
		if ((yyvsp[-6].string) != nullptr) {
			ast_stack.back()->children.back()->str = *(yyvsp[-6].string);
			delete (yyvsp[-6].string);
		}
	}
#line 5322 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 396:
#line 2068 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(assume_asserts_mode ? AST_FAIR : AST_LIVE, (yyvsp[-2].ast)));
		if ((yyvsp[-7].string) != nullptr) {
			ast_stack.back()->children.back()->str = *(yyvsp[-7].string);
			delete (yyvsp[-7].string);
		}
	}
#line 5334 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 397:
#line 2075 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_FAIR, (yyvsp[-2].ast)));
		if ((yyvsp[-7].string) != nullptr) {
			ast_stack.back()->children.back()->str = *(yyvsp[-7].string);
			delete (yyvsp[-7].string);
		}
	}
#line 5346 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 398:
#line 2082 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_COVER, (yyvsp[-2].ast)));
		if ((yyvsp[-6].string) != nullptr) {
			ast_stack.back()->children.back()->str = *(yyvsp[-6].string);
			delete (yyvsp[-6].string);
		}
	}
#line 5358 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 399:
#line 2089 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (norestrict_mode) {
			delete (yyvsp[-2].ast);
		} else {
			ast_stack.back()->children.push_back(new AstNode(AST_ASSUME, (yyvsp[-2].ast)));
			if ((yyvsp[-6].string) != nullptr) {
				ast_stack.back()->children.back()->str = *(yyvsp[-6].string);
				delete (yyvsp[-6].string);
			}
		}
	}
#line 5374 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 400:
#line 2100 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (norestrict_mode) {
			delete (yyvsp[-2].ast);
		} else {
			ast_stack.back()->children.push_back(new AstNode(AST_FAIR, (yyvsp[-2].ast)));
			if ((yyvsp[-7].string) != nullptr) {
				ast_stack.back()->children.back()->str = *(yyvsp[-7].string);
				delete (yyvsp[-7].string);
			}
		}
	}
#line 5390 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 401:
#line 2113 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ASSIGN_EQ, (yyvsp[-3].ast), (yyvsp[0].ast));
		ast_stack.back()->children.push_back(node);
	}
#line 5399 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 402:
#line 2117 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ASSIGN_EQ, (yyvsp[-1].ast), new AstNode(AST_ADD, (yyvsp[-1].ast)->clone(), AstNode::mkconst_int(1, true)));
		ast_stack.back()->children.push_back(node);
	}
#line 5408 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 403:
#line 2121 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ASSIGN_EQ, (yyvsp[-1].ast), new AstNode(AST_SUB, (yyvsp[-1].ast)->clone(), AstNode::mkconst_int(1, true)));
		ast_stack.back()->children.push_back(node);
	}
#line 5417 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 404:
#line 2125 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ASSIGN_LE, (yyvsp[-3].ast), (yyvsp[0].ast));
		ast_stack.back()->children.push_back(node);
	}
#line 5426 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 414:
#line 2135 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_TCALL);
		node->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[0].al));
	}
#line 5439 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 415:
#line 2142 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
	}
#line 5447 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 416:
#line 2145 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_TCALL);
		node->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[0].al));
	}
#line 5460 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 417:
#line 2152 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
	}
#line 5468 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 418:
#line 2155 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[-2].al));
		if ((yyvsp[0].string) != NULL)
			node->str = *(yyvsp[0].string);
	}
#line 5481 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 419:
#line 2162 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-4].string) != NULL && (yyvsp[0].string) != NULL && *(yyvsp[-4].string) != *(yyvsp[0].string))
			frontend_verilog_yyerror("Begin label (%s) and end label (%s) don't match.", (yyvsp[-4].string)->c_str()+1, (yyvsp[0].string)->c_str()+1);
		if ((yyvsp[-4].string) != NULL)
			delete (yyvsp[-4].string);
		if ((yyvsp[0].string) != NULL)
			delete (yyvsp[0].string);
		ast_stack.pop_back();
	}
#line 5495 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 420:
#line 2171 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_FOR);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[-2].al));
	}
#line 5506 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 421:
#line 2176 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back((yyvsp[0].ast));
	}
#line 5514 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 422:
#line 2178 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
	}
#line 5524 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 423:
#line 2182 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5534 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 424:
#line 2187 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_WHILE);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[-4].al));
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back((yyvsp[-1].ast));
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
	}
#line 5549 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 425:
#line 2196 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5559 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 426:
#line 2201 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_REPEAT);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[-4].al));
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back((yyvsp[-1].ast));
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
	}
#line 5574 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 427:
#line 2210 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5584 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 428:
#line 2215 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_CASE);
		AstNode *block = new AstNode(AST_BLOCK);
		AstNode *cond = new AstNode(AST_COND, AstNode::mkconst_int(1, false, 1), block);
		SET_AST_NODE_LOC(cond, (yylsp[-1]), (yylsp[-1]));
		ast_stack.back()->children.push_back(node);
		node->children.push_back(new AstNode(AST_REDUCE_BOOL, (yyvsp[-1].ast)));
		node->children.push_back(cond);
		ast_stack.push_back(node);
		ast_stack.push_back(block);
		append_attr(node, (yyvsp[-4].al));
	}
#line 5601 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 429:
#line 2226 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
	}
#line 5609 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 430:
#line 2228 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[-7]), (yylsp[0]));
		ast_stack.pop_back();
	}
#line 5619 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 431:
#line 2233 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_CASE, (yyvsp[-1].ast));
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[-4].al));
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[-1]), (yylsp[-1]));
	}
#line 5631 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 432:
#line 2239 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[-7]), (yylsp[0]));
		case_type_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5641 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 433:
#line 2246 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 5649 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 434:
#line 2249 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = (yyvsp[0].al);
	}
#line 5657 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 435:
#line 2252 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = true;
	}
#line 5665 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 436:
#line 2257 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].boolean)) (*(yyvsp[-1].al))["\\parallel_case"] = AstNode::mkconst_int(1, false);
		(yyval.al) = (yyvsp[-1].al);
	}
#line 5674 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 437:
#line 2263 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.push_back(0);
	}
#line 5682 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 438:
#line 2266 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.push_back('x');
	}
#line 5690 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 439:
#line 2269 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.push_back('z');
	}
#line 5698 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 440:
#line 2274 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (ast_stack.back()->attributes.count("\\full_case") == 0)
			ast_stack.back()->attributes["\\full_case"] = AstNode::mkconst_int(1, false);
	}
#line 5707 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 441:
#line 2278 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (ast_stack.back()->attributes.count("\\parallel_case") == 0)
			ast_stack.back()->attributes["\\parallel_case"] = AstNode::mkconst_int(1, false);
	}
#line 5716 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 445:
#line 2289 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *block = new AstNode(AST_BLOCK);
		AstNode *cond = new AstNode(AST_COND, new AstNode(AST_DEFAULT), block);
		SET_AST_NODE_LOC(cond, (yylsp[0]), (yylsp[0]));

		ast_stack.pop_back();
		ast_stack.back()->children.push_back(cond);
		ast_stack.push_back(block);
	}
#line 5730 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 446:
#line 2297 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
	}
#line 5738 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 450:
#line 2307 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(
				case_type_stack.size() && case_type_stack.back() == 'x' ? AST_CONDX :
				case_type_stack.size() && case_type_stack.back() == 'z' ? AST_CONDZ : AST_COND);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 5750 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 451:
#line 2313 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
		case_type_stack.push_back(0);
	}
#line 5761 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 452:
#line 2318 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.pop_back();
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5772 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 455:
#line 2330 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(
				case_type_stack.size() && case_type_stack.back() == 'x' ? AST_CONDX :
				case_type_stack.size() && case_type_stack.back() == 'z' ? AST_CONDZ : AST_COND);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 5784 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 456:
#line 2336 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.push_back(0);
	}
#line 5792 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 457:
#line 2338 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5801 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 460:
#line 2348 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_DEFAULT));
	}
#line 5809 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 461:
#line 2351 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_IDENTIFIER));
		ast_stack.back()->children.back()->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 5819 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 462:
#line 2356 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back((yyvsp[0].ast));
	}
#line 5827 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 463:
#line 2359 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back((yyvsp[0].ast));
	}
#line 5835 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 464:
#line 2364 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_PREFIX, (yyvsp[-3].ast), (yyvsp[0].ast));
		(yyval.ast)->str = *(yyvsp[-5].string);
		delete (yyvsp[-5].string);
	}
#line 5845 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 465:
#line 2369 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_IDENTIFIER, (yyvsp[0].ast));
		(yyval.ast)->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		if ((yyvsp[0].ast) == nullptr && ((yyval.ast)->str == "\\$initstate" ||
				(yyval.ast)->str == "\\$anyconst" || (yyval.ast)->str == "\\$anyseq" ||
				(yyval.ast)->str == "\\$allconst" || (yyval.ast)->str == "\\$allseq"))
			(yyval.ast)->type = AST_FCALL;
	}
#line 5859 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 466:
#line 2378 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_IDENTIFIER, (yyvsp[0].ast));
		(yyval.ast)->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
	}
#line 5869 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 467:
#line 2385 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 5877 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 468:
#line 2388 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 5885 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 469:
#line 2393 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_CONCAT);
		(yyval.ast)->children.push_back((yyvsp[0].ast));
	}
#line 5894 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 470:
#line 2397 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
		(yyval.ast)->children.push_back((yyvsp[-2].ast));
	}
#line 5903 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 477:
#line 2415 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back((yyvsp[0].ast));
	}
#line 5911 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 482:
#line 2428 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENFOR);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 5921 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 483:
#line 2432 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back((yyvsp[0].ast));
	}
#line 5929 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 484:
#line 2434 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
	}
#line 5937 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 485:
#line 2437 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENIF);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		ast_stack.back()->children.push_back((yyvsp[-1].ast));
	}
#line 5948 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 486:
#line 2442 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
	}
#line 5956 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 487:
#line 2445 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENCASE, (yyvsp[-1].ast));
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 5966 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 488:
#line 2449 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5975 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 489:
#line 2453 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENBLOCK);
		node->str = (yyvsp[0].string) ? *(yyvsp[0].string) : std::string();
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 5986 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 490:
#line 2458 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-4].string) != NULL)
			delete (yyvsp[-4].string);
		if ((yyvsp[0].string) != NULL)
			delete (yyvsp[0].string);
		ast_stack.pop_back();
	}
#line 5998 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 491:
#line 2465 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_TECALL);
		node->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 6010 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 492:
#line 2471 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
	}
#line 6018 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 493:
#line 2476 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENBLOCK);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 6028 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 494:
#line 2480 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
	}
#line 6036 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 499:
#line 2491 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 6044 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 500:
#line 2494 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_TERNARY);
		(yyval.ast)->children.push_back((yyvsp[-5].ast));
		(yyval.ast)->children.push_back((yyvsp[-2].ast));
		(yyval.ast)->children.push_back((yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-3].al));
	}
#line 6056 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 501:
#line 2503 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 6064 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 502:
#line 2506 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].string)->compare(0, 1, "'") != 0)
			frontend_verilog_yyerror("Cast operation must be applied on sized constants e.g. (<expr>)<constval> , while %s is not a sized constant.", (yyvsp[0].string)->c_str());
		AstNode *bits = (yyvsp[-2].ast);
		AstNode *val = const2ast(*(yyvsp[0].string), case_type_stack.size() == 0 ? 0 : case_type_stack.back(), !lib_mode);
		if (val == NULL)
			log_error("Value conversion failed: `%s'\n", (yyvsp[0].string)->c_str());
		(yyval.ast) = new AstNode(AST_TO_BITS, bits, val);
		delete (yyvsp[0].string);
	}
#line 6079 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 503:
#line 2516 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].string)->compare(0, 1, "'") != 0)
			frontend_verilog_yyerror("Cast operation must be applied on sized constants, e.g. <ID>\'d0, while %s is not a sized constant.", (yyvsp[0].string)->c_str());
		AstNode *bits = new AstNode(AST_IDENTIFIER);
		bits->str = *(yyvsp[-1].string);
		AstNode *val = const2ast(*(yyvsp[0].string), case_type_stack.size() == 0 ? 0 : case_type_stack.back(), !lib_mode);
		if (val == NULL)
			log_error("Value conversion failed: `%s'\n", (yyvsp[0].string)->c_str());
		(yyval.ast) = new AstNode(AST_TO_BITS, bits, val);
		delete (yyvsp[-1].string);
		delete (yyvsp[0].string);
	}
#line 6096 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 504:
#line 2528 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = const2ast(*(yyvsp[-1].string) + *(yyvsp[0].string), case_type_stack.size() == 0 ? 0 : case_type_stack.back(), !lib_mode);
		if ((yyval.ast) == NULL || (*(yyvsp[0].string))[0] != '\'')
			log_error("Value conversion failed: `%s%s'\n", (yyvsp[-1].string)->c_str(), (yyvsp[0].string)->c_str());
		delete (yyvsp[-1].string);
		delete (yyvsp[0].string);
	}
#line 6108 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 505:
#line 2535 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = const2ast(*(yyvsp[0].string), case_type_stack.size() == 0 ? 0 : case_type_stack.back(), !lib_mode);
		if ((yyval.ast) == NULL)
			log_error("Value conversion failed: `%s'\n", (yyvsp[0].string)->c_str());
		delete (yyvsp[0].string);
	}
#line 6119 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 506:
#line 2541 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REALVALUE);
		char *p = (char*)malloc(GetSize(*(yyvsp[0].string)) + 1), *q;
		for (int i = 0, j = 0; j < GetSize(*(yyvsp[0].string)); j++)
			if ((*(yyvsp[0].string))[j] != '_')
				p[i++] = (*(yyvsp[0].string))[j], p[i] = 0;
		(yyval.ast)->realvalue = strtod(p, &q);
		log_assert(*q == 0);
		delete (yyvsp[0].string);
		free(p);
	}
#line 6135 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 507:
#line 2552 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = AstNode::mkconst_str(*(yyvsp[0].string));
		delete (yyvsp[0].string);
	}
#line 6144 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 508:
#line 2556 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_FCALL);
		node->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[0].al));
	}
#line 6156 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 509:
#line 2562 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = ast_stack.back();
		ast_stack.pop_back();
	}
#line 6165 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 510:
#line 2566 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_TO_SIGNED, (yyvsp[-1].ast));
		append_attr((yyval.ast), (yyvsp[-3].al));
	}
#line 6174 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 511:
#line 2570 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_TO_UNSIGNED, (yyvsp[-1].ast));
		append_attr((yyval.ast), (yyvsp[-3].al));
	}
#line 6183 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 512:
#line 2574 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 6191 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 513:
#line 2577 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete (yyvsp[-5].ast);
		(yyval.ast) = (yyvsp[-3].ast);
		delete (yyvsp[-1].ast);
	}
#line 6201 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 514:
#line 2582 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 6209 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 515:
#line 2585 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REPLICATE, (yyvsp[-4].ast), (yyvsp[-2].ast));
	}
#line 6217 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 516:
#line 2588 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_NOT, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6226 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 517:
#line 2592 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_AND, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6235 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 518:
#line 2596 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_NOT, new AstNode(AST_BIT_AND, (yyvsp[-3].ast), (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6244 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 519:
#line 2600 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_OR, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6253 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 520:
#line 2604 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_NOT, new AstNode(AST_BIT_OR, (yyvsp[-3].ast), (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6262 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 521:
#line 2608 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_XOR, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6271 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 522:
#line 2612 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_XNOR, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6280 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 523:
#line 2616 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_AND, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6289 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 524:
#line 2620 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_AND, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
		(yyval.ast) = new AstNode(AST_LOGIC_NOT, (yyval.ast));
	}
#line 6299 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 525:
#line 2625 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_OR, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6308 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 526:
#line 2629 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_OR, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
		(yyval.ast) = new AstNode(AST_LOGIC_NOT, (yyval.ast));
	}
#line 6318 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 527:
#line 2634 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_XOR, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6327 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 528:
#line 2638 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_XNOR, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6336 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 529:
#line 2642 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_SHIFT_LEFT, (yyvsp[-3].ast), new AstNode(AST_TO_UNSIGNED, (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6345 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 530:
#line 2646 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_SHIFT_RIGHT, (yyvsp[-3].ast), new AstNode(AST_TO_UNSIGNED, (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6354 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 531:
#line 2650 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_SHIFT_SLEFT, (yyvsp[-3].ast), new AstNode(AST_TO_UNSIGNED, (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6363 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 532:
#line 2654 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_SHIFT_SRIGHT, (yyvsp[-3].ast), new AstNode(AST_TO_UNSIGNED, (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6372 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 533:
#line 2658 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_LT, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6381 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 534:
#line 2662 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_LE, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6390 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 535:
#line 2666 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_EQ, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6399 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 536:
#line 2670 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_NE, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6408 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 537:
#line 2674 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_EQX, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6417 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 538:
#line 2678 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_NEX, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6426 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 539:
#line 2682 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_GE, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6435 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 540:
#line 2686 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_GT, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6444 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 541:
#line 2690 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_ADD, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6453 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 542:
#line 2694 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_SUB, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6462 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 543:
#line 2698 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_MUL, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6471 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 544:
#line 2702 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_DIV, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6480 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 545:
#line 2706 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_MOD, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6489 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 546:
#line 2710 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_POW, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6498 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 547:
#line 2714 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_POS, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6507 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 548:
#line 2718 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_NEG, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6516 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 549:
#line 2722 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_LOGIC_AND, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6525 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 550:
#line 2726 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_LOGIC_OR, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6534 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 551:
#line 2730 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_LOGIC_NOT, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6543 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 552:
#line 2736 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_CONCAT, (yyvsp[0].ast));
	}
#line 6551 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 553:
#line 2739 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
		(yyval.ast)->children.push_back((yyvsp[-2].ast));
	}
#line 6560 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;


#line 6564 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
