/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */
#pragma once

#include <stdio.h>

#define slang_trap __debugbreak()
#define slang_assert(x) if (!(x)) slang_trap;

typedef struct register_const {
    int reg_index;
    int reg_offset;
    struct slang_node* profileNode; 
} register_const_t;

typedef struct slang_node {
    int tokentype;
    union {
        char* ident;
        int int_const;
        float float_const;
        unsigned int uint_const;
        double double_const;
        register_const_t regConst;
        struct {
            char* ident;
            unsigned int arraySize; // 0 for unsized, 1 non array, arraySizeChild != NULL for other cases
            struct slang_node* arraySizeChild;
            int function_prototype;
        } declarator;
        struct {
            struct slang_node* storageClasses;
            struct slang_node* typeModifiers;
            struct slang_node* type;
            struct slang_node* identifier;
            struct slang_node* semantics;
            struct slang_node* packOffsets;
            struct slang_node* registers;
            struct slang_node* annotations;
        } varDecl;
        struct {
            struct slang_node* identifier;
            struct slang_node* registerList;
            struct slang_node* memberList;
        } bufferDecl;
        struct {
            struct slang_node* typeSpecifiers;
            struct slang_node* identifier;
            struct slang_node* semantic;
            struct slang_node* registerList;
            struct slang_node* packOffsets;
        } bufferMemberDecl;
        struct {
            struct slang_node* identifier;
            struct slang_node* memberList;
        } structDecl;
        struct {
            struct slang_node* typeSpecifiers;
            struct slang_node* identifier;
            struct slang_node* semantic;
        } structMemberDecl;
        struct {
            struct slang_node* declarationSpecifiers;
            struct slang_node* declarator;
            struct slang_node* body;
        } functionDecl;
        struct {
            struct slang_node* typeSpecifiers;
            struct slang_node* identifier;
            struct slang_node* semantic;
        } functionArg;
        struct {
            struct slang_node* expression;
            struct slang_node* statements;
        } whileLoop;
        struct {
            struct slang_node* start;
            struct slang_node* loop_check; 
            struct slang_node* iter;
            struct slang_node* statements;
        } forLoop;
        struct {
            struct slang_node* test;
            struct slang_node* statements;
            struct slang_node* elseClause;
        } ifNode;
        struct {
            struct slang_node* statements;
        } elseNode;
        struct {
            struct slang_node* test;
            struct slang_node* statements;
        } switchNode;
        struct {
            struct slang_node* constant;
            struct slang_node* statements;
        } caseNode;
        struct {
            struct slang_node* statements;
        } defaultCaseNode;
        struct {
            struct slang_node* test;
            struct slang_node* trueClause;
            struct slang_node* falseClause;
        } ternaryOperator;
    };
    struct slang_node* firstChild, *parent;
    struct slang_node* siblingNext, *siblingPrev;
} slang_node_t;


typedef struct slang_parse_context {
    char* current_file;
    slang_node_t* root;
    void *scanner; //Opaque handle to lexer context
    FILE* fin;
} slang_parse_context_t;

slang_node_t* new_slang_node(int code);
slang_node_t* new_slang_null_node();
slang_node_t* new_slang_identifier(const char* ident);
slang_node_t* new_slang_semantic(const char* ident);
slang_node_t* new_slang_int_constant(int int_str);
slang_node_t* new_slang_float_constant(float float_str);
slang_node_t* new_slang_string_literal(const char* ident);
slang_node_t* new_slang_register_constant(slang_node_t* profile, int reg_index, int reg_offset);
slang_node_t* new_slang_var_decl( 
    slang_node_t* type, 
    slang_node_t* ident, 
    slang_node_t* semantics,
    slang_node_t* pack_offsets, 
    slang_node_t* vd_registers,
    slang_node_t* annotations);
slang_node_t* new_slang_struct_decl(
    slang_node_t* identifier,
    slang_node_t* member_list);
slang_node_t* new_slang_struct_member_decl(
    slang_node_t* type_specifier,
    slang_node_t* identifier,
    slang_node_t* semantic);
slang_node_t* new_slang_cbuffer_tbuffer_decl(
    slang_node_t* identifier,
    slang_node_t* register_node,
    slang_node_t* member_list);
slang_node_t* new_slang_buffer_member_decl(
    slang_node_t* type_specifier,
    slang_node_t* identifier,
    slang_node_t* semantic,
    slang_node_t* register_list,
    slang_node_t* pack_offset);
slang_node_t* new_slang_function_arg(
    slang_node_t* type_specifier,
    slang_node_t* identifier,
    slang_node_t* semantic);
slang_node_t* new_slang_while_node(
    slang_node_t* expression,
    slang_node_t* statements);
slang_node_t* new_slang_do_while_node(
    slang_node_t* expression,
    slang_node_t* statements);
slang_node_t* new_slang_for_loop_node(
    slang_node_t* start,
    slang_node_t* loop_check, 
    slang_node_t* iter,
    slang_node_t* statements);
void slang_node_attach_child(slang_node_t* parent, slang_node_t* child);
void slang_node_attach_child_front(slang_node_t* parent, slang_node_t* child);
void slang_node_attach_children(slang_node_t* parent, ...);
void slang_node_make_sibling(slang_node_t* node, slang_node_t* new_sibling);
void slang_node_make_siblings(slang_node_t* node, ...);

char* slang_copy_string(const char* in_str);

//Here, but only temp
void print_slang_AST(slang_node_t* ast_root, FILE* out);