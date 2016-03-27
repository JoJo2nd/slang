#pragma once

#include "slang.h"
#include "slang.tab.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

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
    temp->ident = strdup(ident);
    return temp;
}

slang_node_t* new_slang_semantic(const char* ident) {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = SEMANTIC;
    temp->ident = strdup(ident);
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
    temp->ident = strdup(ident);
    return temp;
}    

slang_node_t* new_slang_register_constant(const char* reg_c) {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = REGISTERCONSTANT;
    //TODO: error check these
    temp->regConst.reg_type = *reg_c;
    temp->regConst.int_const = atoi(reg_c+1);
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
    "IDENTIFIER", // = 258,
    "FLOATCONSTANT", // = 259,
    "DOUBLECONSTANT", // = 260,
    "INTCONSTANT", // = 261,
    "UINTCONSTANT", // = 262,
    "REGISTERCONSTANT", // = 263,
    "STRING_LITERAL", // = 264,
    "TRUE_VALUE", // = 265,
    "FALSE_VALUE", // = 266,
    "VOID", // = 267,
    "FOR", // = 268,
    "IF", // = 269,
    "ELSE", // = 270,
    "DO", // = 271,
    "WHILE", // = 272,
    "CASE", // = 273,
    "DEFAULT", // = 274,
    "BREAK", // = 275,
    "CONTINUE", // = 276,
    "DISCARD", // = 277,
    "SWITCH", // = 278,
    "INLINE", // = 279,
    "RETURN", // = 280,
    "STRUCT", // = 281,
    "CBUFFER", // = 282,
    "TBUFFER", // = 283,
    "BUFFER", // = 284,
    "BOOL", // = 285,
    "BOOL2", // = 286,
    "BOOL3", // = 287,
    "BOOL4", // = 288,
    "BOOL2X2", // = 289,
    "BOOL2X3", // = 290,
    "BOOL2X4", // = 291,
    "BOOL3X2", // = 292,
    "BOOL3X3", // = 293,
    "BOOL3X4", // = 294,
    "BOOL4X2", // = 295,
    "BOOL4X3", // = 296,
    "BOOL4X4", // = 297,
    "INT", // = 298,
    "INT2", // = 299,
    "INT3", // = 300,
    "INT4", // = 301,
    "INT2X2", // = 302,
    "INT2X3", // = 303,
    "INT2X4", // = 304,
    "INT3X2", // = 305,
    "INT3X3", // = 306,
    "INT3X4", // = 307,
    "INT4X2", // = 308,
    "INT4X3", // = 309,
    "INT4X4", // = 310,
    "UINT", // = 311,
    "UINT2", // = 312,
    "UINT3", // = 313,
    "UINT4", // = 314,
    "UINT2X2", // = 315,
    "UINT2X3", // = 316,
    "UINT2X4", // = 317,
    "UINT3X2", // = 318,
    "UINT3X3", // = 319,
    "UINT3X4", // = 320,
    "UINT4X2", // = 321,
    "UINT4X3", // = 322,
    "UINT4X4", // = 323,
    "DWORD", // = 324,
    "HALF", // = 325,
    "HALF2", // = 326,
    "HALF3", // = 327,
    "HALF4", // = 328,
    "HALF2X2", // = 329,
    "HALF2X3", // = 330,
    "HALF2X4", // = 331,
    "HALF3X2", // = 332,
    "HALF3X3", // = 333,
    "HALF3X4", // = 334,
    "HALF4X2", // = 335,
    "HALF4X3", // = 336,
    "HALF4X4", // = 337,
    "FLOAT", // = 338,
    "FLOAT2", // = 339,
    "FLOAT3", // = 340,
    "FLOAT4", // = 341,
    "FLOAT2X2", // = 342,
    "FLOAT2X3", // = 343,
    "FLOAT2X4", // = 344,
    "FLOAT3X2", // = 345,
    "FLOAT3X3", // = 346,
    "FLOAT3X4", // = 347,
    "FLOAT4X2", // = 348,
    "FLOAT4X3", // = 349,
    "FLOAT4X4", // = 350,
    "DOUBLE", // = 351,
    "DOUBLE2", // = 352,
    "DOUBLE3", // = 353,
    "DOUBLE4", // = 354,
    "DOUBLE2X2", // = 355,
    "DOUBLE2X3", // = 356,
    "DOUBLE2X4", // = 357,
    "DOUBLE3X2", // = 358,
    "DOUBLE3X3", // = 359,
    "DOUBLE3X4", // = 360,
    "DOUBLE4X2", // = 361,
    "DOUBLE4X3", // = 362,
    "DOUBLE4X4", // = 363,
    "VECTOR", // = 364,
    "MATRIX", // = 365,
    "SAMPLER", // = 366,
    "SAMPLER1D", // = 367,
    "SAMPLER2D", // = 368,
    "SAMPLER3D", // = 369,
    "SAMPLERCUBE", // = 370,
    "SAMPLERSTATE", // = 371,
    "SAMPLER_STATE", // = 372,
    "TEXTURE1D", // = 373,
    "TEXTURE1DARRAY", // = 374,
    "TEXTURE2D", // = 375,
    "TEXTURE2DARRAY", // = 376,
    "TEXTURE3D", // = 377,
    "TEXTURE3DARRAY", // = 378,
    "TEXTURECUBE", // = 379,
    "STRING", // = 380,
    "LINEAR", // = 381,
    "CENTROID", // = 382,
    "NOINTERPOLATION", // = 383,
    "NOPERSPECTIVE", // = 384,
    "SAMPLE", // = 385,
    "TYPEDEF", // = 386,
    "EXTERN", // = 387,
    "PRECISE", // = 388,
    "SHARED", // = 389,
    "GROUPSHARED", // = 390,
    "STATIC", // = 391,
    "UNIFORM", // = 392,
    "VOLATILE", // = 393,
    "CONST", // = 394,
    "ROW_MAJOR", // = 395,
    "COLUMN_MAJOR", // = 396,
    "REGISTER", // = 397,
    "PACKOFFSET", // = 398,
    "LEFT_OP", // = 399,
    "RIGHT_OP", // = 400,
    "INC_OP", // = 401,
    "DEC_OP", // = 402,
    "LE_OP", // = 403,
    "GE_OP", // = 404,
    "EQ_OP", // = 405,
    "NE_OP", // = 406,
    "AND_OP", // = 407,
    "OR_OP", // = 408,
    "XOR_OP", // = 409,
    "MUL_ASSIGN", // = 410,
    "DIV_ASSIGN", // = 411,
    "ADD_ASSIGN", // = 412,
    "MOD_ASSIGN", // = 413,
    "LEFT_ASSIGN", // = 414,
    "RIGHT_ASSIGN", // = 415,
    "AND_ASSIGN", // = 416,
    "XOR_ASSIGN", // = 417,
    "OR_ASSIGN", // = 418,
    "SUB_ASSIGN", // = 419,
    "VS", // = 420,
    "PS", // = 421,
    "GS", // = 422,
    "DS", // = 423,
    "HS", // = 424,
    "CS_4_0", // = 425,
    "CS_4_1", // = 426,
    "CS_5_0", // = 427,
    "DS_5_0", // = 428,
    "GS_4_0", // = 429,
    "GS_4_1", // = 430,
    "GS_5_0", // = 431,
    "HS_5_0", // = 432,
    "LIB_4_0", // = 433,
    "LIB_4_1", // = 434,
    "LIB_4_0_LEVEL_9_1", // = 435,
    "LIB_4_0_LEVEL_9_3", // = 436,
    "LIB_5_0", // = 437,
    "PS_2_0", // = 438,
    "PS_2_A", // = 439,
    "PS_2_B", // = 440,
    "PS_2_SW", // = 441,
    "PS_3_0", // = 442,
    "PS_3_SW", // = 443,
    "PS_4_0", // = 444,
    "PS_4_0_LEVEL_9_1", // = 445,
    "PS_4_0_LEVEL_9_3", // = 446,
    "PS_4_0_LEVEL_9_0", // = 447,
    "PS_4_1", // = 448,
    "PS_5_0", // = 449,
    "TX_1_0", // = 450,
    "VS_1_1", // = 451,
    "VS_2_0", // = 452,
    "VS_2_A", // = 453,
    "VS_2_SW", // = 454,
    "VS_3_0", // = 455,
    "VS_3_SW", // = 456,
    "VS_4_0", // = 457,
    "VS_4_0_LEVEL_9_1", // = 458,
    "VS_4_0_LEVEL_9_3", // = 459,
    "VS_4_0_LEVEL_9_0", // = 460,
    "VS_4_1", // = 461,
    "VS_5_0", // = 462,
    "TRANSLATION_UNIT", // = 463,
    "COMPOUND_STATEMENT", // = 464,
    "BLOCK_ITEM_LIST", // = 465,
    "FUNCTION", // = 466,
    "FUNCTION_ARG_LIST", // = 467,
    "FUNCTION_ARG", // = 468,
    "ANNOTATION_LIST", // = 469,
    "INITIALIZER_LIST", // = 470,
    "ARGUMENT_EXPRESSION_LIST", // = 471,
    "BUFFER_MEMBER_DECLARATION_LIST", // = 472,
    "VARIABLE_DECL", // = 473,
    "CBUFFER_TBUFFER_DECL", // = 474,
    "BUFFER_MEMBER_DECLARATION", // = 475,
    "STRUCT_DECL", // = 476,
    "STRUCT_MEMBER_DECL", // = 477,
    "STRUCT_INTERPOLATION_MODIFIER_LIST", // = 478,
    "STRUCT_MEMBER_DECLARATION_LIST", // = 479,
    "TYPE_SPECIFIER", // = 480,
    "STATEMENT_BLOCK", // = 481,
    "SEMANTIC", // = 482,
    "TYPEDEF_NAME", // = 483,
    "ENUMERATION_CONSTANT", // = 484,
    "TERNARY_OPERATOR", // = 485,
    "NULL_NODE", // = 486
};

void print_slang_node_and_children(slang_node_t* ast_node, FILE* out) {
    if (ast_node) {
        if (ast_node->tokentype == IDENTIFIER) {
            fprintf(out, " \"%p\" [label=\"IDENTIFER:%s\"]\n", ast_node, ast_node->ident);
        } else if (ast_node->tokentype == INTCONSTANT) {
            fprintf(out, " \"%p\" [label=\"%d\"]\n", ast_node, ast_node->int_const);
        } else if (ast_node->tokentype == FLOATCONSTANT) {
            fprintf(out, " \"%p\" [label=\"%f\"]\n", ast_node, ast_node->float_const);
        } else if (ast_node->tokentype == REGISTERCONSTANT) {
            fprintf(out, " \"%p\" [label=\"register(%c%d)\"]\n", ast_node, ast_node->regConst.reg_type, ast_node->regConst.int_const);
        } else if (ast_node->tokentype == SEMANTIC) {
            fprintf(out, " \"%p\" [label=\"semantic:%s\"]\n", ast_node, ast_node->ident);
        } else if (ast_node->tokentype == STRING_LITERAL) {
            int l = strlen(ast_node->ident+1)-1;
            fprintf(out, " \"%p\" [label=\"STRING_LITERAL:%.*s\"]\n", ast_node, l, ast_node->ident+1);
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
