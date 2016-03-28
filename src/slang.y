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

%type <node> translation_unit
%type <node> external_declaration declaration

%type <node> variable_declaration variable_declarator external_variable_declaration external_declaration_specifiers 
%type <node> scalar_type_specifier sampler_type_specifier
%type <node> type_modifier /*type_modifier_list*/ type_specifier full_type_specifier input_output_qualifier_list input_output_qualifier interpolation_modifier
%type <node> semantic register register_list shader_profile 
//%type <node> annotations full_annotation_type_specifier annotation_type_specifier annotation_declaration_list annotation_declaration annotation_declaration_assignment annotation_initializer_list annotation_initializer
%type <node> cbuffer_or_tbuffer_declaration cbuffer_or_tbuffer
%type <node> buffer_member_declaration_list 
%type <node> struct_declarator struct_declaration struct_member_declaration_list struct_member_declaration
%type <node> function_definition function_declarator function_args_list function_arg
%type <node> type_name
%type <node> primary_expression constant expression expression_statement assignment_expression assignment_operator
%type <node> postfix_expression
%type <node> unary_expression unary_operator
%type <node> cast_expression
%type <node> argument_expression_list
%type <node> initializer_list initializer
%type <node> statement compound_statement 
%type <node> block_item block_item_list 
%type <node> conditional_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> jump_statement

%type <node> declarator init_declarator_list init_declarator

%token <ident> IDENTIFIER
%token <ident> TYPE_NAME
%token <floatConst> FLOATCONSTANT
%token <double> DOUBLECONSTANT
%token <intConst> INTCONSTANT
%token <unsigned int> UINTCONSTANT
%token <regConst> REGISTERCONSTANT
%token <strLiteral> STRING_LITERAL
%token TRUE_VALUE
%token FALSE_VALUE

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

%token INLINE
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

%token TRANSLATION_UNIT 
%token COMPOUND_STATEMENT BLOCK_ITEM_LIST
%token FUNCTION FUNCTION_ARG_LIST FUNCTION_ARG
%token ANNOTATION_LIST
%token INITIALIZER_LIST
%token INPUT_OUTPUT_QUALIFIER_LIST
%token ARGUMENT_EXPRESSION_LIST
%token BUFFER_MEMBER_DECLARATION_LIST

%token INIT_DECLARATOR_LIST DECLARATOR EXTERNAL_DECLARATION_SPECIFIERS
%token EXTERNAL_VARIABLE_DECLARATION VARIABLE_DECL CBUFFER_TBUFFER_DECL BUFFER_MEMBER_DECLARATION 
%token STRUCT_DECL STRUCT_MEMBER_DECL
%token STRUCT_INTERPOLATION_MODIFIER_LIST STRUCT_MEMBER_DECLARATION_LIST

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
    : external_declaration { $$ = new_slang_node(TRANSLATION_UNIT); context->root = $$;  slang_node_attach_child($$, $1); }
    | translation_unit external_declaration { slang_node_attach_child($1, $2); }
    ;

external_declaration
    : external_variable_declaration { $$ = $1; }
    | struct_declaration  ';' { $$ = $1; }
    | function_declarator ';'  { $$ = $1; }
    | cbuffer_or_tbuffer_declaration ';' { $$ = $1; }
    | function_definition { $$ = $1; }
    ;

declaration
    : variable_declaration { $$ = $1; }
    | struct_declaration { $$ = $1; }
    | function_declarator { $$ = $1; }
    ;

compound_statement
    : '{' '}' { $$ = new_slang_node(COMPOUND_STATEMENT); }
    | '{'  block_item_list '}' { $$ = new_slang_node(COMPOUND_STATEMENT); slang_node_attach_child($$, $2); }
    ;

block_item
    : declaration ';' { $$ = $1; }
    | statement { $$ = $1; }
    ;

block_item_list
    : block_item { $$ = new_slang_node(BLOCK_ITEM_LIST); slang_node_attach_child($$, $1); }
    | block_item_list block_item { $$ = $1; slang_node_attach_child($1, $2); }
    ;

external_declaration_specifiers
    : register external_declaration_specifiers { $$ = $2; slang_node_attach_child_front($2, $1); }
    | register { $$ = new_slang_node(EXTERNAL_DECLARATION_SPECIFIERS); slang_node_attach_child_front($$, $1); }
    | interpolation_modifier external_declaration_specifiers { $$ = $2; slang_node_attach_child_front($2, $1); }
    | interpolation_modifier { $$ = new_slang_node(EXTERNAL_DECLARATION_SPECIFIERS); slang_node_attach_child_front($$, $1); }
    | type_modifier external_declaration_specifiers { $$ = $2; slang_node_attach_child_front($2, $1); }
    | type_modifier { $$ = new_slang_node(EXTERNAL_DECLARATION_SPECIFIERS); slang_node_attach_child_front($$, $1); }
    | type_specifier external_declaration_specifiers { $$ = $2; slang_node_attach_child_front($2, $1); }
    | type_specifier { $$ = new_slang_node(EXTERNAL_DECLARATION_SPECIFIERS); slang_node_attach_child_front($$, $1); }
    ;

external_variable_declaration
    : external_declaration_specifiers ';' { $$ = new_slang_node(EXTERNAL_VARIABLE_DECLARATION); slang_node_attach_child($$, $1); }
    | external_declaration_specifiers init_declarator_list ';'  { $$ = $1; slang_node_attach_child($1, $2); }
    ;

variable_declaration
    : variable_declaration '=' initializer { $$ = $1; slang_node_attach_children($1, $3, NULL); }
    //  variable_declaration assignment_expression { $$ = $1; slang_node_attach_children($$, $2, NULL); }
    | variable_declarator { $$ = $1; }    
    ;

variable_declarator
    : full_type_specifier IDENTIFIER { $$ = new_slang_var_decl($1, new_slang_identifier($2), NULL, NULL, NULL, NULL); }
    ;

init_declarator_list
    : init_declarator { $$ = new_slang_node(INIT_DECLARATOR_LIST); slang_node_attach_child($$, $1); }
    | init_declarator_list ',' init_declarator { $$ = $1; slang_node_attach_child($1, $3); }
    ;

init_declarator
    : declarator '=' initializer { $$ = new_slang_node('='); slang_node_attach_children($$, $1, $3, NULL); }
    | declarator { $$ = $1; }
    ;

declarator
    : IDENTIFIER { $$ = new_slang_node(DECLARATOR); $$->declarator.ident = slang_copy_string($1); $$->declarator.arraySize = 1; }
    | '(' declarator ')' { $$ = $2; }
    | declarator '[' ']' { $$ = $1; $1->declarator.arraySize = 0; }
    //| declarator '[' '*' ']' { $$ = $1; }
    //| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    //| direct_declarator '[' STATIC assignment_expression ']'
    //| direct_declarator '[' type_qualifier_list '*' ']'
    //| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    //| direct_declarator '[' type_qualifier_list assignment_expression ']'
    //| direct_declarator '[' type_qualifier_list ']'
    | declarator '[' assignment_expression ']' { $$ = $1; $1->declarator.arraySizeChild = $3; slang_node_attach_child($1, $3); }
    //| direct_declarator '(' parameter_type_list ')'
    | declarator '(' ')' { $$ = $1; }
    //| direct_declarator '(' identifier_list ')'
    ;

full_type_specifier
    : type_specifier full_type_specifier { $$ = $2; slang_node_attach_child($2, $1); }
    | type_specifier { $$ = $1; }
    | type_modifier full_type_specifier { $$ = $2; slang_node_attach_child($2, $1); }
    | type_modifier { $$ = $1; }
    ;
/*
type_modifier_list // aka storage_qualifier_list
    : type_modifier { $$ = $1; }
    | type_modifier_list type_modifier { $$ = $1; slang_node_attach_child($1, $2); }
    ;
*/
type_modifier // aka storage_qualifier
    : CONST { $$ = new_slang_node(CONST); }
    | ROW_MAJOR { $$ = new_slang_node(ROW_MAJOR); }
    | COLUMN_MAJOR { $$ = new_slang_node(COLUMN_MAJOR); }
    | SHARED { $$ = new_slang_node(SHARED); } // groupshared across thread groups
    | STATIC { $$ = new_slang_node(STATIC); } // not visible outside shader. In function, same as C/C++
    ;

semantic
    : SEMANTIC '(' IDENTIFIER ')' { $$ = new_slang_semantic($3); }
    ;

register_list
    : register { $$ = $1; }
    | register_list register { $$ = $1; slang_node_attach_child($1, $2); }
    ;

register
    : REGISTER '(' shader_profile ',' IDENTIFIER ')' { $$ = new_slang_node(REGISTER); slang_node_attach_children($$, $3, new_slang_register_constant($5), NULL); }
    | REGISTER '(' IDENTIFIER ')' { $$ = new_slang_node(REGISTER); slang_node_attach_children($$, new_slang_register_constant($3), NULL); }
    ;

interpolation_modifier
    : LINEAR { $$ = new_slang_node(LINEAR); }
    | CENTROID { $$ = new_slang_node(CENTROID); }
    | NOINTERPOLATION { $$ = new_slang_node(NOINTERPOLATION); } 
    | NOPERSPECTIVE { $$ = new_slang_node(NOPERSPECTIVE); }
    | SAMPLE { $$ = new_slang_node(SAMPLE); }
    ;

input_output_qualifier_list
    : input_output_qualifier { $$ = new_slang_node(INPUT_OUTPUT_QUALIFIER_LIST); slang_node_attach_child($$, $1); }
    | input_output_qualifier_list input_output_qualifier { $$ = $1; slang_node_attach_child($1, $2); }
    ;

input_output_qualifier
    : interpolation_modifier { $$ = $1; }
    | semantic { $$ = $1; }
    ;

/*
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
*/

cbuffer_or_tbuffer_declaration
    : register_list cbuffer_or_tbuffer IDENTIFIER '{' '}' { $$ = new_slang_cbuffer_tbuffer_decl(new_slang_identifier($3), $1, NULL); }
    | register_list cbuffer_or_tbuffer IDENTIFIER '{' buffer_member_declaration_list '}' { $$ = new_slang_cbuffer_tbuffer_decl(new_slang_identifier($3), $1, $5); }
    | cbuffer_or_tbuffer IDENTIFIER '{' '}' { $$ = new_slang_cbuffer_tbuffer_decl(new_slang_identifier($2), NULL, NULL); }
    | cbuffer_or_tbuffer IDENTIFIER '{' buffer_member_declaration_list '}' { $$ = new_slang_cbuffer_tbuffer_decl(new_slang_identifier($2), NULL, $4); }
    ;

cbuffer_or_tbuffer
    : CBUFFER { $$ = new_slang_node(CBUFFER); }
    | TBUFFER { $$ = new_slang_node(TBUFFER); }
    ;

buffer_member_declaration_list
    : variable_declaration ';' { $$ = new_slang_node(BUFFER_MEMBER_DECLARATION_LIST); slang_node_attach_child($$, $1); }
    | buffer_member_declaration_list variable_declaration ';' { $$ = $1; slang_node_attach_child($1, $2); }
    ;

struct_declaration
	: struct_declarator { $$ = $1; }
	;

struct_declarator
    : STRUCT IDENTIFIER '{' '}' { $$ = new_slang_struct_decl(new_slang_identifier($2), NULL); }
    | STRUCT IDENTIFIER '{' struct_member_declaration_list '}' { $$ = new_slang_struct_decl(new_slang_identifier($2), $4); }
    | STRUCT '{' struct_member_declaration_list '}' { $$ = new_slang_struct_decl(NULL, $3); } // anonymous
    ;

struct_member_declaration
    : input_output_qualifier_list variable_declarator { $$ = $2; slang_node_attach_children($2, $1, NULL); }
    | variable_declarator { $$ = $1; }    
    ;

struct_member_declaration_list
    : struct_member_declaration ';' { $$ = new_slang_node(STRUCT_MEMBER_DECLARATION_LIST); slang_node_attach_child($$, $1); }
    | struct_member_declaration_list struct_member_declaration ';'{ $$ = $1; slang_node_attach_child($1, $2); }
    ;

function_args_list
    : function_arg { $$ = new_slang_node(FUNCTION_ARG_LIST); slang_node_attach_child($$, $1); }
    | function_args_list ',' function_arg { $$ = $1; slang_node_attach_child($1, $3); }
    ;

function_arg
    : input_output_qualifier_list full_type_specifier IDENTIFIER { $$ = new_slang_function_arg($2, new_slang_identifier($3), $1); }
    | full_type_specifier IDENTIFIER { $$ = new_slang_function_arg($1, new_slang_identifier($2), NULL); }
    ;

function_declarator
    : semantic full_type_specifier IDENTIFIER '(' function_args_list ')' { $$ = new_slang_function_declarator($2, new_slang_identifier($3), $5, $1); }
    | semantic full_type_specifier IDENTIFIER '(' ')' { $$ = new_slang_function_declarator($2, new_slang_identifier($3), NULL, $1); }
    | full_type_specifier IDENTIFIER '(' function_args_list ')' { $$ = new_slang_function_declarator($1, new_slang_identifier($2), $4, NULL); }
    | full_type_specifier IDENTIFIER '(' ')' { $$ = new_slang_function_declarator($1, new_slang_identifier($2), NULL, NULL); }
    ;

function_definition
    : function_declarator compound_statement { $$ = $1; slang_node_attach_child($$, $2); };
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
    ;

sampler_type_specifier
    : SAMPLER { $$ = new_slang_node(SAMPLER); }
    | SAMPLER1D { $$ = new_slang_node(SAMPLER1D); }
    | SAMPLER2D { $$ = new_slang_node(SAMPLER2D); }
    | SAMPLER3D { $$ = new_slang_node(SAMPLER3D); }
    | SAMPLERCUBE { $$ = new_slang_node(SAMPLERCUBE); }
    | SAMPLERSTATE { $$ = new_slang_node(SAMPLERSTATE); }
    | SAMPLER_STATE { $$ = new_slang_node(SAMPLER_STATE); }
    | TEXTURE1D { $$ = new_slang_node(TEXTURE1D); }
    | TEXTURE1DARRAY { $$ = new_slang_node(TEXTURE1DARRAY); }
    | TEXTURE2D { $$ = new_slang_node(TEXTURE2D); }
    | TEXTURE2DARRAY { $$ = new_slang_node(TEXTURE2DARRAY); }
    | TEXTURE3D { $$ = new_slang_node(TEXTURE3D); }
    | TEXTURE3DARRAY { $$ = new_slang_node(TEXTURE3DARRAY); }
    | TEXTURECUBE { $$ = new_slang_node(TEXTURECUBE); }
    ;

type_specifier
    : scalar_type_specifier { $$ = $1; }
    | sampler_type_specifier { $$ = $1; }
    | struct_declarator { $$ = $1; }
    | TYPE_NAME { $$ = new_slang_identifier($1); }
    ;

type_name
    : type_specifier type_name { $$ = $1; slang_node_attach_child($1, $2); }
    | type_specifier { $$ = $1; }
    | type_modifier type_name { $$ = $1; slang_node_attach_child($1, $2); }
    | type_modifier { $$ = $1; }
    ;

shader_profile
    : VS { $$ = new_slang_node(VS); }
    | PS { $$ = new_slang_node(PS); }
    | GS { $$ = new_slang_node(GS); }
    | DS { $$ = new_slang_node(DS); }
    | HS { $$ = new_slang_node(HS); }
    ;

statement
    : /*labeled_statement { $$ = $1; }
    | */compound_statement { $$ = $1; }
    | expression_statement { $$ = $1; }
    /*| selection_statement { $$ = $1; }
    | iteration_statement { $$ = $1; } */
    | jump_statement { $$ = $1; }
    ;

expression_statement
    : ';' { $$ = new_slang_node(NULL_NODE); }
    | expression ';' { $$ = $1; }
    ;

primary_expression
    : IDENTIFIER { $$ = new_slang_identifier($1); }
    | constant { $$ = $1; }
    | '(' expression ')' { $$ = $2; }
    ;

constant
    : INTCONSTANT       { $$ = new_slang_int_constant($1); }// includes character_constant 
    | FLOATCONSTANT     { $$ = new_slang_float_constant($1); }
    ;

expression
    : assignment_expression { $$ = $1; }
    | expression ',' assignment_expression { $$ = $1; slang_node_attach_child($1, $3); }
    ;

assignment_expression
    : conditional_expression { $$ = $1; }
    | unary_expression assignment_operator assignment_expression { $$ = $2; slang_node_attach_children($2, $1, $3, NULL); }
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

unary_expression
    : postfix_expression { $$ = $1; }
    | INC_OP unary_expression { $$ = new_slang_node(INC_OP); slang_node_attach_child($$, $2); }
    | DEC_OP unary_expression { $$ = new_slang_node(DEC_OP); slang_node_attach_child($$, $2); }
    | unary_operator cast_expression { $$ = $1; slang_node_attach_child($1, $2); }
    ;

unary_operator
    : '+' { $$ = new_slang_node('+'); }
    | '-' { $$ = new_slang_node('-'); }
    | '~' { $$ = new_slang_node('~'); }
    | '!' { $$ = new_slang_node('!'); }
    ;

cast_expression
    : unary_expression { $$ = $1; }
    | '(' type_name ')' cast_expression { $$ = $2; slang_node_attach_child($2, $4); }
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
    | type_name '(' argument_expression_list ')' { $$ = $1; slang_node_attach_child($1, $3); }
    ;


argument_expression_list
    : assignment_expression { $$ = new_slang_node(ARGUMENT_EXPRESSION_LIST); slang_node_attach_child($$, $1); }
    | argument_expression_list ',' assignment_expression { $$ = $1; slang_node_attach_child($1, $3); }
    ;

initializer
    : '{' initializer_list '}' { $$ = $2; }
    | '{' initializer_list ',' '}' { $$ = $2; }
    | assignment_expression { $$ = $1; }
    ;

initializer_list
    : initializer { $$ = new_slang_node(INITIALIZER_LIST); slang_node_attach_child($$, $1); }
    | initializer_list ',' initializer { $$ = $1; slang_node_attach_child($1, $3); }
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

equality_expression
    : relational_expression { $$ = $1; }
    | equality_expression EQ_OP relational_expression { $$ = new_slang_node(EQ_OP); slang_node_attach_children($$, $1, $3, NULL); }
    | equality_expression NE_OP relational_expression { $$ = new_slang_node(NE_OP); slang_node_attach_children($$, $1, $3, NULL); }
    ;

and_expression
    : equality_expression { $$ = $1; }
    | and_expression '&' equality_expression { $$ = new_slang_node('&'); slang_node_attach_children($$, $1, $3, NULL); }
    ;

exclusive_or_expression
    : and_expression { $$ = $1; }
    | exclusive_or_expression '^' and_expression { $$ = new_slang_node('^'); slang_node_attach_children($$, $1, $3, NULL); }
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

conditional_expression
    : logical_or_expression { $$ = $1; }
    | logical_or_expression '?' expression ':' conditional_expression { $$ = new_slang_node(TERNARY_OPERATOR); slang_node_attach_children($$, $1, $3, $5, NULL); }
    ;

jump_statement
    : /*CONTINUE ';' { $$ = new_slang_node(CONTINUE); }
    | BREAK ';' { $$ = new_slang_node(BREAK); }
    |*/ RETURN ';' { $$ = new_slang_node(RETURN); }
    | RETURN expression ';' { $$ = new_slang_node(RETURN); slang_node_attach_child($$, $2);}
    ;

%%
