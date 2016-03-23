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
    bmd->bufferMemberDecl.typeSpecifier = type_specifier;
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
     "SWIZZLEMASK_X___", // = 267,
     "SWIZZLEMASK__Y__", // = 268,
     "SWIZZLEMASK___Z_", // = 269,
     "SWIZZLEMASK____W", // = 270,
     "SWIZZLEMASK_R___", // = 271,
     "SWIZZLEMASK__G__", // = 272,
     "SWIZZLEMASK___B_", // = 273,
     "SWIZZLEMASK____A", // = 274,
     "VOID", // = 275,
     "FOR", // = 276,
     "IF", // = 277,
     "ELSE", // = 278,
     "DO", // = 279,
     "WHILE", // = 280,
     "CASE", // = 281,
     "DEFAULT", // = 282,
     "BREAK", // = 283,
     "CONTINUE", // = 284,
     "DISCARD", // = 285,
     "SWITCH", // = 286,
     "RETURN", // = 287,
     "STRUCT", // = 288,
     "CBUFFER", // = 289,
     "TBUFFER", // = 290,
     "BUFFER", // = 291,
     "BOOL", // = 292,
     "BOOL2", // = 293,
     "BOOL3", // = 294,
     "BOOL4", // = 295,
     "BOOL2X2", // = 296,
     "BOOL2X3", // = 297,
     "BOOL2X4", // = 298,
     "BOOL3X2", // = 299,
     "BOOL3X3", // = 300,
     "BOOL3X4", // = 301,
     "BOOL4X2", // = 302,
     "BOOL4X3", // = 303,
     "BOOL4X4", // = 304,
     "INT", // = 305,
     "INT2", // = 306,
     "INT3", // = 307,
     "INT4", // = 308,
     "INT2X2", // = 309,
     "INT2X3", // = 310,
     "INT2X4", // = 311,
     "INT3X2", // = 312,
     "INT3X3", // = 313,
     "INT3X4", // = 314,
     "INT4X2", // = 315,
     "INT4X3", // = 316,
     "INT4X4", // = 317,
     "UINT", // = 318,
     "UINT2", // = 319,
     "UINT3", // = 320,
     "UINT4", // = 321,
     "UINT2X2", // = 322,
     "UINT2X3", // = 323,
     "UINT2X4", // = 324,
     "UINT3X2", // = 325,
     "UINT3X3", // = 326,
     "UINT3X4", // = 327,
     "UINT4X2", // = 328,
     "UINT4X3", // = 329,
     "UINT4X4", // = 330,
     "DWORD", // = 331,
     "HALF", // = 332,
     "HALF2", // = 333,
     "HALF3", // = 334,
     "HALF4", // = 335,
     "HALF2X2", // = 336,
     "HALF2X3", // = 337,
     "HALF2X4", // = 338,
     "HALF3X2", // = 339,
     "HALF3X3", // = 340,
     "HALF3X4", // = 341,
     "HALF4X2", // = 342,
     "HALF4X3", // = 343,
     "HALF4X4", // = 344,
     "FLOAT", // = 345,
     "FLOAT2", // = 346,
     "FLOAT3", // = 347,
     "FLOAT4", // = 348,
     "FLOAT2X2", // = 349,
     "FLOAT2X3", // = 350,
     "FLOAT2X4", // = 351,
     "FLOAT3X2", // = 352,
     "FLOAT3X3", // = 353,
     "FLOAT3X4", // = 354,
     "FLOAT4X2", // = 355,
     "FLOAT4X3", // = 356,
     "FLOAT4X4", // = 357,
     "DOUBLE", // = 358,
     "DOUBLE2", // = 359,
     "DOUBLE3", // = 360,
     "DOUBLE4", // = 361,
     "DOUBLE2X2", // = 362,
     "DOUBLE2X3", // = 363,
     "DOUBLE2X4", // = 364,
     "DOUBLE3X2", // = 365,
     "DOUBLE3X3", // = 366,
     "DOUBLE3X4", // = 367,
     "DOUBLE4X2", // = 368,
     "DOUBLE4X3", // = 369,
     "DOUBLE4X4", // = 370,
     "VECTOR", // = 371,
     "MATRIX", // = 372,
     "SAMPLER", // = 373,
     "SAMPLER1D", // = 374,
     "SAMPLER2D", // = 375,
     "SAMPLER3D", // = 376,
     "SAMPLERCUBE", // = 377,
     "SAMPLERSTATE", // = 378,
     "SAMPLER_STATE", // = 379,
     "TEXTURE1D", // = 380,
     "TEXTURE1DARRAY", // = 381,
     "TEXTURE2D", // = 382,
     "TEXTURE2DARRAY", // = 383,
     "TEXTURE3D", // = 384,
     "TEXTURE3DARRAY", // = 385,
     "TEXTURECUBE", // = 386,
     "STRING", // = 387,
     "LINEAR", // = 388,
     "CENTROID", // = 389,
     "NOINTERPOLATION", // = 390,
     "NOPERSPECTIVE", // = 391,
     "SAMPLE", // = 392,
     "TYPEDEF", // = 393,
     "EXTERN", // = 394,
     "PRECISE", // = 395,
     "SHARED", // = 396,
     "GROUPSHARED", // = 397,
     "STATIC", // = 398,
     "UNIFORM", // = 399,
     "VOLATILE", // = 400,
     "CONST", // = 401,
     "ROW_MAJOR", // = 402,
     "COLUMN_MAJOR", // = 403,
     "REGISTER", // = 404,
     "PACKOFFSET", // = 405,
     "LEFT_OP", // = 406,
     "RIGHT_OP", // = 407,
     "INC_OP", // = 408,
     "DEC_OP", // = 409,
     "LE_OP", // = 410,
     "GE_OP", // = 411,
     "EQ_OP", // = 412,
     "NE_OP", // = 413,
     "AND_OP", // = 414,
     "OR_OP", // = 415,
     "XOR_OP", // = 416,
     "MUL_ASSIGN", // = 417,
     "DIV_ASSIGN", // = 418,
     "ADD_ASSIGN", // = 419,
     "MOD_ASSIGN", // = 420,
     "LEFT_ASSIGN", // = 421,
     "RIGHT_ASSIGN", // = 422,
     "AND_ASSIGN", // = 423,
     "XOR_ASSIGN", // = 424,
     "OR_ASSIGN", // = 425,
     "SUB_ASSIGN", // = 426,
     "VS", // = 427,
     "PS", // = 428,
     "GS", // = 429,
     "DS", // = 430,
     "HS", // = 431,
     "CS_4_0", // = 432,
     "CS_4_1", // = 433,
     "CS_5_0", // = 434,
     "DS_5_0", // = 435,
     "GS_4_0", // = 436,
     "GS_4_1", // = 437,
     "GS_5_0", // = 438,
     "HS_5_0", // = 439,
     "LIB_4_0", // = 440,
     "LIB_4_1", // = 441,
     "LIB_4_0_LEVEL_9_1", // = 442,
     "LIB_4_0_LEVEL_9_3", // = 443,
     "LIB_5_0", // = 444,
     "PS_2_0", // = 445,
     "PS_2_A", // = 446,
     "PS_2_B", // = 447,
     "PS_2_SW", // = 448,
     "PS_3_0", // = 449,
     "PS_3_SW", // = 450,
     "PS_4_0", // = 451,
     "PS_4_0_LEVEL_9_1", // = 452,
     "PS_4_0_LEVEL_9_3", // = 453,
     "PS_4_0_LEVEL_9_0", // = 454,
     "PS_4_1", // = 455,
     "PS_5_0", // = 456,
     "TX_1_0", // = 457,
     "VS_1_1", // = 458,
     "VS_2_0", // = 459,
     "VS_2_A", // = 460,
     "VS_2_SW", // = 461,
     "VS_3_0", // = 462,
     "VS_3_SW", // = 463,
     "VS_4_0", // = 464,
     "VS_4_0_LEVEL_9_1", // = 465,
     "VS_4_0_LEVEL_9_3", // = 466,
     "VS_4_0_LEVEL_9_0", // = 467,
     "VS_4_1", // = 468,
     "VS_5_0", // = 469,
     "TRANSLATION_UNIT", // = 470,
     "FUNCTION_DEFINITION", // = 471,
     "ANNOTATION_LIST", // = 472,
     "INITIALIZER_LIST", // = 473,
     "STRUCT_MEMBER_DECLARATION_LIST", // = 474,
     "VARIABLE_DECL", // = 475,
     "CBUFFER_TBUFFER_DECL", // = 476,
     "BUFFER_MEMBER_DECLARATION", // = 477,
     "TYPE_SPECIFIER", // = 478,
     "STATEMENT_BLOCK", // = 479,
     "SEMANTIC", // = 480,
     "TYPEDEF_NAME", // = 481,
     "ENUMERATION_CONSTANT", // = 482,
     "TERNARY_OPERATOR", // = 483,
     "NULL_NODE", // = 484
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
