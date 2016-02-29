/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
