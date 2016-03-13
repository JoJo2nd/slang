%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slang.h"


#define YY_EXTRA_TYPE slang_parse_context_t*
#define YY_USER_ACTION yylloc->first_line = yylineno;

#define YYSTYPE SLANG_STYPE
#define YYLTYPE SLANG_LTYPE

#include "slang.tab.h"

int slang_get_lineno (yyscan_t yyscanner );
int slang_get_column  (yyscan_t yyscanner );

int slang_lex(SLANG_STYPE* lvalp, SLANG_LTYPE* llocp, void* scanner);
void slang_error(SLANG_LTYPE* locp, slang_parse_context_t* context, const char* err) {
	fprintf(stderr, "ERROR: %s:(%d:%d)", err, slang_get_lineno(context->scanner), slang_get_column(context->scanner));
}

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

whitespace          [ \t]+
digit               [0-9]
nondigit            [_a-zA-Z]
identifier          {nondigit}({nondigit}|{digit})*
integer_constant    {digit}+
floating_constant   {digit}+\.{digit}+

%%

void        return VOID;

const       return CONST;
static		return STATIC;

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

return		return RETURN;

cbuffer     return CBUFFER;
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

struct return STRUCT;

linear  return LINEAR_MODIFIER;
centroid return CENTROID_MODIFIER;
nointerpolation return NOINTERPOLATION_MODIFIER;
noperspective return NOPERSPECTIVE_MODIFIER;
sample return SAMPLE_MODIFIER;

typedef return TYPEDEF;

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

\+ return PLUS;
\- return DASH;
\% return PERCENT;
\* return STAR;
\/ return SLASH;
\~ return TILDE;
\! return BANG;
\^ return CARET;
\( return LEFT_PAREN;
\) return RIGHT_PAREN;
\{ return LEFT_BRACE;
\} return RIGHT_BRACE;
\; return SEMICOLON;
\< return LEFT_ANGLE;
\> return RIGHT_ANGLE;
\. return DOT;
\, return COMMA;
\[ return LEFT_BRACKET;
\] return RIGHT_BRACKET;
\| return VERTICAL_BAR;
\: return COLON;
\= return EQUAL;
\& return AMPERSAND;
\? return QUESTION;

true            { return TRUE_VALUE; }
false           { return FALSE_VALUE; }

{identifier}        { yylval->ident = strdup(yytext); return IDENTIFIER; }
{integer_constant}  { yylval->intConst = atoi(yytext); return INTCONSTANT; }
{floating_constant} { yylval->floatConst = atof(yytext); return FLOATCONSTANT; }

%%