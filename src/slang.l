%{
/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slang.h"
#include "sym_table.h"


#define YY_EXTRA_TYPE slang_parse_context_t*
#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }

#define YYSTYPE SLANG_STYPE
#define YYLTYPE SLANG_LTYPE

#include "slang.tab.h"

int slang_get_lineno (yyscan_t yyscanner );
int slang_get_column  (yyscan_t yyscanner );

int slang_lex(SLANG_STYPE* lvalp, SLANG_LTYPE* llocp, void* scanner);
void slang_error(SLANG_LTYPE* locp, slang_parse_context_t* context, const char* err);

void skip_comment(yyscan_t yyscanner, slang_parse_context_t* context);

#ifdef _MSC_VER
#   pragma warning( disable : 4996 )
#endif

%}

/*prefix with slang_ instead of yy*/
%option prefix="slang_"
/*Generate yylval*/
%option bison-bridge bison-locations
/*Easy to guess but changes API*/
%option reentrant
%option noyywrap
/* Want line no support*/
%option yylineno

ES                  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS                  [ \t\v\n\f]
whitespace          {WS}+
L                   [a-zA-Z_]
A                   [a-zA-Z_0-9]
digit               [0-9]
nondigit            [_a-zA-Z]
identifier          {L}{A}*
integer_constant    {digit}+
floating_constant   {digit}+\.{digit}+

%%

"//".*                                    { /* consume //-comment TODO: /* style comments... */ }
"/*"									  { skip_comment(yyscanner, yyextra); }

(\"([^"\\\n]|{ES})*\"{WS}*)+   { yylval->strLiteral = strdup(yytext); return STRING_LITERAL; }

vs return VS;
ps return PS;
cs return CS;

void        return VOID;

for			return FOR;
if			return IF;
else		return ELSE;
do			return DO;
while		return WHILE;

switch		return SWITCH;
case		return CASE;
default		return DEFAULT;

break		return BREAK;
continue	return CONTINUE;
discard		return DISCARD;

inline      return INLINE;
return		return RETURN;

Buffer      return BUFFER;
bool        return BOOL;
bool2       return BOOL2;
bool3       return BOOL3;
bool4       return BOOL4;
bool2x2     return BOOL2X2;
bool2x3     return BOOL2X3;
bool2x4     return BOOL2X4;
bool3x2     return BOOL3X2;
bool3x3     return BOOL3X3;
bool3x4     return BOOL3X4;
bool4x2     return BOOL4X2;
bool4x3     return BOOL4X3;
bool4x4     return BOOL4X4;
int         return INT;
int2        return INT2;
int3        return INT3;
int4        return INT4;
int2x2      return INT2X2;
int2x3      return INT2X3;
int2x4      return INT2X4;
int3x2      return INT3X2;
int3x3      return INT3X3;
int3x4      return INT3X4;
int4x2      return INT4X2;
int4x3      return INT4X3;
int4x4      return INT4X4;
uint        return UINT;
uint2       return UINT2;
uint3       return UINT3;
uint4       return UINT4;
uint2x2     return UINT2X2;
uint2x3     return UINT2X3;
uint2x4     return UINT2X4;
uint3x2     return UINT3X2;
uint3x3     return UINT3X3;
uint3x4     return UINT3X4;
uint4x2     return UINT4X2;
uint4x3     return UINT4X3;
uint4x4     return UINT4X4;
dword       return DWORD;
half        return HALF;
half2       return HALF2;
half3       return HALF3;
half4       return HALF4;
half2x2     return HALF2X2;
half2x3     return HALF2X3;
half2x4     return HALF2X4;
half3x2     return HALF3X2;
half3x3     return HALF3X3;
half3x4     return HALF3X4;
half4x2     return HALF4X2;
half4x3     return HALF4X3;
half4x4     return HALF4X4;
float       return FLOAT;
float2      return FLOAT2;
float3      return FLOAT3;
float4      return FLOAT4;
float2x2    return FLOAT2X2;
float2x3    return FLOAT2X3;
float2x4    return FLOAT2X4;
float3x2    return FLOAT3X2;
float3x3    return FLOAT3X3;
float3x4    return FLOAT3X4;
float4x2    return FLOAT4X2;
float4x3    return FLOAT4X3;
float4x4    return FLOAT4X4;
double      return DOUBLE;
double2     return DOUBLE2;
double3     return DOUBLE3;
double4     return DOUBLE4;
double2x2   return DOUBLE2X2;
double2x3   return DOUBLE2X3;
double2x4   return DOUBLE2X4;
double3x2   return DOUBLE3X2;
double3x3   return DOUBLE3X3;
double3x4   return DOUBLE3X4;
double4x2   return DOUBLE4X2;
double4x3   return DOUBLE4X3;
double4x4   return DOUBLE4X4;

string      return STRING;

vector      return VECTOR;
matrix      return MATRIX;

sampler     return SAMPLER;
sampler1D   return SAMPLER1D;
sampler2D   return SAMPLER2D;
sampler3D   return SAMPLER3D;
samplerCUBE return SAMPLERCUBE;
SamplerState return SAMPLERSTATE;
sampler_state return SAMPLER_STATE;

texture1D   return TEXTURE1D;
texture1DArray return TEXTURE1DARRAY;
texture2D   return TEXTURE2D;
texture2DArray return TEXTURE2DARRAY;
texture3D   return TEXTURE3D;
texture3DArray return TEXTURE3DARRAY;
textureCube return TEXTURECUBE;

struct   return STRUCT;
cbuffer  return CBUFFER;
tbuffer  return TBUFFER;

extern return EXTERN;
precise return PRECISE;
shared return SHARED;
groupshared return GROUPSHARED;
static return STATIC;
uniform return UNIFORM;
volatile return VOLATILE;

const return CONST;
row_major return ROW_MAJOR;
column_major return COLUMN_MAJOR;

linear  return LINEAR;
centroid return CENTROID;
nointerpolation return NOINTERPOLATION;
noperspective return NOPERSPECTIVE;
sample return SAMPLE;

typedef return TYPEDEF;

register return REGISTER;
semantic return SEMANTIC;

\<\< return LEFT_OP;
\>\> return RIGHT_OP;
\+\+ return INC_OP;
\-\- return DEC_OP;
\<\= return LE_OP;
\>\= return GE_OP;
\=\= return EQ_OP;
\!\= return NE_OP;
\&\& return AND_OP;
\|\| return OR_OP;
\^\^ return XOR_OP;
\*\= return MUL_ASSIGN;
\/\= return DIV_ASSIGN;
\+\= return ADD_ASSIGN;
\%\= return MOD_ASSIGN;
\<\<\= return LEFT_ASSIGN;
\>\>\= return RIGHT_ASSIGN;
\&\= return AND_ASSIGN;
\^\= return XOR_ASSIGN;
\|\= return OR_ASSIGN;
\-\= return SUB_ASSIGN;

\+ return '+';
\- return '-';
\% return '%';
\* return '*';
\/ return '/';
\~ return '~';
\! return '!';
\^ return '^';
\( return '(';
\) return ')';
\{ return '{';
\} return '}';
\; return ';';
\< return '<';
\> return '>';
\. return '.';
\, return ',';
\[ return '[';
\] return ']';
\| return '|';
\: return ':';
\= return '=';
\& return '&';
\? return '?';

true            { return TRUE_VALUE; }
false           { return FALSE_VALUE; }

{identifier}        { yylval->ident = strdup(yytext); return slang_sym_table_check(yytext); }
{integer_constant}  { yylval->intConst = atoi(yytext); return INTCONSTANT; }
{floating_constant} { yylval->floatConst = atof(yytext); return FLOATCONSTANT; }

\n					{ /*++yyg->yylineno_r;*/  }
{WS}+               { /* whitespace separates tokens */ }
.                   { /* discard bad characters */ }

%%

void slang_error(SLANG_LTYPE* locp, slang_parse_context_t* context, const char* err) {
	struct yyguts_t * yyg = (struct yyguts_t*)context->scanner;
    fprintf(stderr, "ERROR: %s around '%s' (%d:%d)\n", err, yytext, locp->first_line, locp->first_column);
}

void skip_comment(yyscan_t yyscanner, slang_parse_context_t* context) {
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
    int c;
    while ((c = input(yyscanner)) != 0) {
        if (c == '*') {
            while ((c = input(yyscanner)) == '*');

            if (c == '/') return;
        }
        if (c == 0) break;
    }
    slang_error(yylloc, context, "EOF in comment");
}
