/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */
#include "slang.h"
#include "slang.tab.h"
#include "sym_table.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

// TODO: create a hash map of 
char* slang_copy_string(const char* in_str) {
    return _strdup(in_str); // shutup the VC compiler...
}

slang_node_t* init_slang_node(slang_node_t* n) {
    n->tokentype = ~0UL;
    memset(&n->varDecl, 0, sizeof(n->varDecl));
    n->parent = NULL;
    n->firstChild = NULL;
    n->siblingNext = n->siblingPrev = n;
    return n;
}

slang_node_t* new_slang_node(int code) {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = code;
    return temp;
}

slang_node_t* new_slang_null_node() {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = NULL_NODE;
    return temp;   
}

slang_node_t* new_slang_identifier(const char* ident) {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = IDENTIFIER;
    temp->ident = slang_copy_string(ident);
    return temp;
}

slang_node_t* new_slang_semantic(const char* ident) {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = SEMANTIC;
    temp->ident = slang_copy_string(ident);
    return temp;
}

void slang_node_make_sibling(slang_node_t* node, slang_node_t* new_sibling) {
    slang_assert(new_sibling->siblingPrev == new_sibling && new_sibling->siblingNext == new_sibling);
    new_sibling->siblingNext = node;
    new_sibling->siblingPrev = node->siblingPrev;
    node->siblingPrev->siblingNext = new_sibling;
    node->siblingPrev = new_sibling;
}

void slang_node_make_siblings(slang_node_t* node, ...) {
    slang_node_t* temp;
    int sibling_i = 0;
    va_list vl;
    va_start(vl, node);
    while (1) {
        temp = va_arg(vl, slang_node_t*);
        if (!temp)
            break;
        slang_node_make_sibling(node, temp);
        ++sibling_i;
    }
    va_end(vl);
}

void slang_node_attach_child(slang_node_t* parent, slang_node_t* child) {
    slang_assert(child->parent == NULL);
    slang_assert(child != parent);
    if (!parent->firstChild) {
        parent->firstChild = child;
    } else {
        child->siblingPrev = parent->firstChild->siblingPrev;
        child->siblingNext = parent->firstChild;
        parent->firstChild->siblingPrev->siblingNext = child;
        parent->firstChild->siblingPrev = child;
    }
    child->parent = parent;
}

void slang_node_attach_child_front(slang_node_t* parent, slang_node_t* child) {
    slang_node_attach_child(parent, child);
    parent->firstChild = child;
}

slang_node_t* new_slang_int_constant(int int_str) {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = INTCONSTANT;
    temp->int_const = int_str;
    return temp;
}

slang_node_t* new_slang_float_constant(float float_str) {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = FLOATCONSTANT;
    temp->float_const = float_str;
    return temp;
}

slang_node_t* new_slang_string_literal(const char* ident) {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = STRING_LITERAL;
    temp->ident = slang_copy_string(ident);
    return temp;
}    

slang_node_t* new_slang_register_constant(slang_node_t* profile, int reg_index, int reg_offset) {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = REGISTER;
    //TODO: error check these
    temp->regConst.reg_index = reg_index;
    temp->regConst.reg_offset = reg_offset;
    temp->regConst.profileNode = profile;
    return temp;   
}

slang_node_t* new_slang_var_decl( 
    slang_node_t* type,
    slang_node_t* ident, 
    slang_node_t* semantics, 
    slang_node_t* pack_offsets, 
    slang_node_t* vd_registers, 
    slang_node_t* annotations) {
    slang_node_t* vd = init_slang_node(malloc(sizeof(slang_node_t)));
    vd->tokentype = VARIABLE_DECL;
    slang_assert(type && ident);
    slang_node_attach_child(vd, type);
    vd->varDecl.type = type;
    slang_node_attach_child(vd, ident);
    vd->varDecl.identifier = ident;
    if (semantics) {
        slang_node_attach_child(vd, semantics);
        vd->varDecl.semantics = semantics;
    }
    if (pack_offsets) {
        slang_node_attach_child(vd, pack_offsets);
        vd->varDecl.packOffsets = pack_offsets;
    }
    if (vd_registers) {
        slang_node_attach_child(vd, vd_registers);
        vd->varDecl.registers = vd_registers;
    }
    if (annotations) {
        slang_node_attach_child(vd, annotations);
        vd->varDecl.annotations = annotations;
    }
    return vd;
}

slang_node_t* new_slang_struct_decl(slang_node_t* identifier, slang_node_t* member_list) {
    slang_node_t* sd = init_slang_node(malloc(sizeof(slang_node_t)));
    sd->tokentype = STRUCT;
    if (identifier) {
        sd->structDecl.identifier = identifier;
        slang_node_attach_child(sd, identifier);
        slang_sym_type_add(identifier->ident);
    }
    if (member_list) {
        sd->structDecl.memberList = member_list;
        slang_node_attach_child(sd, member_list);
    }
    return sd;
}

slang_node_t* new_slang_struct_member_decl(slang_node_t* type_specifier, slang_node_t* identifier, slang_node_t* semantic) {
    slang_node_t* smd = init_slang_node(malloc(sizeof(slang_node_t)));
    slang_assert(type_specifier && identifier);
    smd->tokentype = STRUCT_MEMBER_DECL;
    smd->structMemberDecl.typeSpecifiers = type_specifier;
    slang_node_attach_child(smd, type_specifier);
    smd->structMemberDecl.identifier = identifier;
    slang_node_attach_child(smd, identifier);
    if (semantic) {
        smd->structMemberDecl.semantic = semantic;
        slang_node_attach_child(smd, semantic);
    }
    return smd;
}

slang_node_t* new_slang_cbuffer_tbuffer_decl(
    slang_node_t* identifier,
    slang_node_t* register_node,
    slang_node_t* member_list) {
    slang_node_t* ctb = init_slang_node(malloc(sizeof(slang_node_t)));
    slang_assert(identifier);
    ctb->tokentype = CBUFFER_TBUFFER_DECL;
    slang_node_attach_child(ctb, identifier);
    ctb->bufferDecl.identifier = identifier;
    if (register_node) {
        slang_node_attach_child(ctb, register_node);
        ctb->bufferDecl.registerList = register_node;
    }
    if (member_list) {
        slang_node_attach_child(ctb, member_list);
        ctb->bufferDecl.memberList = member_list;
    }
    return ctb;
}

slang_node_t* new_slang_buffer_member_decl(
    slang_node_t* type_specifier,
    slang_node_t* identifier,
    slang_node_t* semantic,
    slang_node_t* register_list,
    slang_node_t* pack_offset) {
    slang_node_t* bmd = init_slang_node(malloc(sizeof(slang_node_t)));
    bmd->tokentype = BUFFER_MEMBER_DECLARATION;
    slang_assert(type_specifier && identifier);
    slang_node_attach_child(bmd, type_specifier);
    bmd->bufferMemberDecl.typeSpecifiers = type_specifier;
    slang_node_attach_child(bmd, identifier);
    bmd->bufferMemberDecl.identifier = identifier;
    if (semantic) {
        slang_node_attach_child(bmd, semantic);
        bmd->bufferMemberDecl.semantic = semantic;
    }
    if (register_list) {
        slang_node_attach_child(bmd, register_list);
        bmd->bufferMemberDecl.registerList = register_list;
    }
    if (pack_offset) {
        slang_node_attach_child(bmd, pack_offset);
        bmd->bufferMemberDecl.packOffsets = pack_offset;
    }
    return bmd;
}


slang_node_t* new_slang_function_arg(
    slang_node_t* type_specifier,
    slang_node_t* identifier,
    slang_node_t* semantic) {
    slang_node_t* fna = init_slang_node(malloc(sizeof(slang_node_t)));
    fna->tokentype = FUNCTION_ARG;
    slang_assert(type_specifier && identifier);
    slang_node_attach_child(fna, type_specifier);
    fna->functionArg.typeSpecifiers = type_specifier;
    slang_node_attach_child(fna, identifier);
    fna->functionArg.identifier = identifier;
    if (semantic) {
        slang_node_attach_child(fna, semantic);
        fna->functionArg.semantic = semantic;
    }
    return fna;
}
slang_node_t* new_slang_function_declarator(
    slang_node_t* type_specifier,
    slang_node_t* identifier,
    slang_node_t* args,
    slang_node_t* semantic) {
    slang_node_t* fn = init_slang_node(malloc(sizeof(slang_node_t)));
    fn->tokentype = FUNCTION;
    slang_assert(type_specifier && identifier);
    slang_node_attach_child(fn, type_specifier);
    fn->functionDecl.typeSpecifiers = type_specifier;
    slang_node_attach_child(fn, identifier);
    fn->functionDecl.identifier = identifier;
    if (args) {
        fn->functionDecl.args = args;
        slang_node_attach_child(fn, args);
    }
    if (semantic) {
        slang_node_attach_child(fn, semantic);
        fn->functionDecl.semantic = semantic;
    }
    return fn;
}

void slang_node_attach_children(slang_node_t* parent, ...) {
    slang_node_t* temp;
    int child_i = 0;
    va_list vl;
    va_start(vl, parent);
    while (1) {
        temp = va_arg(vl, slang_node_t*);
        if (!temp)
            break;
        slang_node_attach_child(parent, temp);
        ++child_i;
    }
    va_end(vl);
}

static const char* token_type_name [] = {
    "IDENTIFIER",// = 258,
    "TYPE_NAME",// = 259,
    "FLOATCONSTANT",// = 260,
    "DOUBLECONSTANT",// = 261,
    "INTCONSTANT",// = 262,
    "UINTCONSTANT",// = 263,
    "REGISTERCONSTANT",// = 264,
    "STRING_LITERAL",// = 265,
    "TRUE_VALUE",// = 266,
    "FALSE_VALUE",// = 267,
    "VOID",// = 268,
    "FOR",// = 269,
    "IF",// = 270,
    "ELSE",// = 271,
    "DO",// = 272,
    "WHILE",// = 273,
    "CASE",// = 274,
    "DEFAULT",// = 275,
    "BREAK",// = 276,
    "CONTINUE",// = 277,
    "DISCARD",// = 278,
    "SWITCH",// = 279,
    "INLINE",// = 280,
    "RETURN",// = 281,
    "STRUCT",// = 282,
    "CBUFFER",// = 283,
    "TBUFFER",// = 284,
    "BUFFER",// = 285,
    "BOOL",// = 286,
    "BOOL2",// = 287,
    "BOOL3",// = 288,
    "BOOL4",// = 289,
    "BOOL2X2",// = 290,
    "BOOL2X3",// = 291,
    "BOOL2X4",// = 292,
    "BOOL3X2",// = 293,
    "BOOL3X3",// = 294,
    "BOOL3X4",// = 295,
    "BOOL4X2",// = 296,
    "BOOL4X3",// = 297,
    "BOOL4X4",// = 298,
    "INT",// = 299,
    "INT2",// = 300,
    "INT3",// = 301,
    "INT4",// = 302,
    "INT2X2",// = 303,
    "INT2X3",// = 304,
    "INT2X4",// = 305,
    "INT3X2",// = 306,
    "INT3X3",// = 307,
    "INT3X4",// = 308,
    "INT4X2",// = 309,
    "INT4X3",// = 310,
    "INT4X4",// = 311,
    "UINT",// = 312,
    "UINT2",// = 313,
    "UINT3",// = 314,
    "UINT4",// = 315,
    "UINT2X2",// = 316,
    "UINT2X3",// = 317,
    "UINT2X4",// = 318,
    "UINT3X2",// = 319,
    "UINT3X3",// = 320,
    "UINT3X4",// = 321,
    "UINT4X2",// = 322,
    "UINT4X3",// = 323,
    "UINT4X4",// = 324,
    "DWORD",// = 325,
    "HALF",// = 326,
    "HALF2",// = 327,
    "HALF3",// = 328,
    "HALF4",// = 329,
    "HALF2X2",// = 330,
    "HALF2X3",// = 331,
    "HALF2X4",// = 332,
    "HALF3X2",// = 333,
    "HALF3X3",// = 334,
    "HALF3X4",// = 335,
    "HALF4X2",// = 336,
    "HALF4X3",// = 337,
    "HALF4X4",// = 338,
    "FLOAT",// = 339,
    "FLOAT2",// = 340,
    "FLOAT3",// = 341,
    "FLOAT4",// = 342,
    "FLOAT2X2",// = 343,
    "FLOAT2X3",// = 344,
    "FLOAT2X4",// = 345,
    "FLOAT3X2",// = 346,
    "FLOAT3X3",// = 347,
    "FLOAT3X4",// = 348,
    "FLOAT4X2",// = 349,
    "FLOAT4X3",// = 350,
    "FLOAT4X4",// = 351,
    "DOUBLE",// = 352,
    "DOUBLE2",// = 353,
    "DOUBLE3",// = 354,
    "DOUBLE4",// = 355,
    "DOUBLE2X2",// = 356,
    "DOUBLE2X3",// = 357,
    "DOUBLE2X4",// = 358,
    "DOUBLE3X2",// = 359,
    "DOUBLE3X3",// = 360,
    "DOUBLE3X4",// = 361,
    "DOUBLE4X2",// = 362,
    "DOUBLE4X3",// = 363,
    "DOUBLE4X4",// = 364,
    "VECTOR",// = 365,
    "MATRIX",// = 366,
    "SAMPLER",// = 367,
    "SAMPLER1D",// = 368,
    "SAMPLER2D",// = 369,
    "SAMPLER3D",// = 370,
    "SAMPLERCUBE",// = 371,
    "SAMPLERSTATE",// = 372,
    "SAMPLER_STATE",// = 373,
    "TEXTURE1D",// = 374,
    "TEXTURE1DARRAY",// = 375,
    "TEXTURE2D",// = 376,
    "TEXTURE2DARRAY",// = 377,
    "TEXTURE3D",// = 378,
    "TEXTURE3DARRAY",// = 379,
    "TEXTURECUBE",// = 380,
    "STRING",// = 381,
    "LINEAR",// = 382,
    "CENTROID",// = 383,
    "NOINTERPOLATION",// = 384,
    "NOPERSPECTIVE",// = 385,
    "SAMPLE",// = 386,
    "TYPEDEF",// = 387,
    "EXTERN",// = 388,
    "PRECISE",// = 389,
    "SHARED",// = 390,
    "GROUPSHARED",// = 391,
    "STATIC",// = 392,
    "UNIFORM",// = 393,
    "VOLATILE",// = 394,
    "CONST",// = 395,
    "ROW_MAJOR",// = 396,
    "COLUMN_MAJOR",// = 397,
    "REGISTER",// = 398,
    "PACKOFFSET",// = 399,
    "LEFT_OP",// = 400,
    "RIGHT_OP",// = 401,
    "INC_OP",// = 402,
    "DEC_OP",// = 403,
    "LE_OP",// = 404,
    "GE_OP",// = 405,
    "EQ_OP",// = 406,
    "NE_OP",// = 407,
    "AND_OP",// = 408,
    "OR_OP",// = 409,
    "XOR_OP",// = 410,
    "MUL_ASSIGN",// = 411,
    "DIV_ASSIGN",// = 412,
    "ADD_ASSIGN",// = 413,
    "MOD_ASSIGN",// = 414,
    "LEFT_ASSIGN",// = 415,
    "RIGHT_ASSIGN",// = 416,
    "AND_ASSIGN",// = 417,
    "XOR_ASSIGN",// = 418,
    "OR_ASSIGN",// = 419,
    "SUB_ASSIGN",// = 420,
    "VS",// = 421,
    "PS",// = 422,
    "GS",// = 423,
    "DS",// = 424,
    "HS",// = 425,
    "TRANSLATION_UNIT",// = 426,
    "COMPOUND_STATEMENT",// = 427,
    "BLOCK_ITEM_LIST",// = 428,
    "FUNCTION",// = 429,
    "FUNCTION_ARG_LIST",// = 430,
    "FUNCTION_ARG",// = 431,
    "ANNOTATION_LIST",// = 432,
    "INITIALIZER_LIST",// = 433,
    "INPUT_OUTPUT_QUALIFIER_LIST",// = 434,
    "ARGUMENT_EXPRESSION_LIST",// = 435,
    "INIT_DECLARATOR_LIST",// = 436,
    "DECLARATOR",// = 437,
    "EXTERNAL_DECLARATION_SPECIFIERS",// = 438,
    "DECLARATION_SPECIFIERS",// = 439,
    "EXTERNAL_VARIABLE_DECLARATION",// = 440,
    "VARIABLE_DECL",// = 441,
    "CBUFFER_TBUFFER_DECL",// = 442,
    "CBUFFER_OR_TBUFFER_SPECIFIERS",// = 443,
    "BUFFER_MEMBER_DECLARATION",// = 444,
    "STRUCT_DECL",// = 445,
    "STRUCT_MEMBER_DECL",// = 446,
    "BUFFER_MEMBER_DECLARATION_LIST",// = 447,
    "BUFFER_SPECIFIER_QUALIFIER_LIST",// = 448,
    "BUFFER_DECLARATOR_LIST",// = 449,
    "STRUCT_MEMBER_DECLARATION_LIST",// = 450,
    "STRUCT_SPECIFIER_QUALIFIER_LIST",// = 451,
    "STRUCT_DECLARATOR_LIST",// = 452,
    "TYPE_SPECIFIER",// = 453,
    "STATEMENT_BLOCK",// = 454,
    "SEMANTIC",// = 455,
    "TYPEDEF_NAME",// = 456,
    "ENUMERATION_CONSTANT",// = 457,
    "TERNARY_OPERATOR",// = 458,
    "EXPRESSION_STATEMENT",// = 459,
    "VARIABLE_DECLARATION",// = 460,
    "NULL_NODE",// = 461
};

void print_slang_node_and_children(slang_node_t* ast_node, FILE* out) {
    if (ast_node) {
        if (ast_node->tokentype == IDENTIFIER) {
            fprintf(out, " \"%p\" [label=\"IDENTIFER:%s\"]\n", ast_node, ast_node->ident);
        } else if (ast_node->tokentype == INTCONSTANT) {
            fprintf(out, " \"%p\" [label=\"%d\"]\n", ast_node, ast_node->int_const);
        } else if (ast_node->tokentype == FLOATCONSTANT) {
            fprintf(out, " \"%p\" [label=\"%f\"]\n", ast_node, ast_node->float_const);
        } else if (ast_node->tokentype == REGISTER) {
            fprintf(out, " \"%p\" [label=\"register(%d, %d)\"]\n", ast_node,  ast_node->regConst.reg_index, ast_node->regConst.reg_offset);
        } else if (ast_node->tokentype == SEMANTIC) {
            fprintf(out, " \"%p\" [label=\"semantic:%s\"]\n", ast_node, ast_node->ident);
        } else if (ast_node->tokentype == STRING_LITERAL) {
            int l = strlen(ast_node->ident+1)-1;
            fprintf(out, " \"%p\" [label=\"STRING_LITERAL:%.*s\"]\n", ast_node, l, ast_node->ident+1);
        } else if (ast_node->tokentype == DECLARATOR) {
            int l = strlen(ast_node->declarator.ident);
            fprintf(out, " \"%p\" [label=\"DECLARATOR:%.*s", ast_node, l, ast_node->declarator.ident);
            if (ast_node->declarator.function_prototype) {
                fprintf(out, "(func_prototype)\"]\n");
            }else if (ast_node->declarator.arraySizeChild) {
                fprintf(out, "[]\"]\n"); //declarator.arraySizeChild contains the expression
            } else if (ast_node->declarator.arraySize == 1) {
                fprintf(out, "\"]\n");
            } else if (ast_node->declarator.arraySize == 0) {
                fprintf(out, "[{unsized}]\"]\n");
            }
        } else if (ast_node->tokentype < 128) {
            char c = (char)ast_node->tokentype;
            fprintf(out, " \"%p\" [label=\"%c\"]\n", ast_node, c);
        } else {
            fprintf(out, " \"%p\" [label=\"%s\"]\n", ast_node, token_type_name[ast_node->tokentype - IDENTIFIER]);
        }
        if (ast_node->firstChild) {
            slang_node_t* child = ast_node->firstChild;
            do {
                print_slang_node_and_children(child, out);
                fprintf(out, " \"%p\"->\"%p\"\n", ast_node, child);
                child = child->siblingNext;
            } while (child != ast_node->firstChild);
        }
    }
}

void print_slang_AST(slang_node_t* ast_root, FILE* out) {
    slang_node_t* ast_node = ast_root;
    fprintf(out, "digraph {\n");
    if (ast_node) {
        print_slang_node_and_children(ast_node, out);
    }
    fprintf(out, "}\n");
}
