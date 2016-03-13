#pragma once

#include "slang.h"
#include "slang.tab.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

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

slang_node_t* new_slang_int_constant(int int_str) {
    slang_node_t* temp = malloc(sizeof(slang_node_t));
    temp->tokentype = INTCONSTANT;
    temp->int_const = int_str;
    return temp;
}

slang_node_t* new_slang_float_constant(float float_str) {
    slang_node_t* temp = malloc(sizeof(slang_node_t));
    temp->tokentype = FLOATCONSTANT;
    temp->float_const = float_str;
    return temp;
}

void slang_node_attach_children(slang_node_t* parent, ...) {
    slang_node_t* temp;
    va_list vl;
    va_start(vl, parent);
    while (1) {
        temp = va_arg(vl, slang_node_t*);
        if (!temp)
            break;
        slang_node_attach_child(parent, temp);
    }
    va_end(vl);
}
