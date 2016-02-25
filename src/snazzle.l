%{
#include "snazzle.tab.h"  // to get the token types that we return
%}
%%

%option reentrant
%option bison-bridge
%option bison-locations
%option yylineno
%option noyywrap


whitespace          [ \t]+
digit               [0-9]
nondigit            [_a-zA-Z]
identifier          {nondigit}({nondigit}|{digit})*
integer_constant    {digit}+
floating_constant   {digit}+\.{digit}+

%%


const       return CONST;
cbuffer     return CBUFFER;
// Buffer<float4>
Buffer      return BUFFER;
// Scalar types
bool        return BOOL;
int         return INT;
uint        return UINT;
dword       return DWORD;
half        return HALF;
float       return FLOAT;
double      return DOUBLE;
// TODO: to min types e.g. min10float

// Vector types
vector      return VECTOR;
matrix      return MATRIX;

// sampler
sampler     return SAMPLER;
sampler1D   return SAMPLER1D;
sampler2D   return SAMPLER2D;
sampler3D   return SAMPLER3D;
samplerCUBE return SAMPLERCUBE;
SamplerState return SAMPLERSTATE;
sampler_state return SAMPLER_STATE;

// texture types
texture1D   return TEXTURE1D;
texture1DArray return TEXTURE1DARRAY;
texture2D   return TEXTURE2D;
texture2DArray return TEXTURE2DARRAY;
texture3D   return TEXTURE3D;
texture3DArray return TEXTURE3DARRAY;
textureCube return TEXTURECUBE;

struct return STRUCT;

// Interpolation modifiers
linear  return LINEAR_MODIFIER;
centroid return CENTROID_MODIFIER;
nointerpolation return NOINTERPOLATION_MODIFIER;
noperspective return NOPERSPECTIVE_MODIFIER;
sample return SAMPLE_MODIFIER;

typedef return TYPEDEF;
