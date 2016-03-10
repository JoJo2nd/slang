#pragma once

#include "slang.h"
#include "slang.tab.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

slang_node_t* new_slang_node(int code) {
    slang_node_t* temp = malloc(sizeof(slang_node_t));
    temp->tokentype = code;
    temp->ident = NULL;
    temp->parent = NULL;
    temp->firstChild = NULL;
    temp->siblingNext = temp->siblingPrev = temp;
    return temp;
}

slang_node_t* new_slang_identifier(const char* ident) {
    slang_node_t* temp = malloc(sizeof(slang_node_t));
    temp->tokentype = IDENTIFIER;
    temp->ident = strdup(ident);
    temp->parent = NULL;
    temp->firstChild = NULL;
    temp->siblingNext = temp->siblingPrev = temp;
    return temp;
}

void slang_node_attach_child(slang_node_t* parent, slang_node_t* child) {
    assert(child->parent == NULL);
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
