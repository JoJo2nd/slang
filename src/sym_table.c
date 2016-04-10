/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */
// Temp code until I write something better

#include "sym_table.h"
#include "slang.h"
#include "slang.tab.h"
#include "murmur_hash_3.h"
#include "hash_table.h"
#include <string.h>
#include <stdlib.h>

static const uint32_t MURMUR_SEED = 0x45378081;
static hash_table_t* symTable;

static uint32_t sym_hash(const void* in_key) {
    char* key = *((char**)in_key);
    uint32_t r;
    MurmurHash3_x86_32(key, strlen(key), MURMUR_SEED, &r);
    return r;
}

static int sym_key_compare(const void* a, const void* b) {
    return strcmp(*((char**)a), *((char**)b));
}

static void sym_val_free(void* a) {
    free(a);
}

int slang_init_sym_table() {
    symTable = hash_table_init(sizeof(const char*), sym_hash, sym_key_compare, sym_val_free);
    return symTable != 0;
}

int slang_sym_table_check(const char* in_sym) {
    const char* sym = hash_table_find(symTable, &in_sym);
    if (!sym)
        return IDENTIFIER;
    else
        return TYPE_NAME;
}

void slang_sym_type_add(const char* in_sym) {
    if (!hash_table_find(symTable, &in_sym)) {
        char* str = malloc(strlen(in_sym)+1);
        strcpy(str, in_sym);
        hash_table_insert(symTable, &str, str);
    }
}

void slang_sym_type_remove(const char* in_sym) {
    hash_table_erase(symTable, &in_sym);
}