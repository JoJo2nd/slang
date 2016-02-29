%{
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

%}

%defines

// prefix generated functions
%define api.prefix slang_
// make the parser re-entrant
%define api.pure full

%type <struct slang_node*> root
//%type <struct slang_node*> variable_modifier
%type <struct slang_node*> variable_identifier
%type <struct slang_node*> variable_decl
%type <struct slang_node*> type_specifier
%type <struct slang_node*> full_type_specifier


%token <char *> IDENTIFIER
%token <float> FLOATCONSTANT
%token <double> DOUBLECONSTANT
%token <int> INTCONSTANT
%token <unsigned int> UINTCONSTANT
%token TRUE_VALUE
%token FALSE_VALUE

%token TRANSLATION_UNIT
%token VARIABLE_DECL
%token TYPE_SPECIFIER

%token VOID
%token CONST
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

//%start root

%%

root 
    : variable_decl
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
    ;

full_type_specifier
    : type_specifier { $$ = new_slang_node(TYPE_SPECIFIER, $1); }
    //| variable_modifier type_specifier
    ;

variable_identifier 
    : IDENTIFIER { $$ = new_glsl_identifier($1); }
    ;

//variable_modifier
//    : CONST
//    ;

variable_decl
    : full_type_specifier variable_identifier SEMICOLON { $$ = new_slang_node(VARIABLE_DECL, $1, $2); } 
    // TODO: |  type_specifier variable_identifier EQUALS type_specifier LEFT_PAREN expression RIGHT_PAREN  SEMICOLON
    ;


%%

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