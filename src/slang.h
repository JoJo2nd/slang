#pragma once

#include <stdio.h>

typedef struct slang_node {
    int tokentype;
    char* ident;
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
void slang_node_attach_child(slang_node_t* parent, slang_node_t* child);