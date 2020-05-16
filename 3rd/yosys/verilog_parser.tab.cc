/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

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
#include "include/verilog_frontend.h"

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
#line 156 "frontends/verilog/verilog_parser.y" /* yacc.c:355  */

	std::string *string;
	struct YOSYS_NAMESPACE_PREFIX AST::AstNode *ast;
	std::map<std::string, YOSYS_NAMESPACE_PREFIX AST::AstNode*> *al;
	struct specify_target *specify_target_ptr;
	struct specify_triple *specify_triple_ptr;
	struct specify_rise_fall *specify_rise_fall_ptr;
	bool boolean;
	char ch;

#line 368 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 398 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:358  */

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
#define YYLAST   2310

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  145
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  245
/* YYNRULES -- Number of rules.  */
#define YYNRULES  554
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1139

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   373

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   144,     2,   135,     2,   125,   107,     2,
     132,   133,   123,   121,   129,   122,   131,   124,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   136,   134,
     113,   130,   116,   142,   141,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   137,     2,   138,   105,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   139,   103,   140,   143,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102,   104,   106,
     108,   109,   110,   111,   112,   114,   115,   117,   118,   119,
     120,   126,   127,   128
};

#if FRONTEND_VERILOG_YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   228,   228,   228,   240,   241,   242,   243,   244,   245,
     246,   247,   247,   251,   251,   267,   269,   273,   280,   273,
     291,   291,   294,   295,   298,   304,   312,   315,   323,   333,
     336,   336,   358,   358,   358,   358,   361,   361,   363,   365,
     365,   371,   371,   377,   380,   380,   380,   383,   383,   386,
     386,   389,   405,   409,   409,   423,   428,   423,   438,   438,
     453,   458,   458,   471,   472,   476,   477,   480,   480,   500,
     500,   503,   503,   503,   503,   503,   503,   503,   504,   507,
     508,   509,   510,   511,   514,   514,   517,   517,   527,   528,
     529,   530,   537,   540,   543,   549,   551,   554,   557,   560,
     563,   566,   572,   579,   582,   585,   590,   595,   601,   607,
     613,   616,   622,   625,   630,   631,   634,   637,   645,   647,
     647,   651,   651,   651,   651,   651,   651,   651,   651,   651,
     651,   652,   653,   653,   653,   653,   653,   653,   656,   656,
     667,   667,   677,   677,   688,   688,   700,   700,   712,   712,
     736,   741,   747,   747,   751,   752,   753,   753,   757,   757,
     761,   764,   769,   769,   769,   773,   769,   781,   781,   784,
     784,   805,   808,   808,   814,   817,   817,   821,   904,   975,
     978,   983,   986,   991,   994,   999,  1005,  1011,  1017,  1025,
    1026,  1027,  1030,  1038,  1045,  1054,  1066,  1086,  1092,  1102,
    1103,  1106,  1107,  1110,  1113,  1114,  1118,  1119,  1125,  1128,
    1128,  1131,  1134,  1134,  1137,  1143,  1144,  1148,  1149,  1150,
    1154,  1155,  1159,  1159,  1162,  1163,  1164,  1167,  1168,  1169,
    1173,  1174,  1177,  1178,  1181,  1182,  1185,  1186,  1187,  1191,
    1195,  1198,  1201,  1202,  1203,  1206,  1207,  1208,  1215,  1218,
    1219,  1226,  1226,  1232,  1234,  1237,  1244,  1247,  1251,  1254,
    1263,  1264,  1271,  1271,  1280,  1280,  1289,  1289,  1292,  1310,
    1313,  1313,  1316,  1325,  1325,  1346,  1347,  1348,  1351,  1354,
    1355,  1359,  1360,  1364,  1378,  1379,  1383,  1384,  1387,  1398,
    1405,  1420,  1405,  1426,  1426,  1434,  1434,  1443,  1445,  1456,
    1456,  1459,  1501,  1529,  1582,  1585,  1585,  1588,  1595,  1632,
    1639,  1639,  1648,  1648,  1658,  1661,  1666,  1667,  1670,  1670,
    1679,  1679,  1691,  1692,  1695,  1696,  1696,  1702,  1702,  1705,
    1705,  1707,  1709,  1714,  1723,  1750,  1750,  1753,  1758,  1764,
    1772,  1779,  1788,  1795,  1798,  1803,  1806,  1811,  1818,  1811,
    1831,  1831,  1847,  1847,  1861,  1862,  1863,  1864,  1865,  1865,
    1869,  1870,  1871,  1874,  1879,  1884,  1891,  1894,  1899,  1902,
    1907,  1910,  1913,  1918,  1924,  1918,  1930,  1930,  1933,  1933,
    1936,  1937,  1940,  1950,  1950,  1953,  1965,  1977,  1989,  2001,
    2009,  2017,  2025,  2039,  2055,  2062,  2069,  2076,  2083,  2090,
    2101,  2114,  2121,  2126,  2131,  2138,  2146,  2146,  2146,  2146,
    2146,  2146,  2147,  2148,  2148,  2149,  2149,  2160,  2160,  2171,
    2171,  2188,  2193,  2195,  2188,  2205,  2205,  2220,  2220,  2235,
    2246,  2235,  2254,  2254,  2268,  2271,  2274,  2279,  2285,  2288,
    2291,  2296,  2300,  2303,  2307,  2307,  2311,  2311,  2322,  2325,
    2325,  2329,  2335,  2329,  2348,  2348,  2352,  2358,  2352,  2366,
    2367,  2370,  2373,  2378,  2381,  2386,  2391,  2400,  2407,  2410,
    2415,  2419,  2425,  2425,  2429,  2429,  2433,  2434,  2437,  2442,
    2442,  2446,  2446,  2450,  2454,  2450,  2459,  2459,  2467,  2467,
    2475,  2475,  2487,  2487,  2498,  2498,  2507,  2507,  2510,  2510,
    2513,  2516,  2525,  2528,  2538,  2550,  2557,  2563,  2574,  2578,
    2578,  2588,  2592,  2596,  2599,  2604,  2607,  2610,  2614,  2618,
    2622,  2626,  2630,  2634,  2638,  2642,  2647,  2651,  2656,  2660,
    2664,  2668,  2672,  2676,  2680,  2684,  2688,  2692,  2696,  2700,
    2704,  2708,  2712,  2716,  2720,  2724,  2728,  2732,  2736,  2740,
    2744,  2748,  2752,  2758,  2761
};
#endif

#if FRONTEND_VERILOG_YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_STRING", "TOK_ID", "TOK_CONSTVAL",
  "TOK_REALVAL", "TOK_PRIMITIVE", "TOK_USELESS", "TOK_SVA_LABEL",
  "TOK_SPECIFY_OPER", "TOK_MSG_TASKS", "TOK_ASSERT", "TOK_ASSUME",
  "TOK_RESTRICT", "TOK_COVER", "TOK_FINAL", "ATTR_BEGIN", "ATTR_END",
  "DEFATTR_BEGIN", "DEFATTR_END", "TOK_MODULE", "TOK_ENDMODULE",
  "TOK_PARAMETER", "TOK_LOCALPARAM", "TOK_DEFPARAM", "TOK_PACKAGE",
  "TOK_ENDPACKAGE", "TOK_PACKAGESEP", "TOK_INTERFACE", "TOK_ENDINTERFACE",
  "TOK_MODPORT", "TOK_VAR", "TOK_WILDCARD_CONNECT", "TOK_INPUT",
  "TOK_OUTPUT", "TOK_INOUT", "TOK_WIRE", "TOK_WAND", "TOK_WOR", "TOK_REG",
  "TOK_LOGIC", "TOK_INTEGER", "TOK_SIGNED", "TOK_ASSIGN", "TOK_ALWAYS",
  "TOK_INITIAL", "TOK_ALWAYS_FF", "TOK_ALWAYS_COMB", "TOK_ALWAYS_LATCH",
  "TOK_BEGIN", "TOK_END", "TOK_IF", "TOK_ELSE", "TOK_FOR", "TOK_WHILE",
  "TOK_REPEAT", "TOK_DPI_FUNCTION", "TOK_POSEDGE", "TOK_NEGEDGE", "TOK_OR",
  "TOK_AUTOMATIC", "TOK_CASE", "TOK_CASEX", "TOK_CASEZ", "TOK_ENDCASE",
  "TOK_DEFAULT", "TOK_FUNCTION", "TOK_ENDFUNCTION", "TOK_TASK",
  "TOK_ENDTASK", "TOK_SPECIFY", "TOK_IGNORED_SPECIFY", "TOK_ENDSPECIFY",
  "TOK_SPECPARAM", "TOK_SPECIFY_AND", "TOK_IGNORED_SPECIFY_AND",
  "TOK_GENERATE", "TOK_ENDGENERATE", "TOK_GENVAR", "TOK_REAL",
  "TOK_SYNOPSYS_FULL_CASE", "TOK_SYNOPSYS_PARALLEL_CASE", "TOK_SUPPLY0",
  "TOK_SUPPLY1", "TOK_TO_SIGNED", "TOK_TO_UNSIGNED", "TOK_POS_INDEXED",
  "TOK_NEG_INDEXED", "TOK_PROPERTY", "TOK_ENUM", "TOK_TYPEDEF", "TOK_RAND",
  "TOK_CONST", "TOK_CHECKER", "TOK_ENDCHECKER", "TOK_EVENTUALLY",
  "TOK_INCREMENT", "TOK_DECREMENT", "TOK_UNIQUE", "TOK_PRIORITY", "OP_LOR",
  "OP_LAND", "'|'", "OP_NOR", "'^'", "OP_XNOR", "'&'", "OP_NAND", "OP_EQ",
  "OP_NE", "OP_EQX", "OP_NEX", "'<'", "OP_LE", "OP_GE", "'>'", "OP_SHL",
  "OP_SHR", "OP_SSHL", "OP_SSHR", "'+'", "'-'", "'*'", "'/'", "'%'",
  "OP_POW", "UNARY_OPS", "FAKE_THEN", "','", "'='", "'.'", "'('", "')'",
  "';'", "'#'", "':'", "'['", "']'", "'{'", "'}'", "'@'", "'?'", "'~'",
  "'!'", "$accept", "input", "$@1", "design", "attr", "$@2", "attr_opt",
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
     355,   356,   357,   124,   358,    94,   359,    38,   360,   361,
     362,   363,   364,    60,   365,   366,    62,   367,   368,   369,
     370,    43,    45,    42,    47,    37,   371,   372,   373,    44,
      61,    46,    40,    41,    59,    35,    58,    91,    93,   123,
     125,    64,    63,   126,    33
};
# endif

#define YYPACT_NINF -841

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-841)))

#define YYTABLE_NINF -462

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -841,    41,   252,  -841,  -841,    81,    10,  -841,   694,  -841,
     252,   252,   252,   252,   252,   252,   252,   252,   182,  -841,
    -841,    75,   819,   192,   220,  -841,  -841,   232,   245,   268,
     268,   255,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,   207,  -841,    74,   209,   303,  1552,  -841,   390,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,   182,  -841,   754,  -841,  -841,   267,
    -841,    70,    70,  -841,    53,  -841,   366,   407,   182,   398,
     182,   423,  1552,   462,   349,   352,  -841,   550,  -841,   486,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  1552,  1552,  -841,  -841,   125,  -841,   186,  2051,    75,
      51,  -841,  -841,   209,  -841,   452,   504,   504,   376,  -841,
     513,   516,  -841,    57,  -841,   511,  -841,  -841,  -841,  -841,
    -841,  -841,   107,   397,  -841,  -841,  -841,   396,  -841,    75,
    -841,   409,   427,  1552,  1552,  1552,  1552,  1552,  1552,  1552,
    1552,   -15,   129,   430,  1552,  1552,  -841,  1552,  -841,    75,
      75,  -841,  1552,  1552,  1552,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,    75,  -841,   438,  -841,   352,  -841,   484,
     449,   -12,  -841,   117,  -841,   467,   577,   455,  -841,  -841,
     621,   495,  -841,    34,   624,   499,  -841,  -841,   502,  -841,
    -841,   629,  -841,  -841,  1552,  1552,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,   630,  1552,  1552,  1552,  -841,  -841,
    -841,   357,   506,  -841,  -841,   503,   510,   524,  1552,  1552,
    1552,  1552,  1552,  1552,  1552,  1552,  1552,  1552,  1552,  1552,
    1552,  1552,  1552,  1552,  1552,  1552,  1552,  1552,  1552,  1552,
    1552,  1552,  1552,  1552,  1552,  -841,   540,  -841,    75,  1552,
     504,  -841,  -841,    54,   636,   541,  -841,   665,  -841,   545,
     547,   424,   554,  -841,  -841,   557,   685,   563,    75,   108,
     562,   344,   567,    19,  -841,   565,   568,  -841,   564,   587,
    -841,   579,   590,  1552,  -841,  -841,  -841,  2118,  2142,  2164,
    2164,  2184,  2184,  2006,  2006,  1675,  1675,  1675,  1675,   535,
     535,   535,   535,   609,   609,   609,   609,   521,   521,   600,
     600,   600,  -841,   591,  -841,  -841,  -841,  -841,  -841,   704,
    -841,  -841,  -841,   732,  -841,   238,  -841,   467,   734,   495,
    -841,   737,  -841,  -841,  -841,    34,   613,  1552,  -841,  -841,
    -841,   746,  -841,  -841,    75,  -841,   756,   623,   520,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  1552,  -841,
     629,  -841,  -841,  -841,  1552,   622,   182,   635,  -841,  -841,
    -841,  1552,  1869,  -841,   636,  -841,   625,  -841,   640,    75,
    -841,   646,  -841,  -841,   372,    70,    70,  -841,  -841,  -841,
     557,  -841,   182,   211,  -841,  -841,    91,  -841,    38,  -841,
    -841,  -841,  -841,  -841,   772,   774,    75,  -841,  -841,  2093,
    -841,   647,  -841,    66,  -841,  1552,   648,  -841,   643,  -841,
    -841,   654,   650,   651,  -841,  -841,  -841,    97,   279,    31,
    -841,   780,   619,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,   794,  -841,  -841,  -841,  -841,  -841,  -841,
     741,  -841,   667,  -841,  -841,  -841,   467,  -841,  -841,    75,
      52,  -841,  -841,  -841,  -841,  -841,  1552,  2050,  -841,   309,
     605,  -841,  -841,  -841,  -841,   755,  -841,   669,  -841,   544,
    -841,   235,   504,   504,  -841,   557,   671,    75,  -841,   673,
    -841,  -841,  -841,  1552,   239,  -841,   676,   605,  -841,  -841,
    -841,   605,   666,  -841,  -841,  -841,  -841,   677,   804,  -841,
    1552,  -841,   678,   680,   743,    97,   682,  -841,   686,  -841,
     402,  -841,  -841,   689,  -841,   683,  -841,   691,  1552,   820,
     248,  -841,   695,  1903,   692,  -841,  -841,  -841,   623,  -841,
     278,  -841,   739,   742,   747,   748,  1552,   698,   143,  -841,
    -841,   702,  -841,   699,   709,   654,   708,   710,   711,   712,
    -841,  -841,  -841,  -841,  -841,    92,    92,    92,    42,  -841,
     713,  -841,  -841,   623,   623,  -841,  -841,  -841,  1552,  -841,
      33,  -841,    28,    38,  -841,  1552,  -841,  -841,  -841,   623,
    -841,   127,  -841,  1552,   714,  -841,  -841,   716,    36,    82,
    1552,  -841,  -841,    82,    75,  1552,  -841,  -841,   226,   722,
     733,  -841,  1105,   728,  -841,   297,   820,  -841,  1552,  -841,
    -841,  -841,  -841,  -841,   730,  -841,   794,  -841,   735,   736,
     744,   745,   738,  -841,  -841,   737,  -841,   677,  -841,  1552,
    -841,  1552,  -841,  1552,  1552,   456,  -841,  -841,   677,  -841,
    -841,   750,   752,   753,  -841,   760,  1552,  1552,  1552,  -841,
    -841,  -841,  -841,  -841,   740,  -841,  -841,   862,   759,  -841,
    1552,  -841,  -841,   322,   343,   737,   762,  -841,  1099,   605,
     635,  -841,  1973,  -841,   766,  -841,  -841,  1552,   763,  1552,
    -841,   769,   751,  -841,  -841,   820,   757,   229,  -841,  1595,
    1595,   820,   820,  -841,   296,  -841,  1552,  -841,  -841,  -841,
    -841,   771,   869,   869,  -841,  1254,  1284,  1326,  1552,  -841,
    -841,   773,  -841,  -841,   775,    36,   777,   781,   779,  1368,
    1398,  1440,  1482,   783,  -841,  -841,   156,   784,  -841,  -841,
     782,   870,  -841,  -841,   749,  -841,   790,  -841,  -841,  1552,
    1552,   789,   146,  -841,  -841,  -841,   792,   654,  -841,  1552,
     800,  -841,   876,  -841,  1552,   803,   453,   807,  -841,  -841,
     820,   367,   797,  1552,  -841,   776,  -841,  -841,  -841,  1105,
    1105,   796,   793,  1802,   975,    75,   356,  -841,  -841,   389,
    -841,   801,  1552,   799,  1552,   806,  1552,   809,   810,  -841,
    -841,   538,  -841,   802,  -841,  -841,  -841,  1552,   811,  1552,
     812,  1552,   813,   814,   816,  -841,  -841,  -841,  1552,  -841,
     737,   818,  1552,  -841,  -841,  -841,  1170,  1170,  -841,  -841,
    -841,   884,  2007,  -841,  1552,   825,  1637,   822,   824,   840,
    -841,   820,  -841,   820,  -841,   845,   776,   133,  1552,  -841,
    -841,  -841,  -841,  -841,  -841,   963,   329,  -841,  -841,  -841,
     831,   869,  -841,   869,  -841,  -841,   844,   848,   850,   851,
     856,   857,   858,   925,   654,  -841,   605,  1552,   605,   605,
     860,   861,   863,   864,   866,   868,  -841,   871,  -841,   867,
    -841,  -841,  -841,  -841,  -841,   872,  -841,  -841,   873,  -841,
      82,  1552,   877,  -841,  1552,   865,   879,   335,  -841,  -841,
    -841,   820,   880,  1552,   776,   887,   975,  -841,   889,  -841,
    -841,  -841,  1212,   882,   874,  -841,   875,  -841,   878,  -841,
     888,  -841,  -841,  -841,  -841,   394,  -841,  -841,  -841,  -841,
    -841,   900,  -841,   901,  -841,   902,  -841,  -841,   480,  -841,
    -841,  -841,  -841,    36,  1552,   386,   886,  -841,   820,   820,
     820,  -841,   890,  -841,   904,  -841,  1552,  -841,  -841,   909,
    -841,  1000,  -841,  -841,  -841,  -841,  -841,  -841,  -841,   -13,
    -841,   134,  -841,   991,   911,  -841,  -841,  -841,  -841,  -841,
     981,   915,   800,  1552,  1552,  1552,  1701,   383,   240,  -841,
    -841,  1552,   916,   917,  -841,   920,  -841,   872,  1552,  -841,
    -841,  -841,    36,  -841,  -841,   394,  -841,   924,   921,   922,
     259,  1552,   923,  -841,   926,  1552,   927,  1552,   929,   647,
    -841,  -841,  1546,  -841,  -841,   605,   933,  -841,  -841,  1552,
    -841,  -841,  -841,   930,   300,  -841,  1552,   935,  1552,   936,
    1552,  -841,   937,  -841,  -841,   605,   943,  1552,  1552,   939,
     940,   951,   952,   953,  -841,   605,  -841,  1552,   954,   401,
     955,  1552,  -841,   956,  -841,   957,  -841,  -841,   942,  1552,
    -841,  1552,  -841,  -841,  -841,  -841,   403,   647,  1552,  -841,
     964,  1552,   965,  1552,   425,  1552,  -841,   966,  1552,   969,
    1552,   970,  1552,   971,  1552,   972,  1552,   979,  -841
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
       0,     0,     0,     0,     0,    45,   253,   277,   508,   506,
     507,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,     0,     0,    13,    13,   113,   502,     0,   500,   113,
       0,    89,   309,    35,   261,   256,     0,     0,     0,   140,
       0,     0,   160,   113,   146,     0,    19,    23,    27,    25,
      28,    32,    13,     0,   279,   280,   278,     0,   276,   113,
     505,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   553,     0,     0,     0,   504,     0,   509,   112,
     467,   466,     0,     0,     0,   109,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,   115,   114,     0,    29,    45,   255,   258,
       0,     0,   266,     0,    64,   153,     0,     0,   117,   116,
       0,   163,    15,    13,    53,     0,    44,    86,    50,    47,
      70,     0,   259,   275,     0,     0,   526,   527,   528,   529,
     524,   525,   548,   549,   513,     0,     0,     0,   515,   517,
     552,     0,     0,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   308,     0,   257,   113,     0,
       0,   263,   265,    13,   157,     0,   142,     0,   148,   164,
       0,     0,    33,    36,    43,    52,     0,     0,   113,    13,
       0,    13,   285,     0,   281,     0,     0,   503,     0,   553,
     554,     0,   109,   475,   107,   108,   106,   551,   550,   520,
     521,   522,   523,   518,   519,   536,   537,   538,   539,   534,
     535,   540,   541,   530,   531,   532,   533,   542,   543,   544,
     545,   546,   547,     0,   120,   260,   268,   267,    62,     0,
      63,    66,    65,   151,   156,     0,   141,   153,     0,   163,
     162,    13,   173,    39,    41,    13,     0,     0,    54,    56,
      60,     0,    48,    46,   113,    68,     0,    85,    86,    69,
      71,    72,    74,    75,    77,    73,    76,    78,     0,   283,
       0,   274,   511,   512,     0,     0,     0,    50,   474,   476,
     478,     0,    13,   150,   155,   152,     0,   144,     0,   113,
      86,    50,   167,   171,    13,   254,   254,    37,    34,    51,
      52,    58,     0,     0,   270,   373,     0,    84,     0,   345,
     352,   346,   343,   344,     0,     0,   113,   350,   347,   284,
     282,     0,   516,   113,   465,    49,     0,   501,     0,   492,
      31,   367,     0,     0,   438,   439,   440,   176,   213,     0,
     480,     0,    86,   134,   118,   136,   121,   122,   137,   127,
     123,   124,   126,     0,   131,   128,   129,   125,   130,   132,
       0,   135,     0,   119,   154,   143,   153,   173,   303,   113,
      13,   165,   405,    13,   147,   414,     0,    86,   406,   113,
      13,   409,   410,   408,   411,     0,   407,     0,   172,     0,
     468,     0,     0,     0,    57,    52,     0,   113,   269,     0,
      79,    80,    81,     0,     0,   305,     0,    13,   293,   295,
     290,    13,   359,   514,   477,   510,   368,   473,     0,   490,
       0,   483,     0,     0,     0,   176,     0,   251,     0,   200,
     213,   202,   203,     0,   204,     0,   205,     0,     0,     0,
       0,   209,     0,    13,     0,   310,   314,   315,    85,   288,
       0,   286,     0,     0,     0,     0,     0,     0,    13,   169,
     168,     0,   417,     0,   470,   367,     0,     0,     0,     0,
      13,    13,   437,   415,   412,   372,   372,   372,   372,   413,
       0,   402,   403,    85,    85,    40,    42,    59,     0,   271,
       0,   374,     0,     0,   304,     0,   353,   297,   297,    85,
     351,     0,   348,   475,     0,   366,   480,     0,     0,   191,
       0,   174,   175,   191,   113,     0,   199,   201,     0,     0,
       0,   214,     0,     0,   248,     0,     0,   206,     0,   133,
     482,   479,   481,   138,   328,   312,     0,   289,     0,     0,
       0,     0,     0,   145,   149,     0,   166,   473,   469,     0,
     419,     0,   421,     0,     0,   434,   436,   435,   473,   371,
     370,     0,     0,     0,   391,     0,     0,     0,     0,   272,
     382,   383,   384,   376,    50,   378,   381,     0,     0,    82,
       0,   306,   307,     0,     0,     0,     0,   358,     0,    13,
      50,   493,    13,   486,     0,   189,   190,     0,     0,     0,
     252,     0,   249,   222,   223,     0,     0,   238,   239,     0,
       0,     0,     0,   245,     0,   244,     0,   207,   210,   211,
     120,     0,     0,   325,   287,     0,     0,     0,     0,   488,
     170,     0,   471,   445,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   404,   401,    49,     0,   380,   375,
       0,     0,   294,   296,   291,   299,   301,   356,   357,     0,
       0,     0,     0,   360,   365,   349,     0,   367,   494,     0,
     184,   181,     0,   212,     0,     0,   238,     0,   236,   237,
       0,   238,   230,     0,   215,   218,   216,   242,   243,     0,
       0,     0,     0,    13,   331,   318,     0,   316,   324,     0,
     322,     0,     0,     0,     0,     0,     0,     0,     0,   455,
     418,    13,   429,     0,   425,   427,   416,     0,     0,     0,
       0,     0,     0,     0,     0,   432,   379,   377,     0,   298,
       0,     0,     0,   363,   364,   355,     0,     0,   354,   472,
     491,   499,    13,   484,     0,     0,     0,     0,     0,     0,
     230,     0,   232,     0,   231,     0,     0,   249,     0,   219,
     246,   247,   241,   208,   139,     0,     0,   329,   332,   320,
       0,     0,   311,   325,   313,    13,     0,     0,     0,     0,
       0,     0,     0,   456,   367,   444,    13,     0,    13,    13,
       0,     0,     0,     0,     0,     0,   390,     0,   443,     0,
     300,   292,   302,   361,   362,   494,   487,   495,     0,   183,
     191,     0,     0,   185,     0,     0,     0,     0,   234,   240,
     233,     0,     0,     0,   220,     0,   331,   327,     0,    13,
     317,   323,   337,     0,   334,   335,     0,   394,     0,   395,
       0,   399,   398,   489,   454,     0,   420,   430,   422,   426,
     428,     0,   385,     0,   386,     0,   392,   389,   450,    83,
     497,   496,   498,     0,     0,     0,     0,   250,     0,     0,
       0,   227,     0,   217,     0,   221,     0,   330,    13,     0,
     342,     0,   338,   326,    13,   396,   397,   400,   462,   460,
     457,     0,   463,   448,     0,   387,   388,   393,   441,   442,
     451,     0,   184,     0,     0,     0,     0,   238,   238,   235,
     224,     0,     0,     0,   319,   341,   336,   494,     0,   459,
     446,   431,     0,   433,   449,     0,   494,     0,     0,     0,
       0,     0,     0,   192,   197,     0,     0,     0,     0,   250,
     333,   321,     0,   458,   464,    13,     0,   452,   485,     0,
     188,   187,   186,     0,   197,   177,     0,     0,     0,     0,
       0,   340,     0,   447,   423,    13,   180,     0,     0,     0,
       0,     0,     0,     0,   339,    13,   453,     0,     0,     0,
       0,     0,   229,     0,   226,     0,   424,   179,     0,     0,
     193,     0,   198,   228,   225,   178,     0,   198,     0,   194,
       0,     0,     0,     0,     0,     0,   195,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   196
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -841,  -841,  -841,   959,   122,  -841,  -841,    76,  -841,  -841,
     978,  -841,  1008,   -18,  1036,  -841,  -841,  1002,  -841,  -841,
    -841,   727,  -841,  -841,   919,  -841,  -331,  -305,   823,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -359,  -166,    14,  -841,  -841,  -841,  1047,   -50,   -94,
      56,  -401,  -841,   381,  -399,  -841,  -841,  -393,  -841,  -841,
    -841,  -841,  -841,   719,  -294,  -841,  1094,  -841,   768,  -841,
    -841,  -841,   638,  -841,   642,  -841,   580,  -841,  -841,  -841,
     137,  -841,  -607,  -841,  -168,  -841,  -841,   610,  -376,  -841,
     571,   515,  -841,  -841,  -841,   432,  -840,  -841,  -841,  -841,
     440,  -841,   178,  -780,  -702,  -600,  -841,  -233,  -841,   431,
    -623,  -445,  -841,  1122,  -841,  -841,   891,   -68,    17,  -841,
      37,  -841,  1053,  -196,   881,  -841,   655,  1165,  -841,  -841,
    -841,  -841,  -841,   787,  -841,  -841,   522,  -841,  -299,  -841,
    -841,  -841,  -841,   561,  -841,   330,  -622,   885,  -841,   570,
      59,  -841,  -841,  -841,  -841,  -841,  -718,  -841,  -841,  -841,
     288,  -841,  -841,  -841,   241,  -820,  -841,   184,  -841,  -841,
     892,  -841,  -841,  -841,  -841,  -841,  -841,  -269,  -579,  -391,
     109,  -841,  -841,  -841,  -841,  -841,   426,   492,  -841,  -841,
    -841,  -627,  -381,  -841,  -841,  -841,  -841,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,     6,   687,  -841,  -841,  -841,
    -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,  -841,   149,
    -841,  -161,  -406,   526,  -435,   574,  -841,   778,   572,   337,
    -397,  -841,  -841,  -841,  -841,  -841,  -841,  -781,  -841,   163,
    -841,   -37,   883,  -841,   365
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,   497,     9,    31,   498,    18,    79,
      41,    42,    43,   105,   114,    11,   113,    85,   213,   366,
     292,   293,   415,   416,   133,   218,   300,   368,   219,   295,
     296,   420,   515,    12,   118,   283,   350,    13,    45,   301,
     379,   500,   428,   436,    22,    66,    67,    68,    48,   160,
     161,   195,   210,   402,   650,   465,   740,    14,   205,   357,
     486,   211,   359,   354,   285,   355,    76,   123,   290,   361,
     581,   411,   412,   665,   414,   467,   544,   545,  1098,   546,
     865,   932,   717,  1052,  1053,   468,   550,   551,   469,   559,
     560,   561,   553,   554,   555,   804,   879,   725,   639,   640,
     726,   801,   937,   802,   727,   938,   556,   733,   734,   643,
     735,   939,   634,   115,   199,   278,   223,   116,   501,    71,
     502,    72,   201,   202,   472,   423,   424,   473,    46,   137,
     138,   139,   303,   304,   389,   570,   571,   474,   503,   619,
     851,   617,   618,   703,   774,   775,   413,   476,   524,   525,
     504,   478,   654,   743,   568,   816,   818,   890,   948,   819,
     820,   821,   742,   886,   887,   953,   954,   955,   437,   438,
     479,   532,   709,   531,   527,   622,   782,   783,   539,   505,
     681,   387,   519,   698,   611,   694,   695,   696,   697,   506,
     481,   507,   508,   678,   667,   753,   755,  1014,  1095,   908,
     909,   906,  1013,   918,   592,   509,   482,   978,   831,  1041,
    1065,  1020,  1044,  1045,  1085,   903,   964,   965,  1037,  1010,
    1011,   106,   511,   583,   624,   397,   398,   399,   563,   651,
     652,   628,   928,   788,   829,   626,   537,   981,   862,   982,
     926,  1054,   108,   242,   153
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,   714,   383,   464,   117,   483,   670,   861,   488,   466,
     107,   480,   721,   557,   562,   193,   870,   294,   427,    15,
      21,   874,   526,   796,   817,   739,   719,    15,    15,    15,
      15,    15,    15,    15,    15,   547,   942,   690,   200,    16,
      40,     3,    40,   750,   492,   129,   110,    16,    16,    16,
      16,    16,    16,    16,    16,   159,   409,   119,   679,   159,
      44,    17,    44,   406,   151,   152,   446,   691,   692,    17,
      17,    17,    17,    17,    17,    17,    17,    49,    10,    81,
     491,   348,   552,   776,   347,    19,    10,    10,    10,    10,
      10,    10,    10,    10,    81,   520,   521,   522,   872,   208,
      20,   542,    81,   475,   995,   557,   805,   805,   679,   243,
     244,   214,   214,    86,   562,   514,  -461,   280,   234,   594,
     241,   235,   281,  -461,     8,   245,   246,   247,   833,   999,
     156,   680,     8,     8,     8,     8,     8,     8,     8,     8,
     715,   716,   -13,   244,   706,     6,   616,    40,   390,   543,
     620,   492,   448,    81,   493,  -369,  -369,  -369,  -369,   391,
     690,   699,     4,   -38,   700,   194,   693,   -38,   558,   294,
     466,   940,   480,   950,   552,   496,   684,   496,  1033,   209,
     876,   680,    83,   120,   196,   -49,    40,   305,   306,   121,
     691,   692,   577,   728,    47,   222,    69,    83,   308,   309,
     309,   562,    64,   157,    82,    83,   856,   526,   860,   427,
     607,   664,    47,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   523,    70,   154,   155,   158,   776,  -182,
     547,   298,   751,   720,     6,   444,    73,   343,   215,   215,
     216,   -49,   346,   758,   427,   427,   280,  1056,  1058,    74,
     707,   282,   -12,   510,   217,   944,    83,   -13,   236,   708,
     427,   516,   157,  1038,   475,  1068,   234,   510,   237,   943,
    1039,     4,    78,   162,   163,   857,   400,   495,   426,   858,
     728,     5,   496,   547,   723,   724,   807,   808,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   193,   605,   606,   380,   466,
     351,   480,   164,   984,   165,   966,   -13,  1057,   785,    75,
     419,   548,   601,   602,   222,   291,    80,    81,   381,   510,
     517,   992,   352,     6,    84,   518,    86,   512,   513,   603,
     798,   799,   549,   459,   371,   728,  1021,   441,   800,   159,
     385,   798,   799,   767,   447,   604,   510,   404,   613,   374,
     510,   405,   809,   614,   375,   376,    40,   646,   443,   786,
     492,   448,   647,   493,  -369,  -369,  -369,  -369,   377,  1028,
    1029,     4,  1072,   159,   109,   394,   499,    88,    40,    89,
      90,   112,   655,  1008,   443,   349,   547,   656,   400,   122,
     443,   124,   657,   475,   464,  1066,   483,   510,   126,   470,
     466,   217,   480,   378,   489,   810,   646,   128,   728,   811,
     422,   737,  1077,   234,  1079,     6,  1088,   687,   688,   471,
      83,   -13,   494,   -13,   162,   163,   157,   363,   364,   159,
     905,   771,   510,   705,   548,  1091,   772,  1093,   946,   584,
    1009,   477,   947,     6,   990,   194,   130,   510,   991,   466,
    1055,   480,   771,  1023,  1024,   636,   459,   773,   463,    91,
      92,   131,   499,   410,   132,   891,   612,   291,   798,   799,
     892,   140,   530,   164,   198,   312,   873,    93,    94,    95,
      96,    97,    98,   627,   798,   799,   495,   426,   200,   499,
     204,   496,   990,   499,   475,    99,   100,   206,   893,   234,
     207,   644,  1025,   894,   462,   967,   101,   969,   970,   212,
    1109,   220,  1118,   102,  1110,   221,  1119,   103,   104,   662,
     193,   224,    40,    25,    26,   579,   492,   448,   510,   493,
    -369,  -369,  -369,  -369,  1125,   590,   591,     4,  1126,   225,
     499,  1018,  1019,   475,   277,   429,   430,   431,   432,   433,
     238,   689,   275,   422,   798,   799,   880,   881,   702,   279,
     470,   286,   800,   869,   159,   287,   400,   923,   924,   904,
     134,   135,   136,   718,   510,   443,   676,   677,   722,   284,
     471,   310,   311,   434,   435,   722,   454,   455,   456,    40,
     443,   722,   410,   492,   448,   582,   493,  -369,  -369,  -369,
    -369,   593,   477,   565,     4,   288,   566,   289,   -55,     6,
     297,   299,   584,   302,   754,   307,   756,   757,   313,   463,
     353,   314,    25,    26,   188,   189,   190,   191,   315,   763,
     764,   765,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   316,   770,   429,   430,   431,   432,   433,   358,
     510,   784,   495,   426,   344,   356,    28,   496,   360,   567,
     790,   362,   792,   365,  1083,   462,    29,   367,    30,   369,
     194,   499,   722,   722,   370,   373,     6,   388,   392,   644,
     394,   393,   434,   435,  1096,   682,   683,   685,   823,   825,
     827,   828,   675,   675,  1106,    24,   236,    25,    26,   395,
      27,   396,   838,   840,   842,   844,   191,   401,    26,   470,
     186,   187,   188,   189,   190,   191,   403,   443,   407,   495,
     426,   409,   853,   854,   496,   510,   418,   510,   510,   471,
     421,    28,   863,   572,   573,   574,   575,   867,   426,   485,
     425,    29,   442,    30,   445,   889,   877,   595,   596,   597,
     598,   477,   722,   722,   487,   490,   528,   888,   529,   536,
     533,   535,   540,   541,   564,   896,    50,   898,   463,   900,
     538,    54,    55,    56,    57,    58,    59,    60,   569,   576,
     910,   608,   912,   599,   914,   610,   615,   621,   625,   623,
     629,   919,   630,   499,   633,   922,   631,   641,   635,   784,
     784,   638,   510,   642,   547,   648,   653,   929,   658,   933,
     470,   659,   663,    61,   462,   666,   660,   661,   669,   668,
     671,   722,   672,   673,   674,   686,    62,    63,   711,   713,
     471,    50,   729,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,   730,   736,   741,   690,   745,   746,   766,
     968,   749,   477,   815,   849,   864,   747,   748,   850,   470,
     797,   510,   759,  1073,   760,   761,   866,   794,   499,   463,
     499,   499,   762,   769,   985,   777,   791,   987,    61,   471,
     789,  1086,   793,   814,   510,   878,   994,   830,   832,   888,
     834,    62,    63,   836,   835,  1002,   845,   847,   848,  1099,
     852,   477,   855,   871,   510,   859,   868,   875,  1012,  1107,
     882,   883,   897,   895,   510,   462,   907,   925,   463,   899,
     935,  1116,   901,   902,   911,   913,   915,  1022,   916,   917,
    1120,    64,   921,  1122,   930,  1124,   936,  1127,   934,  1032,
    1129,   941,  1131,   949,  1133,   443,  1135,   945,  1137,    32,
      33,    34,    35,    36,    37,    38,    39,   956,    88,    40,
      89,    90,   957,   958,   462,   959,  1048,  1049,  1050,   960,
     963,   961,   962,   971,  1059,   972,   973,   988,   974,   975,
     979,  1064,   976,  1004,  1035,   977,   980,   983,  1012,  1005,
     986,   989,  1006,   993,  1074,  1003,  1026,   952,   722,   996,
     722,   998,  1007,  1030,   443,  1082,   226,   227,   228,   229,
     230,   231,   232,   233,  1015,  1016,  1017,   239,   240,  1089,
    1031,   722,  1034,   722,  1040,  1042,  1043,   499,  1046,  1060,
    1061,  1100,  1062,  1069,  1070,  1071,   125,  1075,    65,  1087,
      91,    92,  1076,  1078,  1112,  1080,  1084,   499,  1090,  1092,
    1094,   952,  1097,  1102,  1117,  1101,  1115,   499,    93,    94,
      95,    96,    97,    98,  1103,  1104,  1105,  1108,   127,  1113,
    1114,  1111,   417,  1121,  1123,  1128,    99,   100,  1130,  1132,
    1134,  1136,    88,    40,    89,    90,   885,   101,    88,    40,
      89,    90,  1138,   111,   102,   197,   276,   778,   103,   104,
     952,   813,   372,   484,    77,   632,   952,   408,   580,   578,
     645,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   779,   780,  1047,
     637,   738,   806,   731,   732,   795,  1027,   812,    87,   345,
     203,    23,   609,    88,    40,    89,    90,   440,   744,   704,
     920,   951,   382,   701,    91,    92,   384,   997,  1036,   768,
      91,    92,   846,   386,  1067,   752,   600,   710,   712,   927,
    1063,     0,    93,    94,    95,    96,    97,    98,    93,    94,
      95,    96,    97,    98,     0,    88,    40,    89,    90,     0,
      99,   100,   781,   534,     0,     0,    99,   100,   779,   780,
       0,   101,     0,     0,     0,     0,     0,   101,   102,     0,
       0,     0,   103,   104,   102,  1000,     0,     0,   103,   104,
       0,     0,     0,     0,     0,    91,    92,    88,    40,    89,
      90,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   439,     0,    93,    94,    95,    96,    97,    98,     0,
       0,     0,     0,     0,     0,     0,     0,    88,    40,    89,
      90,    99,   100,     0,     0,     0,     0,    91,    92,     0,
       0,     0,   101,     0,     0,     0,     0,     0,     0,   102,
       0,     0,     0,   103,   104,    93,    94,    95,    96,    97,
      98,     0,     0,     0,     0,     0,     0,     0,     0,    88,
      40,    89,    90,    99,   100,     0,     0,     0,     0,    91,
      92,     0,     0,  1001,   101,     0,     0,     0,     0,     0,
     822,   102,     0,     0,     0,   103,   104,    93,    94,    95,
      96,    97,    98,     0,     0,     0,     0,     0,     0,    91,
      92,    88,    40,    89,    90,    99,   100,     0,     0,     0,
     824,     0,     0,     0,     0,     0,   101,    93,    94,    95,
      96,    97,    98,   102,     0,     0,     0,   103,   104,     0,
       0,    88,    40,    89,    90,    99,   100,     0,     0,     0,
       0,    91,    92,     0,     0,     0,   101,     0,     0,     0,
       0,     0,   826,   102,     0,     0,     0,   103,   104,    93,
      94,    95,    96,    97,    98,     0,     0,     0,     0,     0,
       0,     0,     0,    88,    40,    89,    90,    99,   100,     0,
       0,     0,     0,    91,    92,     0,     0,     0,   101,     0,
       0,     0,     0,     0,   837,   102,     0,     0,     0,   103,
     104,    93,    94,    95,    96,    97,    98,     0,     0,     0,
       0,     0,     0,    91,    92,    88,    40,    89,    90,    99,
     100,     0,     0,     0,   839,     0,     0,     0,     0,     0,
     101,    93,    94,    95,    96,    97,    98,   102,     0,     0,
       0,   103,   104,     0,     0,     0,     0,     0,     0,    99,
     100,     0,     0,     0,     0,    91,    92,     0,     0,     0,
     101,     0,     0,     0,     0,     0,   841,   102,     0,     0,
       0,   103,   104,    93,    94,    95,    96,    97,    98,    88,
      40,    89,    90,     0,     0,    88,    40,    89,    90,     0,
       0,    99,   100,     0,     0,     0,     0,    91,    92,     0,
       0,     0,   101,     0,     0,     0,     0,     0,     0,   102,
       0,     0,     0,   103,   104,    93,    94,    95,    96,    97,
      98,     0,     0,     0,     0,     0,     0,     0,    88,    40,
      89,    90,     0,    99,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,   843,     0,     0,     0,     0,
       0,   102,     0,     0,     0,   103,   104,     0,     0,     0,
       0,    91,    92,     0,     0,     0,     0,    91,    92,     0,
      88,    40,    89,    90,     0,     0,     0,     0,     0,    93,
      94,    95,    96,    97,    98,    93,    94,    95,    96,    97,
      98,     0,     0,     0,     0,     0,     0,    99,   100,     0,
       0,     0,     0,    99,   100,     0,     0,     0,   101,  1081,
      91,    92,     0,     0,   101,   102,     0,     0,     0,   103,
     104,   102,     0,     0,     0,   103,   104,     0,    93,    94,
      95,    96,    97,    98,    88,    40,    89,    90,     0,     0,
       0,     0,     0,     0,     0,     0,    99,   100,     0,     0,
       0,     0,    91,    92,     0,     0,     0,   803,     0,     0,
       0,     0,     0,     0,   102,     0,     0,     0,   103,   104,
      93,    94,    95,    96,    97,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    99,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   931,
       0,     0,     0,     0,     0,     0,   102,     0,     0,     0,
     103,   104,     0,     0,     0,     0,    91,    92,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,     0,     0,    93,    94,    95,    96,    97,    98,
       0,   448,     0,   449,  -369,  -369,  -369,  -369,     0,     0,
       0,     4,    99,   100,     0,     0,     0,   374,     0,     0,
       0,     0,     0,  1051,     0,     0,     0,     0,     0,     0,
     102,     0,     0,     0,   103,   104,   377,     0,     0,     0,
       0,     0,   451,     0,   452,     0,   453,     0,     0,     0,
       0,     0,     0,     0,   454,   455,   456,     0,     0,     0,
       0,     0,     0,   457,   458,     0,   459,     0,   448,   460,
     449,  -369,  -369,  -369,  -369,     0,     0,     0,     4,     0,
       0,   450,    20,     6,   374,     0,   461,   884,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   448,   377,   449,  -369,  -369,  -369,  -369,   451,
       0,   452,     4,   453,     0,     0,     0,     0,   374,     0,
       0,   454,   455,   456,     0,     0,     0,     0,     0,     0,
     457,   458,     0,   459,     0,     0,   460,   377,     0,     0,
       0,     0,     0,   451,     0,   452,     0,   453,     0,    20,
       6,     0,     0,   461,     0,   454,   455,   456,     0,     0,
       0,     0,     0,     0,   457,   458,     0,   459,     0,     0,
     460,   649,   448,     0,   449,  -369,  -369,  -369,  -369,     0,
       0,     0,     4,    20,     6,     0,     0,   461,   374,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   448,   377,   449,  -369,
    -369,  -369,  -369,   451,   787,   452,     4,   453,     0,     0,
       0,     0,   374,     0,     0,   454,   455,   456,     0,     0,
       0,     0,     0,     0,   457,   458,     0,   459,     0,     0,
     460,   377,     0,     0,     0,     0,     0,   451,     0,   452,
       0,   453,     0,    20,     6,     0,     0,   461,     0,   454,
     455,   456,     0,    25,    26,     0,     0,     0,   457,   458,
       0,   459,     0,     0,   460,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,     6,     0,
     585,   461,   586,     0,   587,   588,   589,     0,     0,     0,
       0,     0,  -434,  -434,  -434,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   434,   435,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   590,
     591,     0,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   192,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191
};

static const yytype_int16 yycheck[] =
{
      18,   628,   301,   402,    72,   402,   585,   788,   409,   402,
      47,   402,   635,   458,   459,   109,   796,   213,   377,     2,
       6,   801,   428,   725,   742,   648,   633,    10,    11,    12,
      13,    14,    15,    16,    17,     4,   876,     4,     4,     2,
       4,     0,     4,   665,     8,    82,    64,    10,    11,    12,
      13,    14,    15,    16,    17,   105,     4,     4,    16,   109,
      78,     2,    80,   357,   101,   102,   397,    34,    35,    10,
      11,    12,    13,    14,    15,    16,    17,    21,     2,    28,
     411,    27,   458,   705,   280,     4,    10,    11,    12,    13,
      14,    15,    16,    17,    28,     4,     5,     6,   800,    42,
      90,     4,    28,   402,   944,   550,   729,   730,    16,   159,
     160,     4,     4,    43,   559,   420,   129,   129,   133,   500,
     157,   136,   134,   136,     2,   162,   163,   164,   755,   949,
       5,    89,    10,    11,    12,    13,    14,    15,    16,    17,
      58,    59,    17,   193,    17,    91,   527,     4,   129,    52,
     531,     8,     9,    28,    11,    12,    13,    14,    15,   140,
       4,   133,    19,   129,   136,   109,   133,   133,   137,   365,
     563,   873,   563,   891,   550,   139,   134,   139,   998,   123,
     803,    89,   131,   130,   133,   133,     4,   224,   225,   136,
      34,    35,   486,   638,   137,   139,     4,   131,   235,   236,
     237,   646,   132,   137,   130,   131,    60,   613,   787,   568,
     515,    68,   137,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   132,     4,   103,   104,   105,   850,   132,
       4,   217,   667,   634,    91,   396,     4,   274,   131,   131,
     133,   133,   279,   678,   603,   604,   129,  1027,  1028,     4,
     123,   134,     0,   414,   132,   878,   131,   132,   129,   132,
     619,   422,   137,   129,   563,  1046,   133,   428,   139,   136,
     136,    19,    17,    87,    88,   129,   313,   134,   135,   133,
     725,    29,   139,     4,    58,    59,   731,   732,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   409,   512,   513,   301,   712,
     283,   712,   136,   930,   138,   904,    17,    87,   709,    61,
     367,    52,    97,    98,   278,   213,   129,    28,   301,   500,
     129,   941,   283,    91,   135,   134,    43,   415,   416,   114,
     121,   122,    73,    74,   298,   800,   983,   394,   129,   409,
     301,   121,   122,   694,   401,   130,   527,   129,   129,    25,
     531,   133,    76,   134,    30,    31,     4,   129,   396,   710,
       8,     9,   134,    11,    12,    13,    14,    15,    44,   989,
     990,    19,   133,   443,     4,   136,   414,     3,     4,     5,
       6,   134,   568,     9,   422,   283,     4,   129,   445,    43,
     428,     4,   134,   712,   813,  1042,   813,   578,    20,   402,
     813,   299,   813,   301,   410,   129,   129,     4,   873,   133,
     374,   134,  1055,   133,  1057,    91,   136,   603,   604,   402,
     131,   132,    70,   134,    87,    88,   137,    23,    24,   499,
     831,   129,   613,   619,    52,  1078,   134,  1080,   129,   496,
      66,   402,   133,    91,   129,   409,     4,   628,   133,   862,
      87,   862,   129,    87,    88,    73,    74,   134,   402,    85,
      86,   132,   500,   361,   132,   129,   523,   365,   121,   122,
     134,     5,   436,   136,    42,   138,   129,   103,   104,   105,
     106,   107,   108,   540,   121,   122,   134,   135,     4,   527,
     134,   139,   129,   531,   813,   121,   122,     4,   129,   133,
       4,   558,   136,   134,   402,   906,   132,   908,   909,    18,
     129,   134,   129,   139,   133,   139,   133,   143,   144,   576,
     634,   132,     4,    23,    24,   489,     8,     9,   709,    11,
      12,    13,    14,    15,   129,    99,   100,    19,   133,   132,
     578,    81,    82,   862,    80,    45,    46,    47,    48,    49,
     140,   608,   134,   517,   121,   122,   809,   810,   615,   130,
     563,     4,   129,   130,   634,   130,   623,   856,   857,    51,
      40,    41,    42,   630,   755,   613,   590,   591,   635,   132,
     563,   236,   237,    83,    84,   642,    62,    63,    64,     4,
     628,   648,   490,     8,     9,   493,    11,    12,    13,    14,
      15,   499,   563,     4,    19,     4,     7,   132,     4,    91,
     131,   129,   669,     4,   671,     5,   673,   674,   132,   563,
       4,   138,    23,    24,   123,   124,   125,   126,   138,   686,
     687,   688,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   138,   700,    45,    46,    47,    48,    49,     4,
     831,   708,   134,   135,   134,   134,    57,   139,   133,    60,
     717,   134,   719,   129,  1065,   563,    67,   130,    69,     4,
     634,   709,   729,   730,   131,   133,    91,   130,   133,   736,
     136,   133,    83,    84,  1085,   596,   597,   598,   745,   746,
     747,   748,   590,   591,  1095,    21,   129,    23,    24,   140,
      26,   131,   759,   760,   761,   762,   126,   136,    24,   712,
     121,   122,   123,   124,   125,   126,     4,   755,     4,   134,
     135,     4,   779,   780,   139,   906,   133,   908,   909,   712,
       4,    57,   789,    12,    13,    14,    15,   794,   135,   134,
       4,    67,   140,    69,   129,   815,   803,    12,    13,    14,
      15,   712,   809,   810,   134,   129,     4,   814,     4,   136,
     133,   133,   132,   132,     4,   822,    32,   824,   712,   826,
     136,    37,    38,    39,    40,    41,    42,    43,     4,   132,
     837,   130,   839,   134,   841,   132,   130,   141,     4,   132,
     132,   848,   132,   831,   132,   852,    73,   134,   132,   856,
     857,   132,   983,   132,     4,   130,   134,   864,    89,   866,
     813,    89,   134,    79,   712,   133,    89,    89,   129,   140,
     132,   878,   132,   132,   132,   132,    92,    93,   134,   133,
     813,    32,   130,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,   130,   136,   135,     4,   132,   132,   129,
     907,   133,   813,     4,     4,    75,   132,   132,   129,   862,
     123,  1042,   132,  1051,   132,   132,    10,   136,   906,   813,
     908,   909,   132,   134,   931,   133,   133,   934,    79,   862,
     134,  1069,   133,   132,  1065,   129,   943,   134,   133,   946,
     133,    92,    93,   134,   133,   952,   133,   133,   136,  1087,
     130,   862,   133,   116,  1085,   133,   123,   130,   965,  1097,
     134,   138,   133,   132,  1095,   813,   134,    53,   862,   133,
     116,  1109,   133,   133,   133,   133,   133,   984,   134,   133,
    1118,   132,   134,  1121,   129,  1123,   116,  1125,   136,   996,
    1128,   116,  1130,   132,  1132,   983,  1134,     4,  1136,    10,
      11,    12,    13,    14,    15,    16,    17,   133,     3,     4,
       5,     6,   134,   133,   862,   134,  1023,  1024,  1025,   133,
      65,   134,   134,   133,  1031,   134,   133,   132,   134,   133,
     133,  1038,   134,   129,     4,   134,   134,   134,  1045,   134,
     133,   132,   134,   133,  1051,   133,   130,   895,  1055,   132,
    1057,   132,   134,   133,  1042,  1062,   143,   144,   145,   146,
     147,   148,   149,   150,   134,   134,   134,   154,   155,  1076,
     136,  1078,   133,  1080,    53,   134,    65,  1065,   133,   133,
     133,  1088,   132,   129,   133,   133,    78,   134,    22,   129,
      85,    86,   136,   136,  1101,   136,   133,  1085,   133,   133,
     133,   949,   129,   133,  1111,   136,   134,  1095,   103,   104,
     105,   106,   107,   108,   133,   133,   133,   133,    80,   133,
     133,   136,   365,   129,   129,   129,   121,   122,   129,   129,
     129,   129,     3,     4,     5,     6,   131,   132,     3,     4,
       5,     6,   133,    66,   139,   113,   197,    18,   143,   144,
     998,   740,   299,   404,    30,   545,  1004,   359,   490,   487,
     559,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,    58,    59,  1022,
     550,   646,   730,    58,    59,   725,   988,   736,    46,   278,
     117,     6,   517,     3,     4,     5,     6,   390,   656,   618,
     850,   893,   301,   613,    85,    86,   301,   946,  1004,   697,
      85,    86,   766,   301,  1045,   669,   509,   623,   626,   862,
    1037,    -1,   103,   104,   105,   106,   107,   108,   103,   104,
     105,   106,   107,   108,    -1,     3,     4,     5,     6,    -1,
     121,   122,   123,   445,    -1,    -1,   121,   122,    58,    59,
      -1,   132,    -1,    -1,    -1,    -1,    -1,   132,   139,    -1,
      -1,    -1,   143,   144,   139,    33,    -1,    -1,   143,   144,
      -1,    -1,    -1,    -1,    -1,    85,    86,     3,     4,     5,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   388,    -1,   103,   104,   105,   106,   107,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,   121,   122,    -1,    -1,    -1,    -1,    85,    86,    -1,
      -1,    -1,   132,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      -1,    -1,    -1,   143,   144,   103,   104,   105,   106,   107,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,   121,   122,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,   131,   132,    -1,    -1,    -1,    -1,    -1,
      96,   139,    -1,    -1,    -1,   143,   144,   103,   104,   105,
     106,   107,   108,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,     3,     4,     5,     6,   121,   122,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,    -1,   132,   103,   104,   105,
     106,   107,   108,   139,    -1,    -1,    -1,   143,   144,    -1,
      -1,     3,     4,     5,     6,   121,   122,    -1,    -1,    -1,
      -1,    85,    86,    -1,    -1,    -1,   132,    -1,    -1,    -1,
      -1,    -1,    96,   139,    -1,    -1,    -1,   143,   144,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,   121,   122,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    -1,   132,    -1,
      -1,    -1,    -1,    -1,    96,   139,    -1,    -1,    -1,   143,
     144,   103,   104,   105,   106,   107,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,     3,     4,     5,     6,   121,
     122,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,
     132,   103,   104,   105,   106,   107,   108,   139,    -1,    -1,
      -1,   143,   144,    -1,    -1,    -1,    -1,    -1,    -1,   121,
     122,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,
     132,    -1,    -1,    -1,    -1,    -1,    96,   139,    -1,    -1,
      -1,   143,   144,   103,   104,   105,   106,   107,   108,     3,
       4,     5,     6,    -1,    -1,     3,     4,     5,     6,    -1,
      -1,   121,   122,    -1,    -1,    -1,    -1,    85,    86,    -1,
      -1,    -1,   132,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      -1,    -1,    -1,   143,   144,   103,   104,   105,   106,   107,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,    -1,   121,   122,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   132,   133,    -1,    -1,    -1,    -1,
      -1,   139,    -1,    -1,    -1,   143,   144,    -1,    -1,    -1,
      -1,    85,    86,    -1,    -1,    -1,    -1,    85,    86,    -1,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,   103,
     104,   105,   106,   107,   108,   103,   104,   105,   106,   107,
     108,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,    -1,
      -1,    -1,    -1,   121,   122,    -1,    -1,    -1,   132,   133,
      85,    86,    -1,    -1,   132,   139,    -1,    -1,    -1,   143,
     144,   139,    -1,    -1,    -1,   143,   144,    -1,   103,   104,
     105,   106,   107,   108,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   121,   122,    -1,    -1,
      -1,    -1,    85,    86,    -1,    -1,    -1,   132,    -1,    -1,
      -1,    -1,    -1,    -1,   139,    -1,    -1,    -1,   143,   144,
     103,   104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,
      -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,    -1,    -1,
     143,   144,    -1,    -1,    -1,    -1,    85,    86,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,    -1,    -1,   103,   104,   105,   106,   107,   108,
      -1,     9,    -1,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    19,   121,   122,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,   132,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,    -1,    -1,   143,   144,    44,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    52,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    -1,    74,    -1,     9,    77,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    19,    -1,
      -1,    22,    90,    91,    25,    -1,    94,    95,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    44,    11,    12,    13,    14,    15,    50,
      -1,    52,    19,    54,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    -1,    74,    -1,    -1,    77,    44,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    52,    -1,    54,    -1,    90,
      91,    -1,    -1,    94,    -1,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    -1,    74,    -1,    -1,
      77,    78,     9,    -1,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    19,    90,    91,    -1,    -1,    94,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    44,    11,    12,
      13,    14,    15,    50,    51,    52,    19,    54,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    -1,    74,    -1,    -1,
      77,    44,    -1,    -1,    -1,    -1,    -1,    50,    -1,    52,
      -1,    54,    -1,    90,    91,    -1,    -1,    94,    -1,    62,
      63,    64,    -1,    23,    24,    -1,    -1,    -1,    71,    72,
      -1,    74,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,    -1,
      50,    94,    52,    -1,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    62,    63,    64,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    83,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,
     100,    -1,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   146,   147,     0,    19,    29,    91,   148,   149,   150,
     152,   160,   178,   182,   202,   263,   265,   295,   153,     4,
      90,   188,   189,   272,    21,    23,    24,    26,    57,    67,
      69,   151,   148,   148,   148,   148,   148,   148,   148,   148,
       4,   155,   156,   157,   158,   183,   273,   137,   193,   195,
      32,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    79,    92,    93,   132,   159,   190,   191,   192,     4,
       4,   264,   266,     4,     4,    61,   211,   211,    17,   154,
     129,    28,   130,   131,   135,   162,    43,   258,     3,     5,
       6,    85,    86,   103,   104,   105,   106,   107,   108,   121,
     122,   132,   139,   143,   144,   158,   366,   386,   387,     4,
     158,   192,   134,   161,   159,   258,   262,   262,   179,     4,
     130,   136,    43,   212,     4,   155,    20,   157,     4,   386,
       4,   132,   132,   169,    40,    41,    42,   274,   275,   276,
       5,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   386,   386,   389,   149,   149,     5,   137,   149,   193,
     194,   195,    87,    88,   136,   138,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   142,   194,   195,   196,   133,   162,    42,   259,
       4,   267,   268,   267,   134,   203,     4,     4,    42,   195,
     197,   206,    18,   163,     4,   131,   133,   149,   170,   173,
     134,   139,   195,   261,   132,   132,   387,   387,   387,   387,
     387,   387,   387,   387,   133,   136,   129,   139,   140,   387,
     387,   386,   388,   193,   193,   386,   386,   386,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   134,   169,    80,   260,   130,
     129,   134,   134,   180,   132,   209,     4,   130,     4,   132,
     213,   149,   165,   166,   268,   174,   175,   131,   188,   129,
     171,   184,     4,   277,   278,   386,   386,     5,   386,   386,
     389,   389,   138,   132,   138,   138,   138,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   386,   134,   261,   386,   268,    27,   149,
     181,   265,   295,     4,   208,   210,   134,   204,     4,   207,
     133,   214,   134,    23,    24,   129,   164,   130,   172,     4,
     131,   195,   173,   133,    25,    30,    31,    44,   149,   185,
     263,   265,   269,   283,   292,   295,   315,   326,   130,   279,
     129,   140,   133,   133,   136,   140,   131,   370,   371,   372,
     386,   136,   198,     4,   129,   133,   209,     4,   213,     4,
     149,   216,   217,   291,   219,   167,   168,   166,   133,   386,
     176,     4,   195,   270,   271,     4,   135,   186,   187,    45,
      46,    47,    48,    49,    83,    84,   188,   313,   314,   387,
     278,   386,   140,   158,   366,   129,   171,   386,     9,    11,
      22,    50,    52,    54,    62,    63,    64,    71,    72,    74,
      77,    94,   149,   152,   199,   200,   202,   220,   230,   233,
     263,   265,   269,   272,   282,   283,   292,   295,   296,   315,
     324,   335,   351,   375,   208,   134,   205,   134,   196,   188,
     129,   171,     8,    11,    70,   134,   139,   149,   152,   158,
     186,   263,   265,   283,   295,   324,   334,   336,   337,   350,
     366,   367,   262,   262,   172,   177,   366,   129,   134,   327,
       4,     5,     6,   132,   293,   294,   367,   319,     4,     4,
     195,   318,   316,   133,   372,   133,   136,   381,   136,   323,
     132,   132,     4,    52,   221,   222,   224,     4,    52,    73,
     231,   232,   233,   237,   238,   239,   251,   256,   137,   234,
     235,   236,   256,   373,     4,     4,     7,    60,   299,     4,
     280,   281,    12,    13,    14,    15,   132,   209,   219,   195,
     217,   215,   149,   368,   386,    50,    52,    54,    55,    56,
      99,   100,   349,   149,   337,    12,    13,    14,    15,   134,
     351,    97,    98,   114,   130,   268,   268,   172,   130,   271,
     132,   329,   386,   129,   134,   130,   337,   286,   287,   284,
     337,   141,   320,   132,   369,     4,   380,   386,   376,   132,
     132,    73,   221,   132,   257,   132,    73,   232,   132,   243,
     244,   134,   132,   254,   386,   235,   129,   134,   130,    78,
     199,   374,   375,   134,   297,   187,   129,   134,    89,    89,
      89,    89,   386,   134,    68,   218,   133,   339,   140,   129,
     323,   132,   132,   132,   132,   149,   350,   350,   338,    16,
      89,   325,   325,   325,   134,   325,   132,   187,   187,   386,
       4,    34,    35,   133,   330,   331,   332,   333,   328,   133,
     136,   294,   386,   288,   288,   187,    17,   123,   132,   317,
     370,   134,   373,   133,   336,    58,    59,   227,   386,   227,
     196,   255,   386,    58,    59,   242,   245,   249,   256,   130,
     130,    58,    59,   252,   253,   255,   136,   134,   236,   255,
     201,   135,   307,   298,   281,   132,   132,   132,   132,   133,
     291,   369,   368,   340,   386,   341,   386,   386,   369,   132,
     132,   132,   132,   386,   386,   386,   129,   171,   332,   134,
     386,   129,   134,   134,   289,   290,   291,   133,    18,    58,
      59,   123,   321,   322,   386,   337,   171,    51,   378,   134,
     386,   133,   386,   133,   136,   245,   249,   123,   121,   122,
     129,   246,   248,   132,   240,   255,   240,   256,   256,    76,
     129,   133,   254,   198,   132,     4,   300,   301,   301,   304,
     305,   306,    96,   386,    96,   386,    96,   386,   386,   379,
     134,   353,   133,   336,   133,   133,   134,    96,   386,    96,
     386,    96,   386,   133,   386,   133,   331,   133,   136,     4,
     129,   285,   130,   386,   386,   133,    60,   129,   133,   133,
     323,   382,   383,   386,    75,   225,    10,   386,   123,   130,
     248,   116,   249,   129,   248,   130,   255,   386,   129,   241,
     252,   252,   134,   138,    95,   131,   308,   309,   386,   193,
     302,   129,   134,   129,   134,   132,   386,   133,   386,   133,
     386,   133,   133,   360,    51,   337,   346,   134,   344,   345,
     386,   133,   386,   133,   386,   133,   134,   133,   348,   386,
     290,   134,   386,   322,   322,    53,   385,   374,   377,   386,
     129,   132,   226,   386,   136,   116,   116,   247,   250,   256,
     249,   116,   241,   136,   255,     4,   129,   133,   303,   132,
     301,   305,   149,   310,   311,   312,   133,   134,   133,   134,
     133,   134,   134,    65,   361,   362,   323,   337,   386,   337,
     337,   133,   134,   133,   134,   133,   134,   134,   352,   133,
     134,   382,   384,   134,   227,   386,   133,   386,   132,   132,
     129,   133,   250,   133,   386,   241,   132,   309,   132,   310,
      33,   131,   386,   133,   129,   134,   134,   134,     9,    66,
     364,   365,   386,   347,   342,   134,   134,   134,    81,    82,
     356,   336,   386,    87,    88,   136,   130,   247,   250,   250,
     133,   136,   386,   310,   133,     4,   312,   363,   129,   136,
      53,   354,   134,    65,   357,   358,   133,   225,   386,   386,
     386,   132,   228,   229,   386,    87,   248,    87,   248,   386,
     133,   133,   132,   384,   386,   355,   336,   364,   382,   129,
     133,   133,   133,   229,   386,   134,   136,   255,   136,   255,
     136,   133,   386,   337,   133,   359,   229,   129,   136,   386,
     133,   255,   133,   255,   133,   343,   337,   129,   223,   229,
     386,   136,   133,   133,   133,   133,   337,   229,   133,   129,
     133,   136,   386,   133,   133,   134,   229,   386,   129,   133,
     229,   129,   229,   129,   229,   129,   133,   229,   129,   229,
     129,   229,   129,   229,   129,   229,   129,   229,   133
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   145,   147,   146,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   150,   149,   151,   151,   153,   154,   152,
     155,   155,   156,   156,   157,   157,   158,   158,   158,   159,
     161,   160,   163,   164,   162,   162,   165,   165,   166,   167,
     166,   168,   166,   166,   169,   169,   169,   170,   170,   171,
     171,   172,   172,   174,   173,   175,   176,   173,   177,   173,
     173,   179,   178,   180,   180,   181,   181,   183,   182,   184,
     184,   185,   185,   185,   185,   185,   185,   185,   185,   186,
     186,   186,   186,   186,   187,   187,   189,   188,   190,   190,
     190,   190,   191,   191,   191,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   193,   193,   193,   193,
     194,   194,   195,   195,   196,   196,   197,   197,   198,   198,
     198,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   201,   200,
     203,   202,   204,   202,   205,   202,   206,   202,   207,   202,
     208,   208,   209,   209,   210,   210,   210,   210,   211,   211,
     212,   212,   213,   213,   214,   215,   213,   216,   216,   218,
     217,   217,   219,   219,   220,   221,   221,   222,   222,   223,
     223,   224,   224,   225,   225,   226,   226,   226,   226,   227,
     227,   227,   228,   228,   228,   228,   228,   229,   229,   230,
     230,   231,   231,   232,   232,   232,   233,   233,   234,   235,
     235,   236,   237,   237,   238,   239,   239,   240,   240,   240,
     241,   241,   242,   242,   243,   243,   243,   244,   244,   244,
     245,   245,   246,   246,   247,   247,   248,   248,   248,   249,
     250,   251,   252,   252,   252,   253,   253,   253,   254,   255,
     255,   257,   256,   258,   258,   259,   259,   260,   260,   261,
     262,   262,   264,   263,   266,   265,   267,   267,   268,   269,
     270,   270,   271,   273,   272,   274,   274,   274,   275,   276,
     276,   277,   277,   278,   279,   279,   280,   280,   281,   282,
     284,   285,   283,   286,   283,   287,   283,   288,   288,   289,
     289,   290,   290,   291,   292,   293,   293,   294,   295,   295,
     297,   296,   298,   296,   299,   299,   300,   300,   302,   301,
     303,   301,   304,   304,   305,   306,   305,   307,   307,   308,
     308,   309,   309,   309,   310,   311,   311,   312,   312,   312,
     312,   312,   312,   313,   313,   314,   314,   316,   317,   315,
     318,   315,   319,   315,   320,   320,   320,   320,   320,   320,
     321,   321,   321,   322,   322,   322,   323,   323,   324,   324,
     325,   325,   325,   327,   328,   326,   329,   329,   330,   330,
     331,   331,   332,   333,   333,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   335,   335,   335,   335,   335,   335,
     335,   336,   336,   336,   336,   336,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   338,   337,   339,   337,   340,
     337,   341,   342,   343,   337,   344,   337,   345,   337,   346,
     347,   337,   348,   337,   349,   349,   349,   350,   351,   351,
     351,   352,   352,   352,   353,   353,   355,   354,   354,   356,
     356,   358,   359,   357,   360,   360,   362,   363,   361,   364,
     364,   365,   365,   365,   365,   366,   366,   366,   367,   367,
     368,   368,   369,   369,   370,   370,   371,   371,   372,   373,
     373,   374,   374,   376,   377,   375,   378,   375,   379,   375,
     380,   375,   381,   375,   383,   382,   384,   384,   385,   385,
     386,   386,   387,   387,   387,   387,   387,   387,   387,   388,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     387,   387,   387,   389,   389
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
       1,     1,     2,     2,     1,     0,     5,     0,     5,     0,
       7,     0,     0,     0,    13,     0,     7,     0,     7,     0,
       0,     9,     0,     9,     0,     2,     2,     2,     1,     1,
       1,     2,     2,     0,     2,     0,     0,     3,     0,     2,
       0,     0,     0,     4,     2,     0,     0,     0,     4,     2,
       1,     1,     1,     1,     3,     6,     2,     2,     1,     3,
       1,     3,     4,     0,     1,     0,     1,     3,     1,     2,
       0,     1,     1,     0,     0,    11,     0,     7,     0,     7,
       0,     6,     0,     4,     0,     2,     1,     1,     2,     0,
       1,     6,     1,     4,     2,     2,     1,     1,     1,     0,
       7,     5,     5,     3,     7,     3,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     3,     3,     3,     3,     3,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     3,
       4,     4,     3,     1,     3
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
#line 228 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
	ast_stack.clear();
	ast_stack.push_back(current_ast);
}
#line 2925 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 231 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
	ast_stack.pop_back();
	log_assert(GetSize(ast_stack) == 0);
	for (auto &it : default_attr_list)
		delete it.second;
	default_attr_list.clear();
}
#line 2937 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 251 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (attr_list != nullptr)
			attr_list_stack.push(attr_list);
		attr_list = new std::map<std::string, AstNode*>;
		for (auto &it : default_attr_list)
			(*attr_list)[it.first] = it.second->clone();
	}
#line 2949 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 257 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.al) = attr_list;
		if (!attr_list_stack.empty()) {
			attr_list = attr_list_stack.top();
			attr_list_stack.pop();
		} else
			attr_list = nullptr;
	}
#line 2962 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 267 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_RULE_LOC((yyloc), (yylsp[-2]), (yyloc));
	}
#line 2970 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 273 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (attr_list != nullptr)
			attr_list_stack.push(attr_list);
		attr_list = new std::map<std::string, AstNode*>;
		for (auto &it : default_attr_list)
			delete it.second;
		default_attr_list.clear();
	}
#line 2983 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 280 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		attr_list->swap(default_attr_list);
		delete attr_list;
		if (!attr_list_stack.empty()) {
			attr_list = attr_list_stack.top();
			attr_list_stack.pop();
		} else
			attr_list = nullptr;
	}
#line 2997 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 298 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (attr_list->count(*(yyvsp[0].string)) != 0)
			delete (*attr_list)[*(yyvsp[0].string)];
		(*attr_list)[*(yyvsp[0].string)] = AstNode::mkconst_int(1, false);
		delete (yyvsp[0].string);
	}
#line 3008 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 304 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (attr_list->count(*(yyvsp[-2].string)) != 0)
			delete (*attr_list)[*(yyvsp[-2].string)];
		(*attr_list)[*(yyvsp[-2].string)] = (yyvsp[0].ast);
		delete (yyvsp[-2].string);
	}
#line 3019 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 312 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = (yyvsp[0].string);
	}
#line 3027 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 315 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].string)->compare(0, 1, "\\") == 0)
			*(yyvsp[-2].string) += "::" + (yyvsp[0].string)->substr(1);
		else
			*(yyvsp[-2].string) += "::" + *(yyvsp[0].string);
		delete (yyvsp[0].string);
		(yyval.string) = (yyvsp[-2].string);
	}
#line 3040 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 323 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].string)->compare(0, 1, "\\") == 0)
			*(yyvsp[-2].string) += "." + (yyvsp[0].string)->substr(1);
		else
			*(yyvsp[-2].string) += "." + *(yyvsp[0].string);
		delete (yyvsp[0].string);
		(yyval.string) = (yyvsp[-2].string);
	}
#line 3053 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 333 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[-1].string); }
#line 3059 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 336 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3076 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 347 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (port_stubs.size() != 0)
			frontend_verilog_yyerror("Missing details for module port `%s'.",
					port_stubs.begin()->first.c_str());
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[-7]), (yyloc));
		ast_stack.pop_back();
		log_assert(ast_stack.size() == 1);
		current_ast_mod = NULL;
	}
#line 3090 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 358 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { astbuf1 = nullptr; }
#line 3096 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 358 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { if (astbuf1) delete astbuf1; }
#line 3102 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 365 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (astbuf1) delete astbuf1;
		astbuf1 = new AstNode(AST_PARAMETER);
		astbuf1->children.push_back(AstNode::mkconst_int(0, true));
		append_attr(astbuf1, (yyvsp[-1].al));
	}
#line 3113 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 371 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (astbuf1) delete astbuf1;
		astbuf1 = new AstNode(AST_LOCALPARAM);
		astbuf1->children.push_back(AstNode::mkconst_int(0, true));
		append_attr(astbuf1, (yyvsp[-1].al));
	}
#line 3124 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 389 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3146 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 409 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3165 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 423 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = new AstNode(AST_INTERFACEPORT);
		astbuf1->children.push_back(new AstNode(AST_INTERFACEPORTTYPE));
		astbuf1->children[0]->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 3176 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 428 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3191 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 438 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3211 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 453 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		do_not_require_port_stubs = true;
	}
#line 3219 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 458 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *mod = new AstNode(AST_PACKAGE);
		ast_stack.back()->children.push_back(mod);
		ast_stack.push_back(mod);
		current_ast_mod = mod;
		mod->str = *(yyvsp[0].string);
		append_attr(mod, (yyvsp[-2].al));
	}
#line 3232 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 465 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
		current_ast_mod = NULL;
	}
#line 3241 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 480 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3257 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 490 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (port_stubs.size() != 0)
			frontend_verilog_yyerror("Missing details for module port `%s'.",
				port_stubs.begin()->first.c_str());
		ast_stack.pop_back();
		log_assert(ast_stack.size() == 1);
		current_ast_mod = NULL;
	}
#line 3270 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 507 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; delete (yyvsp[0].string); }
#line 3276 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 508 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = const2ast(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 3282 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 509 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; delete (yyvsp[0].string); }
#line 3288 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 510 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; delete (yyvsp[-1].ast); }
#line 3294 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 511 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; delete (yyvsp[-5].ast); delete (yyvsp[-3].ast); delete (yyvsp[-1].ast); }
#line 3300 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 514 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 3306 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 514 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; }
#line 3312 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 517 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3 = new AstNode(AST_WIRE);
		current_wire_rand = false;
		current_wire_const = false;
	}
#line 3322 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 521 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = astbuf3;
		SET_RULE_LOC((yyloc), (yylsp[0]), (yyloc));
	}
#line 3331 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 530 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_custom_type = true;
		astbuf3->children.push_back(new AstNode(AST_WIRETYPE));
		astbuf3->children.back()->str = *(yyvsp[0].string);
	}
#line 3341 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 537 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_input = true;
	}
#line 3349 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 540 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_output = true;
	}
#line 3357 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 543 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_input = true;
		astbuf3->is_output = true;
	}
#line 3366 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 549 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
	}
#line 3373 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 551 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_wor = true;
	}
#line 3381 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 554 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_wand = true;
	}
#line 3389 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 557 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_reg = true;
	}
#line 3397 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 560 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_logic = true;
	}
#line 3405 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 563 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_logic = true;
	}
#line 3413 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 566 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_reg = true;
		astbuf3->range_left = 31;
		astbuf3->range_right = 0;
		astbuf3->is_signed = true;
	}
#line 3424 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 572 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->type = AST_GENVAR;
		astbuf3->is_reg = true;
		astbuf3->is_signed = true;
		astbuf3->range_left = 31;
		astbuf3->range_right = 0;
	}
#line 3436 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 579 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf3->is_signed = true;
	}
#line 3444 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 582 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_wire_rand = true;
	}
#line 3452 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 585 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_wire_const = true;
	}
#line 3460 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 590 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_RANGE);
		(yyval.ast)->children.push_back((yyvsp[-3].ast));
		(yyval.ast)->children.push_back((yyvsp[-1].ast));
	}
#line 3470 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 595 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_RANGE);
		AstNode *expr = new AstNode(AST_CONCAT, (yyvsp[-3].ast));
		(yyval.ast)->children.push_back(new AstNode(AST_SUB, new AstNode(AST_ADD, expr->clone(), (yyvsp[-1].ast)), AstNode::mkconst_int(1, true)));
		(yyval.ast)->children.push_back(new AstNode(AST_ADD, expr, AstNode::mkconst_int(0, true)));
	}
#line 3481 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 601 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_RANGE);
		AstNode *expr = new AstNode(AST_CONCAT, (yyvsp[-3].ast));
		(yyval.ast)->children.push_back(new AstNode(AST_ADD, expr, AstNode::mkconst_int(0, true)));
		(yyval.ast)->children.push_back(new AstNode(AST_SUB, new AstNode(AST_ADD, expr->clone(), AstNode::mkconst_int(1, true)), (yyvsp[-1].ast)));
	}
#line 3492 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 607 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_RANGE);
		(yyval.ast)->children.push_back((yyvsp[-1].ast));
	}
#line 3501 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 613 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_MULTIRANGE, (yyvsp[-1].ast), (yyvsp[0].ast));
	}
#line 3509 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 616 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
		(yyval.ast)->children.push_back((yyvsp[0].ast));
	}
#line 3518 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 622 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 3526 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 625 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = NULL;
	}
#line 3534 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 630 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 3540 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 631 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 3546 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 634 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 3554 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 637 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_RANGE);
		(yyval.ast)->children.push_back(AstNode::mkconst_int(31, true));
		(yyval.ast)->children.push_back(AstNode::mkconst_int(0, true));
		(yyval.ast)->is_signed = true;
	}
#line 3565 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 656 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENBLOCK);
		node->str = *(yyvsp[-1].string);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 3576 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 661 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete (yyvsp[-4].string);
		ast_stack.pop_back();
	}
#line 3585 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 667 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = new AstNode(AST_DPI_FUNCTION, AstNode::mkconst_str(*(yyvsp[-1].string)), AstNode::mkconst_str(*(yyvsp[0].string)));
		current_function_or_task->str = *(yyvsp[0].string);
		append_attr(current_function_or_task, (yyvsp[-3].al));
		ast_stack.back()->children.push_back(current_function_or_task);
		delete (yyvsp[-1].string);
		delete (yyvsp[0].string);
	}
#line 3598 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 674 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = NULL;
	}
#line 3606 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 677 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = new AstNode(AST_DPI_FUNCTION, AstNode::mkconst_str(*(yyvsp[-1].string)), AstNode::mkconst_str(*(yyvsp[-3].string)));
		current_function_or_task->str = *(yyvsp[0].string);
		append_attr(current_function_or_task, (yyvsp[-5].al));
		ast_stack.back()->children.push_back(current_function_or_task);
		delete (yyvsp[-3].string);
		delete (yyvsp[-1].string);
		delete (yyvsp[0].string);
	}
#line 3620 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 685 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = NULL;
	}
#line 3628 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 688 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3643 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 697 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = NULL;
	}
#line 3651 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 700 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = new AstNode(AST_TASK);
		current_function_or_task->str = *(yyvsp[0].string);
		append_attr(current_function_or_task, (yyvsp[-3].al));
		ast_stack.back()->children.push_back(current_function_or_task);
		ast_stack.push_back(current_function_or_task);
		current_function_or_task_port_id = 1;
		delete (yyvsp[0].string);
	}
#line 3665 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 708 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = NULL;
		ast_stack.pop_back();
	}
#line 3674 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 712 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3698 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 730 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task = NULL;
		ast_stack.pop_back();
	}
#line 3707 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 736 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task->children.push_back(AstNode::mkconst_str(*(yyvsp[-1].string)));
		delete (yyvsp[-1].string);
		delete (yyvsp[0].string);
	}
#line 3717 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 741 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		current_function_or_task->children.push_back(AstNode::mkconst_str(*(yyvsp[0].string)));
		delete (yyvsp[0].string);
	}
#line 3726 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 160:
#line 761 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = true;
	}
#line 3734 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 161:
#line 764 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 3742 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 769 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		albuf = nullptr;
		astbuf1 = nullptr;
		astbuf2 = nullptr;
	}
#line 3752 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 165:
#line 773 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
		if (astbuf2 != NULL)
			delete astbuf2;
		free_attr(albuf);
	}
#line 3763 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 784 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3790 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 177:
#line 821 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3878 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 178:
#line 904 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 3952 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 179:
#line 975 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_triple_ptr) = (yyvsp[0].specify_triple_ptr);
	}
#line 3960 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 180:
#line 978 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_triple_ptr) = nullptr;
	}
#line 3968 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 181:
#line 983 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 3976 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 182:
#line 986 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
	}
#line 3984 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 183:
#line 991 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 3992 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 184:
#line 994 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
	}
#line 4000 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 185:
#line 999 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_target_ptr) = new specify_target;
		(yyval.specify_target_ptr)->polarity_op = 0;
		(yyval.specify_target_ptr)->dst = (yyvsp[0].ast);
		(yyval.specify_target_ptr)->dat = nullptr;
	}
#line 4011 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 186:
#line 1005 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_target_ptr) = new specify_target;
		(yyval.specify_target_ptr)->polarity_op = 0;
		(yyval.specify_target_ptr)->dst = (yyvsp[-3].ast);
		(yyval.specify_target_ptr)->dat = (yyvsp[-1].ast);
	}
#line 4022 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 187:
#line 1011 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_target_ptr) = new specify_target;
		(yyval.specify_target_ptr)->polarity_op = '-';
		(yyval.specify_target_ptr)->dst = (yyvsp[-3].ast);
		(yyval.specify_target_ptr)->dat = (yyvsp[-1].ast);
	}
#line 4033 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 188:
#line 1017 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_target_ptr) = new specify_target;
		(yyval.specify_target_ptr)->polarity_op = '+';
		(yyval.specify_target_ptr)->dst = (yyvsp[-3].ast);
		(yyval.specify_target_ptr)->dat = (yyvsp[-1].ast);
	}
#line 4044 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 189:
#line 1025 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ch) = 'p'; }
#line 4050 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 190:
#line 1026 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ch) = 'n'; }
#line 4056 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 191:
#line 1027 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ch) = 0; }
#line 4062 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 192:
#line 1030 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_rise_fall_ptr) = new specify_rise_fall;
		(yyval.specify_rise_fall_ptr)->rise = *(yyvsp[0].specify_triple_ptr);
		(yyval.specify_rise_fall_ptr)->fall.t_min = (yyvsp[0].specify_triple_ptr)->t_min->clone();
		(yyval.specify_rise_fall_ptr)->fall.t_avg = (yyvsp[0].specify_triple_ptr)->t_avg->clone();
		(yyval.specify_rise_fall_ptr)->fall.t_max = (yyvsp[0].specify_triple_ptr)->t_max->clone();
		delete (yyvsp[0].specify_triple_ptr);
	}
#line 4075 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 193:
#line 1038 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_rise_fall_ptr) = new specify_rise_fall;
		(yyval.specify_rise_fall_ptr)->rise = *(yyvsp[-3].specify_triple_ptr);
		(yyval.specify_rise_fall_ptr)->fall = *(yyvsp[-1].specify_triple_ptr);
		delete (yyvsp[-3].specify_triple_ptr);
		delete (yyvsp[-1].specify_triple_ptr);
	}
#line 4087 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 194:
#line 1045 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_rise_fall_ptr) = new specify_rise_fall;
		(yyval.specify_rise_fall_ptr)->rise = *(yyvsp[-5].specify_triple_ptr);
		(yyval.specify_rise_fall_ptr)->fall = *(yyvsp[-3].specify_triple_ptr);
		delete (yyvsp[-5].specify_triple_ptr);
		delete (yyvsp[-3].specify_triple_ptr);
        delete (yyvsp[-1].specify_triple_ptr);
        log_file_warning(current_filename, get_line_num(), "Path delay expressions beyond rise/fall not currently supported. Ignoring.\n");
	}
#line 4101 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 195:
#line 1054 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 4118 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 196:
#line 1066 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 4141 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 197:
#line 1086 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_triple_ptr) = new specify_triple;
		(yyval.specify_triple_ptr)->t_min = (yyvsp[0].ast);
		(yyval.specify_triple_ptr)->t_avg = (yyvsp[0].ast)->clone();
		(yyval.specify_triple_ptr)->t_max = (yyvsp[0].ast)->clone();
	}
#line 4152 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 198:
#line 1092 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.specify_triple_ptr) = new specify_triple;
		(yyval.specify_triple_ptr)->t_min = (yyvsp[-4].ast);
		(yyval.specify_triple_ptr)->t_avg = (yyvsp[-2].ast);
		(yyval.specify_triple_ptr)->t_max = (yyvsp[0].ast);
	}
#line 4163 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 248:
#line 1215 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].ast); }
#line 4169 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 249:
#line 1218 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].ast); }
#line 4175 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 250:
#line 1219 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete (yyvsp[-4].ast);
		delete (yyvsp[-2].ast);
		delete (yyvsp[0].ast);
	}
#line 4185 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 251:
#line 1226 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].string); }
#line 4191 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 252:
#line 1227 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { delete (yyvsp[0].ast); }
#line 4197 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 253:
#line 1232 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1->is_signed = true;
	}
#line 4205 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 255:
#line 1237 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (astbuf1->children.size() != 1)
			frontend_verilog_yyerror("Internal error in param_integer - should not happen?");
		astbuf1->children.push_back(new AstNode(AST_RANGE));
		astbuf1->children.back()->children.push_back(AstNode::mkconst_int(31, true));
		astbuf1->children.back()->children.push_back(AstNode::mkconst_int(0, true));
		astbuf1->is_signed = true;
	}
#line 4218 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 257:
#line 1247 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (astbuf1->children.size() != 1)
			frontend_verilog_yyerror("Parameter already declared as integer, cannot set to real.");
		astbuf1->children.push_back(new AstNode(AST_REALVALUE));
	}
#line 4228 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 259:
#line 1254 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].ast) != NULL) {
			if (astbuf1->children.size() != 1)
				frontend_verilog_yyerror("integer/real parameters should not have a range.");
			astbuf1->children.push_back((yyvsp[0].ast));
		}
	}
#line 4240 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 261:
#line 1264 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1->is_custom_type = true;
		astbuf1->children.push_back(new AstNode(AST_WIRETYPE));
		astbuf1->children.back()->str = *(yyvsp[0].string);
	}
#line 4250 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 262:
#line 1271 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = new AstNode(AST_PARAMETER);
		astbuf1->children.push_back(AstNode::mkconst_int(0, true));
		append_attr(astbuf1, (yyvsp[-1].al));
	}
#line 4260 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 263:
#line 1275 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
	}
#line 4268 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 264:
#line 1280 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = new AstNode(AST_LOCALPARAM);
		astbuf1->children.push_back(AstNode::mkconst_int(0, true));
		append_attr(astbuf1, (yyvsp[-1].al));
	}
#line 4278 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 265:
#line 1284 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
	}
#line 4286 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 268:
#line 1292 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 4307 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 272:
#line 1316 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_DEFPARAM);
		node->children.push_back((yyvsp[-2].ast));
		node->children.push_back((yyvsp[0].ast));
		if ((yyvsp[-3].ast) != NULL)
			node->children.push_back((yyvsp[-3].ast));
		ast_stack.back()->children.push_back(node);
	}
#line 4320 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 273:
#line 1325 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 4336 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 274:
#line 1335 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {  // create template for the enum vars
								auto tnode = astbuf1->clone();
								delete astbuf1;
								astbuf1 = tnode;
								tnode->type = AST_WIRE;
								tnode->attributes["\\enum_type"] = AstNode::mkconst_str(astbuf2->str);
								// drop constant but keep any range
								delete tnode->children[0];
								tnode->children.erase(tnode->children.begin()); }
#line 4350 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 277:
#line 1348 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {astbuf1->is_reg = true; addRange(astbuf1); }
#line 4356 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 278:
#line 1351 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {astbuf1->is_reg=true; addRange(astbuf1); }
#line 4362 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 279:
#line 1354 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {astbuf1->is_reg = true;}
#line 4368 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 280:
#line 1355 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {astbuf1->is_logic = true;}
#line 4374 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 283:
#line 1364 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		// put in fn
		log_assert(astbuf1);
		log_assert(astbuf2);
		auto node = astbuf1->clone();
		node->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		delete node->children[0];
		node->children[0] = (yyvsp[0].ast) ?: new AstNode(AST_NONE);
		astbuf2->children.push_back(node);
	}
#line 4390 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 284:
#line 1378 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 4396 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 285:
#line 1379 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = NULL; }
#line 4402 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 288:
#line 1387 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		log_assert(astbuf1);
		log_assert(astbuf2);
		auto node = astbuf1->clone();
		ast_stack.back()->children.push_back(node);
		node->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
		node->is_enum = true;
	}
#line 4416 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 289:
#line 1398 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		//enum_type creates astbuf1 for use by typedef only
		delete astbuf1;
	}
#line 4425 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 290:
#line 1405 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 4446 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 291:
#line 1420 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
		if (astbuf2 != NULL)
			delete astbuf2;
		free_attr(albuf);
	}
#line 4457 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 293:
#line 1426 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_WIRE));
		ast_stack.back()->children.back()->str = *(yyvsp[0].string);
		append_attr(ast_stack.back()->children.back(), (yyvsp[-2].al));
		ast_stack.back()->children.push_back(new AstNode(AST_ASSIGN, new AstNode(AST_IDENTIFIER), AstNode::mkconst_int(0, false, 1)));
		ast_stack.back()->children.back()->children[0]->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 4470 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 295:
#line 1434 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_WIRE));
		ast_stack.back()->children.back()->str = *(yyvsp[0].string);
		append_attr(ast_stack.back()->children.back(), (yyvsp[-2].al));
		ast_stack.back()->children.push_back(new AstNode(AST_ASSIGN, new AstNode(AST_IDENTIFIER), AstNode::mkconst_int(1, false, 1)));
		ast_stack.back()->children.back()->children[0]->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 4483 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 298:
#line 1445 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *wire_node = ast_stack.back()->children.at(GetSize(ast_stack.back()->children)-2)->clone();
		AstNode *assign_node = ast_stack.back()->children.at(GetSize(ast_stack.back()->children)-1)->clone();
		wire_node->str = *(yyvsp[0].string);
		assign_node->children[0]->str = *(yyvsp[0].string);
		ast_stack.back()->children.push_back(wire_node);
		ast_stack.back()->children.push_back(assign_node);
		delete (yyvsp[0].string);
	}
#line 4497 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 301:
#line 1459 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 4544 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 302:
#line 1501 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 4575 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 303:
#line 1529 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 4631 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 307:
#line 1588 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ASSIGN, (yyvsp[-2].ast), (yyvsp[0].ast));
		SET_AST_NODE_LOC(node, (yyloc), (yyloc));
		ast_stack.back()->children.push_back(node);
	}
#line 4641 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 308:
#line 1595 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 4683 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 309:
#line 1632 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_TYPEDEF, astbuf1));
		ast_stack.back()->children.back()->str = *(yyvsp[-1].string);
	}
#line 4692 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 310:
#line 1639 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = new AstNode(AST_CELL);
		append_attr(astbuf1, (yyvsp[-1].al));
		astbuf1->children.push_back(new AstNode(AST_CELLTYPE));
		astbuf1->children[0]->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 4704 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 311:
#line 1645 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
	}
#line 4712 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 312:
#line 1648 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf1 = new AstNode(AST_PRIMITIVE);
		astbuf1->str = *(yyvsp[-1].string);
		append_attr(astbuf1, (yyvsp[-2].al));
		delete (yyvsp[-1].string);
	}
#line 4723 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 313:
#line 1653 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete astbuf1;
	}
#line 4731 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 314:
#line 1658 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = (yyvsp[0].string);
	}
#line 4739 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 315:
#line 1661 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = new std::string("or");
	}
#line 4747 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 318:
#line 1670 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf2 = astbuf1->clone();
		if (astbuf2->type != AST_PRIMITIVE)
			astbuf2->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
		ast_stack.back()->children.push_back(astbuf2);
	}
#line 4759 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 319:
#line 1676 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(astbuf2, (yylsp[-4]), (yyloc));
	}
#line 4767 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 320:
#line 1679 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf2 = astbuf1->clone();
		if (astbuf2->type != AST_PRIMITIVE)
			astbuf2->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		ast_stack.back()->children.push_back(new AstNode(AST_CELLARRAY, (yyvsp[0].ast), astbuf2));
	}
#line 4779 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 321:
#line 1685 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(astbuf2, (yylsp[-5]), (yyloc));
		SET_AST_NODE_LOC(astbuf3, (yylsp[-5]), (yyloc));
	}
#line 4788 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 325:
#line 1696 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		astbuf2 = astbuf1->clone();
		ast_stack.back()->children.push_back(astbuf2);
	}
#line 4797 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 332:
#line 1709 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_PARASET);
		astbuf1->children.push_back(node);
		node->children.push_back((yyvsp[0].ast));
	}
#line 4807 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 333:
#line 1714 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_PARASET);
		node->str = *(yyvsp[-3].string);
		astbuf1->children.push_back(node);
		node->children.push_back((yyvsp[-1].ast));
		delete (yyvsp[-3].string);
	}
#line 4819 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 334:
#line 1723 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 4849 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 337:
#line 1753 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ARGUMENT);
		astbuf2->children.push_back(node);
		free_attr((yyvsp[0].al));
	}
#line 4859 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 338:
#line 1758 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ARGUMENT);
		astbuf2->children.push_back(node);
		node->children.push_back((yyvsp[0].ast));
		free_attr((yyvsp[-1].al));
	}
#line 4870 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 339:
#line 1764 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ARGUMENT);
		node->str = *(yyvsp[-3].string);
		astbuf2->children.push_back(node);
		node->children.push_back((yyvsp[-1].ast));
		delete (yyvsp[-3].string);
		free_attr((yyvsp[-5].al));
	}
#line 4883 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 340:
#line 1772 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ARGUMENT);
		node->str = *(yyvsp[-2].string);
		astbuf2->children.push_back(node);
		delete (yyvsp[-2].string);
		free_attr((yyvsp[-4].al));
	}
#line 4895 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 341:
#line 1779 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ARGUMENT);
		node->str = *(yyvsp[0].string);
		astbuf2->children.push_back(node);
		node->children.push_back(new AstNode(AST_IDENTIFIER));
		node->children.back()->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
		free_attr((yyvsp[-2].al));
	}
#line 4909 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 342:
#line 1788 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (!sv_mode)
			frontend_verilog_yyerror("Wildcard port connections are only supported in SystemVerilog mode.");
		astbuf2->attributes[ID(wildcard_port_conns)] = AstNode::mkconst_int(1, false);
	}
#line 4919 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 343:
#line 1795 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 4927 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 344:
#line 1798 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = true;
	}
#line 4935 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 345:
#line 1803 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 4943 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 346:
#line 1806 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = true;
	}
#line 4951 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 347:
#line 1811 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ALWAYS);
		append_attr(node, (yyvsp[-1].al));
		if ((yyvsp[0].boolean))
			node->attributes[ID(always_ff)] = AstNode::mkconst_int(1, false);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 4964 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 348:
#line 1818 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
	}
#line 4974 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 349:
#line 1822 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
		ast_stack.pop_back();

		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[-4]), (yyloc));
		ast_stack.pop_back();

		SET_RULE_LOC((yyloc), (yylsp[-4]), (yyloc));
	}
#line 4988 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 350:
#line 1831 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5006 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 351:
#line 1843 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5015 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 352:
#line 1847 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_INITIAL);
		append_attr(node, (yyvsp[-1].al));
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
	}
#line 5029 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 353:
#line 1855 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5038 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 363:
#line 1874 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_POSEDGE);
		ast_stack.back()->children.push_back(node);
		node->children.push_back((yyvsp[0].ast));
	}
#line 5048 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 364:
#line 1879 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_NEGEDGE);
		ast_stack.back()->children.push_back(node);
		node->children.push_back((yyvsp[0].ast));
	}
#line 5058 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 365:
#line 1884 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_EDGE);
		ast_stack.back()->children.push_back(node);
		node->children.push_back((yyvsp[0].ast));
	}
#line 5068 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 366:
#line 1891 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = (yyvsp[0].string);
	}
#line 5076 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 367:
#line 1894 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = NULL;
	}
#line 5084 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 368:
#line 1899 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = (yyvsp[-1].string);
	}
#line 5092 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 369:
#line 1902 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.string) = NULL;
	}
#line 5100 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 370:
#line 1907 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = true;
	}
#line 5108 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 371:
#line 1910 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 5116 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 372:
#line 1913 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 5124 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 373:
#line 1918 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
        AstNode *modport = new AstNode(AST_MODPORT);
        ast_stack.back()->children.push_back(modport);
        ast_stack.push_back(modport);
        modport->str = *(yyvsp[0].string);
        delete (yyvsp[0].string);
    }
#line 5136 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 374:
#line 1924 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
        ast_stack.pop_back();
        log_assert(ast_stack.size() == 2);
    }
#line 5145 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 382:
#line 1940 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
        AstNode *modport_member = new AstNode(AST_MODPORTMEMBER);
        ast_stack.back()->children.push_back(modport_member);
        modport_member->str = *(yyvsp[0].string);
        modport_member->is_input = current_modport_input;
        modport_member->is_output = current_modport_output;
        delete (yyvsp[0].string);
    }
#line 5158 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 383:
#line 1950 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {current_modport_input = 1; current_modport_output = 0;}
#line 5164 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 384:
#line 1950 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {current_modport_input = 0; current_modport_output = 1;}
#line 5170 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 385:
#line 1953 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5187 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 386:
#line 1965 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5204 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 387:
#line 1977 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5221 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 388:
#line 1989 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5238 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 389:
#line 2001 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_COVER, (yyvsp[-2].ast));
		if ((yyvsp[-6].string) != nullptr) {
			node->str = *(yyvsp[-6].string);
			delete (yyvsp[-6].string);
		}
		ast_stack.back()->children.push_back(node);
	}
#line 5251 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 390:
#line 2009 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_COVER, AstNode::mkconst_int(1, false));
		if ((yyvsp[-5].string) != nullptr) {
			node->str = *(yyvsp[-5].string);
			delete (yyvsp[-5].string);
		}
		ast_stack.back()->children.push_back(node);
	}
#line 5264 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 391:
#line 2017 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_COVER, AstNode::mkconst_int(1, false));
		if ((yyvsp[-2].string) != nullptr) {
			node->str = *(yyvsp[-2].string);
			delete (yyvsp[-2].string);
		}
		ast_stack.back()->children.push_back(node);
	}
#line 5277 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 392:
#line 2025 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5296 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 393:
#line 2039 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5315 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 394:
#line 2055 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(assume_asserts_mode ? AST_ASSUME : AST_ASSERT, (yyvsp[-2].ast)));
		if ((yyvsp[-6].string) != nullptr) {
			ast_stack.back()->children.back()->str = *(yyvsp[-6].string);
			delete (yyvsp[-6].string);
		}
	}
#line 5327 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 395:
#line 2062 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_ASSUME, (yyvsp[-2].ast)));
		if ((yyvsp[-6].string) != nullptr) {
			ast_stack.back()->children.back()->str = *(yyvsp[-6].string);
			delete (yyvsp[-6].string);
		}
	}
#line 5339 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 396:
#line 2069 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(assume_asserts_mode ? AST_FAIR : AST_LIVE, (yyvsp[-2].ast)));
		if ((yyvsp[-7].string) != nullptr) {
			ast_stack.back()->children.back()->str = *(yyvsp[-7].string);
			delete (yyvsp[-7].string);
		}
	}
#line 5351 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 397:
#line 2076 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_FAIR, (yyvsp[-2].ast)));
		if ((yyvsp[-7].string) != nullptr) {
			ast_stack.back()->children.back()->str = *(yyvsp[-7].string);
			delete (yyvsp[-7].string);
		}
	}
#line 5363 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 398:
#line 2083 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_COVER, (yyvsp[-2].ast)));
		if ((yyvsp[-6].string) != nullptr) {
			ast_stack.back()->children.back()->str = *(yyvsp[-6].string);
			delete (yyvsp[-6].string);
		}
	}
#line 5375 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 399:
#line 2090 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5391 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 400:
#line 2101 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5407 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 401:
#line 2114 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ASSIGN_EQ, (yyvsp[-3].ast), (yyvsp[0].ast));
		if((yyvsp[-1].ast))
			node->during_delay = (yyvsp[-1].ast)->integer;
		ast_stack.back()->children.push_back(node);
		(yyval.ast) = node;
	}
#line 5419 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 402:
#line 2121 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ASSIGN_EQ, (yyvsp[-1].ast), new AstNode(AST_ADD, (yyvsp[-1].ast)->clone(), AstNode::mkconst_int(1, true)));
		ast_stack.back()->children.push_back(node);
		(yyval.ast) = node;
	}
#line 5429 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 403:
#line 2126 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ASSIGN_EQ, (yyvsp[-1].ast), new AstNode(AST_SUB, (yyvsp[-1].ast)->clone(), AstNode::mkconst_int(1, true)));
		ast_stack.back()->children.push_back(node);
		(yyval.ast) = node;
	}
#line 5439 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 404:
#line 2131 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_ASSIGN_LE, (yyvsp[-3].ast), (yyvsp[0].ast));
		if((yyvsp[-1].ast))
			node->during_delay = (yyvsp[-1].ast)->integer;
		ast_stack.back()->children.push_back(node);
		(yyval.ast) = node;
	}
#line 5451 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 405:
#line 2138 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode* node = new AstNode();
		ast_stack.back()->children.push_back(node);
		(yyval.ast) = node;
	}
#line 5461 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 406:
#line 2146 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; }
#line 5467 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 407:
#line 2146 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; }
#line 5473 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 408:
#line 2146 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; }
#line 5479 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 409:
#line 2146 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; }
#line 5485 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 410:
#line 2146 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; }
#line 5491 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 411:
#line 2146 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; }
#line 5497 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 412:
#line 2147 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); if((yyval.ast) && (yyvsp[-1].ast)) (yyval.ast)->after_delay = (yyvsp[-1].ast)->integer; }
#line 5503 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 413:
#line 2148 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 5509 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 414:
#line 2148 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = nullptr; }
#line 5515 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 415:
#line 2149 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_TCALL);
		node->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[0].al));
	}
#line 5528 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 416:
#line 2156 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
		ast_stack.pop_back();
	}
#line 5537 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 417:
#line 2160 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_TCALL);
		node->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[0].al));
	}
#line 5550 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 418:
#line 2167 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
		ast_stack.pop_back();
	}
#line 5559 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 419:
#line 2171 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[-2].al));
		if ((yyvsp[0].string) != NULL)
			node->str = *(yyvsp[0].string);
	}
#line 5572 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 420:
#line 2178 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
		if ((yyvsp[-4].string) != NULL && (yyvsp[0].string) != NULL && *(yyvsp[-4].string) != *(yyvsp[0].string))
			frontend_verilog_yyerror("Begin label (%s) and end label (%s) don't match.", (yyvsp[-4].string)->c_str()+1, (yyvsp[0].string)->c_str()+1);
		if ((yyvsp[-4].string) != NULL)
			delete (yyvsp[-4].string);
		if ((yyvsp[0].string) != NULL)
			delete (yyvsp[0].string);
		ast_stack.pop_back();
	}
#line 5587 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 421:
#line 2188 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_FOR);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[-2].al));
	}
#line 5598 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 422:
#line 2193 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back((yyvsp[0].ast));
	}
#line 5606 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 423:
#line 2195 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
	}
#line 5616 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 424:
#line 2199 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5627 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 425:
#line 2205 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5642 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 426:
#line 2214 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5653 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 427:
#line 2220 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5668 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 428:
#line 2229 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5679 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 429:
#line 2235 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 5696 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 430:
#line 2246 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
	}
#line 5704 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 431:
#line 2248 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
		ast_stack.pop_back();
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[-7]), (yylsp[0]));
		ast_stack.pop_back();
	}
#line 5715 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 432:
#line 2254 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_CASE, (yyvsp[-1].ast));
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[-4].al));
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[-1]), (yylsp[-1]));
	}
#line 5727 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 433:
#line 2260 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = nullptr;
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[-7]), (yylsp[0]));
		case_type_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5738 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 434:
#line 2268 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = false;
	}
#line 5746 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 435:
#line 2271 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = (yyvsp[0].al);
	}
#line 5754 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 436:
#line 2274 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.boolean) = true;
	}
#line 5762 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 437:
#line 2279 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0].boolean)) (*(yyvsp[-1].al))["\\parallel_case"] = AstNode::mkconst_int(1, false);
		(yyval.al) = (yyvsp[-1].al);
	}
#line 5771 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 438:
#line 2285 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.push_back(0);
	}
#line 5779 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 439:
#line 2288 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.push_back('x');
	}
#line 5787 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 440:
#line 2291 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.push_back('z');
	}
#line 5795 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 441:
#line 2296 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (ast_stack.back()->attributes.count("\\full_case") == 0)
			ast_stack.back()->attributes["\\full_case"] = AstNode::mkconst_int(1, false);
	}
#line 5804 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 442:
#line 2300 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if (ast_stack.back()->attributes.count("\\parallel_case") == 0)
			ast_stack.back()->attributes["\\parallel_case"] = AstNode::mkconst_int(1, false);
	}
#line 5813 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 446:
#line 2311 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *block = new AstNode(AST_BLOCK);
		AstNode *cond = new AstNode(AST_COND, new AstNode(AST_DEFAULT), block);
		SET_AST_NODE_LOC(cond, (yylsp[0]), (yylsp[0]));

		ast_stack.pop_back();
		ast_stack.back()->children.push_back(cond);
		ast_stack.push_back(block);
	}
#line 5827 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 447:
#line 2319 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
	}
#line 5835 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 451:
#line 2329 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(
				case_type_stack.size() && case_type_stack.back() == 'x' ? AST_CONDX :
				case_type_stack.size() && case_type_stack.back() == 'z' ? AST_CONDZ : AST_COND);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 5847 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 452:
#line 2335 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *block = new AstNode(AST_BLOCK);
		ast_stack.back()->children.push_back(block);
		ast_stack.push_back(block);
		case_type_stack.push_back(0);
	}
#line 5858 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 453:
#line 2340 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.pop_back();
		SET_AST_NODE_LOC(ast_stack.back(), (yylsp[0]), (yylsp[0]));
		ast_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5869 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 456:
#line 2352 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(
				case_type_stack.size() && case_type_stack.back() == 'x' ? AST_CONDX :
				case_type_stack.size() && case_type_stack.back() == 'z' ? AST_CONDZ : AST_COND);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 5881 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 457:
#line 2358 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.push_back(0);
	}
#line 5889 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 458:
#line 2360 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.pop_back();
		ast_stack.pop_back();
	}
#line 5898 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 461:
#line 2370 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_DEFAULT));
	}
#line 5906 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 462:
#line 2373 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back(new AstNode(AST_IDENTIFIER));
		ast_stack.back()->children.back()->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
	}
#line 5916 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 463:
#line 2378 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back((yyvsp[0].ast));
	}
#line 5924 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 464:
#line 2381 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back((yyvsp[0].ast));
	}
#line 5932 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 465:
#line 2386 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_PREFIX, (yyvsp[-3].ast), (yyvsp[0].ast));
		(yyval.ast)->str = *(yyvsp[-5].string);
		delete (yyvsp[-5].string);
	}
#line 5942 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 466:
#line 2391 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_IDENTIFIER, (yyvsp[0].ast));
		(yyval.ast)->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		if ((yyvsp[0].ast) == nullptr && ((yyval.ast)->str == "\\$initstate" ||
				(yyval.ast)->str == "\\$anyconst" || (yyval.ast)->str == "\\$anyseq" ||
				(yyval.ast)->str == "\\$allconst" || (yyval.ast)->str == "\\$allseq"))
			(yyval.ast)->type = AST_FCALL;
	}
#line 5956 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 467:
#line 2400 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_IDENTIFIER, (yyvsp[0].ast));
		(yyval.ast)->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
	}
#line 5966 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 468:
#line 2407 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 5974 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 469:
#line 2410 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 5982 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 470:
#line 2415 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_CONCAT);
		(yyval.ast)->children.push_back((yyvsp[0].ast));
	}
#line 5991 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 471:
#line 2419 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
		(yyval.ast)->children.push_back((yyvsp[-2].ast));
	}
#line 6000 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 478:
#line 2437 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back((yyvsp[0].ast));
	}
#line 6008 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 483:
#line 2450 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENFOR);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 6018 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 484:
#line 2454 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.back()->children.push_back((yyvsp[0].ast));
	}
#line 6026 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 485:
#line 2456 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
	}
#line 6034 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 486:
#line 2459 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENIF);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
		ast_stack.back()->children.push_back((yyvsp[-1].ast));
	}
#line 6045 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 487:
#line 2464 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
	}
#line 6053 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 488:
#line 2467 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENCASE, (yyvsp[-1].ast));
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 6063 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 489:
#line 2471 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		case_type_stack.pop_back();
		ast_stack.pop_back();
	}
#line 6072 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 490:
#line 2475 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENBLOCK);
		node->str = (yyvsp[0].string) ? *(yyvsp[0].string) : std::string();
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 6083 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 491:
#line 2480 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-4].string) != NULL)
			delete (yyvsp[-4].string);
		if ((yyvsp[0].string) != NULL)
			delete (yyvsp[0].string);
		ast_stack.pop_back();
	}
#line 6095 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 492:
#line 2487 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_TECALL);
		node->str = *(yyvsp[0].string);
		delete (yyvsp[0].string);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 6107 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 493:
#line 2493 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
	}
#line 6115 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 494:
#line 2498 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_GENBLOCK);
		ast_stack.back()->children.push_back(node);
		ast_stack.push_back(node);
	}
#line 6125 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 495:
#line 2502 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		ast_stack.pop_back();
	}
#line 6133 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 500:
#line 2513 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 6141 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 501:
#line 2516 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_TERNARY);
		(yyval.ast)->children.push_back((yyvsp[-5].ast));
		(yyval.ast)->children.push_back((yyvsp[-2].ast));
		(yyval.ast)->children.push_back((yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-3].al));
	}
#line 6153 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 502:
#line 2525 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 6161 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 503:
#line 2528 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 6176 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 504:
#line 2538 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 6193 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 505:
#line 2550 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = const2ast(*(yyvsp[-1].string) + *(yyvsp[0].string), case_type_stack.size() == 0 ? 0 : case_type_stack.back(), !lib_mode);
		if ((yyval.ast) == NULL || (*(yyvsp[0].string))[0] != '\'')
			log_error("Value conversion failed: `%s%s'\n", (yyvsp[-1].string)->c_str(), (yyvsp[0].string)->c_str());
		delete (yyvsp[-1].string);
		delete (yyvsp[0].string);
	}
#line 6205 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 506:
#line 2557 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = const2ast(*(yyvsp[0].string), case_type_stack.size() == 0 ? 0 : case_type_stack.back(), !lib_mode);
		if ((yyval.ast) == NULL)
			log_error("Value conversion failed: `%s'\n", (yyvsp[0].string)->c_str());
		delete (yyvsp[0].string);
	}
#line 6216 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 507:
#line 2563 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
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
#line 6232 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 508:
#line 2574 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = AstNode::mkconst_str(*(yyvsp[0].string));
		delete (yyvsp[0].string);
	}
#line 6241 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 509:
#line 2578 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		AstNode *node = new AstNode(AST_FCALL);
		node->str = *(yyvsp[-1].string);
		delete (yyvsp[-1].string);
		ast_stack.push_back(node);
		append_attr(node, (yyvsp[0].al));
	}
#line 6253 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 510:
#line 2584 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = ast_stack.back();
		ast_stack.pop_back();
	}
#line 6262 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 511:
#line 2588 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_TO_SIGNED, (yyvsp[-1].ast));
		append_attr((yyval.ast), (yyvsp[-3].al));
	}
#line 6271 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 512:
#line 2592 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_TO_UNSIGNED, (yyvsp[-1].ast));
		append_attr((yyval.ast), (yyvsp[-3].al));
	}
#line 6280 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 513:
#line 2596 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 6288 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 514:
#line 2599 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		delete (yyvsp[-5].ast);
		(yyval.ast) = (yyvsp[-3].ast);
		delete (yyvsp[-1].ast);
	}
#line 6298 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 515:
#line 2604 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
	}
#line 6306 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 516:
#line 2607 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REPLICATE, (yyvsp[-4].ast), (yyvsp[-2].ast));
	}
#line 6314 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 517:
#line 2610 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_NOT, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6323 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 518:
#line 2614 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_AND, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6332 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 519:
#line 2618 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_NOT, new AstNode(AST_BIT_AND, (yyvsp[-3].ast), (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6341 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 520:
#line 2622 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_OR, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6350 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 521:
#line 2626 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_NOT, new AstNode(AST_BIT_OR, (yyvsp[-3].ast), (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6359 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 522:
#line 2630 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_XOR, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6368 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 523:
#line 2634 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_BIT_XNOR, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6377 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 524:
#line 2638 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_AND, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6386 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 525:
#line 2642 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_AND, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
		(yyval.ast) = new AstNode(AST_LOGIC_NOT, (yyval.ast));
	}
#line 6396 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 526:
#line 2647 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_OR, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6405 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 527:
#line 2651 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_OR, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
		(yyval.ast) = new AstNode(AST_LOGIC_NOT, (yyval.ast));
	}
#line 6415 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 528:
#line 2656 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_XOR, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6424 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 529:
#line 2660 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_REDUCE_XNOR, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6433 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 530:
#line 2664 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_SHIFT_LEFT, (yyvsp[-3].ast), new AstNode(AST_TO_UNSIGNED, (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6442 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 531:
#line 2668 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_SHIFT_RIGHT, (yyvsp[-3].ast), new AstNode(AST_TO_UNSIGNED, (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6451 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 532:
#line 2672 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_SHIFT_SLEFT, (yyvsp[-3].ast), new AstNode(AST_TO_UNSIGNED, (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6460 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 533:
#line 2676 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_SHIFT_SRIGHT, (yyvsp[-3].ast), new AstNode(AST_TO_UNSIGNED, (yyvsp[0].ast)));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6469 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 534:
#line 2680 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_LT, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6478 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 535:
#line 2684 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_LE, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6487 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 536:
#line 2688 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_EQ, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6496 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 537:
#line 2692 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_NE, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6505 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 538:
#line 2696 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_EQX, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6514 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 539:
#line 2700 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_NEX, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6523 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 540:
#line 2704 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_GE, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6532 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 541:
#line 2708 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_GT, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6541 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 542:
#line 2712 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_ADD, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6550 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 543:
#line 2716 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_SUB, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6559 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 544:
#line 2720 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_MUL, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6568 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 545:
#line 2724 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_DIV, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6577 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 546:
#line 2728 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_MOD, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6586 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 547:
#line 2732 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_POW, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6595 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 548:
#line 2736 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_POS, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6604 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 549:
#line 2740 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_NEG, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6613 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 550:
#line 2744 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_LOGIC_AND, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6622 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 551:
#line 2748 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_LOGIC_OR, (yyvsp[-3].ast), (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6631 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 552:
#line 2752 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_LOGIC_NOT, (yyvsp[0].ast));
		append_attr((yyval.ast), (yyvsp[-1].al));
	}
#line 6640 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 553:
#line 2758 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = new AstNode(AST_CONCAT, (yyvsp[0].ast));
	}
#line 6648 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;

  case 554:
#line 2761 "frontends/verilog/verilog_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);
		(yyval.ast)->children.push_back((yyvsp[-2].ast));
	}
#line 6657 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
    break;


#line 6661 "frontends/verilog/verilog_parser.tab.cc" /* yacc.c:1646  */
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
