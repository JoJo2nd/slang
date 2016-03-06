#pragma once

#include "slang.h"
#include "slang.tab.h"
#include <stdlib.h>

slang_node_t* new_slang_node(int code, ...) {
    slang_node_t* temp = malloc(sizeof(slang_node_t));
    temp->tokentype = code;
    return temp;
}

slang_node_t* new_slang_identifier(const char* ident) {
    slang_node_t* temp = malloc(sizeof(slang_node_t));
    temp->tokentype = IDENTIFIER;
    return temp;
}
