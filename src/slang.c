#pragma once

#include "slang.h"
#include "slang.tab.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

slang_node_t* init_slang_node(slang_node_t* n) {
    n->tokentype = ~0UL;
    n->ident = NULL;
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

slang_node_t* new_slang_identifier(const char* ident) {
    slang_node_t* temp = init_slang_node(malloc(sizeof(slang_node_t)));
    temp->tokentype = IDENTIFIER;
    temp->ident = strdup(ident);
    return temp;
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
    "TRUE_VALUE", // = 263,
    "FALSE_VALUE", // = 264,
    "VOID", // = 265,
    "FOR", // = 266,
    "IF", // = 267,
    "ELSE", // = 268,
    "DO", // = 269,
    "WHILE", // = 270,
    "CASE", // = 271,
    "DEFAULT", // = 272,
    "BREAK", // = 273,
    "CONTINUE", // = 274,
    "DISCARD", // = 275,
    "SWITCH", // = 276,
    "RETURN", // = 277,
    "CONST", // = 278,
    "STATIC", // = 279,
    "CBUFFER", // = 280,
    "BUFFER", // = 281,
    "BOOL", // = 282,
    "BOOL2", // = 283,
    "BOOL3", // = 284,
    "BOOL4", // = 285,
    "BOOL2X2", // = 286,
    "BOOL2X3", // = 287,
    "BOOL2X4", // = 288,
    "BOOL3X2", // = 289,
    "BOOL3X3", // = 290,
    "BOOL3X4", // = 291,
    "BOOL4X2", // = 292,
    "BOOL4X3", // = 293,
    "BOOL4X4", // = 294,
    "INT", // = 295,
    "INT2", // = 296,
    "INT3", // = 297,
    "INT4", // = 298,
    "INT2X2", // = 299,
    "INT2X3", // = 300,
    "INT2X4", // = 301,
    "INT3X2", // = 302,
    "INT3X3", // = 303,
    "INT3X4", // = 304,
    "INT4X2", // = 305,
    "INT4X3", // = 306,
    "INT4X4", // = 307,
    "UINT", // = 308,
    "UINT2", // = 309,
    "UINT3", // = 310,
    "UINT4", // = 311,
    "UINT2X2", // = 312,
    "UINT2X3", // = 313,
    "UINT2X4", // = 314,
    "UINT3X2", // = 315,
    "UINT3X3", // = 316,
    "UINT3X4", // = 317,
    "UINT4X2", // = 318,
    "UINT4X3", // = 319,
    "UINT4X4", // = 320,
    "DWORD", // = 321,
    "HALF", // = 322,
    "HALF2", // = 323,
    "HALF3", // = 324,
    "HALF4", // = 325,
    "HALF2X2", // = 326,
    "HALF2X3", // = 327,
    "HALF2X4", // = 328,
    "HALF3X2", // = 329,
    "HALF3X3", // = 330,
    "HALF3X4", // = 331,
    "HALF4X2", // = 332,
    "HALF4X3", // = 333,
    "HALF4X4", // = 334,
    "FLOAT", // = 335,
    "FLOAT2", // = 336,
    "FLOAT3", // = 337,
    "FLOAT4", // = 338,
    "FLOAT2X2", // = 339,
    "FLOAT2X3", // = 340,
    "FLOAT2X4", // = 341,
    "FLOAT3X2", // = 342,
    "FLOAT3X3", // = 343,
    "FLOAT3X4", // = 344,
    "FLOAT4X2", // = 345,
    "FLOAT4X3", // = 346,
    "FLOAT4X4", // = 347,
    "DOUBLE", // = 348,
    "DOUBLE2", // = 349,
    "DOUBLE3", // = 350,
    "DOUBLE4", // = 351,
    "DOUBLE2X2", // = 352,
    "DOUBLE2X3", // = 353,
    "DOUBLE2X4", // = 354,
    "DOUBLE3X2", // = 355,
    "DOUBLE3X3", // = 356,
    "DOUBLE3X4", // = 357,
    "DOUBLE4X2", // = 358,
    "DOUBLE4X3", // = 359,
    "DOUBLE4X4", // = 360,
    "VECTOR", // = 361,
    "MATRIX", // = 362,
    "SAMPLER", // = 363,
    "SAMPLER1D", // = 364,
    "SAMPLER2D", // = 365,
    "SAMPLER3D", // = 366,
    "SAMPLERCUBE", // = 367,
    "SAMPLERSTATE", // = 368,
    "SAMPLER_STATE", // = 369,
    "TEXTURE1D", // = 370,
    "TEXTURE1DARRAY", // = 371,
    "TEXTURE2D", // = 372,
    "TEXTURE2DARRAY", // = 373,
    "TEXTURE3D", // = 374,
    "TEXTURE3DARRAY", // = 375,
    "TEXTURECUBE", // = 376,
    "STRUCT", // = 377,
    "LINEAR_MODIFIER", // = 378,
    "CENTROID_MODIFIER", // = 379,
    "NOINTERPOLATION_MODIFIER", // = 380,
    "NOPERSPECTIVE_MODIFIER", // = 381,
    "SAMPLE_MODIFIER", // = 382,
    "TYPEDEF", // = 383,
    "LEFT_OP", // = 384,
    "RIGHT_OP", // = 385,
    "INC_OP", // = 386,
    "DEC_OP", // = 387,
    "LE_OP", // = 388,
    "GE_OP", // = 389,
    "EQ_OP", // = 390,
    "NE_OP", // = 391,
    "AND_OP", // = 392,
    "OR_OP", // = 393,
    "XOR_OP", // = 394,
    "MUL_ASSIGN", // = 395,
    "DIV_ASSIGN", // = 396,
    "ADD_ASSIGN", // = 397,
    "MOD_ASSIGN", // = 398,
    "LEFT_ASSIGN", // = 399,
    "RIGHT_ASSIGN", // = 400,
    "AND_ASSIGN", // = 401,
    "XOR_ASSIGN", // = 402,
    "OR_ASSIGN", // = 403,
    "SUB_ASSIGN", // = 404,
    "PLUS", // = 405,
    "DASH", // = 406,
    "PERCENT", // = 407,
    "STAR", // = 408,
    "SLASH", // = 409,
    "TILDE", // = 410,
    "BANG", // = 411,
    "CARET", // = 412,
    "LEFT_PAREN", // = 413,
    "RIGHT_PAREN", // = 414,
    "LEFT_BRACE", // = 415,
    "RIGHT_BRACE", // = 416,
    "SEMICOLON", // = 417,
    "LEFT_ANGLE", // = 418,
    "RIGHT_ANGLE", // = 419,
    "DOT", // = 420,
    "COMMA", // = 421,
    "LEFT_BRACKET", // = 422,
    "RIGHT_BRACKET", // = 423,
    "VERTICAL_BAR", // = 424,
    "COLON", // = 425,
    "EQUAL", // = 426,
    "AMPERSAND", // = 427,
    "QUESTION", // = 428,
    "TRANSLATION_UNIT", // = 429,
    "FUNCTION_DEFINITION", // = 430,
    "VARIABLE_DECL", // = 431,
    "TYPE_SPECIFIER", // = 432,
    "STATEMENT_BLOCK", // = 433,
    "TYPEDEF_NAME", // = 434,
    "ENUMERATION_CONSTANT", // = 435,
    "TERNARY_OPERATOR", // = 436,
    "NULL_NODE", // = 437
};

void print_slang_node_and_children(slang_node_t* ast_node, FILE* out) {
    if (ast_node) {
        if (ast_node->tokentype == IDENTIFIER) {
            fprintf(out, " \"%p\" [label=\"IDENTIFER:%s\"]\n", ast_node, ast_node->ident);
        }
        else if (ast_node->tokentype == INTCONSTANT) {
            fprintf(out, " \"%p\" [label=\"%d\"]\n", ast_node, ast_node->int_const);
        }
        else if (ast_node->tokentype == FLOATCONSTANT) {
            fprintf(out, " \"%p\" [label=\"%f\"]\n", ast_node, ast_node->float_const);
        }
        else {
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
