/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         SLANG_STYPE
/* Substitute the variable and function names.  */
#define yyparse         slang_parse
#define yylex           slang_lex
#define yyerror         slang_error
#define yylval          slang_lval
#define yychar          slang_char
#define yydebug         slang_debug
#define yynerrs         slang_nerrs

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "slang.y"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "getopt.h"

// stuff from flex that bison needs to know about:
extern int yylex();
extern int yyparse();
extern void yyerror(char const *);
extern FILE *yyin;

struct slang_node* g_slang_root;


/* Line 371 of yacc.c  */
#line 93 "slang.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "slang.tab.h".  */
#ifndef YY_SLANG_SLANG_TAB_H_INCLUDED
# define YY_SLANG_SLANG_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef SLANG_DEBUG
# if defined YYDEBUG
#  if YYDEBUG
#   define SLANG_DEBUG 1
#  else
#   define SLANG_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define SLANG_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined SLANG_DEBUG */
#if SLANG_DEBUG
extern int slang_debug;
#endif

/* Tokens.  */
#ifndef SLANG_TOKENTYPE
# define SLANG_TOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum slang_tokentype {
     IDENTIFIER = 258,
     FLOATCONSTANT = 259,
     DOUBLECONSTANT = 260,
     INTCONSTANT = 261,
     UINTCONSTANT = 262,
     TRUE_VALUE = 263,
     FALSE_VALUE = 264,
     TRANSLATION_UNIT = 265,
     VARIABLE_DECL = 266,
     TYPE_SPECIFIER = 267,
     VOID = 268,
     CONST = 269,
     CBUFFER = 270,
     BUFFER = 271,
     BOOL = 272,
     BOOL2 = 273,
     BOOL3 = 274,
     BOOL4 = 275,
     BOOL2X2 = 276,
     BOOL2X3 = 277,
     BOOL2X4 = 278,
     BOOL3X2 = 279,
     BOOL3X3 = 280,
     BOOL3X4 = 281,
     BOOL4X2 = 282,
     BOOL4X3 = 283,
     BOOL4X4 = 284,
     INT = 285,
     INT2 = 286,
     INT3 = 287,
     INT4 = 288,
     INT2X2 = 289,
     INT2X3 = 290,
     INT2X4 = 291,
     INT3X2 = 292,
     INT3X3 = 293,
     INT3X4 = 294,
     INT4X2 = 295,
     INT4X3 = 296,
     INT4X4 = 297,
     UINT = 298,
     UINT2 = 299,
     UINT3 = 300,
     UINT4 = 301,
     UINT2X2 = 302,
     UINT2X3 = 303,
     UINT2X4 = 304,
     UINT3X2 = 305,
     UINT3X3 = 306,
     UINT3X4 = 307,
     UINT4X2 = 308,
     UINT4X3 = 309,
     UINT4X4 = 310,
     DWORD = 311,
     HALF = 312,
     HALF2 = 313,
     HALF3 = 314,
     HALF4 = 315,
     HALF2X2 = 316,
     HALF2X3 = 317,
     HALF2X4 = 318,
     HALF3X2 = 319,
     HALF3X3 = 320,
     HALF3X4 = 321,
     HALF4X2 = 322,
     HALF4X3 = 323,
     HALF4X4 = 324,
     FLOAT = 325,
     FLOAT2 = 326,
     FLOAT3 = 327,
     FLOAT4 = 328,
     FLOAT2X2 = 329,
     FLOAT2X3 = 330,
     FLOAT2X4 = 331,
     FLOAT3X2 = 332,
     FLOAT3X3 = 333,
     FLOAT3X4 = 334,
     FLOAT4X2 = 335,
     FLOAT4X3 = 336,
     FLOAT4X4 = 337,
     DOUBLE = 338,
     DOUBLE2 = 339,
     DOUBLE3 = 340,
     DOUBLE4 = 341,
     DOUBLE2X2 = 342,
     DOUBLE2X3 = 343,
     DOUBLE2X4 = 344,
     DOUBLE3X2 = 345,
     DOUBLE3X3 = 346,
     DOUBLE3X4 = 347,
     DOUBLE4X2 = 348,
     DOUBLE4X3 = 349,
     DOUBLE4X4 = 350,
     VECTOR = 351,
     MATRIX = 352,
     SAMPLER = 353,
     SAMPLER1D = 354,
     SAMPLER2D = 355,
     SAMPLER3D = 356,
     SAMPLERCUBE = 357,
     SAMPLERSTATE = 358,
     SAMPLER_STATE = 359,
     TEXTURE1D = 360,
     TEXTURE1DARRAY = 361,
     TEXTURE2D = 362,
     TEXTURE2DARRAY = 363,
     TEXTURE3D = 364,
     TEXTURE3DARRAY = 365,
     TEXTURECUBE = 366,
     STRUCT = 367,
     LINEAR_MODIFIER = 368,
     CENTROID_MODIFIER = 369,
     NOINTERPOLATION_MODIFIER = 370,
     NOPERSPECTIVE_MODIFIER = 371,
     SAMPLE_MODIFIER = 372,
     TYPEDEF = 373,
     LEFT_OP = 374,
     RIGHT_OP = 375,
     INC_OP = 376,
     DEC_OP = 377,
     LE_OP = 378,
     GE_OP = 379,
     EQ_OP = 380,
     NE_OP = 381,
     AND_OP = 382,
     OR_OP = 383,
     XOR_OP = 384,
     MUL_ASSIGN = 385,
     DIV_ASSIGN = 386,
     ADD_ASSIGN = 387,
     MOD_ASSIGN = 388,
     LEFT_ASSIGN = 389,
     RIGHT_ASSIGN = 390,
     AND_ASSIGN = 391,
     XOR_ASSIGN = 392,
     OR_ASSIGN = 393,
     SUB_ASSIGN = 394,
     PLUS = 395,
     DASH = 396,
     PERCENT = 397,
     STAR = 398,
     SLASH = 399,
     TILDE = 400,
     BANG = 401,
     CARET = 402,
     LEFT_PAREN = 403,
     RIGHT_PAREN = 404,
     LEFT_BRACE = 405,
     RIGHT_BRACE = 406,
     SEMICOLON = 407,
     LEFT_ANGLE = 408,
     RIGHT_ANGLE = 409,
     DOT = 410,
     COMMA = 411,
     LEFT_BRACKET = 412,
     RIGHT_BRACKET = 413,
     VERTICAL_BAR = 414,
     COLON = 415,
     EQUAL = 416,
     AMPERSAND = 417,
     QUESTION = 418
   };
#endif


#if ! defined SLANG_STYPE && ! defined SLANG_STYPE_IS_DECLARED

# define slang_stype SLANG_STYPE /* obsolescent; will be withdrawn */
# define SLANG_STYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int slang_parse (void *YYPARSE_PARAM);
#else
int slang_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int slang_parse (void);
#else
int slang_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_SLANG_SLANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 328 "slang.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined SLANG_STYPE_IS_TRIVIAL && SLANG_STYPE_IS_TRIVIAL)))

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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  84
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   82

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  164
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  6
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNRULES -- Number of states.  */
#define YYNSTATES  88

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   418

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163
};

#if SLANG_DEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    35,    37,
      39,    41,    43,    45,    47,    49,    51,    53,    55,    57,
      59,    61,    63,    65,    67,    69,    71,    73,    75,    77,
      79,    81,    83,    85,    87,    89,    91,    93,    95,    97,
      99,   101,   103,   105,   107,   109,   111,   113,   115,   117,
     119,   121,   123,   125,   127,   129,   131,   133,   135,   137,
     139,   141,   143,   145,   147,   149,   151,   153,   155,   157,
     159,   161,   163,   165,   167
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     165,     0,    -1,   169,    -1,    13,    -1,    17,    -1,    18,
      -1,    19,    -1,    20,    -1,    21,    -1,    22,    -1,    23,
      -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,
      -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,
      -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,    38,
      -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,    43,
      -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,    48,
      -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,    53,
      -1,    54,    -1,    55,    -1,    70,    -1,    71,    -1,    72,
      -1,    73,    -1,    74,    -1,    75,    -1,    76,    -1,    77,
      -1,    78,    -1,    79,    -1,    80,    -1,    81,    -1,    82,
      -1,    57,    -1,    58,    -1,    59,    -1,    60,    -1,    61,
      -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,    66,
      -1,    67,    -1,    68,    -1,    69,    -1,    83,    -1,    84,
      -1,    85,    -1,    86,    -1,    87,    -1,    88,    -1,    89,
      -1,    90,    -1,    91,    -1,    92,    -1,    93,    -1,    94,
      -1,    95,    -1,   166,    -1,     3,    -1,   167,   168,   152,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   203,   203,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   289,   294,   302
};
#endif

#if SLANG_DEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "FLOATCONSTANT",
  "DOUBLECONSTANT", "INTCONSTANT", "UINTCONSTANT", "TRUE_VALUE",
  "FALSE_VALUE", "TRANSLATION_UNIT", "VARIABLE_DECL", "TYPE_SPECIFIER",
  "VOID", "CONST", "CBUFFER", "BUFFER", "BOOL", "BOOL2", "BOOL3", "BOOL4",
  "BOOL2X2", "BOOL2X3", "BOOL2X4", "BOOL3X2", "BOOL3X3", "BOOL3X4",
  "BOOL4X2", "BOOL4X3", "BOOL4X4", "INT", "INT2", "INT3", "INT4", "INT2X2",
  "INT2X3", "INT2X4", "INT3X2", "INT3X3", "INT3X4", "INT4X2", "INT4X3",
  "INT4X4", "UINT", "UINT2", "UINT3", "UINT4", "UINT2X2", "UINT2X3",
  "UINT2X4", "UINT3X2", "UINT3X3", "UINT3X4", "UINT4X2", "UINT4X3",
  "UINT4X4", "DWORD", "HALF", "HALF2", "HALF3", "HALF4", "HALF2X2",
  "HALF2X3", "HALF2X4", "HALF3X2", "HALF3X3", "HALF3X4", "HALF4X2",
  "HALF4X3", "HALF4X4", "FLOAT", "FLOAT2", "FLOAT3", "FLOAT4", "FLOAT2X2",
  "FLOAT2X3", "FLOAT2X4", "FLOAT3X2", "FLOAT3X3", "FLOAT3X4", "FLOAT4X2",
  "FLOAT4X3", "FLOAT4X4", "DOUBLE", "DOUBLE2", "DOUBLE3", "DOUBLE4",
  "DOUBLE2X2", "DOUBLE2X3", "DOUBLE2X4", "DOUBLE3X2", "DOUBLE3X3",
  "DOUBLE3X4", "DOUBLE4X2", "DOUBLE4X3", "DOUBLE4X4", "VECTOR", "MATRIX",
  "SAMPLER", "SAMPLER1D", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE",
  "SAMPLERSTATE", "SAMPLER_STATE", "TEXTURE1D", "TEXTURE1DARRAY",
  "TEXTURE2D", "TEXTURE2DARRAY", "TEXTURE3D", "TEXTURE3DARRAY",
  "TEXTURECUBE", "STRUCT", "LINEAR_MODIFIER", "CENTROID_MODIFIER",
  "NOINTERPOLATION_MODIFIER", "NOPERSPECTIVE_MODIFIER", "SAMPLE_MODIFIER",
  "TYPEDEF", "LEFT_OP", "RIGHT_OP", "INC_OP", "DEC_OP", "LE_OP", "GE_OP",
  "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "XOR_OP", "MUL_ASSIGN",
  "DIV_ASSIGN", "ADD_ASSIGN", "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "SUB_ASSIGN", "PLUS", "DASH",
  "PERCENT", "STAR", "SLASH", "TILDE", "BANG", "CARET", "LEFT_PAREN",
  "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "SEMICOLON", "LEFT_ANGLE",
  "RIGHT_ANGLE", "DOT", "COMMA", "LEFT_BRACKET", "RIGHT_BRACKET",
  "VERTICAL_BAR", "COLON", "EQUAL", "AMPERSAND", "QUESTION", "$accept",
  "root", "type_specifier", "full_type_specifier", "variable_identifier",
  "variable_decl", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
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
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   164,   165,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   167,   168,   169
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
       0,    82,     0,     2,     1,    83,     0,    84
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    80,    81,    82,    86,    83
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -150
static const yytype_int16 yypact[] =
{
     -13,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
       1,  -150,    -1,  -150,  -150,  -150,  -149,  -150
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -150,  -150,  -150,  -150,  -150,  -150
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       1,    84,    85,    87,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-150)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      13,     0,     3,   152,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
     165,   166,   167,   169,     0,     3,   168,   152
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if SLANG_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !SLANG_DEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !SLANG_DEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
/* Line 1792 of yacc.c  */
#line 207 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(VOID); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 208 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 209 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL2); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 210 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL3); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 211 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL4); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 212 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL2X2); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 213 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL2X3); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 214 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL2X4); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 215 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL3X2); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 216 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL3X3); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 217 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL3X4); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 218 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL4X2); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 219 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL4X3); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 220 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(BOOL4X4); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 221 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 222 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT2); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 223 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT3); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 224 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT4); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 225 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT2X2); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 226 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT2X3); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 227 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT2X4); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 228 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT3X2); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 229 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT3X3); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 230 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT3X4); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 231 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT4X2); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 232 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT4X3); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 233 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(INT4X4); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 234 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 235 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT2); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 236 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT3); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 237 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT4); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 238 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT2X2); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 239 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT2X3); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 240 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT2X4); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 241 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT3X2); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 242 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT3X3); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 243 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT3X4); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 244 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT4X2); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 245 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT4X3); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 246 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(UINT4X4); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 247 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 248 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT2); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 249 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT3); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 250 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT4); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 251 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT2X2); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 252 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT2X3); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 253 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT2X4); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 254 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT3X2); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 255 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT3X3); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 256 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT3X4); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 257 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT4X2); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 258 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT4X3); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 259 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(FLOAT4X4); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 260 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 261 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF2); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 262 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF3); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 263 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF4); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 264 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF2X2); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 265 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF2X3); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 266 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF2X4); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 267 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF3X2); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 268 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF3X3); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 269 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF3X4); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 270 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF4X2); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 271 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF4X3); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 272 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(HALF4X4); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 273 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 274 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE2); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 275 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE3); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 276 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE4); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 277 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE2X2); }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 278 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE2X3); }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 279 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE2X4); }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 280 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE3X2); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 281 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE3X3); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 282 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE3X4); }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 283 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE4X2); }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 284 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE4X3); }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 285 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(DOUBLE4X4); }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 289 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(TYPE_SPECIFIER, (yyvsp[(1) - (1)].struct slang_node*)); }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 294 "slang.y"
    { (yyval.struct slang_node*) = new_glsl_identifier((yyvsp[(1) - (1)].char *)); }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 302 "slang.y"
    { (yyval.struct slang_node*) = new_slang_node(VARIABLE_DECL, (yyvsp[(1) - (3)].struct slang_node*), (yyvsp[(2) - (3)].struct slang_node*)); }
    break;


/* Line 1792 of yacc.c  */
#line 2158 "slang.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 307 "slang.y"


void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}
int yywrap() {
   // open next reference or source file and start scanning
   //if((yyin = compiler->getNextFile()) != NULL) {
   //   line = 0; // reset line counter for next source file
   //   return 0;
   //}
   return 1;
}

int main(int argc, char** argv) {
    static const char argopts[] = "v";
    struct option long_options[] = {
        { "verbose", no_argument, NULL, (int)'v' },
        { NULL, 0, NULL, 0 }
    };
    int verbose = 0;
    int option_index = 0;
    int c;
    while ((c = gop_getopt_long(argc, argv, argopts, long_options, &option_index)) != -1) {
        switch(c) {
        case 'v': verbose = 1; break;
        case '?':
            if (strchr(argopts, optopt))
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isalpha(optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            exit(-1);
        }
    }

    /* For any remaining command line arguments (not options). */
    while (optind < argc) {
        yyin = fopen(argv[optind], "rb");
        break;
        //out_opts->inputFiles_.push_back(argv[optind++]);
    }

    if (!yyin) {
        fprintf(stderr, "Cannot open input file %s", argv[optind]);
        exit(-2);
    }

    // parse through the input until there is no more:
    do {
        yyparse();
    } while (!feof(yyin));

    fclose(yyin);
}