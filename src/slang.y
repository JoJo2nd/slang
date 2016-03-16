%{
/*

In 1985, Jeff Lee published his Yacc grammar based on a draft version of the ANSI C standard, along with a supporting Lex specification. Tom Stockfisch reposted those files to net.sources in 1987; as mentioned in the answer to question 17.25 of the comp.lang.c FAQ, they used to be available from ftp.uu.net as usenet/net.sources/ansi.c.grammar.Z.

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
	int intConst;
	float floatConst;
}

%type <node> translation_unit external_declaration function_definition declaration_specifiers type_qualifier type_qualifier_list
%type <node> storage_class_specifier type_specifier assignment_operator declarator direct_declarator constant expression
%type <node> primary_expression postfix_expression assignment_expression conditional_expression unary_expression unary_operator
%type <node> cast_expression multiplicative_expression additive_expression shift_expression relational_expression equality_expression
%type <node> and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> compound_statement block_item_list block_item declaration statement initializer initializer_list declaration_list
%type <node> identifier_list parameter_type_list type_name abstract_declarator direct_abstract_declarator init_declarator_list
%type <node> parameter_list parameter_declaration init_declarator argument_expression_list specifier_qualifier_list 
%type <node> expression_statement selection_statement iteration_statement jump_statement labeled_statement constant_expression
%type <node> struct_or_cbuffer_specifier struct_or_cbuffer struct_declaration_list struct_declarator_list struct_declaration 
%type <node> struct_declarator type_specifier_identifier

%token <ident> IDENTIFIER
%token <floatConst> FLOATCONSTANT
%token <double> DOUBLECONSTANT
%token <intConst> INTCONSTANT
%token <unsigned int> UINTCONSTANT
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
%token RETURN
%token CONST
%token STATIC
%token CBUFFER
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
%token STRUCT
%token LINEAR_MODIFIER
%token CENTROID_MODIFIER
%token NOINTERPOLATION_MODIFIER
%token NOPERSPECTIVE_MODIFIER
%token SAMPLE_MODIFIER
%token TYPEDEF

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
%token PLUS
%token DASH
%token PERCENT
%token STAR
%token SLASH
%token TILDE
%token BANG
%token CARET
%token LEFT_PAREN
%token RIGHT_PAREN
%token LEFT_BRACE
%token RIGHT_BRACE
%token SEMICOLON
%token LEFT_ANGLE
%token RIGHT_ANGLE
%token DOT
%token COMMA
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token VERTICAL_BAR
%token COLON
%token EQUAL
%token AMPERSAND
%token QUESTION

%token TRANSLATION_UNIT
%token FUNCTION_DEFINITION
%token VARIABLE_DECL
%token TYPE_SPECIFIER
%token STATEMENT_BLOCK
// typedef name and enumeration must be defined (but are they valid in HLSL?)
%token TYPEDEF_NAME ENUMERATION_CONSTANT
%token TERNARY_OPERATOR
%token NULL_NODE

%start translation_unit

%%

translation_unit
	: external_declaration { $$ = $1; context->root = $1; }
	| translation_unit external_declaration { context->root = $1; slang_node_attach_child($1, $2); }
	;

external_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; }
	;

compound_statement
	: LEFT_BRACE RIGHT_BRACE { $$ = new_slang_node(NULL_NODE); }
	| LEFT_BRACE  block_item_list RIGHT_BRACE { $$ = $2; }
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
	: declaration_specifiers SEMICOLON { $$ = $1; }
	| declaration_specifiers init_declarator_list SEMICOLON { $$ = $1; slang_node_attach_child($1, $2); }
	// | static_assert_declaration // HLSL doesn't handle static asserts
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
	| identifier_list COMMA IDENTIFIER { $$ = $1; slang_node_attach_child($$, new_slang_identifier($3)); }
	;

parameter_type_list
	: parameter_list { $$ = $1; }
	;

parameter_list
	: parameter_declaration { $$ = $1; }
	| parameter_list COMMA parameter_declaration { $$ = $1; slang_node_attach_child($1, $3); }
	;

parameter_declaration
	: declaration_specifiers declarator { $$ = $1; slang_node_attach_child($1, $2); }
	| declaration_specifiers abstract_declarator { $$ = $1; slang_node_attach_child($1, $2); }
	| declaration_specifiers { $$ = $1; }
	;

init_declarator_list
	: init_declarator { $$ = $1; }
	| init_declarator_list COMMA init_declarator { $$ = $1; slang_node_attach_child($1, $3); }
	;

init_declarator
	: declarator EQUAL initializer { $$ = new_slang_node(EQUAL); slang_node_attach_children($$, $1, $3, NULL); }
	| declarator { $$ = $1; }
	;

initializer
	: LEFT_BRACE initializer_list RIGHT_BRACE { $$ = $2; }
	| LEFT_BRACE initializer_list COMMA RIGHT_BRACE { $$ = $2; }
	| assignment_expression { $$ = $1; }
	;

initializer_list
	: initializer { $$ = $1; }
	| initializer_list COMMA initializer { $$ = $1; slang_node_attach_child($1, $3); }
	;

struct_or_cbuffer_specifier
    : struct_or_cbuffer LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = $1; slang_node_attach_child($1, $3); }
    | struct_or_cbuffer IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE { $$ = $1; slang_node_attach_children($1, new_slang_identifier($2), $4, NULL); }
    | struct_or_cbuffer IDENTIFIER { $$ = $1; slang_node_attach_child($1, new_slang_identifier($2)); }
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
    : specifier_qualifier_list struct_declarator_list SEMICOLON { $$ = $1; slang_node_attach_child($1, $2); }
    ;

struct_declarator_list
    : struct_declarator { $$ = $1; }
    | struct_declarator_list COMMA struct_declarator { $$ = $1; slang_node_attach_child($1, $3); }
    ;

struct_declarator
    : COLON constant_expression { $$ = $2; }
    | declarator COLON constant_expression { $$ = $1; slang_node_attach_child($1, $3); }
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
	: TYPEDEF	{ $$ = new_slang_node(TYPEDEF); } /* identifiers must be flagged as TYPEDEF_NAME */
	| LINEAR_MODIFIER { $$ = new_slang_node(LINEAR_MODIFIER); }
	| CENTROID_MODIFIER { $$ = new_slang_node(CENTROID_MODIFIER); }
	| NOINTERPOLATION_MODIFIER { $$ = new_slang_node(NOINTERPOLATION_MODIFIER); }
	| NOPERSPECTIVE_MODIFIER { $$ = new_slang_node(NOPERSPECTIVE_MODIFIER); }
	| SAMPLE_MODIFIER { $$ = new_slang_node(SAMPLE_MODIFIER); }
	;

type_specifier_identifier
    : IDENTIFIER { $$ = new_slang_identifier($1); }
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
    | struct_or_cbuffer_specifier
    //| type_specifier_identifier
    ;

assignment_operator
	: EQUAL { $$ = new_slang_node(EQUAL); }
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
	| LEFT_PAREN declarator RIGHT_PAREN { $$ = $2; }
	| direct_declarator LEFT_BRACKET RIGHT_BRACKET { $$ = $1; }
	| direct_declarator LEFT_BRACKET STATIC type_qualifier_list assignment_expression RIGHT_BRACKET { $$ = $1; slang_node_attach_children($1, $4, $5, NULL); }
	| direct_declarator LEFT_BRACKET STATIC assignment_expression RIGHT_BRACKET { $$ = $1; slang_node_attach_child($1, $4); }
	| direct_declarator LEFT_BRACKET type_qualifier_list STATIC assignment_expression RIGHT_BRACKET { $$ = $1; slang_node_attach_children($1, $3, $5, NULL); }
	| direct_declarator LEFT_BRACKET type_qualifier_list assignment_expression RIGHT_BRACKET { $$ = $1; slang_node_attach_children($1, $3, $4, NULL); }
	| direct_declarator LEFT_BRACKET type_qualifier_list RIGHT_BRACKET { $$ = $1; slang_node_attach_child($1, $3); }
	| direct_declarator LEFT_BRACKET assignment_expression RIGHT_BRACKET { $$ = $1; slang_node_attach_child($1, $3); }
	| direct_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN { $$ = $1; slang_node_attach_child($1, $3); }
	| direct_declarator LEFT_PAREN RIGHT_PAREN { $$ = $1; }
	| direct_declarator LEFT_PAREN identifier_list RIGHT_PAREN { $$ = $1; slang_node_attach_child($1, $3); }
	// | direct_declarator LEFT_BRACKET type_qualifier_list '*' RIGHT_BRACKET
	// | direct_declarator '[' '*' ']' // 
	;

constant
	: INTCONSTANT		{ $$ = new_slang_int_constant($1); }/* includes character_constant */
	| FLOATCONSTANT		{ $$ = new_slang_float_constant($1); }
	//| ENUMERATION_CONSTANT	// Are ENUMS valid in HLSL?
	;

//string // HLSL doesn't do string literials (not in a normal way)
//	: STRING_LITERAL { $$ = new_slang_node() }
//	;


expression
	: assignment_expression { $$ = $1; }
	| expression COMMA assignment_expression { $$ = $1; slang_node_attach_child($1, $3); }
	;

primary_expression
	: IDENTIFIER { $$ = new_slang_identifier($1); }
	| constant { $$ = $1; }
	| LEFT_PAREN expression RIGHT_PAREN { $$ = $2; }
	;

argument_expression_list
	: assignment_expression { $$ = $1; }
	| argument_expression_list COMMA assignment_expression { $$ = $1; slang_node_attach_child($1, $3); }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression LEFT_BRACKET expression RIGHT_BRACKET { $$ = $1; slang_node_attach_child($1, $3); }
	| postfix_expression LEFT_PAREN RIGHT_PAREN { $$ = $1; }
	| postfix_expression LEFT_PAREN argument_expression_list RIGHT_PAREN { $$ = $1; slang_node_attach_child($1, $3); }
	| postfix_expression DOT IDENTIFIER { $$ = $1; slang_node_attach_children($1, new_slang_node(DOT), new_slang_identifier($3), NULL); }
	| postfix_expression INC_OP { $$ = $1; slang_node_attach_child($1, new_slang_node(INC_OP)); }
	| postfix_expression DEC_OP { $$ = $1; slang_node_attach_child($1, new_slang_node(DEC_OP)); }
	| LEFT_PAREN type_name RIGHT_PAREN LEFT_BRACE initializer_list RIGHT_BRACE { $$ = $2; slang_node_attach_child($2, $5); }
	| LEFT_PAREN type_name RIGHT_PAREN LEFT_BRACE initializer_list COMMA RIGHT_BRACE { $$ = $2; slang_node_attach_child($2, $5); }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression { $$ = $1; slang_node_attach_children($1, $2, $3, NULL); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression QUESTION expression COLON conditional_expression { $$ = new_slang_node(TERNARY_OPERATOR); slang_node_attach_children($1, $3, $5, NULL); }
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
	: AMPERSAND { $$ = new_slang_node(AMPERSAND); }
	| STAR { $$ = new_slang_node(STAR); }
	| PLUS { $$ = new_slang_node(PLUS); }
	| DASH { $$ = new_slang_node(DASH); }
	| TILDE { $$ = new_slang_node(TILDE); }
	| BANG { $$ = new_slang_node(BANG); }
	;

cast_expression
	: unary_expression { $$ = $1; }
	| LEFT_PAREN type_name RIGHT_PAREN cast_expression { $$ = $2; slang_node_attach_child($2, $4); }
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression STAR cast_expression { $$ = new_slang_node(STAR); slang_node_attach_children($$, $1, $3, NULL); }
	| multiplicative_expression SLASH cast_expression { $$ = new_slang_node(SLASH); slang_node_attach_children($$, $1, $3, NULL); }
	| multiplicative_expression PERCENT cast_expression { $$ = new_slang_node(PERCENT); slang_node_attach_children($$, $1, $3, NULL); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression PLUS multiplicative_expression { $$ = new_slang_node(PLUS); slang_node_attach_children($$, $1, $3, NULL); }
	| additive_expression DASH multiplicative_expression { $$ = new_slang_node(DASH); slang_node_attach_children($$, $1, $3, NULL); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = new_slang_node(LEFT_OP); slang_node_attach_children($$, $1, $3, NULL); }
	| shift_expression RIGHT_OP additive_expression { $$ = new_slang_node(RIGHT_OP); slang_node_attach_children($$, $1, $3, NULL); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression LEFT_ANGLE shift_expression { $$ = new_slang_node(LEFT_ANGLE); slang_node_attach_children($$, $1, $3, NULL); }
	| relational_expression RIGHT_ANGLE shift_expression { $$ = new_slang_node(RIGHT_ANGLE); slang_node_attach_children($$, $1, $3, NULL); }
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
	| and_expression AMPERSAND equality_expression { $$ = new_slang_node(AMPERSAND); slang_node_attach_children($$, $1, $3, NULL); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression CARET and_expression { $$ = new_slang_node(CARET); slang_node_attach_children($$, $1, $3, NULL); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression VERTICAL_BAR exclusive_or_expression { $$ = new_slang_node(VERTICAL_BAR); slang_node_attach_children($$, $1, $3, NULL); }
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
	: LEFT_PAREN abstract_declarator RIGHT_PAREN { $$ = $2; }
	| LEFT_BRACKET RIGHT_BRACKET { $$ = new_slang_node(NULL_NODE); }
	//| '[' '*' ']'
	| LEFT_BRACKET STATIC type_qualifier_list assignment_expression RIGHT_BRACKET { $$ = new_slang_node(STATIC); slang_node_attach_children($$, $3, $4, NULL); }
	| LEFT_BRACKET STATIC assignment_expression RIGHT_BRACKET { $$ = new_slang_node(STATIC); slang_node_attach_children($$, $3, NULL); }
	| LEFT_BRACKET type_qualifier_list STATIC assignment_expression RIGHT_BRACKET { $$ = $2; slang_node_attach_children($$, new_slang_node(STATIC), $4, NULL); }
	| LEFT_BRACKET type_qualifier_list assignment_expression RIGHT_BRACKET { $$ = $2; slang_node_attach_child($$, $3); }
	| LEFT_BRACKET type_qualifier_list RIGHT_BRACKET { $$ = $2; }
	| LEFT_BRACKET assignment_expression RIGHT_BRACKET { $$ = $2; }
	| direct_abstract_declarator LEFT_BRACKET RIGHT_BRACKET { $$ = $1; }
	//| direct_abstract_declarator LEFT_BRACKET '*' RIGHT_BRACKET
	| direct_abstract_declarator LEFT_BRACKET STATIC type_qualifier_list assignment_expression RIGHT_BRACKET { $$ = $1; slang_node_attach_children($$, new_slang_node(STATIC), $4, $5, NULL); }
	| direct_abstract_declarator LEFT_BRACKET STATIC assignment_expression RIGHT_BRACKET { $$ = $1; slang_node_attach_children($$, new_slang_node(STATIC), $4, NULL); }
	| direct_abstract_declarator LEFT_BRACKET type_qualifier_list assignment_expression RIGHT_BRACKET { $$ = $1; slang_node_attach_children($$, $3, $4, NULL); }
	| direct_abstract_declarator LEFT_BRACKET type_qualifier_list STATIC assignment_expression RIGHT_BRACKET { $$ = $1; slang_node_attach_children($$, $3, new_slang_node(STATIC), $5, NULL); }
	| direct_abstract_declarator LEFT_BRACKET type_qualifier_list RIGHT_BRACKET { $$ = $1; slang_node_attach_child($$, $3); }
	| direct_abstract_declarator LEFT_BRACKET assignment_expression RIGHT_BRACKET { $$ = $1; slang_node_attach_child($$, $3); }
	| LEFT_PAREN RIGHT_PAREN { $$ = new_slang_node(NULL_NODE); }
	| LEFT_PAREN parameter_type_list RIGHT_PAREN { $$ = $2; }
	| direct_abstract_declarator LEFT_PAREN RIGHT_PAREN { $$ = $1; }
	| direct_abstract_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN { $$ = $1; slang_node_attach_child($$, $3); }
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
	: IDENTIFIER COLON statement { $$ = new_slang_identifier($1); slang_node_attach_child($$, $3); }
	| CASE constant_expression COLON statement { $$ = $2; slang_node_attach_child($$, $4); }
	| DEFAULT COLON statement { $$ = new_slang_node(DEFAULT); slang_node_attach_child($$, $3); }
	;

expression_statement
	: SEMICOLON { $$ = new_slang_node(NULL_NODE); }
	| expression SEMICOLON { $$ = $1; }
	;

selection_statement
	: IF LEFT_PAREN expression RIGHT_PAREN statement ELSE statement { $$ = new_slang_node(IF); slang_node_attach_children($$, $3, $5, $7, NULL); }
	| IF LEFT_PAREN expression RIGHT_PAREN statement { $$ = new_slang_node(IF); slang_node_attach_children($$, $3, $5, NULL); }
	| SWITCH LEFT_PAREN expression RIGHT_PAREN statement { $$ = new_slang_node(SWITCH); slang_node_attach_children($$, $3, $5, NULL); }
	;

iteration_statement
	: WHILE LEFT_PAREN expression RIGHT_PAREN statement { $$ = new_slang_node(WHILE); slang_node_attach_children($$, $3, $5, NULL); }
	| DO statement WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON { $$ = new_slang_node(DO); slang_node_attach_children($$, $2, $5, NULL); }
	| FOR LEFT_PAREN expression_statement expression_statement RIGHT_PAREN statement { $$ = new_slang_node(FOR); slang_node_attach_children($$, $3, $4, new_slang_node(NULL_NODE), $6, NULL); }
	| FOR LEFT_PAREN expression_statement expression_statement expression RIGHT_PAREN statement { $$ = new_slang_node(FOR); slang_node_attach_children($$, $3, $4, $5, $7, NULL); }
	| FOR LEFT_PAREN declaration expression_statement RIGHT_PAREN statement { $$ = new_slang_node(FOR); slang_node_attach_children($$, $3, $4, new_slang_node(NULL_NODE), $6, NULL); }
	| FOR LEFT_PAREN declaration expression_statement expression RIGHT_PAREN statement { $$ = new_slang_node(FOR); slang_node_attach_children($$, $3, $4, $5, $7, NULL); }
	;

jump_statement
	: CONTINUE SEMICOLON { $$ = new_slang_node(CONTINUE); }
	| BREAK SEMICOLON { $$ = new_slang_node(BREAK); }
	| RETURN SEMICOLON { $$ = new_slang_node(RETURN); }
	| RETURN expression SEMICOLON { $$ = new_slang_node(RETURN); slang_node_attach_child($$, $2);}
	;

constant_expression
	: conditional_expression	{ $$ = $1; }/* with constraints */
	;
%%
