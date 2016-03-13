#pragma once

#include <stdio.h>

typedef struct slang_node {
    int tokentype;
    union {
        char* ident;
        int int_const;
        float float_const;
        unsigned int uint_const;
        double double_const;
    };
    struct slang_node* firstChild, *parent;
    struct slang_node* siblingNext, *siblingPrev;
} slang_node_t;


typedef struct slang_parse_context {
    slang_node_t* root;
    void *scanner; //Opaque handle to lexer context
    FILE* fin;
} slang_parse_context_t;

slang_node_t* new_slang_node(int code);
slang_node_t* new_slang_identifier(const char* ident);
slang_node_t* new_slang_int_constant(int int_str);
slang_node_t* new_slang_float_constant(float float_str);
void slang_node_attach_child(slang_node_t* parent, slang_node_t* child);
void slang_node_attach_children(slang_node_t* parent, ...);