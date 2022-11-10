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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parse.y" /* yacc.c:339  */
     /* pars1.y    Pascal Parser      Gordon S. Novak Jr.  ; 08 Jul 22   */

/* Copyright (c) 2022 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/* 14 Feb 01; 01 Oct 04; 02 Mar 07; 27 Feb 08; 24 Jul 09; 02 Aug 12;
   30 Jul 13; 25 Jul 19 ; 28 Feb 22 */

/*
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.

; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.

; You should have received a copy of the GNU General Public License
; along with this program; if not, see <http://www.gnu.org/licenses/>.
  */


/* NOTE:   Copy your lexan.l lexical analyzer to this directory.      */

       /* To use:
                     make pars1y              has 1 shift/reduce conflict
                     pars1y                   execute the parser
                     i:=j .
                     ^D                       control-D to end input

                     pars1y                   execute the parser
                     begin i:=j; if i+j then x:=a+b*c else x:=a*b+c; k:=i end.
                     ^D

                     pars1y                   execute the parser
                     if x+y then if y+z then i:=j else k:=2.
                     ^D

           You may copy pars1.y to be parse.y and extend it for your
           assignment.  Then use   make parser   as above.
        */

        /* Yacc reports 1 shift/reduce conflict, due to the ELSE part of
           the IF statement, but Yacc's default resolves it in the right way.*/

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "token.h"
#include "lexan.h"
#include "symtab.h"
#include "parse.h"
#include "pprint.h"
#include <string.h>

        /* define the type of the Yacc stack element to be TOKEN */

#define YYSTYPE TOKEN

TOKEN parseresult;


#line 131 "y.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    STRING = 259,
    NUMBER = 260,
    PLUS = 261,
    MINUS = 262,
    TIMES = 263,
    DIVIDE = 264,
    ASSIGN = 265,
    EQ = 266,
    NE = 267,
    LT = 268,
    LE = 269,
    GE = 270,
    GT = 271,
    POINT = 272,
    DOT = 273,
    AND = 274,
    OR = 275,
    NOT = 276,
    DIV = 277,
    MOD = 278,
    IN = 279,
    COMMA = 280,
    SEMICOLON = 281,
    COLON = 282,
    LPAREN = 283,
    RPAREN = 284,
    LBRACKET = 285,
    RBRACKET = 286,
    DOTDOT = 287,
    ARRAY = 288,
    BEGINBEGIN = 289,
    CASE = 290,
    CONST = 291,
    DO = 292,
    DOWNTO = 293,
    ELSE = 294,
    END = 295,
    FILEFILE = 296,
    FOR = 297,
    FUNCTION = 298,
    GOTO = 299,
    IF = 300,
    LABEL = 301,
    NIL = 302,
    OF = 303,
    PACKED = 304,
    PROCEDURE = 305,
    PROGRAM = 306,
    RECORD = 307,
    REPEAT = 308,
    SET = 309,
    THEN = 310,
    TO = 311,
    TYPE = 312,
    UNTIL = 313,
    VAR = 314,
    WHILE = 315,
    WITH = 316,
    thenthen = 317
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define STRING 259
#define NUMBER 260
#define PLUS 261
#define MINUS 262
#define TIMES 263
#define DIVIDE 264
#define ASSIGN 265
#define EQ 266
#define NE 267
#define LT 268
#define LE 269
#define GE 270
#define GT 271
#define POINT 272
#define DOT 273
#define AND 274
#define OR 275
#define NOT 276
#define DIV 277
#define MOD 278
#define IN 279
#define COMMA 280
#define SEMICOLON 281
#define COLON 282
#define LPAREN 283
#define RPAREN 284
#define LBRACKET 285
#define RBRACKET 286
#define DOTDOT 287
#define ARRAY 288
#define BEGINBEGIN 289
#define CASE 290
#define CONST 291
#define DO 292
#define DOWNTO 293
#define ELSE 294
#define END 295
#define FILEFILE 296
#define FOR 297
#define FUNCTION 298
#define GOTO 299
#define IF 300
#define LABEL 301
#define NIL 302
#define OF 303
#define PACKED 304
#define PROCEDURE 305
#define PROGRAM 306
#define RECORD 307
#define REPEAT 308
#define SET 309
#define THEN 310
#define TO 311
#define TYPE 312
#define UNTIL 313
#define VAR 314
#define WHILE 315
#define WITH 316
#define thenthen 317

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 303 "y.tab.c" /* yacc.c:358  */

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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   241

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  184

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   317

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    85,    85,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    97,    98,   100,   101,   103,   104,   106,   108,
     109,   111,   112,   114,   115,   116,   117,   118,   120,   121,
     122,   123,   126,   127,   129,   130,   132,   133,   135,   137,
     138,   139,   140,   142,   144,   145,   146,   147,   149,   151,
     152,   154,   155,   157,   158,   159,   161,   162,   164,   165,
     166,   167,   169,   171,   172,   174,   176,   178,   179,   181,
     181,   181,   181,   181,   181,   181,   183,   184,   185,   187,
     187,   189,   189,   189,   191,   191,   191,   191,   191,   193,
     195,   196,   197,   199,   200,   201,   202,   203
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "NUMBER", "PLUS",
  "MINUS", "TIMES", "DIVIDE", "ASSIGN", "EQ", "NE", "LT", "LE", "GE", "GT",
  "POINT", "DOT", "AND", "OR", "NOT", "DIV", "MOD", "IN", "COMMA",
  "SEMICOLON", "COLON", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "DOTDOT", "ARRAY", "BEGINBEGIN", "CASE", "CONST", "DO", "DOWNTO", "ELSE",
  "END", "FILEFILE", "FOR", "FUNCTION", "GOTO", "IF", "LABEL", "NIL", "OF",
  "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET", "THEN",
  "TO", "TYPE", "UNTIL", "VAR", "WHILE", "WITH", "thenthen", "$accept",
  "program", "statement", "statement_list", "endpart", "endif",
  "assignment", "expr", "term", "factor", "variable", "idlist", "numlist",
  "lblock", "cdef", "cdef_list", "cblock", "tdef", "tdef_list", "tblock",
  "vdef", "vdef_list", "vblock", "simple_type", "simple_type_list", "type",
  "fields", "field_list", "block", "funcall", "expr_list", "compare_op",
  "simple_expression", "sign", "plus_op", "times_op", "label",
  "unsigned_constant", "constant", YY_NULLPTR
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
     315,   316,   317
};
# endif

#define YYPACT_NINF -124

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-124)))

#define YYTABLE_NINF -95

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -32,    25,    43,    33,  -124,    47,    58,    39,    47,    46,
    -124,   137,    22,    86,    96,    88,    47,    97,  -124,  -124,
    -124,  -124,    76,    89,    22,   115,   116,   128,    22,   128,
      73,  -124,     5,  -124,  -124,   118,   100,    60,   102,   122,
     141,   125,   -10,   142,   127,   134,  -124,   128,    22,    73,
    -124,   114,  -124,  -124,  -124,  -124,  -124,    75,   128,  -124,
     126,    62,  -124,   106,  -124,    32,    75,  -124,   146,   119,
     150,    22,  -124,  -124,   128,  -124,   173,   128,   140,    86,
    -124,    96,    52,    41,    88,  -124,    41,    47,  -124,   197,
     149,  -124,  -124,   128,  -124,   191,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,    22,   128,  -124,  -124,  -124,  -124,  -124,
      75,  -124,  -124,  -124,    75,    62,    22,   128,    22,    73,
     212,  -124,   148,  -124,  -124,  -124,    48,  -124,  -124,  -124,
    -124,   152,   179,    47,   155,    47,  -124,  -124,   154,  -124,
    -124,  -124,   128,  -124,   177,  -124,   156,    32,  -124,    62,
    -124,   212,  -124,  -124,  -124,  -124,  -124,  -124,   151,    27,
     170,   172,   159,   140,  -124,    22,    22,  -124,  -124,   175,
     185,    41,    47,  -124,  -124,  -124,  -124,    27,   169,  -124,
    -124,  -124,    41,  -124
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,    33,     0,     0,     0,
      32,     0,     0,     0,     0,     0,     0,     0,    37,    42,
      47,    52,    28,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     7,    11,     0,     0,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     2,     0,     0,     0,
      28,     0,    10,    92,    90,    79,    80,     0,     0,    91,
       0,    77,    22,    24,    25,    20,     0,    23,    13,     0,
       0,     0,    15,    65,     0,    31,     0,     0,     0,    40,
      41,     0,     0,     0,    45,    46,     0,    50,    51,    68,
       0,    89,     3,     0,    27,     0,    69,    72,    70,    73,
      74,    71,    75,     0,     0,    84,    85,    88,    86,    87,
       0,    81,    82,    83,     0,    76,     0,     0,     0,     0,
      18,    30,     0,    94,    97,    96,     0,    38,    39,    34,
      36,    53,     0,     0,     0,     0,    58,    43,     0,    44,
      48,    49,     0,    66,     0,    26,    17,    19,    21,    78,
      12,     5,     9,    14,    29,    93,    95,    61,     0,     0,
       0,    64,     0,     0,    67,     0,     0,     4,    54,    57,
       0,     0,     0,    60,    55,     8,    16,     0,     0,    62,
      63,    56,     0,    59
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -124,  -124,    -6,   103,   -42,  -124,   193,   -17,   -55,   -48,
     -11,    -5,   153,  -124,  -124,   158,   147,  -124,   157,   194,
    -124,   143,   190,  -123,    56,   -84,  -124,    63,   195,    -8,
     -69,  -124,   135,   -57,  -124,  -124,  -124,  -124,   -73
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    68,    69,    73,   167,    31,    89,    61,    62,
      63,    43,    39,    17,    36,    37,    18,    41,    42,    19,
      44,    45,    20,   136,   170,   137,   161,   162,    21,    64,
      90,   104,    65,    66,   114,   110,    34,    67,   138
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    32,   140,    10,    33,   127,    30,    92,   122,    94,
      60,   115,    70,    32,    32,    74,    33,    32,    49,     1,
      33,   126,    75,    76,    12,    22,   126,    23,     3,   126,
     131,   124,   125,    55,    56,    77,   169,    32,   111,   112,
      33,    95,    91,     4,   131,   124,   125,    55,    56,    16,
       6,   155,   113,   156,   169,   133,    24,   120,   132,   149,
      32,     5,   148,    33,    25,   119,    26,    27,     9,   133,
     105,   106,    11,   164,   134,    28,   144,   153,    22,    53,
      54,   107,    29,     8,   108,   109,    12,   179,    13,    35,
     174,    40,    32,   135,    12,    33,    57,   146,   183,    71,
     151,    38,   126,    58,    47,    32,   126,    32,    33,    15,
      33,    16,   152,    72,   126,    46,    48,    15,    50,    16,
     126,    52,    59,    75,    76,   126,    79,    81,   158,    78,
     160,    22,    53,    54,    55,    56,    77,    96,    97,    98,
      99,   100,   101,   123,   124,   125,    55,    56,    82,    57,
     102,    84,    83,    87,    32,    32,    58,    33,    33,   175,
     176,    96,    97,    98,    99,   100,   101,   160,    12,    86,
      93,    12,   116,    13,   102,    59,   121,   117,   143,   154,
     168,   103,   157,    14,   -94,   159,   163,   118,    96,    97,
      98,    99,   100,   101,    15,   166,    16,   171,   172,   173,
     177,   102,    96,    97,    98,    99,   100,   101,    96,    97,
      98,    99,   100,   101,   165,   102,   178,   182,    51,   150,
     145,   102,   142,    96,    97,    98,    99,   100,   101,   130,
     141,    80,    85,   181,   129,   180,   102,   128,     0,   147,
      88,   139
};

static const yytype_int16 yycheck[] =
{
       5,    12,    86,     8,    12,    78,    12,    49,    77,    57,
      27,    66,    29,    24,    25,    10,    24,    28,    24,    51,
      28,    78,    17,    18,    34,     3,    83,     5,     3,    86,
       3,     4,     5,     6,     7,    30,   159,    48,     6,     7,
      48,    58,    48,     0,     3,     4,     5,     6,     7,    59,
       3,     3,    20,     5,   177,    28,    34,    74,    17,   114,
      71,    28,   110,    71,    42,    71,    44,    45,    29,    28,
       8,     9,    26,   142,    33,    53,    93,   119,     3,     4,
       5,    19,    60,    25,    22,    23,    34,   171,    36,     3,
     163,     3,   103,    52,    34,   103,    21,   103,   182,    26,
     117,     5,   159,    28,    28,   116,   163,   118,   116,    57,
     118,    59,   118,    40,   171,    18,    27,    57,     3,    59,
     177,     5,    47,    17,    18,   182,    26,    25,   133,    11,
     135,     3,     4,     5,     6,     7,    30,    11,    12,    13,
      14,    15,    16,     3,     4,     5,     6,     7,    26,    21,
      24,    26,    11,    26,   165,   166,    28,   165,   166,   165,
     166,    11,    12,    13,    14,    15,    16,   172,    34,    27,
      56,    34,    26,    36,    24,    47,     3,    58,    29,    31,
      29,    55,     3,    46,    32,    30,    32,    37,    11,    12,
      13,    14,    15,    16,    57,    39,    59,    27,    26,    40,
      25,    24,    11,    12,    13,    14,    15,    16,    11,    12,
      13,    14,    15,    16,    37,    24,    31,    48,    25,   116,
      29,    24,    25,    11,    12,    13,    14,    15,    16,    82,
      87,    37,    42,   177,    81,   172,    24,    79,    -1,   104,
      45,    84
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    51,    64,     3,     0,    28,     3,    74,    25,    29,
      74,    26,    34,    36,    46,    57,    59,    76,    79,    82,
      85,    91,     3,     5,    34,    42,    44,    45,    53,    60,
      65,    69,    73,    92,    99,     3,    77,    78,     5,    75,
       3,    80,    81,    74,    83,    84,    18,    28,    27,    65,
       3,    69,     5,     4,     5,     6,     7,    21,    28,    47,
      70,    71,    72,    73,    92,    95,    96,   100,    65,    66,
      70,    26,    40,    67,    10,    17,    18,    30,    11,    26,
      82,    25,    26,    11,    26,    85,    27,    26,    91,    70,
      93,    65,    67,    56,    72,    70,    11,    12,    13,    14,
      15,    16,    24,    55,    94,     8,     9,    19,    22,    23,
      98,     6,     7,    20,    97,    71,    26,    58,    37,    65,
      70,     3,    93,     3,     4,     5,    96,   101,    78,    75,
      79,     3,    17,    28,    33,    52,    86,    88,   101,    81,
      88,    84,    25,    29,    70,    29,    65,    95,    72,    71,
      66,    70,    65,    67,    31,     3,     5,     3,    74,    30,
      74,    89,    90,    32,    93,    37,    39,    68,    29,    86,
      87,    27,    26,    40,   101,    65,    65,    25,    31,    88,
      90,    87,    48,    88
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    66,    66,    67,    67,    68,    68,    69,    70,
      70,    71,    71,    72,    72,    72,    72,    72,    73,    73,
      73,    73,    74,    74,    75,    75,    76,    76,    77,    78,
      78,    79,    79,    80,    81,    81,    82,    82,    83,    84,
      84,    85,    85,    86,    86,    86,    87,    87,    88,    88,
      88,    88,    89,    90,    90,    91,    92,    93,    93,    94,
      94,    94,    94,    94,    94,    94,    95,    95,    95,    96,
      96,    97,    97,    97,    98,    98,    98,    98,    98,    99,
     100,   100,   100,   101,   101,   101,   101,   101
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     8,     3,     5,     4,     1,     1,     6,     4,
       2,     1,     3,     1,     3,     1,     2,     0,     3,     3,
       1,     3,     1,     1,     1,     1,     3,     2,     1,     4,
       3,     2,     3,     1,     3,     1,     4,     1,     3,     3,
       2,     3,     1,     3,     3,     2,     3,     1,     3,     3,
       2,     3,     1,     1,     3,     3,     3,     1,     1,     6,
       3,     2,     3,     3,     1,     3,     4,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     2,     1,     2,     1,     1
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
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
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 85 "parse.y" /* yacc.c:1646  */
    { parseresult = makeprogram((yyvsp[-6]), (yyvsp[-4]), (yyvsp[-1])); }
#line 1528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 87 "parse.y" /* yacc.c:1646  */
    { (yyval) = makeprogn((yyvsp[-2]),cons((yyvsp[-1]), (yyvsp[0]))); }
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 88 "parse.y" /* yacc.c:1646  */
    { (yyval) = makeif((yyvsp[-4]), (yyvsp[-3]), (yyvsp[-1]), (yyvsp[0])); }
#line 1540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "parse.y" /* yacc.c:1646  */
    {(yyval) = makerepeat((yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 92 "parse.y" /* yacc.c:1646  */
    { (yyval) = makefor(1, (yyvsp[-5]), (yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 93 "parse.y" /* yacc.c:1646  */
    { (yyval) = makewhile((yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 94 "parse.y" /* yacc.c:1646  */
    { (yyval) = dogoto((yyvsp[-1]), (yyvsp[0])); }
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 97 "parse.y" /* yacc.c:1646  */
    { (yyval) = cons((yyvsp[-2]), (yyvsp[0])); }
#line 1570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 100 "parse.y" /* yacc.c:1646  */
    { (yyval) = cons((yyvsp[-1]), (yyvsp[0])); }
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 101 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 103 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 104 "parse.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 106 "parse.y" /* yacc.c:1646  */
    { (yyval) = binop((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 108 "parse.y" /* yacc.c:1646  */
    { (yyval) = binop((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 111 "parse.y" /* yacc.c:1646  */
    { (yyval) = binop((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 117 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 118 "parse.y" /* yacc.c:1646  */
    { (yyval) = unaryop((yyvsp[-1]), (yyvsp[0])); }
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 120 "parse.y" /* yacc.c:1646  */
    { (yyval) = findid((yyvsp[0])); }
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 121 "parse.y" /* yacc.c:1646  */
    { (yyval) = arrayref((yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 122 "parse.y" /* yacc.c:1646  */
    { (yyval) = reducedot((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 123 "parse.y" /* yacc.c:1646  */
    { (yyval) = dopoint((yyvsp[-1]), (yyvsp[0])); }
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 126 "parse.y" /* yacc.c:1646  */
    { (yyval) = cons((yyvsp[-2]), (yyvsp[0])); }
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 127 "parse.y" /* yacc.c:1646  */
    { (yyval) = cons((yyvsp[0]), NULL); }
#line 1660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 129 "parse.y" /* yacc.c:1646  */
    { instlabel((yyvsp[-2])); }
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 130 "parse.y" /* yacc.c:1646  */
    { instlabel((yyvsp[0])); }
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 132 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 135 "parse.y" /* yacc.c:1646  */
    { instconst((yyvsp[-2]), (yyvsp[0])); }
#line 1684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 139 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 142 "parse.y" /* yacc.c:1646  */
    { insttype((yyvsp[-2]), (yyvsp[0])); }
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 146 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 149 "parse.y" /* yacc.c:1646  */
    { instvars((yyvsp[-2]), (yyvsp[0])); }
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 154 "parse.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 157 "parse.y" /* yacc.c:1646  */
    { (yyval) = findtype((yyvsp[0])); }
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 158 "parse.y" /* yacc.c:1646  */
    { (yyval) = instenum((yyvsp[-1])); }
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 159 "parse.y" /* yacc.c:1646  */
    { (yyval) = instdotdot((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]));}
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 161 "parse.y" /* yacc.c:1646  */
    { (yyval) = cons((yyvsp[-2]), (yyvsp[0])); }
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 162 "parse.y" /* yacc.c:1646  */
    { (yyval) = cons((yyvsp[0]), NULL); }
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 165 "parse.y" /* yacc.c:1646  */
    { (yyval) = instarray((yyvsp[-3]), (yyvsp[0])); }
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 166 "parse.y" /* yacc.c:1646  */
    { (yyval) = instrec((yyvsp[-2]), (yyvsp[-1])); }
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 167 "parse.y" /* yacc.c:1646  */
    { (yyval) = instpoint((yyvsp[-1]), (yyvsp[0])); }
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 169 "parse.y" /* yacc.c:1646  */
    { (yyval) = instfields((yyvsp[-2]), (yyvsp[0])); }
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 171 "parse.y" /* yacc.c:1646  */
    { (yyval) = nconc((yyvsp[-2]), (yyvsp[0])); }
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 174 "parse.y" /* yacc.c:1646  */
    { (yyval) = makeprogn((yyvsp[-2]),cons((yyvsp[-1]), (yyvsp[0]))); }
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 176 "parse.y" /* yacc.c:1646  */
    { (yyval) = makefuncall((yyvsp[-2]), (yyvsp[-3]), (yyvsp[-1])); }
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 178 "parse.y" /* yacc.c:1646  */
    { (yyval) = cons((yyvsp[-2]), (yyvsp[0])); }
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 183 "parse.y" /* yacc.c:1646  */
    { (yyval) = unaryop((yyvsp[-1]), (yyvsp[0])); }
#line 1798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 185 "parse.y" /* yacc.c:1646  */
    { (yyval) = binop((yyvsp[-1]), (yyvsp[-2]), (yyvsp[0])); }
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 193 "parse.y" /* yacc.c:1646  */
    { (yyval) = dolabel((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 196 "parse.y" /* yacc.c:1646  */
    { (yyval) = makeintc(0); }
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 199 "parse.y" /* yacc.c:1646  */
    { (yyval) = unaryop((yyvsp[-1]), (yyvsp[0])); }
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 201 "parse.y" /* yacc.c:1646  */
    { (yyval) = unaryop((yyvsp[-1]), (yyvsp[0])); }
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1832 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 206 "parse.y" /* yacc.c:1906  */


/* You should add your own debugging flags below, and add debugging
   printouts to your programs.

   You will want to change DEBUG to turn off printouts once things
   are working.
  */

#define DEBUG         32             /* set bits here for debugging, 0 = off  */
#define DB_CONS       1             /* bit to trace cons */
#define DB_BINOP      2             /* bit to trace binop */
#define DB_MAKEIF     4             /* bit to trace makeif */
#define DB_MAKEPROGN  8             /* bit to trace makeprogn */
#define DB_PARSERES  16             /* bit to trace parseresult */

 int labelnumber = 0;  /* sequential counter for internal label numbers */

 int labels[100];

   /*  Note: you should add to the above values and insert debugging
       printouts in your routines similar to those that are shown here.     */

TOKEN cons(TOKEN item, TOKEN list)           /* add item to front of list */
  { item->link = list;
    if (DEBUG & DB_CONS)
       { printf("cons\n");
         dbugprinttok(item);
         dbugprinttok(list);
       };
    return item;
  }

TOKEN makeif(TOKEN tok, TOKEN exp, TOKEN thenpart, TOKEN elsepart)
  {  tok->tokentype = OPERATOR;  /* Make it look like an operator   */
     tok->whichval = IFOP;
     if (elsepart != NULL) elsepart->link = NULL;
     thenpart->link = elsepart;
     exp->link = thenpart;
     tok->operands = exp;
     if (DEBUG & DB_MAKEIF)
        { printf("makeif\n");
          dbugprinttok(tok);
          dbugprinttok(exp);
          dbugprinttok(thenpart);
          dbugprinttok(elsepart);
        };
     return tok;
   }

TOKEN makeprogn(TOKEN tok, TOKEN statements)
  {  tok->tokentype = OPERATOR;
     tok->whichval = PROGNOP;
     tok->operands = statements;
     if (DEBUG & DB_MAKEPROGN)
       { printf("makeprogn\n");
         dbugprinttok(tok);
         dbugprinttok(statements);
       };
     return tok;
   }

//add da constant to da symbol table
void  instconst(TOKEN idtok, TOKEN consttok) {
    SYMBOL sym, type;
    TOKEN tokToCopy;

    if (consttok->tokentype == OPERATOR) {
		tokToCopy = consttok->operands;
	} else {
		tokToCopy = consttok;
	}
    //add in symtype
    sym = insertsym(idtok->stringval);
    if (tokToCopy->tokentype == NUMBERTOK) {
        if (tokToCopy->basicdt == INTEGER) {
            sym->basicdt = INTEGER;
            type = searchst("integer");
            sym->constval.intnum = tokToCopy->intval;
        } else if (tokToCopy->basicdt == REAL) {
            sym->basicdt = REAL;
            type = searchst("real");
            sym->constval.realnum = tokToCopy->realval;
        } else {
            yyerror("fail");
        }
    } else if (tokToCopy->tokentype == STRINGTOK) {
        type = searchst("char");
        sym->basicdt = STRING;
        strcpy(sym->constval.stringconst, tokToCopy->stringval);
    }

    sym->datatype = type;
    sym->kind = CONSTSYM;
}

//return the data type of a token or operator token
int infer_type(TOKEN tok) {
    if (tok->tokentype == IDENTIFIERTOK || tok->tokentype == NUMBERTOK) {
        return tok->basicdt;
    } else if (tok->tokentype == STRINGTOK) {
        return STRINGTYPE;
    } else if (tok->tokentype == OPERATOR) {
        if (tok->whichval == FLOATOP) {
            return REAL;
        } else if (tok->whichval == FUNCALLOP) {
            printf("inferring funcall type as %d\n", tok->operands->basicdt);
            return tok->operands->basicdt;
        } else if (tok->whichval == FIXOP) {
            return INTEGER;
        }
        return infer_type(tok->operands); //we may need to go down another level
    }

    return -1; //err
}

int check_op_simple(TOKEN op) {
    int action = op->whichval;
    return (action >= 1 && action <= 4) || (action == DIVOP || action == MODOP);
}


TOKEN findid(TOKEN tok) { 
    SYMBOL sym = searchst(tok->stringval);

    if ( sym->kind == CONSTSYM ) {
        tok->basicdt = sym->basicdt;
        if (sym->basicdt == STRINGTYPE) {
            strcpy(tok->stringval, sym->constval.stringconst);
            tok->tokentype = STRINGTOK;
        } else if (sym->basicdt == REAL) {
            tok->tokentype = NUMBERTOK;
            tok->realval = sym->constval.realnum;
        } else if (sym->basicdt == INTEGER) {
            tok->intval = sym->constval.intnum;
            tok->tokentype = NUMBERTOK;
        }
    } else {
        tok->symentry = sym;
        tok->basicdt = sym->datatype->basicdt;
        tok->symtype = sym->datatype;
    }
    return tok; 
}


TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  { 
    
    int typ_lhs = infer_type(lhs);
    int typ_rhs = infer_type(rhs);

    if ( (typ_lhs == REAL && typ_rhs == INTEGER) ) {
        if (check_op_simple(op)) {
            rhs = makefloat(rhs);
        }
        if (op->whichval == ASSIGNOP) {
            rhs = makefloat(rhs);
        }
    }
    if ( (typ_lhs == INTEGER && typ_rhs == REAL) ) {
        if (check_op_simple(op)) {
            lhs = makefloat(lhs); 
        }
        if (op->whichval == ASSIGNOP) {
            rhs = makefix(rhs);
        }
    }
    
    op->operands = lhs;          /* link operands to operator       */
    lhs->link = rhs;             /* link second operand to first    */
    rhs->link = NULL;            /* terminate operand list          */
    if (DEBUG & DB_BINOP)
       { printf("binop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
         dbugprinttok(rhs);
       };
    return op;
  }


TOKEN makefloat(TOKEN tok) {
	if (tok->tokentype == NUMBERTOK && tok->basicdt == INTEGER) {
        tok->basicdt = REAL;
		tok->realval = tok->intval;
		return tok;
	} else if (tok->tokentype == IDENTIFIERTOK) {
        TOKEN floatTok = makeop(FLOATOP);
		floatTok->operands = tok;
        return floatTok;
	} else {
        return tok;
	}
	return tok;
}

/* makefix forces the item tok to be integer, by truncating a constant
   or by inserting a FIXOP operator */
TOKEN makefix(TOKEN tok) {
	if (tok->tokentype == NUMBERTOK && tok->basicdt == REAL) {
        tok->basicdt = INTEGER;
		tok->intval = tok->realval;
		return tok;
	} else {
        TOKEN fixTok = makeop(FIXOP);
		fixTok->operands = tok;
        return fixTok;
	}
	return tok;
}


TOKEN unaryop(TOKEN op, TOKEN lhs) {
	op->operands = lhs;
	lhs->link = NULL;
	if (DEBUG) { 
		printf("unaryop\n");
	    dbugprinttok(op);
	    dbugprinttok(lhs);
	};
	return op;
}


TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr) {
	makeprogn(tok, statements);
	TOKEN repeatTok = makeprogn(talloc(), 0);
    TOKEN goto_tok = makegoto(labelnumber); 
	makeif(tokb, expr, repeatTok, goto_tok);
    TOKEN l_tok = makelabel();
	l_tok->link = tok;
    tok->link = tokb;
	return makeprogn(talloc(), l_tok);
}





// concatenate two token lists
TOKEN nconc(TOKEN lista, TOKEN listb) {
    TOKEN newList = lista;
    if (lista==NULL)
    return lista;
    else {
        while(newList->link) {
            newList = newList->link;
        }
        newList->link = listb;
    }

    if (DEBUG) {
        printf("nconc\n");
    }
    return newList;
}

// action for the goto
TOKEN dogoto(TOKEN tok, TOKEN labeltok) {
    int currentLabelNumber;
    int i = 0;
    while (i < labelnumber) {
      if (labels[i] == labeltok->intval) {
        currentLabelNumber = i; 
      }
      i++;
    }
    tok = makegoto(currentLabelNumber);
    if (DEBUG) {
      printf("hello from dogoto\n");
    }
    return tok;
}

// action for label
// basically the same as goto
TOKEN dolabel(TOKEN labeltok, TOKEN tok, TOKEN statement) {
    int i = 0;
    int currentLabelNumber;
    while (i < labelnumber) {
      if (labels[i] == labeltok->intval) {
        currentLabelNumber = i; 
      }
      i++;
    }
    TOKEN intTok = makeintc(currentLabelNumber);
    labeltok = makeop(LABELOP);
    labeltok->operands = intTok;
    labeltok->link = statement;
    tok = makeprogn(tok, labeltok);
    if (DEBUG) {
      printf("dolabel\n");
    }
    return tok;
}

/* instlabel installs a user label into the label table */
void instlabel (TOKEN num) {
    labels[labelnumber++] = num->intval;  
}

// while statement structure
TOKEN makewhile(TOKEN tok, TOKEN expr, TOKEN tokb, TOKEN statement) {
    if (tok != NULL) {
        TOKEN label = makelabel();
        
        tok = makeprogn(tok, label);
        int currentlabel = labelnumber - 1;
        TOKEN gototok = makegoto(currentlabel);
        statement->link = gototok;
        TOKEN bodytok = makeprogn(tokb, statement);

        TOKEN iftok = talloc();
        iftok = makeif(iftok, expr, bodytok, NULL);
        label->link = iftok;
        if (DEBUG) {
            printf("makewhile\n");
            dbugprinttok(tok);
        }
        return tok;
    }
    return NULL;
}

/* makesubrange makes a SUBRANGE symbol table entry, puts the pointer to it
   into tok, and returns tok. */
TOKEN makesubrange(TOKEN tok, int low, int high) {
    if (tok != NULL) {
        SYMBOL subrange = symalloc();
        subrange->lowbound = low;
        subrange->highbound = high;
        subrange->kind = SUBRANGE;
        subrange->size = basicsizes[INTEGER];
        subrange->basicdt = INTEGER;
        tok->symtype = subrange;
        return tok;
    }
    if (DEBUG) {
        printf("makesubrange\n");
    }
}

/* instenum installs an enumerated subrange in the symbol table,
   e.g., type color = (red, white, blue)
   by calling makesubrange and returning the token it returns. */
TOKEN instenum(TOKEN idlist) {
    int size = 0;
    TOKEN arr = copytok(idlist);
    for (int i = 0; arr; i++) {
        instconst(arr, makeintc(size));
        arr = arr->link;
        size++;
    }
    TOKEN tok = makesubrange(idlist, 0, size - 1);
    if (DEBUG){
        printf("instenum\n");
    }
    return tok;
}

/* instdotdot installs a .. subrange in the symbol table.
   dottok is a (now) unused token that is recycled. */
TOKEN instdotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok) {
    int highBound = hightok->intval;
    int lowBound = lowtok->intval;
    return makesubrange(dottok, lowBound, highBound);
}

/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
void  insttype(TOKEN typename, TOKEN typetok) {
    SYMBOL typeSymbol = searchins(typename->stringval);
    typeSymbol->kind = TYPESYM;
    typeSymbol->size = typetok->symtype->size;
    typeSymbol->datatype = typetok->symtype;
    if (DEBUG) {
        printf("insttype\n");
    }
}

/* instpoint will install a pointer type in symbol table */
TOKEN instpoint(TOKEN tok, TOKEN typename) {
    if (tok != NULL) {
        SYMBOL typeSymbol = searchins(typename->stringval);
        SYMBOL pointerSymbol = symalloc();
        pointerSymbol->size = basicsizes[POINTER];
        pointerSymbol->basicdt = POINTER;
        pointerSymbol->datatype = typeSymbol;
        pointerSymbol->kind = POINTERSYM;
        tok->symtype = pointerSymbol;
    } else {
        return NULL;
    }
    if (DEBUG) {
        printf("instpoint\n");
        dbugprinttok(tok);
    }
    return tok;
}

/* instrec will install a record definition.  Each token in the linked list
   argstok has a pointer its type.  rectok is just a trash token to be
   used to return the result in its symtype */
TOKEN instrec(TOKEN rectok, TOKEN argstok) {
    SYMBOL recordSymbol = symalloc();
    int count = 0; 
    int next = 0;
    int align;
    recordSymbol->kind = RECORDSYM;
    SYMBOL prev = NULL;
    for (int i = 0; argstok; i++){
        align = alignsize(argstok->symtype);
        SYMBOL currentRecordField = makesym(argstok->stringval);
        currentRecordField->datatype = argstok->symtype;
        currentRecordField->size = currentRecordField->datatype->size;
        currentRecordField->offset = wordaddress(next, align);
        next = currentRecordField->offset + currentRecordField->size;
        if (count == 0) {
            recordSymbol->datatype = currentRecordField;
            prev = currentRecordField;
        } else {
            prev->link = currentRecordField;
            prev = currentRecordField;
        }
        count++;
        argstok = argstok->link;
        currentRecordField->link = NULL;
    }
    recordSymbol->size = wordaddress(next, 16); 
    rectok->symtype = recordSymbol;
    if (DEBUG) {
        printf("instrect\n");
    }
    return rectok;
}

/* instfields will install type in a list idlist of field name tokens:
   re, im: real    put the pointer to REAL in the RE, IM tokens.
   typetok is a token whose symtype is a symbol table pointer.
   Note that nconc() can be used to combine these lists after instrec() */
TOKEN instfields(TOKEN idlist, TOKEN typetok) {
    TOKEN tok = idlist;
    SYMBOL typeSymbol = typetok->symtype;
    for (int i = 0; tok; i++) {
        tok->symtype = typeSymbol;     
        tok = tok->link;
    }
    if (DEBUG) {
        printf("instfields\n");
    }
    return idlist;
}

/* makearef makes an array reference operation.
   off is be an integer constant token
   tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makearef(TOKEN var, TOKEN off, TOKEN tok) {
    int flag = 0;
    if (tok != NULL) { 
        if (var->whichval == AREFOP) {
            TOKEN plusToken = makeop(PLUSOP);
            TOKEN temp = var->operands->link;
            temp->link = off;
            plusToken->operands = temp;
            var->operands->link = plusToken;
            var->basicdt = var->symentry->basicdt;
            return var;
        }
    } 
    TOKEN arefToken = makeop(AREFOP);
    var->link = off;
    arefToken->operands = var;
    arefToken->symentry = var->symentry; 
    arefToken->basicdt = arefToken->symentry->basicdt; 
    if (DEBUG) {
        printf("makearef\n");
    }
    return arefToken;
}

/* reducedot handles a record reference.
   dot is a (now) unused token that is recycled. */
TOKEN reducedot(TOKEN var, TOKEN dot, TOKEN field) {
    SYMBOL record = var->symentry;
    SYMBOL currentRecordField = record->datatype->datatype;
    int offset = 0;
    while(currentRecordField) {
        if (strcmp(currentRecordField->namestring, field->stringval) == 0) {
            offset = currentRecordField->offset;
            var->symentry = currentRecordField;
            break;
        } else {
            currentRecordField = currentRecordField->link;
        }
    }
    dot = makearef(var, makeintc(offset), dot);
    if (DEBUG) {
        printf("reducedot\n");
    }
    return dot;
}

/* arrayref processes an array reference a[i]
   subs is a list of subscript expressions.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN arrayref(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb) {
    if (subs->link) {
        TOKEN timesop = makeop(TIMESOP);
        int low = arr->symtype->lowbound;
        int high = arr->symtype->highbound;
        int size = (arr->symtype->size / (high + low - 1));
        TOKEN subsToken = copytok(subs);
        subsToken->link = NULL;
        TOKEN sizeElementToken = makeintc(size);
        sizeElementToken->link = subsToken;
        timesop->operands = sizeElementToken;
        TOKEN newSizeToken = makeintc(-1 * size);
        newSizeToken->link = timesop;
        TOKEN plusop = makeop(PLUSOP);
        plusop->operands = newSizeToken;
        TOKEN subarref = makearef(arr, plusop, tokb);
        subarref->symtype = arr->symtype->datatype;
        return arrayref(subarref, tok, subs->link, tokb);
    } else {
        TOKEN timesop = makeop(TIMESOP);
        int low = arr->symtype->lowbound;
        int high = arr->symtype->highbound;
        int size = (arr->symtype->size / (high + low - 1));

        TOKEN sizeElementToken = makeintc(size);
        sizeElementToken->link = subs;
        timesop->operands = sizeElementToken;

        TOKEN newSizeToken = makeintc(size * -1);
        newSizeToken->link = timesop;
        TOKEN plusop = makeop(PLUSOP);
        plusop->operands = newSizeToken;
        return makearef(arr, plusop, tokb);
    }
    if (DEBUG) {
        printf("arrayref\n");
    }
}

/* dopoint handles a ^ operator.  john^ becomes (^ john) with type record
   tok is a (now) unused token that is recycled. */
TOKEN dopoint(TOKEN var, TOKEN tok) {
    tok->operands = var;
    tok->symentry = var->symentry->datatype->datatype;
    if (DEBUG) {
        printf("dopoint\n");
    }
    return tok;
}

/* instarray installs an array declaration into the symbol table.
   bounds points to a SUBRANGE symbol table entry.
   The symbol table pointer is returned in token typetok. */
TOKEN instarray(TOKEN bounds, TOKEN typetok) {
  int ready = 0; 
  if (bounds->link) {
    typetok = instarray(bounds->link, typetok);

    SYMBOL symbolSubRange = bounds->symtype;
    SYMBOL typeSymbol = typetok->symtype;
    SYMBOL arraySymbol = symalloc();

    arraySymbol->kind = ARRAYSYM;
    arraySymbol->datatype = typeSymbol;
    arraySymbol->lowbound = symbolSubRange->lowbound;
    arraySymbol->highbound = symbolSubRange->highbound;
    arraySymbol->size = (arraySymbol->lowbound + arraySymbol->highbound - 1) * (typeSymbol->size);
    typetok->symtype = arraySymbol;
    return typetok;
  } else {
    SYMBOL symbolSubRange = bounds->symtype;
    SYMBOL typeSymbol = typetok->symtype;
    SYMBOL arraySymbol = symalloc();
    arraySymbol->kind = ARRAYSYM;
    arraySymbol->datatype = typeSymbol;
    arraySymbol->lowbound = symbolSubRange->lowbound;
    arraySymbol->highbound = symbolSubRange->highbound;
    arraySymbol->size = (arraySymbol->highbound - arraySymbol->lowbound +  1) * (typeSymbol->size);
    typetok->symtype = arraySymbol;
    return typetok;
  }
    if (DEBUG) {
        printf("instarray\n");
    }
}


/* makefuncall makes a FUNCALL operator and links it to the fn and args.
   tok is a (now) unused token that is recycled. */

TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args) {
    int func; 
    if (strcmp(fn->stringval, "new") == 0)
        func = 0; 
    else if (strcmp(fn->stringval, "writeln") == 0)
        func = 1; 
    else func = 2;

    switch(func)
    {
        case 0: 
        tok = makeop(ASSIGNOP);
        tok->operands = args;

        SYMBOL typsym = args->symtype;
        typsym = typsym->datatype;

        TOKEN funcal = talloc();
        funcal->tokentype = OPERATOR;
        funcal->whichval = FUNCALLOP;
        funcal->operands = fn;
        fn->link = makeintc(typsym->size);
        args->link = funcal;

        break; 

        case 1: 
        if (args->basicdt == REAL) 
            strcpy(fn->stringval, "writelnf");
        if (args->tokentype == STRINGTOK) 
            strcpy(fn->stringval, "writeln");
        else strcpy(fn->stringval, "writelni");
        tok->tokentype = OPERATOR;
        tok->whichval = FUNCALLOP;
        tok->operands = fn;
        fn->link=args; 
        break; 

        case 2: 
        tok->tokentype = OPERATOR;
        tok->whichval = FUNCALLOP;
        tok->operands = fn;
        fn->link=args;
    }

    if (DEBUG) {
            printf("makefuncall\n");
    }
    return tok;
}




TOKEN makeop(int opnum){
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = opnum;
    if (DEBUG) {
      printf("makeop\n");
      dbugprinttok(tok);
    }
    return tok;
}

TOKEN copytok(TOKEN origtok) {
  TOKEN tok = talloc();
  tok->tokentype = origtok->tokentype;
  tok->basicdt = origtok->basicdt;
  tok->link = origtok->link;
  tok->symtype = origtok->symtype;
  tok->symentry = origtok->symentry;
  tok->whichval = origtok->whichval;
  tok->intval = origtok->intval;
  tok->realval = origtok->realval;
  if (DEBUG) {
    printf("copytok\n");
    dbugprinttok(tok);
  }
  return tok;
}


TOKEN makefor(int sign, TOKEN tok, TOKEN assign, TOKEN tokb, TOKEN expr, TOKEN tokc, TOKEN statements) {
    tok = makeprogn(tok, assign);
    TOKEN if_part = talloc();
    TOKEN then_part = talloc();

    //for loop needs to end when i >= expr
    TOKEN less_than_op = makeop(LEOP);

    then_part = makeprogn(then_part, statements);
    if_part = makeif(if_part, less_than_op, then_part, NULL);

    //duplicate i token
    TOKEN i_to_lim = copytok(assign->operands);
    //need 3 tokens, link i to lim, and i := (i + 1) 
    TOKEN set_i = copytok(assign->operands); //for i :=
    TOKEN change_i = copytok(assign->operands); //for (i + 1)

    //link i to lim
    i_to_lim->link = expr;

    //for checking if i <= lim
    less_than_op->operands = i_to_lim;

    //for i :=
    TOKEN set = makeop(ASSIGNOP);

    //for i := i + 1
    TOKEN change = makeop(PLUSOP);

    
    //link if to <=
    if_part->operands = less_than_op;
    less_than_op->link = then_part;

    //create tree for i :=
    set->operands = set_i;
    set_i->link = change;


    //create goto links
    TOKEN l = makelabel();
    assign->link = l;
    TOKEN goto_tok = makegoto(labelnumber - 1);
    set->link = goto_tok;

    //create tree for (i + 1)
    change->operands = change_i;
    change_i->link = makeintc(1);
    
    //link funcall to assignment :=
    statements->link = set;
    l->link = if_part;
    if (DEBUG) {
         printf("makefor\n");
         dbugprinttok(tok);
    }
    return tok;
}


TOKEN makeprogram(TOKEN name, TOKEN args, TOKEN statements) {
    printf("running make program\n");
    //token for program
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = PROGRAMOP;
    tok->operands = name;

    //need graph1 to point to a progn
    TOKEN progn_tok = makeprogn(talloc(), args);
    
    //make graph1 token point to progn token
    name->link = progn_tok;

    //need to link progn to statements
    progn_tok->link = statements;


    if (DEBUG)
    { printf("makeprogram\n");
        /* dbugprinttok(tok);
        dbugprinttok(statements); */
    };
    return tok;
}

//creates a label which contains a number that identifies it
TOKEN makelabel() {
    TOKEN l = talloc();
    l->tokentype = OPERATOR;
    l->whichval = LABELOP;

    TOKEN num = makeintc(labelnumber);
    labelnumber++;

    l->operands = num;
    //num->link = NULL; //no more operands
    return l;
}

TOKEN makegoto(int label) {
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = GOTOOP;
    TOKEN l_tok = makeintc(label);
    //we must assign the goto operator (tok) to the label reference
    tok->operands = l_tok;
    //l_tok->link = NULL; //no more operands
    return tok;
}

TOKEN makeintc(int num) {
    TOKEN tok = talloc();
    tok->basicdt = INTEGER;
    tok->intval = num; //set the value to num
    tok->tokentype = NUMBERTOK;
    return tok;
}

TOKEN findtype(TOKEN tok) {
    SYMBOL sym = searchst(tok->stringval);

    switch(sym->kind){
       case TYPESYM:
       sym = sym->datatype;
       break;

       case BASICTYPE:
       tok->symtype = sym; 
       tok->basicdt = sym->basicdt; 
    }
  
   tok->symtype = sym;
    if (DEBUG) {
      printf("fin\n");
      dbugprinttok(tok);
    }

    return tok;
}

/* install variables in symbol table */
void instvars(TOKEN idlist, TOKEN typetok) {
    int align;
    SYMBOL type, sym; 
    type = typetok->symtype;
    align = alignsize(type);
    while (idlist != NULL)  {  
        sym = insertsym(idlist->stringval);
        sym->kind = VARSYM; 
        sym->offset = wordaddress(blockoffs[blocknumber],align);
        sym->size = type->size;
        blockoffs[blocknumber] = sym->offset + sym->size;
        sym->datatype = type;
        sym->basicdt = type->basicdt;
        idlist = idlist->link;
    };
}

int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

int main(void)          /*  */
  { int res;
    initsyms();
    res = yyparse();
    printst();       /* to shorten, change to:  printstlevel(1);  */
    printf("yyparse result = %8d\n", res);
    if (DEBUG & DB_PARSERES) dbugprinttok(parseresult);
    ppexpr(parseresult);           /* Pretty-print the result tree */
    /* uncomment following to call code generator. */
     /* 
    gencode(parseresult, blockoffs[blocknumber], labelnumber);
 */
  }
