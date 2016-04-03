
#include "../../slang.h"
#include "../../slang.tab.h"
#include <unordered_set>
#include <vector>
#include <functional>

#define slang2hlsl_trap __debugbreak()
#define slang2hlsl_assert(x) if (!(x)) slang2hlsl_trap;
#define slang2hlsl_validate(ctx, x, msg, ...) if (!(x)) { fprintf(stderr, msg, __VA_ARGS__); slang2hlsl_trap; }

struct HLSLContext {
    FILE* output = nullptr;
    bool deferRegisterNodes = false;
    int currentRegType = 0;
    std::vector<const slang_node_t*> registerNodeList;
};

typedef int (*NodeAction)(const slang_node_t*, HLSLContext*);
static NodeAction nodeActionTable[NULL_NODE];

static int handleNode(const slang_node_t* ast_node, HLSLContext* ctx) {
    if (!nodeActionTable[ast_node->tokentype])
        return -1;
    return nodeActionTable[ast_node->tokentype](ast_node, ctx);
}

static int handleChildNodes(const slang_node_t* ast_node, HLSLContext* ctx) {
    if (ast_node->firstChild) {
        slang_node_t* child = ast_node->firstChild;
        do {
            int err = handleNode(child, ctx);
            if (err != 0)
                return err;
            child = child->siblingNext;
        } while (child != ast_node->firstChild);
    }
    return 0;
}

static int handleChildNodesOfType(const slang_node_t* ast_node, HLSLContext* ctx, slang_tokentype type) {
    if (ast_node->firstChild) {
        slang_node_t* child = ast_node->firstChild;
        do {
            if (child->tokentype == type) {
                int err = handleNode(child, ctx);
                if (err != 0)
                    return err;
            }
            child = child->siblingNext;
        } while (child != ast_node->firstChild);
    }
    return 0;
}

template< size_t t_array_size > 
static int handleChildNodesNotOfType(const slang_node_t* ast_node, HLSLContext* ctx, slang_tokentype (&types)[t_array_size]) {
    if (ast_node->firstChild) {
        slang_node_t* child = ast_node->firstChild;
        do {
            bool processNode = true;
            for (int i=0; i<t_array_size; ++i) processNode &= types[i] != child->tokentype;
            if (processNode) {
                int err = handleNode(child, ctx);
                if (err != 0)
                    return err;
            }
            child = child->siblingNext;
        } while (child != ast_node->firstChild);
    }
    return 0;
}

const char* getTypename(int token);

static void initialiseActionTable() {
    auto skipAndProcessChildren = [](const slang_node_t* node, HLSLContext* ctx) {
        if (int err = handleChildNodes(node, ctx)) return err;
        return 0;
    };
    nodeActionTable['='] = [](const slang_node_t* node, HLSLContext* ctx) {
        if (int err = handleNode(node->firstChild, ctx)) return err;
        fprintf(ctx->output, "=");
        if (int err = handleNode(node->firstChild->siblingNext, ctx)) return err;
        slang2hlsl_validate(ctx, node->firstChild->siblingNext == node->firstChild->siblingPrev, "assignment/'=' nodes should alwasy have only two children.");
        return 0;
    };
    nodeActionTable[IDENTIFIER] = [](const slang_node_t* node, HLSLContext* ctx) {
        fprintf(ctx->output, "%s ", node->ident);
        if (int err = handleChildNodes(node, ctx)) return err;
        return 0;
    };
    nodeActionTable[FLOATCONSTANT] = [](const slang_node_t* node, HLSLContext* ctx) {
        fprintf(ctx->output, "%.06ff ", node->float_const);
        return 0;
    };
    nodeActionTable[INTCONSTANT] = [](const slang_node_t* node, HLSLContext* ctx) {
        fprintf(ctx->output, "%d ", node->int_const);
        return 0;
    };
    nodeActionTable[BOOL] = 
    nodeActionTable[BOOL2] = 
    nodeActionTable[BOOL3] = 
    nodeActionTable[BOOL4] = 
    nodeActionTable[BOOL2X2] = 
    nodeActionTable[BOOL2X3] = 
    nodeActionTable[BOOL2X4] = 
    nodeActionTable[BOOL3X2] = 
    nodeActionTable[BOOL3X3] = 
    nodeActionTable[BOOL3X4] = 
    nodeActionTable[BOOL4X2] = 
    nodeActionTable[BOOL4X3] = 
    nodeActionTable[BOOL4X4] = 
    nodeActionTable[INT] = 
    nodeActionTable[INT2] = 
    nodeActionTable[INT3] = 
    nodeActionTable[INT4] = 
    nodeActionTable[INT2X2] = 
    nodeActionTable[INT2X3] = 
    nodeActionTable[INT2X4] = 
    nodeActionTable[INT3X2] = 
    nodeActionTable[INT3X3] = 
    nodeActionTable[INT3X4] = 
    nodeActionTable[INT4X2] = 
    nodeActionTable[INT4X3] = 
    nodeActionTable[INT4X4] = 
    nodeActionTable[UINT] = 
    nodeActionTable[UINT2] = 
    nodeActionTable[UINT3] = 
    nodeActionTable[UINT4] = 
    nodeActionTable[UINT2X2] = 
    nodeActionTable[UINT2X3] = 
    nodeActionTable[UINT2X4] = 
    nodeActionTable[UINT3X2] = 
    nodeActionTable[UINT3X3] = 
    nodeActionTable[UINT3X4] = 
    nodeActionTable[UINT4X2] = 
    nodeActionTable[UINT4X3] = 
    nodeActionTable[UINT4X4] = 
    nodeActionTable[DWORD] = 
    nodeActionTable[HALF] = 
    nodeActionTable[HALF2] = 
    nodeActionTable[HALF3] = 
    nodeActionTable[HALF4] = 
    nodeActionTable[HALF2X2] = 
    nodeActionTable[HALF2X3] = 
    nodeActionTable[HALF2X4] = 
    nodeActionTable[HALF3X2] = 
    nodeActionTable[HALF3X3] = 
    nodeActionTable[HALF3X4] = 
    nodeActionTable[HALF4X2] = 
    nodeActionTable[HALF4X3] = 
    nodeActionTable[HALF4X4] = 
    nodeActionTable[FLOAT] = 
    nodeActionTable[FLOAT2] = 
    nodeActionTable[FLOAT3] = 
    nodeActionTable[FLOAT4] = 
    nodeActionTable[FLOAT2X2] = 
    nodeActionTable[FLOAT2X3] = 
    nodeActionTable[FLOAT2X4] = 
    nodeActionTable[FLOAT3X2] = 
    nodeActionTable[FLOAT3X3] = 
    nodeActionTable[FLOAT3X4] = 
    nodeActionTable[FLOAT4X2] = 
    nodeActionTable[FLOAT4X3] = 
    nodeActionTable[FLOAT4X4] = 
    nodeActionTable[DOUBLE] = 
    nodeActionTable[DOUBLE2] = 
    nodeActionTable[DOUBLE3] = 
    nodeActionTable[DOUBLE4] = 
    nodeActionTable[DOUBLE2X2] = 
    nodeActionTable[DOUBLE2X3] = 
    nodeActionTable[DOUBLE2X4] = 
    nodeActionTable[DOUBLE3X2] = 
    nodeActionTable[DOUBLE3X3] = 
    nodeActionTable[DOUBLE3X4] = 
    nodeActionTable[DOUBLE4X2] = 
    nodeActionTable[DOUBLE4X3] = 
    nodeActionTable[DOUBLE4X4] = 
    nodeActionTable[VECTOR] = 
    nodeActionTable[MATRIX] = 
    nodeActionTable[SAMPLER] = 
    nodeActionTable[SAMPLER1D] = 
    nodeActionTable[SAMPLER2D] = 
    nodeActionTable[SAMPLER3D] = 
    nodeActionTable[SAMPLERCUBE] = 
    nodeActionTable[SAMPLERSTATE] = 
    nodeActionTable[SAMPLER_STATE] = 
    nodeActionTable[TEXTURE1D] = 
    nodeActionTable[TEXTURE1DARRAY] = 
    nodeActionTable[TEXTURE2D] = 
    nodeActionTable[TEXTURE2DARRAY] = 
    nodeActionTable[TEXTURE3D] = 
    nodeActionTable[TEXTURE3DARRAY] = 
    nodeActionTable[TEXTURECUBE] = 
    nodeActionTable[STRING] = 
    nodeActionTable[LINEAR] = 
    nodeActionTable[CENTROID] = 
    nodeActionTable[NOINTERPOLATION] = 
    nodeActionTable[NOPERSPECTIVE] = 
    nodeActionTable[SAMPLE] = 
    nodeActionTable[TYPEDEF] = 
    nodeActionTable[SHARED] = 
    nodeActionTable[STATIC] = 
    nodeActionTable[CONST] = 
    nodeActionTable[ROW_MAJOR] = 
    nodeActionTable[COLUMN_MAJOR] =
    nodeActionTable[STRUCT] =
    [](const slang_node_t* node, HLSLContext* ctx) {
        fprintf(ctx->output, "%s ", getTypename(node->tokentype));
        handleChildNodes(node, ctx);
        return 0;
    };
    nodeActionTable[REGISTER] = // TODO: handle register correctly
    [](const slang_node_t* node, HLSLContext* ctx) { 
        if (ctx->deferRegisterNodes) {
            ctx->registerNodeList.push_back(node);
        } else {
            char registerType[] = { 'c' };
            char offset[] = {'x', 'y', 'z', 'w'};
            if (node->regConst.profileNode && node->regConst.reg_offset > 0)
            {
                fprintf(ctx->output, "%s(%s, %c%d.%c) ", getTypename(REGISTER), getTypename(node->regConst.profileNode->tokentype), registerType[ctx->currentRegType], node->regConst.reg_index, offset[node->regConst.reg_offset]);
            }
            else if (node->regConst.profileNode)
            {
                fprintf(ctx->output, "%s(%s, %c%d) ", getTypename(REGISTER), getTypename(node->regConst.profileNode->tokentype), registerType[ctx->currentRegType], node->regConst.reg_index);
            }
            else if (node->regConst.reg_offset > 0)
            {
                fprintf(ctx->output, "%s(%c%d.%c) ", getTypename(REGISTER), registerType[ctx->currentRegType], node->regConst.reg_index, offset[node->regConst.reg_offset]);
            }
            else
            {
                fprintf(ctx->output, "%s(%c%d) ", getTypename(REGISTER), registerType[ctx->currentRegType], node->regConst.reg_index);
            }
            handleChildNodes(node, ctx);
        }
        return 0;
    };
    nodeActionTable[TRANSLATION_UNIT] = [](const slang_node_t* node, HLSLContext* ctx) {
        fprintf(ctx->output, "/**\nAuto generated HLSL code from slangc.\n**/\n");
        return handleChildNodes(node, ctx);
    };
    nodeActionTable[INITIALIZER_LIST] = [](const slang_node_t* node, HLSLContext* ctx) {
        fprintf(ctx->output, "{");
        slang_node_t* child = node->firstChild;
        do {
            if (int err = handleNode(child, ctx)) return err;
            child = child->siblingNext;
            if (child != node->firstChild) {
                fprintf(ctx->output, ", ");
            }
        } while (child != node->firstChild);
        fprintf(ctx->output, "}");
        return 0;
    };
    nodeActionTable[ARGUMENT_EXPRESSION_LIST] = [](const slang_node_t* node, HLSLContext* ctx) {
        fprintf(ctx->output, "(");
        slang_node_t* child = node->firstChild;
        do {
            if (int err = handleNode(child, ctx)) return err;
            child = child->siblingNext;
            if (child != node->firstChild) {
                fprintf(ctx->output, ", ");
            }
        } while (child != node->firstChild);
        fprintf(ctx->output, ")");
        return 0;
    };
    nodeActionTable[INIT_DECLARATOR_LIST] = 
    nodeActionTable[BUFFER_DECLARATOR_LIST] =
    nodeActionTable[STRUCT_DECLARATOR_LIST] =
    [](const slang_node_t* node, HLSLContext* ctx) {
        slang2hlsl_validate(ctx, node->firstChild, "INIT_DECLARATOR_LIST expected a list of nodes.");
        slang_node_t* child = node->firstChild;
        do {
            if (int err = handleNode(child, ctx)) return err;
            child = child->siblingNext;
            if (child != node->firstChild) {
                fprintf(ctx->output, ", ");
            }
        } while (child != node->firstChild);
        return 0;
    };
    nodeActionTable[DECLARATOR] = [](const slang_node_t* node, HLSLContext* ctx) {
        if (node->declarator.arraySizeChild) {
            fprintf(ctx->output, "%s[ ", node->declarator.ident);
            if (int err = handleNode(node->declarator.arraySizeChild, ctx)) return err;
            fprintf(ctx->output, "]");
        } else if (node->declarator.arraySize == 0) { // unsized
            fprintf(ctx->output, "%s[]", node->declarator.ident);
        } else {
            fprintf(ctx->output, "%s ", node->declarator.ident);
        }
        return 0;
    };
    nodeActionTable[EXTERNAL_DECLARATION_SPECIFIERS] = [](const slang_node_t* node, HLSLContext* ctx) {
        ctx->deferRegisterNodes = true;
        if (int err = handleChildNodes(node, ctx)) return err;
        ctx->deferRegisterNodes = false;
        for (const auto& i : ctx->registerNodeList) {
            handleNode(i, ctx);
        }
        ctx->registerNodeList.clear();

        fprintf(ctx->output, ";\n");
        return 0;
    };
    nodeActionTable[EXTERNAL_VARIABLE_DECLARATION] = skipAndProcessChildren;
    nodeActionTable[CBUFFER_TBUFFER_DECL] = [](const slang_node_t* node, HLSLContext* ctx) {
        fprintf(ctx->output, "%s ", getTypename(CBUFFER));
        slang_tokentype child_order[] = { IDENTIFIER, REGISTER };
        handleChildNodesOfType(node, ctx, child_order[0]);
        handleChildNodesOfType(node, ctx, child_order[1]);
        handleChildNodesNotOfType(node, ctx, child_order);
        fprintf(ctx->output, ";\n");
        return 0;
    };
    nodeActionTable[BUFFER_MEMBER_DECLARATION_LIST] = 
    nodeActionTable[STRUCT_MEMBER_DECLARATION_LIST] =
    [](const slang_node_t* node, HLSLContext* ctx) {
        fprintf(ctx->output, "{\n");
        slang_node_t* child = node->firstChild;
        do {
            if (int err = handleNode(child, ctx)) return err;
            child = child->siblingNext;
        } while (child != node->firstChild);
        fprintf(ctx->output, "}");
        return 0;
    };
    nodeActionTable[BUFFER_SPECIFIER_QUALIFIER_LIST] =
    nodeActionTable[STRUCT_SPECIFIER_QUALIFIER_LIST] =
    [](const slang_node_t* node, HLSLContext* ctx) {
        slang_tokentype first_childs[] = {SEMANTIC};
        //BUFFER should never encounter a SEMANTIC, grammer would force a syntax error first.
        handleChildNodesNotOfType(node, ctx, first_childs);
        handleChildNodesOfType(node, ctx, SEMANTIC);
        fprintf(ctx->output, ";\n");
        return 0;
    };
    nodeActionTable[SEMANTIC] = [](const slang_node_t* node, HLSLContext* ctx) {
        fprintf(ctx->output, "%s(%s) ", getTypename(node->tokentype), node->ident);
        return 0;
    };
}

extern "C" __declspec(dllexport) int process_slang_ast(const slang_node_t* ast_root, FILE* output) {
    HLSLContext context;
    context.output = output;
    if (!context.output) return -1;

    initialiseActionTable();
    const slang_node_t* ast_node = ast_root;
    if (!ast_node) 
        return -2;
    if (!nodeActionTable[ast_node->tokentype])
        return -1;
    int err = nodeActionTable[ast_node->tokentype](ast_node, &context);

    return err;
}


const char* typenames[] = {
    "identifier", // = 258,
    "type_name", // = 259,
    "floatconstant", // = 260,
    "doubleconstant", // = 261,
    "intconstant", // = 262,
    "uintconstant", // = 263,
    "registerconstant", // = 264,
    "string_literal", // = 265,
    "true_value", // = 266,
    "false_value", // = 267,
    "void", // = 268,
    "for", // = 269,
    "if", // = 270,
    "else", // = 271,
    "do", // = 272,
    "while", // = 273,
    "case", // = 274,
    "default", // = 275,
    "break", // = 276,
    "continue", // = 277,
    "discard", // = 278,
    "switch", // = 279,
    "inline", // = 280,
    "return", // = 281,
    "struct", // = 282,
    "cbuffer", // = 283,
    "tbuffer", // = 284,
    "buffer", // = 285,
    "bool", // = 286,
    "bool2", // = 287,
    "bool3", // = 288,
    "bool4", // = 289,
    "bool2x2", // = 290,
    "bool2x3", // = 291,
    "bool2x4", // = 292,
    "bool3x2", // = 293,
    "bool3x3", // = 294,
    "bool3x4", // = 295,
    "bool4x2", // = 296,
    "bool4x3", // = 297,
    "bool4x4", // = 298,
    "int", // = 299,
    "int2", // = 300,
    "int3", // = 301,
    "int4", // = 302,
    "int2x2", // = 303,
    "int2x3", // = 304,
    "int2x4", // = 305,
    "int3x2", // = 306,
    "int3x3", // = 307,
    "int3x4", // = 308,
    "int4x2", // = 309,
    "int4x3", // = 310,
    "int4x4", // = 311,
    "uint", // = 312,
    "uint2", // = 313,
    "uint3", // = 314,
    "uint4", // = 315,
    "uint2x2", // = 316,
    "uint2x3", // = 317,
    "uint2x4", // = 318,
    "uint3x2", // = 319,
    "uint3x3", // = 320,
    "uint3x4", // = 321,
    "uint4x2", // = 322,
    "uint4x3", // = 323,
    "uint4x4", // = 324,
    "dword", // = 325,
    "half", // = 326,
    "half2", // = 327,
    "half3", // = 328,
    "half4", // = 329,
    "half2x2", // = 330,
    "half2x3", // = 331,
    "half2x4", // = 332,
    "half3x2", // = 333,
    "half3x3", // = 334,
    "half3x4", // = 335,
    "half4x2", // = 336,
    "half4x3", // = 337,
    "half4x4", // = 338,
    "float", // = 339,
    "float2", // = 340,
    "float3", // = 341,
    "float4", // = 342,
    "float2x2", // = 343,
    "float2x3", // = 344,
    "float2x4", // = 345,
    "float3x2", // = 346,
    "float3x3", // = 347,
    "float3x4", // = 348,
    "float4x2", // = 349,
    "float4x3", // = 350,
    "float4x4", // = 351,
    "double", // = 352,
    "double2", // = 353,
    "double3", // = 354,
    "double4", // = 355,
    "double2x2", // = 356,
    "double2x3", // = 357,
    "double2x4", // = 358,
    "double3x2", // = 359,
    "double3x3", // = 360,
    "double3x4", // = 361,
    "double4x2", // = 362,
    "double4x3", // = 363,
    "double4x4", // = 364,
    "vector", // = 365,
    "matrix", // = 366,
    "sampler", // = 367,
    "sampler1d", // = 368,
    "sampler2d", // = 369,
    "sampler3d", // = 370,
    "samplercube", // = 371,
    "samplerstate", // = 372,
    "sampler_state", // = 373,
    "texture1d", // = 374,
    "texture1darray", // = 375,
    "texture2d", // = 376,
    "texture2darray", // = 377,
    "texture3d", // = 378,
    "texture3darray", // = 379,
    "texturecube", // = 380,
    "string", // = 381,
    "linear", // = 382,
    "centroid", // = 383,
    "nointerpolation", // = 384,
    "noperspective", // = 385,
    "sample", // = 386,
    "typedef", // = 387,
    "extern", // = 388,
    "precise", // = 389,
    "shared", // = 390,
    "groupshared", // = 391,
    "static", // = 392,
    "uniform", // = 393,
    "volatile", // = 394,
    "const", // = 395,
    "row_major", // = 396,
    "column_major", // = 397,
    ": register", // = 398,
    ": packoffset", // = 399,
    "left_op", // = 400,
    "right_op", // = 401,
    "inc_op", // = 402,
    "dec_op", // = 403,
    "le_op", // = 404,
    "ge_op", // = 405,
    "eq_op", // = 406,
    "ne_op", // = 407,
    "and_op", // = 408,
    "or_op", // = 409,
    "xor_op", // = 410,
    "mul_assign", // = 411,
    "div_assign", // = 412,
    "add_assign", // = 413,
    "mod_assign", // = 414,
    "left_assign", // = 415,
    "right_assign", // = 416,
    "and_assign", // = 417,
    "xor_assign", // = 418,
    "or_assign", // = 419,
    "sub_assign", // = 420,
    "vs", // = 421,
    "ps", // = 422,
    "gs", // = 423,
    "ds", // = 424,
    "hs", // = 425,
    "translation_unit", // = 426,
    "compound_statement", // = 427,
    "block_item_list", // = 428,
    "function", // = 429,
    "function_arg_list", // = 430,
    "function_arg", // = 431,
    "annotation_list", // = 432,
    "initializer_list", // = 433,
    "input_output_qualifier_list", // = 434,
    "argument_expression_list", // = 435,
    "init_declarator_list", // = 436,
    "declarator", // = 437,
    "external_declaration_specifiers", // = 438,
    "external_variable_declaration", // = 439,
    "variable_decl", // = 440,
    "cbuffer_tbuffer_decl", // = 441,
    "buffer_member_declaration", // = 442,
    "struct_decl", // = 443,
    "struct_member_decl", // = 444,
    "buffer_member_declaration_list", // = 445,
    "buffer_specifier_qualifier_list", // = 446,
    "buffer_declarator_list", // = 447,
    "struct_member_declaration_list", // = 448,
    "struct_specifier_qualifier_list", // = 449,
    "struct_declarator_list", // = 450,
    "type_specifier", // = 451,
    "statement_block", // = 452,
    ": semantic", // = 453,
    "typedef_name", // = 454,
    "enumeration_constant", // = 455,
    "ternary_operator", // = 456,
    "null_node", // = 457
};

const char* getTypename(int token) {
    return typenames[token - IDENTIFIER]; 
}