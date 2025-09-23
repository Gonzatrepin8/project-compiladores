/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "parser.tab.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "ast.h"
#include "symbol_table/symtab.h"
#include "symbol_table/build_symtab.h"

extern int debug_mode;
int yylex(void);
void yyerror(const char *s);

AST *root = NULL;

#line 91 "src/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_EXTERN = 4,                     /* EXTERN  */
  YYSYMBOL_BOOL_TYPE = 5,                  /* BOOL_TYPE  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_THEN = 7,                       /* THEN  */
  YYSYMBOL_FALSE = 8,                      /* FALSE  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_INTEGER_TYPE = 10,              /* INTEGER_TYPE  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_TRUE = 12,                      /* TRUE  */
  YYSYMBOL_VOID = 13,                      /* VOID  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_EQ = 15,                        /* EQ  */
  YYSYMBOL_AND = 16,                       /* AND  */
  YYSYMBOL_OR = 17,                        /* OR  */
  YYSYMBOL_INT_LIT = 18,                   /* INT_LIT  */
  YYSYMBOL_BOOL_LIT = 19,                  /* BOOL_LIT  */
  YYSYMBOL_ID = 20,                        /* ID  */
  YYSYMBOL_21_ = 21,                       /* '<'  */
  YYSYMBOL_22_ = 22,                       /* '>'  */
  YYSYMBOL_23_ = 23,                       /* '+'  */
  YYSYMBOL_24_ = 24,                       /* '-'  */
  YYSYMBOL_25_ = 25,                       /* '*'  */
  YYSYMBOL_26_ = 26,                       /* '/'  */
  YYSYMBOL_27_ = 27,                       /* '%'  */
  YYSYMBOL_28_ = 28,                       /* '!'  */
  YYSYMBOL_UMINUS = 29,                    /* UMINUS  */
  YYSYMBOL_30_ = 30,                       /* '{'  */
  YYSYMBOL_31_ = 31,                       /* '}'  */
  YYSYMBOL_32_ = 32,                       /* '='  */
  YYSYMBOL_33_ = 33,                       /* ';'  */
  YYSYMBOL_34_ = 34,                       /* '('  */
  YYSYMBOL_35_ = 35,                       /* ')'  */
  YYSYMBOL_36_ = 36,                       /* ','  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_program = 38,                   /* program  */
  YYSYMBOL_var_decls = 39,                 /* var_decls  */
  YYSYMBOL_var_decl = 40,                  /* var_decl  */
  YYSYMBOL_method_decls = 41,              /* method_decls  */
  YYSYMBOL_method_decl = 42,               /* method_decl  */
  YYSYMBOL_method_body = 43,               /* method_body  */
  YYSYMBOL_param_list_opt = 44,            /* param_list_opt  */
  YYSYMBOL_param_list = 45,                /* param_list  */
  YYSYMBOL_block = 46,                     /* block  */
  YYSYMBOL_stmt_list = 47,                 /* stmt_list  */
  YYSYMBOL_stmt = 48,                      /* stmt  */
  YYSYMBOL_op_else = 49,                   /* op_else  */
  YYSYMBOL_method_call = 50,               /* method_call  */
  YYSYMBOL_arg_list_opt = 51,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 52,                  /* arg_list  */
  YYSYMBOL_return_body = 53,               /* return_body  */
  YYSYMBOL_type = 54,                      /* type  */
  YYSYMBOL_expr = 55,                      /* expr  */
  YYSYMBOL_literal = 56                    /* literal  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   229

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  116

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,     2,     2,     2,    27,     2,     2,
      34,    35,    25,    23,    36,    24,     2,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
      21,    32,    22,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,    31,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    54,    54,    58,    62,    66,    73,    76,    89,   103,
     106,   119,   128,   136,   139,   145,   148,   154,   163,   184,
     187,   193,   196,   211,   215,   218,   222,   225,   228,   231,
     237,   240,   246,   253,   256,   262,   265,   272,   275,   281,
     282,   286,   290,   293,   296,   299,   302,   305,   308,   311,
     314,   317,   320,   323,   326,   329,   332,   338,   341
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "EXTERN",
  "BOOL_TYPE", "ELSE", "THEN", "FALSE", "IF", "INTEGER_TYPE", "RETURN",
  "TRUE", "VOID", "WHILE", "EQ", "AND", "OR", "INT_LIT", "BOOL_LIT", "ID",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "UMINUS", "'{'",
  "'}'", "'='", "';'", "'('", "')'", "','", "$accept", "program",
  "var_decls", "var_decl", "method_decls", "method_decl", "method_body",
  "param_list_opt", "param_list", "block", "stmt_list", "stmt", "op_else",
  "method_call", "arg_list_opt", "arg_list", "return_body", "type", "expr",
  "literal", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-76)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,   -21,    47,     0,   -76,   -76,   -76,    -5,   -76,    29,
     -76,    30,   -76,     9,    14,   -76,   -76,    39,   -76,   -76,
      43,    -4,    40,   -76,    25,   139,    40,    31,    33,    45,
     -76,   -76,    46,   139,   139,   139,   -76,   116,   -76,    42,
       3,    40,   -76,   139,   -76,   -76,    86,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   -76,     3,    41,
      40,   -76,   -76,    59,    50,    57,   169,   -76,   202,   195,
     182,    65,    65,    79,    79,   -76,   -76,   -76,   -76,   -76,
      40,    53,    62,   -76,   -76,   139,    67,    60,   139,   139,
      21,   -76,   -76,   -76,   -76,    63,    82,   169,   -76,   139,
      66,   169,   153,   139,   -76,   101,   -76,   -76,   129,   108,
     -76,    89,   114,    89,   -76,   -76
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,    40,    39,     0,     5,     0,
       6,     0,     9,     0,     0,     3,     7,     0,     4,    10,
       0,     0,    15,     2,     0,     0,    15,     0,    16,     0,
      57,    58,    41,     0,     0,     0,    42,     0,    43,     0,
       0,     0,    17,    33,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     0,
      21,    12,    13,     0,     0,    34,    35,    56,    51,    52,
      53,    49,    50,    44,    45,    46,    47,    48,    11,    14,
      21,     0,     0,    18,    32,     0,     0,     0,    37,     0,
       0,    20,    28,    29,    22,     0,     0,    36,    19,     0,
       0,    38,     0,     0,    24,     0,    27,    26,     0,     0,
      23,     0,    30,     0,    25,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -76,   -76,    69,    -9,   121,    -3,    76,   109,   -76,   -75,
      68,   -76,   -76,   -35,   -76,   -76,   -76,    15,   -31,   -76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     9,    10,    11,    12,    61,    27,    28,    62,
      81,    94,   114,    36,    64,    65,   100,    13,    37,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      16,     1,    44,    45,    46,     5,    93,    59,    19,     3,
       6,    93,    66,     7,    19,    14,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    20,   107,    25,    21,
      26,     8,    20,    60,     5,     5,   112,    29,   115,     6,
       6,    29,     7,     7,     5,     5,    95,     4,    22,     6,
       6,    95,     7,   103,    97,    43,    63,   101,   102,    26,
      15,    18,    87,    24,    88,    42,    40,    89,   105,    41,
      23,    16,   108,    90,    79,    82,    87,    58,    88,    83,
      43,    89,    96,    60,    91,    84,    92,    90,    52,    53,
      54,    55,    56,    85,    99,    82,   104,    60,    98,   106,
      92,    47,    48,    49,    54,    55,    56,    50,    51,    52,
      53,    54,    55,    56,    25,   111,    47,    48,    49,    60,
     113,    67,    50,    51,    52,    53,    54,    55,    56,    80,
      17,    47,    48,    49,    78,    39,   109,    50,    51,    52,
      53,    54,    55,    56,    47,    48,    49,     0,    86,    57,
      50,    51,    52,    53,    54,    55,    56,    30,    31,    32,
       0,     0,   110,    33,     0,     0,     0,    34,    47,    48,
      49,     0,     0,    35,    50,    51,    52,    53,    54,    55,
      56,     0,     0,    60,    47,    48,    49,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    47,    48,     0,
       0,     0,     0,    50,    51,    52,    53,    54,    55,    56,
      47,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    56,    50,    51,    52,    53,    54,    55,    56
};

static const yytype_int8 yycheck[] =
{
       9,     3,    33,    34,    35,     5,    81,     4,    11,    30,
      10,    86,    43,    13,    17,    20,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    11,   102,    32,    20,
      34,    31,    17,    30,     5,     5,   111,    22,   113,    10,
      10,    26,    13,    13,     5,     5,    81,     0,    34,    10,
      10,    86,    13,    32,    85,    34,    41,    88,    89,    34,
      31,    31,     9,    20,    11,    20,    35,    14,    99,    36,
      31,    80,   103,    20,    33,    60,     9,    35,    11,    20,
      34,    14,    20,    30,    31,    35,    33,    20,    23,    24,
      25,    26,    27,    36,    34,    80,    33,    30,    31,    33,
      33,    15,    16,    17,    25,    26,    27,    21,    22,    23,
      24,    25,    26,    27,    32,     7,    15,    16,    17,    30,
       6,    35,    21,    22,    23,    24,    25,    26,    27,    60,
       9,    15,    16,    17,    58,    26,    35,    21,    22,    23,
      24,    25,    26,    27,    15,    16,    17,    -1,    80,    33,
      21,    22,    23,    24,    25,    26,    27,    18,    19,    20,
      -1,    -1,    33,    24,    -1,    -1,    -1,    28,    15,    16,
      17,    -1,    -1,    34,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    15,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    26,    27,    15,    16,    -1,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    26,    27,
      15,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    26,    27,    21,    22,    23,    24,    25,    26,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    38,    30,     0,     5,    10,    13,    31,    39,
      40,    41,    42,    54,    20,    31,    40,    41,    31,    42,
      54,    20,    34,    31,    20,    32,    34,    44,    45,    54,
      18,    19,    20,    24,    28,    34,    50,    55,    56,    44,
      35,    36,    20,    34,    55,    55,    55,    15,    16,    17,
      21,    22,    23,    24,    25,    26,    27,    33,    35,     4,
      30,    43,    46,    54,    51,    52,    55,    35,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    43,    33,
      39,    47,    54,    20,    35,    36,    47,     9,    11,    14,
      20,    31,    33,    46,    48,    50,    20,    55,    31,    34,
      53,    55,    55,    32,    33,    55,    33,    46,    55,    35,
      33,     7,    46,     6,    49,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    38,    38,    39,    39,    40,    41,
      41,    42,    42,    43,    43,    44,    44,    45,    45,    46,
      46,    47,    47,    48,    48,    48,    48,    48,    48,    48,
      49,    49,    50,    51,    51,    52,    52,    53,    53,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    56,    56
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     4,     3,     1,     2,     5,     1,
       2,     6,     6,     1,     2,     0,     1,     2,     4,     4,
       3,     0,     2,     4,     2,     7,     3,     3,     1,     1,
       0,     2,     4,     0,     1,     1,     3,     0,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: PROGRAM '{' var_decls method_decls '}'  */
#line 54 "src/parser.y"
                                             {
        (yyval.ast) = make_node(NODE_PROG, NULL, 0, 0, NULL, (yyvsp[-2].ast), (yyvsp[-1].ast));
        root = (yyval.ast);
    }
#line 1226 "src/parser.tab.c"
    break;

  case 3: /* program: PROGRAM '{' var_decls '}'  */
#line 58 "src/parser.y"
                                {
        (yyval.ast) = make_node(NODE_PROG, NULL, 0, 0, NULL, (yyvsp[-1].ast), NULL);
        root = (yyval.ast);
    }
#line 1235 "src/parser.tab.c"
    break;

  case 4: /* program: PROGRAM '{' method_decls '}'  */
#line 62 "src/parser.y"
                                   {
        (yyval.ast) = make_node(NODE_PROG, NULL, 0, 0, NULL, NULL, (yyvsp[-1].ast));
        root = (yyval.ast);
    }
#line 1244 "src/parser.tab.c"
    break;

  case 5: /* program: PROGRAM '{' '}'  */
#line 66 "src/parser.y"
                      {
        (yyval.ast) = make_node(NODE_PROG, NULL, 0, 0, NULL, NULL, NULL);
        root = (yyval.ast);
    }
#line 1253 "src/parser.tab.c"
    break;

  case 6: /* var_decls: var_decl  */
#line 73 "src/parser.y"
               {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1261 "src/parser.tab.c"
    break;

  case 7: /* var_decls: var_decls var_decl  */
#line 76 "src/parser.y"
                         {
        AST *temp = (yyvsp[-1].ast);
        if(temp) {
            while(temp->next) temp = temp->next;
            temp->next = (yyvsp[0].ast);
            (yyval.ast) = (yyvsp[-1].ast);
        } else {
            (yyval.ast) = (yyvsp[0].ast);
        }
    }
#line 1276 "src/parser.tab.c"
    break;

  case 8: /* var_decl: type ID '=' expr ';'  */
#line 89 "src/parser.y"
                           {
        AST* id_node = make_node(NODE_ID, (yyvsp[-3].sval), 0, 0, NULL, NULL, NULL);
        AST* assign_node = make_node(NODE_ASSIGN, NULL, 0, 0, NULL, id_node, (yyvsp[-1].ast));
        (yyval.ast) = make_node(NODE_VAR_DECL, (yyvsp[-3].sval), 0, 0, NULL, NULL, assign_node);
        if (strcmp((char*)(yyvsp[-4].sval), "integer") == 0) {
            (yyval.ast)->info->eval_type = TYPE_INT;
        } else if (strcmp((char*)(yyvsp[-4].sval), "bool") == 0) {
            (yyval.ast)->info->eval_type = TYPE_BOOL;
        }
        free((yyvsp[-3].sval));
    }
#line 1292 "src/parser.tab.c"
    break;

  case 9: /* method_decls: method_decl  */
#line 103 "src/parser.y"
                  {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1300 "src/parser.tab.c"
    break;

  case 10: /* method_decls: method_decls method_decl  */
#line 106 "src/parser.y"
                               {
        AST *temp = (yyvsp[-1].ast);
        if (temp) {
            while(temp->next) temp = temp->next;
            temp->next = (yyvsp[0].ast);
            (yyval.ast) = (yyvsp[-1].ast);
        } else {
            (yyval.ast) = (yyvsp[0].ast);
        }
    }
#line 1315 "src/parser.tab.c"
    break;

  case 11: /* method_decl: type ID '(' param_list_opt ')' method_body  */
#line 119 "src/parser.y"
                                                 {
        (yyval.ast) = make_node(NODE_FUNCTION, (yyvsp[-4].sval), 0, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast));
        if (strcmp((char*)(yyvsp[-5].sval), "integer") == 0) {
            (yyval.ast)->info->eval_type = TYPE_INT;
        } else if (strcmp((char*)(yyvsp[-5].sval), "bool") == 0) {
            (yyval.ast)->info->eval_type = TYPE_BOOL;
        }
        free((yyvsp[-4].sval));
    }
#line 1329 "src/parser.tab.c"
    break;

  case 12: /* method_decl: VOID ID '(' param_list_opt ')' method_body  */
#line 128 "src/parser.y"
                                                 {
        (yyval.ast) = make_node(NODE_FUNCTION, (yyvsp[-4].sval), 0, 0, NULL, (yyvsp[-2].ast), (yyvsp[0].ast));
        (yyval.ast)->info->eval_type = TYPE_VOID;
        free((yyvsp[-4].sval));
    }
#line 1339 "src/parser.tab.c"
    break;

  case 13: /* method_body: block  */
#line 136 "src/parser.y"
            {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1347 "src/parser.tab.c"
    break;

  case 14: /* method_body: EXTERN ';'  */
#line 139 "src/parser.y"
                 {
        (yyval.ast) = make_node(NODE_ID, "EXTERN", 0, 0, NULL, NULL, NULL);
    }
#line 1355 "src/parser.tab.c"
    break;

  case 15: /* param_list_opt: %empty  */
#line 145 "src/parser.y"
                  {
        (yyval.ast) = NULL;
    }
#line 1363 "src/parser.tab.c"
    break;

  case 16: /* param_list_opt: param_list  */
#line 148 "src/parser.y"
                 {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1371 "src/parser.tab.c"
    break;

  case 17: /* param_list: type ID  */
#line 154 "src/parser.y"
              {
        (yyval.ast) = make_node(NODE_PARAM, (yyvsp[0].sval), 0, 0, NULL, NULL, NULL);
        if (strcmp((char*)(yyvsp[-1].sval), "integer") == 0) {
            (yyval.ast)->info->eval_type = TYPE_INT;
        } else if (strcmp((char*)(yyvsp[-1].sval), "bool") == 0) {
            (yyval.ast)->info->eval_type = TYPE_BOOL;
        }
        free((yyvsp[0].sval));
    }
#line 1385 "src/parser.tab.c"
    break;

  case 18: /* param_list: param_list ',' type ID  */
#line 163 "src/parser.y"
                             {
        AST* new_param = make_node(NODE_PARAM, (yyvsp[0].sval), 0, 0, NULL, NULL, NULL);
        if (strcmp((char*)(yyvsp[-1].sval), "integer") == 0) {
            new_param->info->eval_type = TYPE_INT;
        } else if (strcmp((char*)(yyvsp[-1].sval), "bool") == 0) {
            new_param->info->eval_type = TYPE_BOOL;
        }
        free((yyvsp[0].sval));

        AST* tail = (yyvsp[-3].ast);
        while (tail->next){
            tail = tail->next;
        }
        tail->next = new_param;

        (yyval.ast) = (yyvsp[-3].ast);
    }
#line 1407 "src/parser.tab.c"
    break;

  case 19: /* block: '{' var_decls stmt_list '}'  */
#line 184 "src/parser.y"
                                  {
        (yyval.ast) = make_node(NODE_BLOCK, NULL, 0, 0, NULL, (yyvsp[-2].ast), (yyvsp[-1].ast));
    }
#line 1415 "src/parser.tab.c"
    break;

  case 20: /* block: '{' stmt_list '}'  */
#line 187 "src/parser.y"
                        {
        (yyval.ast) = make_node(NODE_BLOCK, NULL, 0, 0, NULL, NULL, (yyvsp[-1].ast));
    }
#line 1423 "src/parser.tab.c"
    break;

  case 21: /* stmt_list: %empty  */
#line 193 "src/parser.y"
                  {
        (yyval.ast) = NULL;
    }
#line 1431 "src/parser.tab.c"
    break;

  case 22: /* stmt_list: stmt_list stmt  */
#line 196 "src/parser.y"
                     {
        if ((yyvsp[-1].ast) == NULL) {
            (yyval.ast) = (yyvsp[0].ast);
        } else if ((yyvsp[0].ast) != NULL) {
            AST *temp = (yyvsp[-1].ast);
            while(temp->next) temp = temp->next;
            temp->next = (yyvsp[0].ast);
            (yyval.ast) = (yyvsp[-1].ast);
        } else {
            (yyval.ast) = (yyvsp[-1].ast);
        }
    }
#line 1448 "src/parser.tab.c"
    break;

  case 23: /* stmt: ID '=' expr ';'  */
#line 211 "src/parser.y"
                      {
        (yyval.ast) = make_node(NODE_ASSIGN, NULL, 0, 0, NULL, make_node(NODE_ID, (yyvsp[-3].sval), 0, 0, NULL, NULL, NULL), (yyvsp[-1].ast));
        free((yyvsp[-3].sval));
    }
#line 1457 "src/parser.tab.c"
    break;

  case 24: /* stmt: method_call ';'  */
#line 215 "src/parser.y"
                      {
        (yyval.ast) = (yyvsp[-1].ast);
    }
#line 1465 "src/parser.tab.c"
    break;

  case 25: /* stmt: IF '(' expr ')' THEN block op_else  */
#line 218 "src/parser.y"
                                         {
        (yyval.ast) = make_node(NODE_IF, NULL, 0, 0, NULL, (yyvsp[-4].ast), (yyvsp[-1].ast));
        if ((yyvsp[-1].ast)) (yyvsp[-1].ast)->next = (yyvsp[0].ast);
    }
#line 1474 "src/parser.tab.c"
    break;

  case 26: /* stmt: WHILE expr block  */
#line 222 "src/parser.y"
                       {
        (yyval.ast) = make_node(NODE_WHILE, NULL, 0, 0, NULL, (yyvsp[-1].ast), (yyvsp[0].ast));
    }
#line 1482 "src/parser.tab.c"
    break;

  case 27: /* stmt: RETURN return_body ';'  */
#line 225 "src/parser.y"
                             {
        (yyval.ast) = make_node(NODE_RETURN, NULL, 0, 0, NULL, (yyvsp[-1].ast), NULL);
    }
#line 1490 "src/parser.tab.c"
    break;

  case 28: /* stmt: ';'  */
#line 228 "src/parser.y"
          {
        (yyval.ast) = NULL;
    }
#line 1498 "src/parser.tab.c"
    break;

  case 29: /* stmt: block  */
#line 231 "src/parser.y"
            {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1506 "src/parser.tab.c"
    break;

  case 30: /* op_else: %empty  */
#line 237 "src/parser.y"
                  {
        (yyval.ast) = NULL;
    }
#line 1514 "src/parser.tab.c"
    break;

  case 31: /* op_else: ELSE block  */
#line 240 "src/parser.y"
                 {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1522 "src/parser.tab.c"
    break;

  case 32: /* method_call: ID '(' arg_list_opt ')'  */
#line 246 "src/parser.y"
                              {
        (yyval.ast) = make_node(NODE_CALL, (yyvsp[-3].sval), 0, 0, NULL, (yyvsp[-1].ast), NULL);
        free((yyvsp[-3].sval));
    }
#line 1531 "src/parser.tab.c"
    break;

  case 33: /* arg_list_opt: %empty  */
#line 253 "src/parser.y"
                  {
        (yyval.ast) = NULL;
    }
#line 1539 "src/parser.tab.c"
    break;

  case 34: /* arg_list_opt: arg_list  */
#line 256 "src/parser.y"
               {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1547 "src/parser.tab.c"
    break;

  case 35: /* arg_list: expr  */
#line 262 "src/parser.y"
           {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1555 "src/parser.tab.c"
    break;

  case 36: /* arg_list: arg_list ',' expr  */
#line 265 "src/parser.y"
                        {
        (yyvsp[-2].ast)->next = (yyvsp[0].ast);
        (yyval.ast) = (yyvsp[-2].ast);
    }
#line 1564 "src/parser.tab.c"
    break;

  case 37: /* return_body: %empty  */
#line 272 "src/parser.y"
                  {
        (yyval.ast) = NULL;
    }
#line 1572 "src/parser.tab.c"
    break;

  case 38: /* return_body: expr  */
#line 275 "src/parser.y"
           {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1580 "src/parser.tab.c"
    break;

  case 39: /* type: INTEGER_TYPE  */
#line 281 "src/parser.y"
                   { (yyval.sval) = strdup("integer"); }
#line 1586 "src/parser.tab.c"
    break;

  case 40: /* type: BOOL_TYPE  */
#line 282 "src/parser.y"
                   { (yyval.sval) = strdup("bool"); }
#line 1592 "src/parser.tab.c"
    break;

  case 41: /* expr: ID  */
#line 286 "src/parser.y"
         {
        (yyval.ast) = make_node(NODE_ID, (yyvsp[0].sval), 0, 0, NULL, NULL, NULL);
        free((yyvsp[0].sval));
    }
#line 1601 "src/parser.tab.c"
    break;

  case 42: /* expr: method_call  */
#line 290 "src/parser.y"
                  {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1609 "src/parser.tab.c"
    break;

  case 43: /* expr: literal  */
#line 293 "src/parser.y"
              {
        (yyval.ast) = (yyvsp[0].ast);
    }
#line 1617 "src/parser.tab.c"
    break;

  case 44: /* expr: expr '+' expr  */
#line 296 "src/parser.y"
                    {
        (yyval.ast) = make_node(NODE_BINOP, NULL, 0, 0, "+", (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1625 "src/parser.tab.c"
    break;

  case 45: /* expr: expr '-' expr  */
#line 299 "src/parser.y"
                    {
        (yyval.ast) = make_node(NODE_BINOP, NULL, 0, 0, "-", (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1633 "src/parser.tab.c"
    break;

  case 46: /* expr: expr '*' expr  */
#line 302 "src/parser.y"
                    {
        (yyval.ast) = make_node(NODE_BINOP, NULL, 0, 0, "*", (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1641 "src/parser.tab.c"
    break;

  case 47: /* expr: expr '/' expr  */
#line 305 "src/parser.y"
                    {
        (yyval.ast) = make_node(NODE_BINOP, NULL, 0, 0, "/", (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1649 "src/parser.tab.c"
    break;

  case 48: /* expr: expr '%' expr  */
#line 308 "src/parser.y"
                    {
        (yyval.ast) = make_node(NODE_BINOP, NULL, 0, 0, "%", (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1657 "src/parser.tab.c"
    break;

  case 49: /* expr: expr '<' expr  */
#line 311 "src/parser.y"
                    {
        (yyval.ast) = make_node(NODE_BINOP, NULL, 0, 0, "<", (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1665 "src/parser.tab.c"
    break;

  case 50: /* expr: expr '>' expr  */
#line 314 "src/parser.y"
                    {
        (yyval.ast) = make_node(NODE_BINOP, NULL, 0, 0, ">", (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1673 "src/parser.tab.c"
    break;

  case 51: /* expr: expr EQ expr  */
#line 317 "src/parser.y"
                   {
        (yyval.ast) = make_node(NODE_BINOP, NULL, 0, 0, "==", (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1681 "src/parser.tab.c"
    break;

  case 52: /* expr: expr AND expr  */
#line 320 "src/parser.y"
                    {
        (yyval.ast) = make_node(NODE_BINOP, NULL, 0, 0, "&&", (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1689 "src/parser.tab.c"
    break;

  case 53: /* expr: expr OR expr  */
#line 323 "src/parser.y"
                   {
        (yyval.ast) = make_node(NODE_BINOP, NULL, 0, 0, "||", (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 1697 "src/parser.tab.c"
    break;

  case 54: /* expr: '-' expr  */
#line 326 "src/parser.y"
                            {
        (yyval.ast) = make_node(NODE_UNOP, NULL, 0, 0, "-", (yyvsp[0].ast), NULL);
    }
#line 1705 "src/parser.tab.c"
    break;

  case 55: /* expr: '!' expr  */
#line 329 "src/parser.y"
               {
        (yyval.ast) = make_node(NODE_UNOP, NULL, 0, 0, "!", (yyvsp[0].ast), NULL);
    }
#line 1713 "src/parser.tab.c"
    break;

  case 56: /* expr: '(' expr ')'  */
#line 332 "src/parser.y"
                   {
        (yyval.ast) = (yyvsp[-1].ast);
    }
#line 1721 "src/parser.tab.c"
    break;

  case 57: /* literal: INT_LIT  */
#line 338 "src/parser.y"
              {
        (yyval.ast) = make_node(NODE_INT, NULL, (yyvsp[0].ival), 0, NULL, NULL, NULL);
    }
#line 1729 "src/parser.tab.c"
    break;

  case 58: /* literal: BOOL_LIT  */
#line 341 "src/parser.y"
               {
        (yyval.ast) = make_node(NODE_BOOL, NULL, 0, (yyvsp[0].bval), NULL, NULL, NULL);
    }
#line 1737 "src/parser.tab.c"
    break;


#line 1741 "src/parser.tab.c"

      default: break;
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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 345 "src/parser.y"


extern FILE *yyin;
extern FILE *lexout;
FILE *semout;
FILE *sintout;
FILE *symout;
char lex_filename[256];
char sint_filename[256];
char sent_filename[256];
char sym_filename[256];

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-debug] <sourcefile>\n", argv[0]);
        return 1;
    }

    int argi = 1;
    if (strcmp(argv[1], "-debug") == 0) {
        debug_mode = 1;
        argi++;
    }

    if (argi >= argc) {
        fprintf(stderr, "No input file given.\n");
        return 1;
    }

    yyin = fopen(argv[argi], "r");
    if (!yyin) {
        perror("fopen");
        return 1;
    }

    const char *inputfile = argv[argi];

    struct stat st = {0};
    if (stat("output", &st) == -1) {
        if (mkdir("output", 0700) != 0) {
            perror("mkdir");
            return 1;
        }
    }

    char base[256];
    strncpy(base, basename((char *)inputfile), sizeof(base) - 1);
    base[sizeof(base) - 1] = '\0';

    char *dot = strrchr(base, '.');
    if (dot) *dot = '\0';

    snprintf(lex_filename, sizeof(lex_filename), "output/%s.lex", base);
    snprintf(sint_filename, sizeof(sint_filename), "output/%s.sint", base);
    snprintf(sent_filename, sizeof(sent_filename), "output/%s.sem", base);
    snprintf(sym_filename, sizeof(sym_filename), "output/%s.sym", base);

    lexout = fopen(lex_filename, "w");
    sintout = fopen(sint_filename, "w");
    semout = fopen(sent_filename, "w");
    symout = fopen(sym_filename, "w");

    if (!lexout || !sintout || !semout || !symout) {
        perror("fopen");
        return 1;
    }

    int result = yyparse();

    if (result == 0) {
        fprintf(sintout, "Parser: SUCCESS\n");
        if (root) {
            print_ast(root, 0, 1);
            SymTab *global = symtab_new();
            build_symtab(root, global, symout);
            symtab_print(global, symout);
        }
    } else {
        fprintf(sintout, "Parser: FAILED\n");
    }

    fclose(yyin);
    fclose(lexout);
    fclose(sintout);
    fclose(semout);
    fclose(symout);

    if (debug_mode) {
        FILE *f = fopen(lex_filename, "r");
        if (f) {
            printf("---- Lexer Output (%s) ----\n", lex_filename);
            char c;
            while ((c = fgetc(f)) != EOF) putchar(c);
            fclose(f);
        }

        f = fopen(sint_filename, "r");
        if (f) {
            printf("---- Parser Output (%s) ----\n", sint_filename);
            char c;
            while ((c = fgetc(f)) != EOF) putchar(c);
            fclose(f);
        }

        f = fopen(sent_filename, "r");
        if(f) {
            printf("---- AST (%s) ----\n", sent_filename);
            char c;
            while((c = fgetc(f)) != EOF) putchar(c);
            fclose(f);
        }

        f = fopen(sym_filename, "r");
        if (f) {
            printf("---- Symbol Table (%s) ----\n", sym_filename);
            char c;
            while((c = fgetc(f)) != EOF) putchar(c);
            fclose(f);
        }
        
        if (result == 0) {
            printf("Create symbol table success.\n");
        } else {
            printf("Failed to create symbol table due to parsing errors.\n");
        }
        
    }

    return result;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
