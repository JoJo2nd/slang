%{
/*

In 1985, Jeff Lee published his Yacc grammar based on a draft version of the ANSI C standard, along with a supporting Lex specification. Tom Stockfisch reposted those files to net.sources in 1987; as mentioned in the answer to '?' 17.25 of the comp.lang.c FAQ, they used to be available from ftp.uu.net as usenet/net.sources/ansi.c.grammar.Z.

The version you see here has been updated based on the 2011 ISO C standard. (The previous version's Lex and Yacc files for ANSI C9X still exist as archived copies.)

This grammar assumes that translation phases 1..5 have already been completed, including preprocessing and _Pragma processing. The Lex rule for string literals will perform concatenation (translation phase 6). Transliteration of universal character names (\uHHHH or \UHHHHHHHH) must have been done by either the preprocessor or a replacement for the input() macro used by Lex (or the YY_INPUT function used by Flex) to read characters. Although comments should have been changed to space characters during translation phase 3, there are Lex rules for them anyway.

I want to keep this version as close to the current C Standard grammar as possible; please let me know if you discover discrepancies.
(There is an FAQ for this grammar that you might want to read first.)

jutta@pobox.com, 2012

Last edit: 2012-12-18 DAGwyn@aol.com

The grammer here is largely based on Jeff Lee's grammer. Credit where credit due.

*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "slang.h"
#include "slang.tab.h"
#include "slang.yy.h"

void slang_error(SLANG_LTYPE* locp, slang_parse_context_t* context, const char* err);

#define scanner context->scanner

%}

%defines
// prefix generated functions
%define api.prefix slang_
// make the parser re-entrant
%define api.pure full
%parse-param { slang_parse_context_t* context }
%lex-param { void * scanner }
%locations
// easier debugging (...sometimes)
//%no-lines

%union {
	struct slang_node* node;
	char* ident;
    char* strLiteral;
	int intConst;
	float floatConst;
    register_const_t regConst;
}

/*
%type <node> translation_unit external_declaration function_definition declaration_specifiers type_qualifier type_qualifier_list
%type <node> storage_class_specifier type_specifier assignment_operator declarator direct_declarator constant expression
%type <node> primary_expression postfix_expression assignment_expression conditional_expression unary_expression unary_operator
%type <node> cast_expression multiplicative_expression additive_expression shift_expression relational_expression '='ity_expression
%type <node> and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> compound_statement block_item_list block_item declaration statement initializer initializer_list declaration_list
%type <node> identifier_list parameter_type_list type_name abstract_declarator direct_abstract_declarator init_declarator_list
%type <node> parameter_list parameter_declaration init_declarator argument_expression_list specifier_qualifier_list 
%type <node> expression_statement selection_statement iteration_statement jump_statement labeled_statement constant_expression
%type <node> struct_or_cbuffer_specifier struct_or_cbuffer struct_declaration_list struct_declarator_list struct_declaration 
%type <node> struct_declarator semantic
*/

%type <node> translation_unit
%type <node> external_declaration declaration

%type <node> variable_declaration 
%type <node> scalar_type_specifier
%type <node> storage_class storage_class_list type_modifier type_modifier_list type_specifier full_type_specifier
%type <node> semantic register register_list shader_profile pack_offset single_swizzle_mask
%type <node> annotations full_annotation_type_specifier annotation_type_specifier annotation_declaration_list annotation_declaration annotation_declaration_assignment annotation_initializer_list annotation_initializer
%type <node> cbuffer_or_tbuffer_declaration cbuffer_or_tbuffer
%type <node> interpolation_modifier interpolation_modifier_list 
%type <node> full_struct_member_type_specifier struct_member_declaration struct_member_declaration_list 

%token <ident> IDENTIFIER
%token <floatConst> FLOATCONSTANT
%token <double> DOUBLECONSTANT
%token <intConst> INTCONSTANT
%token <unsigned int> UINTCONSTANT
%token <regConst> REGISTERCONSTANT
%token <strLiteral> STRING_LITERAL
%token TRUE_VALUE
%token FALSE_VALUE

%token SWIZZLEMASK_X___
%token SWIZZLEMASK__Y__
%token SWIZZLEMASK___Z_
%token SWIZZLEMASK____W

%token SWIZZLEMASK_R___
%token SWIZZLEMASK__G__
%token SWIZZLEMASK___B_
%token SWIZZLEMASK____A

%token VOID
%token FOR
%token IF
%token ELSE
%token DO
%token WHILE
%token CASE
%token DEFAULT
%token BREAK
%token CONTINUE
%token DISCARD
%token SWITCH
%token RETURN

%token STRUCT
%token CBUFFER
%token TBUFFER

%token BUFFER
%token BOOL
%token BOOL2
%token BOOL3
%token BOOL4
%token BOOL2X2
%token BOOL2X3
%token BOOL2X4
%token BOOL3X2
%token BOOL3X3
%token BOOL3X4
%token BOOL4X2
%token BOOL4X3
%token BOOL4X4
%token INT
%token INT2
%token INT3
%token INT4
%token INT2X2
%token INT2X3
%token INT2X4
%token INT3X2
%token INT3X3
%token INT3X4
%token INT4X2
%token INT4X3
%token INT4X4
%token UINT
%token UINT2
%token UINT3
%token UINT4
%token UINT2X2
%token UINT2X3
%token UINT2X4
%token UINT3X2
%token UINT3X3
%token UINT3X4
%token UINT4X2
%token UINT4X3
%token UINT4X4
%token DWORD
%token HALF
%token HALF2
%token HALF3
%token HALF4
%token HALF2X2
%token HALF2X3
%token HALF2X4
%token HALF3X2
%token HALF3X3
%token HALF3X4
%token HALF4X2
%token HALF4X3
%token HALF4X4
%token FLOAT
%token FLOAT2
%token FLOAT3
%token FLOAT4
%token FLOAT2X2
%token FLOAT2X3
%token FLOAT2X4
%token FLOAT3X2
%token FLOAT3X3
%token FLOAT3X4
%token FLOAT4X2
%token FLOAT4X3
%token FLOAT4X4
%token DOUBLE
%token DOUBLE2
%token DOUBLE3
%token DOUBLE4
%token DOUBLE2X2
%token DOUBLE2X3
%token DOUBLE2X4
%token DOUBLE3X2
%token DOUBLE3X3
%token DOUBLE3X4
%token DOUBLE4X2
%token DOUBLE4X3
%token DOUBLE4X4
%token VECTOR
%token MATRIX
%token SAMPLER
%token SAMPLER1D
%token SAMPLER2D
%token SAMPLER3D
%token SAMPLERCUBE
%token SAMPLERSTATE
%token SAMPLER_STATE
%token TEXTURE1D
%token TEXTURE1DARRAY
%token TEXTURE2D
%token TEXTURE2DARRAY
%token TEXTURE3D
%token TEXTURE3DARRAY
%token TEXTURECUBE

%token STRING

%token LINEAR
%token CENTROID
%token NOINTERPOLATION
%token NOPERSPECTIVE
%token SAMPLE
%token TYPEDEF

%token EXTERN
%token PRECISE
%token SHARED
%token GROUPSHARED
%token STATIC
%token UNIFORM
%token VOLATILE

%token CONST
%token ROW_MAJOR
%token COLUMN_MAJOR

%token REGISTER
%token PACKOFFSET

%token LEFT_OP
%token RIGHT_OP
%token INC_OP
%token DEC_OP
%token LE_OP
%token GE_OP
%token EQ_OP
%token NE_OP
%token AND_OP
%token OR_OP
%token XOR_OP
%token MUL_ASSIGN
%token DIV_ASSIGN
%token ADD_ASSIGN
%token MOD_ASSIGN
%token LEFT_ASSIGN
%token RIGHT_ASSIGN
%token AND_ASSIGN
%token XOR_ASSIGN
%token OR_ASSIGN
%token SUB_ASSIGN

%token VS
%token PS
%token GS
%token DS
%token HS
%token CS_4_0
%token CS_4_1
%token CS_5_0
%token DS_5_0
%token GS_4_0
%token GS_4_1
%token GS_5_0
%token HS_5_0
%token LIB_4_0
%token LIB_4_1
%token LIB_4_0_LEVEL_9_1
%token LIB_4_0_LEVEL_9_3
%token LIB_5_0
%token PS_2_0
%token PS_2_A
%token PS_2_B
%token PS_2_SW
%token PS_3_0
%token PS_3_SW
%token PS_4_0
%token PS_4_0_LEVEL_9_1
%token PS_4_0_LEVEL_9_3
%token PS_4_0_LEVEL_9_0
%token PS_4_1
%token PS_5_0
%token TX_1_0
%token VS_1_1
%token VS_2_0
%token VS_2_A
%token VS_2_SW
%token VS_3_0
%token VS_3_SW
%token VS_4_0
%token VS_4_0_LEVEL_9_1
%token VS_4_0_LEVEL_9_3
%token VS_4_0_LEVEL_9_0
%token VS_4_1
%token VS_5_0

%token TRANSLATION_UNIT
%token FUNCTION_DEFINITION
%token ANNOTATION_LIST
%token INITIALIZER_LIST
%token STRUCT_MEMBER_DECLARATION_LIST

%token VARIABLE_DECL CBUFFER_TBUFFER_DECL BUFFER_MEMBER_DECLARATION

%token TYPE_SPECIFIER
%token STATEMENT_BLOCK
%token SEMANTIC
// typedef name and enumeration must be defined (but are they valid in HLSL?)
%token TYPEDEF_NAME ENUMERATION_CONSTANT
%token TERNARY_OPERATOR

%token NULL_NODE

%start translation_unit

%%

translation_unit
    : external_declaration { $$ = $1; context->root = $1; }
    | translation_unit external_declaration { context->root = $1; slang_node_make_sibling($1, $2); }
    ;

external_declaration
    : declaration ';' { $$ = $1; }
    ;

declaration
    : variable_declaration { $$ = $1; }
    | cbuffer_or_tbuffer_declaration { $$ = $1; }
    ;

variable_declaration
    : full_type_specifier IDENTIFIER register_list annotations {
        $$ = new_slang_var_decl($1, new_slang_identifier($2), NULL, $3, NULL, $4);
    }
    | full_type_specifier IDENTIFIER register_list {
		$$ = new_slang_var_decl($1, new_slang_identifier($2), NULL, $3, NULL, NULL);
    }
    | full_type_specifier IDENTIFIER semantic annotations{
		$$ = new_slang_var_decl($1, new_slang_identifier($2), $3, NULL, NULL, $4);
    }
    | full_type_specifier IDENTIFIER semantic {
        $$ = new_slang_var_decl($1, new_slang_identifier($2), $3, NULL, NULL, NULL);
    }
    | full_type_specifier IDENTIFIER annotations {
        $$ = new_slang_var_decl($1, new_slang_identifier($2), NULL, NULL, NULL, $3);
    }
    | full_type_specifier IDENTIFIER {
        $$ = new_slang_var_decl($1, new_slang_identifier($2), NULL, NULL, NULL, NULL);
    }
    ;

full_type_specifier
    : storage_class_list type_modifier_list type_specifier { $$ = $1; slang_node_attach_children($1, $2, $3, NULL); }
    | storage_class_list type_specifier { $$ = $1; slang_node_attach_child($1, $2); }
    | type_modifier_list type_specifier { $$ = $1; slang_node_attach_child($1, $2); }
    | type_specifier { $$ = $1; }
    ;

storage_class_list
    : storage_class { $$ = $1; }
    | storage_class_list storage_class { $$ = $1; slang_node_attach_child($1, $2); }
    ;

storage_class
    : EXTERN { $$ = new_slang_node(EXTERN); }
    | NOINTERPOLATION { $$ = new_slang_node(NOINTERPOLATION); }
    | PRECISE { $$ = new_slang_node(PRECISE); }
    | SHARED { $$ = new_slang_node(SHARED); }
    | GROUPSHARED { $$ = new_slang_node(GROUPSHARED); }
    | STATIC { $$ = new_slang_node(STATIC); }
    | UNIFORM { $$ = new_slang_node(UNIFORM); }
    | VOLATILE {} // volatile is ignored by HLSL 
    ;

type_modifier_list
    : type_modifier { $$ = $1; }
    | type_modifier_list type_modifier { $$ = $1; slang_node_attach_child($1, $2); }
    ;

type_modifier
    : CONST { $$ = new_slang_node(CONST); }
    | ROW_MAJOR { $$ = new_slang_node(ROW_MAJOR); }
    | COLUMN_MAJOR { $$ = new_slang_node(COLUMN_MAJOR); }
    ;

semantic
    : ':' IDENTIFIER { $$ = new_slang_semantic($2); }
    ;

register_list
    : register { $$ = $1; }
    | register_list register { $$ = $1; slang_node_attach_child($1, $2); }
    ;

register
    : ':' REGISTER '(' shader_profile ',' IDENTIFIER ')' { $$ = new_slang_node(REGISTER); slang_node_attach_children($$, $4, new_slang_register_constant($6), NULL); }
    | ':' REGISTER '(' IDENTIFIER ')' { $$ = new_slang_node(REGISTER); slang_node_attach_children($$, new_slang_register_constant($4), NULL); }
    ;

pack_offset
    : ':' PACKOFFSET '(' IDENTIFIER '.' single_swizzle_mask ')' { $$ = new_slang_node(PACKOFFSET); slang_node_attach_children($$, new_slang_register_constant($4), $6, NULL); }
    | ':' PACKOFFSET '(' IDENTIFIER ')' { $$ = new_slang_node(PACKOFFSET); slang_node_attach_child($$, new_slang_register_constant($4)); }
    ;

single_swizzle_mask
    : SWIZZLEMASK_X___ { $$ = new_slang_node('x'); }
    | SWIZZLEMASK__Y__ { $$ = new_slang_node('y'); }
    | SWIZZLEMASK___Z_ { $$ = new_slang_node('z'); }
    | SWIZZLEMASK____W { $$ = new_slang_node('w'); }
    | SWIZZLEMASK_R___ { $$ = new_slang_node('r'); }
    | SWIZZLEMASK__G__ { $$ = new_slang_node('g'); }
    | SWIZZLEMASK___B_ { $$ = new_slang_node('b'); }
    | SWIZZLEMASK____A { $$ = new_slang_node('a'); }
    ;

annotations
    : '<' annotation_declaration_list '>' { $$ = $2; }
    ;

annotation_declaration_list
    : annotation_declaration { $$ = new_slang_node(ANNOTATION_LIST); slang_node_attach_child($$, $1); }
    | annotation_declaration_list annotation_declaration { $$ = $1; slang_node_attach_child($1, $2); }
    ;

annotation_declaration
    : full_annotation_type_specifier IDENTIFIER '=' annotation_declaration_assignment ';' { 
        $$ = new_slang_node('='); 
        slang_node_attach_children($$, new_slang_var_decl($1, new_slang_identifier($2), NULL, NULL, NULL, NULL), $4, NULL);
    }
    ;

full_annotation_type_specifier
    : type_modifier_list annotation_type_specifier { $$ = $1; slang_node_attach_child($1, $2); }
    | annotation_type_specifier { $$ = $1; }
    ;

annotation_type_specifier
    : STRING { $$ = new_slang_node(STRING); }
    | scalar_type_specifier { $$ = $1; }
    ; 

annotation_declaration_assignment
    : scalar_type_specifier '(' annotation_initializer_list ')' { $$ = $1; slang_node_attach_child($1, $3); }
    | '{' annotation_initializer_list '}' { $$ = $2; }
    | annotation_initializer { $$ = $1; }
    | STRING_LITERAL { $$ = new_slang_string_literal($1); }
    ;

annotation_initializer_list
    : annotation_initializer { $$ = new_slang_node(INITIALIZER_LIST); slang_node_attach_child($$, $1); }
    | annotation_initializer_list ',' annotation_initializer { $$ = $1; slang_node_attach_child($1, $3); }
    ;

annotation_initializer
    : INTCONSTANT { $$ = new_slang_int_constant($1); }
    | FLOATCONSTANT { $$ = new_slang_float_constant($1); }
    ;

cbuffer_or_tbuffer_declaration
    : cbuffer_or_tbuffer IDENTIFIER register_list '{' '}' { $$ = new_slang_cbuffer_tbuffer_decl(new_slang_identifier($2), $3, NULL); }
    | cbuffer_or_tbuffer IDENTIFIER register_list '{' struct_member_declaration_list '}' { $$ = new_slang_cbuffer_tbuffer_decl(new_slang_identifier($2), $3, $5); }
    | cbuffer_or_tbuffer IDENTIFIER '{' '}' { $$ = new_slang_cbuffer_tbuffer_decl(new_slang_identifier($2), NULL, NULL); }
    | cbuffer_or_tbuffer IDENTIFIER '{' struct_member_declaration_list '}' { $$ = new_slang_cbuffer_tbuffer_decl(new_slang_identifier($2), NULL, $4); }
    ;

cbuffer_or_tbuffer
    : CBUFFER { $$ = new_slang_node(CBUFFER); }
    | TBUFFER { $$ = new_slang_node(TBUFFER); }
    ;

struct_member_declaration_list
    : struct_member_declaration { $$ = new_slang_node(STRUCT_MEMBER_DECLARATION_LIST); slang_node_attach_child($$, $1); }
    | struct_member_declaration_list struct_member_declaration { $$ = $1; slang_node_attach_child($1, $2); }
    ;

struct_member_declaration
    : full_struct_member_type_specifier IDENTIFIER semantic register_list ';' { $$ = new_slang_buffer_member_decl($1, new_slang_identifier($2), $3, $4, NULL); }
    | full_struct_member_type_specifier IDENTIFIER semantic pack_offset ';' { $$ = new_slang_buffer_member_decl($1, new_slang_identifier($2), $3, NULL, $4); }
    | full_struct_member_type_specifier IDENTIFIER register_list ';' { $$ = new_slang_buffer_member_decl($1, new_slang_identifier($2), NULL, $3, NULL); }
    | full_struct_member_type_specifier IDENTIFIER pack_offset ';' { $$ = new_slang_buffer_member_decl($1, new_slang_identifier($2), NULL, NULL, $3); }
    | full_struct_member_type_specifier IDENTIFIER semantic ';' { $$ = new_slang_buffer_member_decl($1, new_slang_identifier($2), $3, NULL, NULL); }
    | full_struct_member_type_specifier IDENTIFIER ';'{ $$ = new_slang_buffer_member_decl($1, new_slang_identifier($2), NULL, NULL, NULL); }
    ;

full_struct_member_type_specifier
    : interpolation_modifier_list full_type_specifier { $$ = $1; slang_node_attach_child($1, $2); }
    | full_type_specifier { $$ = $1; }
    ;

interpolation_modifier_list
    : interpolation_modifier { $$ = $1; }
    | interpolation_modifier_list interpolation_modifier { $$ = $1; slang_node_attach_child($1, $2); }
    ;

interpolation_modifier
    : LINEAR { $$ = new_slang_node(LINEAR); }
    | CENTROID { $$ = new_slang_node(CENTROID); }
    | NOINTERPOLATION { $$ = new_slang_node(NOINTERPOLATION); }
    | NOPERSPECTIVE { $$ = new_slang_node(NOPERSPECTIVE); }
    | SAMPLE { $$ = new_slang_node(SAMPLE); }
    ;

scalar_type_specifier
    : VOID { $$ = new_slang_node(VOID); }
    | BOOL { $$ = new_slang_node(BOOL); }
    | BOOL2 { $$ = new_slang_node(BOOL2); }
    | BOOL3 { $$ = new_slang_node(BOOL3); }
    | BOOL4 { $$ = new_slang_node(BOOL4); }
    | BOOL2X2 { $$ = new_slang_node(BOOL2X2); }
    | BOOL2X3 { $$ = new_slang_node(BOOL2X3); }
    | BOOL2X4 { $$ = new_slang_node(BOOL2X4); }
    | BOOL3X2 { $$ = new_slang_node(BOOL3X2); }
    | BOOL3X3 { $$ = new_slang_node(BOOL3X3); }
    | BOOL3X4 { $$ = new_slang_node(BOOL3X4); }
    | BOOL4X2 { $$ = new_slang_node(BOOL4X2); }
    | BOOL4X3 { $$ = new_slang_node(BOOL4X3); }
    | BOOL4X4 { $$ = new_slang_node(BOOL4X4); }
    | INT { $$ = new_slang_node(INT); }
    | INT2 { $$ = new_slang_node(INT2); }
    | INT3 { $$ = new_slang_node(INT3); }
    | INT4 { $$ = new_slang_node(INT4); }
    | INT2X2 { $$ = new_slang_node(INT2X2); }
    | INT2X3 { $$ = new_slang_node(INT2X3); }
    | INT2X4 { $$ = new_slang_node(INT2X4); }
    | INT3X2 { $$ = new_slang_node(INT3X2); }
    | INT3X3 { $$ = new_slang_node(INT3X3); }
    | INT3X4 { $$ = new_slang_node(INT3X4); }
    | INT4X2 { $$ = new_slang_node(INT4X2); }
    | INT4X3 { $$ = new_slang_node(INT4X3); }
    | INT4X4 { $$ = new_slang_node(INT4X4); }
    | UINT { $$ = new_slang_node(UINT); }
    | UINT2 { $$ = new_slang_node(UINT2); }
    | UINT3 { $$ = new_slang_node(UINT3); }
    | UINT4 { $$ = new_slang_node(UINT4); }
    | UINT2X2 { $$ = new_slang_node(UINT2X2); }
    | UINT2X3 { $$ = new_slang_node(UINT2X3); }
    | UINT2X4 { $$ = new_slang_node(UINT2X4); }
    | UINT3X2 { $$ = new_slang_node(UINT3X2); }
    | UINT3X3 { $$ = new_slang_node(UINT3X3); }
    | UINT3X4 { $$ = new_slang_node(UINT3X4); }
    | UINT4X2 { $$ = new_slang_node(UINT4X2); }
    | UINT4X3 { $$ = new_slang_node(UINT4X3); }
    | UINT4X4 { $$ = new_slang_node(UINT4X4); }
    | FLOAT { $$ = new_slang_node(FLOAT); }
    | FLOAT2 { $$ = new_slang_node(FLOAT2); }
    | FLOAT3 { $$ = new_slang_node(FLOAT3); }
    | FLOAT4 { $$ = new_slang_node(FLOAT4); }
    | FLOAT2X2 { $$ = new_slang_node(FLOAT2X2); }
    | FLOAT2X3 { $$ = new_slang_node(FLOAT2X3); }
    | FLOAT2X4 { $$ = new_slang_node(FLOAT2X4); }
    | FLOAT3X2 { $$ = new_slang_node(FLOAT3X2); }
    | FLOAT3X3 { $$ = new_slang_node(FLOAT3X3); }
    | FLOAT3X4 { $$ = new_slang_node(FLOAT3X4); }
    | FLOAT4X2 { $$ = new_slang_node(FLOAT4X2); }
    | FLOAT4X3 { $$ = new_slang_node(FLOAT4X3); }
    | FLOAT4X4 { $$ = new_slang_node(FLOAT4X4); }
    | HALF { $$ = new_slang_node(HALF); }
    | HALF2 { $$ = new_slang_node(HALF2); }
    | HALF3 { $$ = new_slang_node(HALF3); }
    | HALF4 { $$ = new_slang_node(HALF4); }
    | HALF2X2 { $$ = new_slang_node(HALF2X2); }
    | HALF2X3 { $$ = new_slang_node(HALF2X3); }
    | HALF2X4 { $$ = new_slang_node(HALF2X4); }
    | HALF3X2 { $$ = new_slang_node(HALF3X2); }
    | HALF3X3 { $$ = new_slang_node(HALF3X3); }
    | HALF3X4 { $$ = new_slang_node(HALF3X4); }
    | HALF4X2 { $$ = new_slang_node(HALF4X2); }
    | HALF4X3 { $$ = new_slang_node(HALF4X3); }
    | HALF4X4 { $$ = new_slang_node(HALF4X4); }
    | DOUBLE { $$ = new_slang_node(DOUBLE); }
    | DOUBLE2 { $$ = new_slang_node(DOUBLE2); }
    | DOUBLE3 { $$ = new_slang_node(DOUBLE3); }
    | DOUBLE4 { $$ = new_slang_node(DOUBLE4); }
    | DOUBLE2X2 { $$ = new_slang_node(DOUBLE2X2); }
    | DOUBLE2X3 { $$ = new_slang_node(DOUBLE2X3); }
    | DOUBLE2X4 { $$ = new_slang_node(DOUBLE2X4); }
    | DOUBLE3X2 { $$ = new_slang_node(DOUBLE3X2); }
    | DOUBLE3X3 { $$ = new_slang_node(DOUBLE3X3); }
    | DOUBLE3X4 { $$ = new_slang_node(DOUBLE3X4); }
    | DOUBLE4X2 { $$ = new_slang_node(DOUBLE4X2); }
    | DOUBLE4X3 { $$ = new_slang_node(DOUBLE4X3); }
    | DOUBLE4X4 { $$ = new_slang_node(DOUBLE4X4); }

type_specifier
    : scalar_type_specifier { $$ = $1; }
    //| struct_or_cbuffer_specifier { $$ = $1; }
    | IDENTIFIER { $$ = new_slang_identifier($1); }
    ;

shader_profile
    : VS { $$ = new_slang_node(VS); }
    | PS { $$ = new_slang_node(PS); }
    | GS { $$ = new_slang_node(GS); }
    | DS { $$ = new_slang_node(DS); }
    | HS { $$ = new_slang_node(HS); }
    | CS_4_0 { $$ = new_slang_node(CS_4_0); }
    | CS_4_1 { $$ = new_slang_node(CS_4_1); }
    | CS_5_0 { $$ = new_slang_node(CS_5_0); }
    | DS_5_0 { $$ = new_slang_node(DS_5_0); }
    | GS_4_0 { $$ = new_slang_node(GS_4_0); }
    | GS_4_1 { $$ = new_slang_node(GS_4_1); }
    | GS_5_0 { $$ = new_slang_node(GS_5_0); }
    | HS_5_0 { $$ = new_slang_node(HS_5_0); }
    | LIB_4_0 { $$ = new_slang_node(LIB_4_0); }
    | LIB_4_1 { $$ = new_slang_node(LIB_4_1); }
    | LIB_4_0_LEVEL_9_1 { $$ = new_slang_node(LIB_4_0_LEVEL_9_1); }
    | LIB_4_0_LEVEL_9_3 { $$ = new_slang_node(LIB_4_0_LEVEL_9_3); }
    | LIB_5_0 { $$ = new_slang_node(LIB_5_0); }
    | PS_2_0 { $$ = new_slang_node(PS_2_0); }
    | PS_2_A { $$ = new_slang_node(PS_2_A); }
    | PS_2_B { $$ = new_slang_node(PS_2_B); }
    | PS_2_SW { $$ = new_slang_node(PS_2_SW); }
    | PS_3_0 { $$ = new_slang_node(PS_3_0); }
    | PS_3_SW { $$ = new_slang_node(PS_3_SW); }
    | PS_4_0 { $$ = new_slang_node(PS_4_0); }
    | PS_4_0_LEVEL_9_1 { $$ = new_slang_node(PS_4_0_LEVEL_9_1); }
    | PS_4_0_LEVEL_9_3 { $$ = new_slang_node(PS_4_0_LEVEL_9_3); }
    | PS_4_0_LEVEL_9_0 { $$ = new_slang_node(PS_4_0_LEVEL_9_0); }
    | PS_4_1 { $$ = new_slang_node(PS_4_1); }
    | PS_5_0 { $$ = new_slang_node(PS_5_0); }
    | TX_1_0 { $$ = new_slang_node(TX_1_0); }
    | VS_1_1 { $$ = new_slang_node(VS_1_1); }
    | VS_2_0 { $$ = new_slang_node(VS_2_0); }
    | VS_2_A { $$ = new_slang_node(VS_2_A); }
    | VS_2_SW { $$ = new_slang_node(VS_2_SW); }
    | VS_3_0 { $$ = new_slang_node(VS_3_0); }
    | VS_3_SW { $$ = new_slang_node(VS_3_SW); }
    | VS_4_0 { $$ = new_slang_node(VS_4_0); }
    | VS_4_0_LEVEL_9_1 { $$ = new_slang_node(VS_4_0_LEVEL_9_1); }
    | VS_4_0_LEVEL_9_3 { $$ = new_slang_node(VS_4_0_LEVEL_9_3); }
    | VS_4_0_LEVEL_9_0 { $$ = new_slang_node(VS_4_0_LEVEL_9_0); }
    | VS_4_1 { $$ = new_slang_node(VS_4_1); }
    | VS_5_0 { $$ = new_slang_node(VS_5_0); }
    ;

/* Let's start again 
translation_unit
	: external_declaration { $$ = $1; context->root = $1; }
	| translation_unit external_declaration { context->root = $1; slang_node_attach_child($1, $2); }
	;

external_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; }
	;

compound_statement
	: '{' '}' { $$ = new_slang_node(NULL_NODE); }
	| '{'  block_item_list '}' { $$ = $2; }
	;

block_item
	: declaration { $$ = $1; }
	| statement { $$ = $1; }
	;

block_item_list
	: block_item { $$ = $1; }
	| block_item_list block_item { $$ = $1; slang_node_attach_child($1, $2); }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement { $$ = new_slang_node(FUNCTION_DEFINITION); slang_node_attach_children($$, $1, $2, $3, $4, NULL); }
	| declaration_specifiers declarator compound_statement { $$ = new_slang_node(FUNCTION_DEFINITION); slang_node_attach_children($$, $1, $2, $3, NULL); }
	;
	
declaration_list
	: declaration { $$ = $1; }
	| declaration_list declaration { $$ = $1; slang_node_attach_child($$, $2); }
	;

declaration
	: declaration_specifiers ';' { $$ = $1; }
	| declaration_specifiers init_declarator_list ';' { $$ = $1; slang_node_attach_child($1, $2); }
	;

declaration_specifiers
	: storage_class_specifier declaration_specifiers { $$ = $1; slang_node_attach_child($1, $2); }
	| storage_class_specifier { $$ = $1; }
	| type_specifier declaration_specifiers { $$ = $1; slang_node_attach_child($1, $2); }
	| type_specifier { $$ = $1; }
	| type_qualifier declaration_specifiers { $$ = $1; slang_node_attach_child($1, $2); }
	| type_qualifier { $$ = $1; }
	;

identifier_list
	: IDENTIFIER { $$ = new_slang_identifier($1); }
	| identifier_list ',' IDENTIFIER { $$ = $1; slang_node_attach_child($$, new_slang_identifier($3)); }
	;

parameter_type_list
	: parameter_list { $$ = $1; }
	;

parameter_list
	: parameter_declaration { $$ = $1; }
	| parameter_list ',' parameter_declaration { $$ = $1; slang_node_attach_child($1, $3); }
	;

parameter_declaration
	: declaration_specifiers declarator { $$ = $1; slang_node_attach_child($1, $2); }
	| declaration_specifiers abstract_declarator { $$ = $1; slang_node_attach_child($1, $2); }
	| declaration_specifiers { $$ = $1; }
	;

init_declarator_list
	: init_declarator { $$ = $1; }
	| init_declarator_list ',' init_declarator { $$ = $1; slang_node_attach_child($1, $3); }
	;

init_declarator
	: declarator '=' initializer { $$ = new_slang_node('='); slang_node_attach_children($$, $1, $3, NULL); }
	| declarator { $$ = $1; }
	;

initializer
	: '{' initializer_list '}' { $$ = $2; }
	| '{' initializer_list ',' '}' { $$ = $2; }
	| assignment_expression { $$ = $1; }
	;

initializer_list
	: initializer { $$ = $1; }
	| initializer_list ',' initializer { $$ = $1; slang_node_attach_child($1, $3); }
	;

struct_or_cbuffer_specifier
    : struct_or_cbuffer IDENTIFIER '{' struct_declaration_list '}' { $$ = $1; slang_node_attach_children($1, new_slang_identifier($2), $4, NULL); }
    | struct_or_cbuffer IDENTIFIER { $$ = $1; slang_node_attach_child($1, new_slang_identifier($2)); }
    ;

semantic
    : IDENTIFIER { $$ = new_slang_identifier($1); }
    ;

struct_or_cbuffer
    : STRUCT { $$ = new_slang_node(STRUCT); }
    | CBUFFER { $$ = new_slang_node(CBUFFER); }
    ;

struct_declaration_list
    : struct_declaration { $$ = $1; }
    | struct_declaration_list struct_declaration { $$ = $1; slang_node_attach_child($1, $2); }
    ;

struct_declaration
    : storage_class_specifier type_specifier IDENTIFIER ':' semantic ';' { $$ = $1; slang_node_attach_children($1, $2, new_slang_identifier($3), $5, NULL); }
    | type_specifier IDENTIFIER ':' semantic ';' { $$ = $1; slang_node_attach_children($1, new_slang_identifier($2), $4, NULL); }
    | type_specifier IDENTIFIER ';' { $$ = $1; slang_node_attach_children($1, new_slang_identifier($2), NULL); }
    ;
// prev
struct_declaration_list
    : struct_declaration { $$ = $1; }
    | struct_declaration_list struct_declaration { $$ = $1; slang_node_attach_child($1, $2); }
    ;

struct_declaration
    : specifier_qualifier_list struct_declarator_list ';' { $$ = $1; slang_node_attach_child($1, $2); }
    ;
// End prev
struct_declarator_list
    : struct_declarator { $$ = $1; }
    | struct_declarator_list ',' struct_declarator { $$ = $1; slang_node_attach_child($1, $3); }
    ;

struct_declarator
    : ':' constant_expression { $$ = $2; }
    | declarator ':' constant_expression { $$ = $1; slang_node_attach_child($1, $3); }
    | declarator { $$ = $1; }
    ;

type_qualifier
	: CONST { $$ = new_slang_node(CONST); }
	;

type_qualifier_list
	: type_qualifier { $$ = $1; }
	| type_qualifier_list type_qualifier { $$ = $1; slang_node_attach_child($1, $2); }
	;

storage_class_specifier
	: TYPEDEF { $$ = new_slang_node(TYPEDEF); } // identifiers must be flagged as TYPEDEF_NAME 
	| LINEAR_MODIFIER { $$ = new_slang_node(LINEAR_MODIFIER); }
	| CENTROID_MODIFIER { $$ = new_slang_node(CENTROID_MODIFIER); }
	| NOINTERPOLATION { $$ = new_slang_node(NOINTERPOLATION); }
	| NOPERSPECTIVE_MODIFIER { $$ = new_slang_node(NOPERSPECTIVE_MODIFIER); }
	| SAMPLE_MODIFIER { $$ = new_slang_node(SAMPLE_MODIFIER); }
	;

type_specifier
    : VOID { $$ = new_slang_node(VOID); }
    | BOOL { $$ = new_slang_node(BOOL); }
    | BOOL2 { $$ = new_slang_node(BOOL2); }
    | BOOL3 { $$ = new_slang_node(BOOL3); }
    | BOOL4 { $$ = new_slang_node(BOOL4); }
    | BOOL2X2 { $$ = new_slang_node(BOOL2X2); }
    | BOOL2X3 { $$ = new_slang_node(BOOL2X3); }
    | BOOL2X4 { $$ = new_slang_node(BOOL2X4); }
    | BOOL3X2 { $$ = new_slang_node(BOOL3X2); }
    | BOOL3X3 { $$ = new_slang_node(BOOL3X3); }
    | BOOL3X4 { $$ = new_slang_node(BOOL3X4); }
    | BOOL4X2 { $$ = new_slang_node(BOOL4X2); }
    | BOOL4X3 { $$ = new_slang_node(BOOL4X3); }
    | BOOL4X4 { $$ = new_slang_node(BOOL4X4); }
    | INT { $$ = new_slang_node(INT); }
    | INT2 { $$ = new_slang_node(INT2); }
    | INT3 { $$ = new_slang_node(INT3); }
    | INT4 { $$ = new_slang_node(INT4); }
    | INT2X2 { $$ = new_slang_node(INT2X2); }
    | INT2X3 { $$ = new_slang_node(INT2X3); }
    | INT2X4 { $$ = new_slang_node(INT2X4); }
    | INT3X2 { $$ = new_slang_node(INT3X2); }
    | INT3X3 { $$ = new_slang_node(INT3X3); }
    | INT3X4 { $$ = new_slang_node(INT3X4); }
    | INT4X2 { $$ = new_slang_node(INT4X2); }
    | INT4X3 { $$ = new_slang_node(INT4X3); }
    | INT4X4 { $$ = new_slang_node(INT4X4); }
    | UINT { $$ = new_slang_node(UINT); }
    | UINT2 { $$ = new_slang_node(UINT2); }
    | UINT3 { $$ = new_slang_node(UINT3); }
    | UINT4 { $$ = new_slang_node(UINT4); }
    | UINT2X2 { $$ = new_slang_node(UINT2X2); }
    | UINT2X3 { $$ = new_slang_node(UINT2X3); }
    | UINT2X4 { $$ = new_slang_node(UINT2X4); }
    | UINT3X2 { $$ = new_slang_node(UINT3X2); }
    | UINT3X3 { $$ = new_slang_node(UINT3X3); }
    | UINT3X4 { $$ = new_slang_node(UINT3X4); }
    | UINT4X2 { $$ = new_slang_node(UINT4X2); }
    | UINT4X3 { $$ = new_slang_node(UINT4X3); }
    | UINT4X4 { $$ = new_slang_node(UINT4X4); }
    | FLOAT { $$ = new_slang_node(FLOAT); }
    | FLOAT2 { $$ = new_slang_node(FLOAT2); }
    | FLOAT3 { $$ = new_slang_node(FLOAT3); }
    | FLOAT4 { $$ = new_slang_node(FLOAT4); }
    | FLOAT2X2 { $$ = new_slang_node(FLOAT2X2); }
    | FLOAT2X3 { $$ = new_slang_node(FLOAT2X3); }
    | FLOAT2X4 { $$ = new_slang_node(FLOAT2X4); }
    | FLOAT3X2 { $$ = new_slang_node(FLOAT3X2); }
    | FLOAT3X3 { $$ = new_slang_node(FLOAT3X3); }
    | FLOAT3X4 { $$ = new_slang_node(FLOAT3X4); }
    | FLOAT4X2 { $$ = new_slang_node(FLOAT4X2); }
    | FLOAT4X3 { $$ = new_slang_node(FLOAT4X3); }
    | FLOAT4X4 { $$ = new_slang_node(FLOAT4X4); }
    | HALF { $$ = new_slang_node(HALF); }
    | HALF2 { $$ = new_slang_node(HALF2); }
    | HALF3 { $$ = new_slang_node(HALF3); }
    | HALF4 { $$ = new_slang_node(HALF4); }
    | HALF2X2 { $$ = new_slang_node(HALF2X2); }
    | HALF2X3 { $$ = new_slang_node(HALF2X3); }
    | HALF2X4 { $$ = new_slang_node(HALF2X4); }
    | HALF3X2 { $$ = new_slang_node(HALF3X2); }
    | HALF3X3 { $$ = new_slang_node(HALF3X3); }
    | HALF3X4 { $$ = new_slang_node(HALF3X4); }
    | HALF4X2 { $$ = new_slang_node(HALF4X2); }
    | HALF4X3 { $$ = new_slang_node(HALF4X3); }
    | HALF4X4 { $$ = new_slang_node(HALF4X4); }
    | DOUBLE { $$ = new_slang_node(DOUBLE); }
    | DOUBLE2 { $$ = new_slang_node(DOUBLE2); }
    | DOUBLE3 { $$ = new_slang_node(DOUBLE3); }
    | DOUBLE4 { $$ = new_slang_node(DOUBLE4); }
    | DOUBLE2X2 { $$ = new_slang_node(DOUBLE2X2); }
    | DOUBLE2X3 { $$ = new_slang_node(DOUBLE2X3); }
    | DOUBLE2X4 { $$ = new_slang_node(DOUBLE2X4); }
    | DOUBLE3X2 { $$ = new_slang_node(DOUBLE3X2); }
    | DOUBLE3X3 { $$ = new_slang_node(DOUBLE3X3); }
    | DOUBLE3X4 { $$ = new_slang_node(DOUBLE3X4); }
    | DOUBLE4X2 { $$ = new_slang_node(DOUBLE4X2); }
    | DOUBLE4X3 { $$ = new_slang_node(DOUBLE4X3); }
    | DOUBLE4X4 { $$ = new_slang_node(DOUBLE4X4); }
    | struct_or_cbuffer_specifier { $$ = $1; }
    | IDENTIFIER { $$ = new_slang_identifier($1); }
    ;

assignment_operator
	: '=' { $$ = new_slang_node('='); }
	| MUL_ASSIGN { $$ = new_slang_node(MUL_ASSIGN); }
	| DIV_ASSIGN { $$ = new_slang_node(DIV_ASSIGN); }
	| MOD_ASSIGN { $$ = new_slang_node(MOD_ASSIGN); }
	| ADD_ASSIGN { $$ = new_slang_node(ADD_ASSIGN); }
	| SUB_ASSIGN { $$ = new_slang_node(SUB_ASSIGN); }
	| LEFT_ASSIGN { $$ = new_slang_node(LEFT_ASSIGN); }
	| RIGHT_ASSIGN { $$ = new_slang_node(RIGHT_ASSIGN); }
	| AND_ASSIGN { $$ = new_slang_node(AND_ASSIGN); }
	| XOR_ASSIGN { $$ = new_slang_node(XOR_ASSIGN); }
	| OR_ASSIGN { $$ = new_slang_node(OR_ASSIGN); }
	;

declarator
	: direct_declarator { $$ = $1; }
	// pointer direct_declarator // HLSL has no pointers
	;

direct_declarator
	: IDENTIFIER { $$ = new_slang_identifier($1); }
	| '(' declarator ')' { $$ = $2; }
	| direct_declarator '[' ']' { $$ = $1; }
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']' { $$ = $1; slang_node_attach_children($1, $4, $5, NULL); }
	| direct_declarator '[' STATIC assignment_expression ']' { $$ = $1; slang_node_attach_child($1, $4); }
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']' { $$ = $1; slang_node_attach_children($1, $3, $5, NULL); }
	| direct_declarator '[' type_qualifier_list assignment_expression ']' { $$ = $1; slang_node_attach_children($1, $3, $4, NULL); }
	| direct_declarator '[' type_qualifier_list ']' { $$ = $1; slang_node_attach_child($1, $3); }
	| direct_declarator '[' assignment_expression ']' { $$ = $1; slang_node_attach_child($1, $3); }
	| direct_declarator '(' parameter_type_list ')' { $$ = $1; slang_node_attach_child($1, $3); }
	| direct_declarator '(' ')' { $$ = $1; }
	| direct_declarator '(' identifier_list ')' { $$ = $1; slang_node_attach_child($1, $3); }
	// | direct_declarator '[' type_qualifier_list '*' ']'
	// | direct_declarator '[' '*' ']' // 
	;

constant
	: INTCONSTANT		{ $$ = new_slang_int_constant($1); }// includes character_constant 
	| FLOATCONSTANT		{ $$ = new_slang_float_constant($1); }
	//| ENUMERATION_CONSTANT	// Are ENUMS valid in HLSL?
	;

//string // HLSL doesn't do string literials (not in a normal way)
//	: STRING_LITERAL { $$ = new_slang_node() }
//	;


expression
	: assignment_expression { $$ = $1; }
	| expression ',' assignment_expression { $$ = $1; slang_node_attach_child($1, $3); }
	;

primary_expression
	: IDENTIFIER { $$ = new_slang_identifier($1); }
	| constant { $$ = $1; }
	| '(' expression ')' { $$ = $2; }
	;

argument_expression_list
	: assignment_expression { $$ = $1; }
	| argument_expression_list ',' assignment_expression { $$ = $1; slang_node_attach_child($1, $3); }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' { $$ = $1; slang_node_attach_child($1, $3); }
	| postfix_expression '(' ')' { $$ = $1; }
	| postfix_expression '(' argument_expression_list ')' { $$ = $1; slang_node_attach_child($1, $3); }
	| postfix_expression '.' IDENTIFIER { $$ = $1; slang_node_attach_children($1, new_slang_node('.'), new_slang_identifier($3), NULL); }
	| postfix_expression INC_OP { $$ = $1; slang_node_attach_child($1, new_slang_node(INC_OP)); }
	| postfix_expression DEC_OP { $$ = $1; slang_node_attach_child($1, new_slang_node(DEC_OP)); }
	| '(' type_name ')' '{' initializer_list '}' { $$ = $2; slang_node_attach_child($2, $5); }
	| '(' type_name ')' '{' initializer_list ',' '}' { $$ = $2; slang_node_attach_child($2, $5); }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression { $$ = $1; slang_node_attach_children($1, $2, $3, NULL); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { $$ = new_slang_node(TERNARY_OPERATOR); slang_node_attach_children($1, $3, $5, NULL); }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { $$ = new_slang_node(INC_OP); slang_node_attach_child($$, $2); }
	| DEC_OP unary_expression { $$ = new_slang_node(DEC_OP); slang_node_attach_child($$, $2); }
	| unary_operator cast_expression { $$ = $1; slang_node_attach_child($1, $2); }
	//| SIZEOF unary_expression
	//| SIZEOF '(' type_name ')'
	//| ALIGNOF '(' type_name ')'
	;

unary_operator
	: '&' { $$ = new_slang_node('&'); }
	| '*' { $$ = new_slang_node('*'); }
	| '+' { $$ = new_slang_node('+'); }
	| '-' { $$ = new_slang_node('-'); }
	| '~' { $$ = new_slang_node('~'); }
	| '!' { $$ = new_slang_node('!'); }
	;

cast_expression
	: unary_expression { $$ = $1; }
	| '(' type_name ')' cast_expression { $$ = $2; slang_node_attach_child($2, $4); }
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression { $$ = new_slang_node('*'); slang_node_attach_children($$, $1, $3, NULL); }
	| multiplicative_expression '/' cast_expression { $$ = new_slang_node('/'); slang_node_attach_children($$, $1, $3, NULL); }
	| multiplicative_expression '%' cast_expression { $$ = new_slang_node('%'); slang_node_attach_children($$, $1, $3, NULL); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = new_slang_node('+'); slang_node_attach_children($$, $1, $3, NULL); }
	| additive_expression '-' multiplicative_expression { $$ = new_slang_node('-'); slang_node_attach_children($$, $1, $3, NULL); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = new_slang_node(LEFT_OP); slang_node_attach_children($$, $1, $3, NULL); }
	| shift_expression RIGHT_OP additive_expression { $$ = new_slang_node(RIGHT_OP); slang_node_attach_children($$, $1, $3, NULL); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ = new_slang_node('<'); slang_node_attach_children($$, $1, $3, NULL); }
	| relational_expression '>' shift_expression { $$ = new_slang_node('>'); slang_node_attach_children($$, $1, $3, NULL); }
	| relational_expression LE_OP shift_expression { $$ = new_slang_node(LE_OP); slang_node_attach_children($$, $1, $3, NULL); }
	| relational_expression GE_OP shift_expression { $$ = new_slang_node(GE_OP); slang_node_attach_children($$, $1, $3, NULL); }
	;

'='ity_expression
	: relational_expression { $$ = $1; }
	| '='ity_expression EQ_OP relational_expression { $$ = new_slang_node(EQ_OP); slang_node_attach_children($$, $1, $3, NULL); }
	| '='ity_expression NE_OP relational_expression { $$ = new_slang_node(NE_OP); slang_node_attach_children($$, $1, $3, NULL); }
	;

and_expression
	: '='ity_expression { $$ = $1; }
	| and_expression '&' '='ity_expression { $$ = new_slang_node('&'); slang_node_attach_children($$, $1, $3, NULL); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression CARET and_expression { $$ = new_slang_node(CARET); slang_node_attach_children($$, $1, $3, NULL); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ = new_slang_node('|'); slang_node_attach_children($$, $1, $3, NULL); }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { $$ = new_slang_node(AND_OP); slang_node_attach_children($$, $1, $3, NULL); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression { $$ = new_slang_node(OR_OP); slang_node_attach_children($$, $1, $3, NULL); }
	;

type_name
	: specifier_qualifier_list abstract_declarator { $$ = $1; slang_node_attach_child($1, $2); }
	| specifier_qualifier_list { $$ = $1; }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list { $$ = $1; slang_node_attach_child($1, $2); }
	| type_specifier { $$ = $1; }
	| type_qualifier specifier_qualifier_list { $$ = $1; slang_node_attach_child($1, $2); }
	| type_qualifier { $$ = $1; }
	;

abstract_declarator
	: direct_abstract_declarator { $$ = $1; }
	//| pointer direct_abstract_declarator
	//| pointer
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' { $$ = $2; }
	| '[' ']' { $$ = new_slang_node(NULL_NODE); }
	//| '[' '*' ']'
	| '[' STATIC type_qualifier_list assignment_expression ']' { $$ = new_slang_node(STATIC); slang_node_attach_children($$, $3, $4, NULL); }
	| '[' STATIC assignment_expression ']' { $$ = new_slang_node(STATIC); slang_node_attach_children($$, $3, NULL); }
	| '[' type_qualifier_list STATIC assignment_expression ']' { $$ = $2; slang_node_attach_children($$, new_slang_node(STATIC), $4, NULL); }
	| '[' type_qualifier_list assignment_expression ']' { $$ = $2; slang_node_attach_child($$, $3); }
	| '[' type_qualifier_list ']' { $$ = $2; }
	| '[' assignment_expression ']' { $$ = $2; }
	| direct_abstract_declarator '[' ']' { $$ = $1; }
	//| direct_abstract_declarator '[' '*' ']'
	| direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']' { $$ = $1; slang_node_attach_children($$, new_slang_node(STATIC), $4, $5, NULL); }
	| direct_abstract_declarator '[' STATIC assignment_expression ']' { $$ = $1; slang_node_attach_children($$, new_slang_node(STATIC), $4, NULL); }
	| direct_abstract_declarator '[' type_qualifier_list assignment_expression ']' { $$ = $1; slang_node_attach_children($$, $3, $4, NULL); }
	| direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']' { $$ = $1; slang_node_attach_children($$, $3, new_slang_node(STATIC), $5, NULL); }
	| direct_abstract_declarator '[' type_qualifier_list ']' { $$ = $1; slang_node_attach_child($$, $3); }
	| direct_abstract_declarator '[' assignment_expression ']' { $$ = $1; slang_node_attach_child($$, $3); }
	| '(' ')' { $$ = new_slang_node(NULL_NODE); }
	| '(' parameter_type_list ')' { $$ = $2; }
	| direct_abstract_declarator '(' ')' { $$ = $1; }
	| direct_abstract_declarator '(' parameter_type_list ')' { $$ = $1; slang_node_attach_child($$, $3); }
	;

statement
	: labeled_statement { $$ = $1; }
	| compound_statement { $$ = $1; }
	| expression_statement { $$ = $1; }
	| selection_statement { $$ = $1; }
	| iteration_statement { $$ = $1; }
	| jump_statement { $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement { $$ = new_slang_identifier($1); slang_node_attach_child($$, $3); }
	| CASE constant_expression ':' statement { $$ = $2; slang_node_attach_child($$, $4); }
	| DEFAULT ':' statement { $$ = new_slang_node(DEFAULT); slang_node_attach_child($$, $3); }
	;

expression_statement
	: ';' { $$ = new_slang_node(NULL_NODE); }
	| expression ';' { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement ELSE statement { $$ = new_slang_node(IF); slang_node_attach_children($$, $3, $5, $7, NULL); }
	| IF '(' expression ')' statement { $$ = new_slang_node(IF); slang_node_attach_children($$, $3, $5, NULL); }
	| SWITCH '(' expression ')' statement { $$ = new_slang_node(SWITCH); slang_node_attach_children($$, $3, $5, NULL); }
	;

iteration_statement
	: WHILE '(' expression ')' statement { $$ = new_slang_node(WHILE); slang_node_attach_children($$, $3, $5, NULL); }
	| DO statement WHILE '(' expression ')' ';' { $$ = new_slang_node(DO); slang_node_attach_children($$, $2, $5, NULL); }
	| FOR '(' expression_statement expression_statement ')' statement { $$ = new_slang_node(FOR); slang_node_attach_children($$, $3, $4, new_slang_node(NULL_NODE), $6, NULL); }
	| FOR '(' expression_statement expression_statement expression ')' statement { $$ = new_slang_node(FOR); slang_node_attach_children($$, $3, $4, $5, $7, NULL); }
	| FOR '(' declaration expression_statement ')' statement { $$ = new_slang_node(FOR); slang_node_attach_children($$, $3, $4, new_slang_node(NULL_NODE), $6, NULL); }
	| FOR '(' declaration expression_statement expression ')' statement { $$ = new_slang_node(FOR); slang_node_attach_children($$, $3, $4, $5, $7, NULL); }
	;

jump_statement
	: CONTINUE ';' { $$ = new_slang_node(CONTINUE); }
	| BREAK ';' { $$ = new_slang_node(BREAK); }
	| RETURN ';' { $$ = new_slang_node(RETURN); }
	| RETURN expression ';' { $$ = new_slang_node(RETURN); slang_node_attach_child($$, $2);}
	;

constant_expression
	: conditional_expression	{ $$ = $1; }// with constraints
	;
*/
%%
