/*
* Copyright 2016 James Moran. All rights reserved.
* License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
*/
#pragma once

#include <stdint.h>

// may expose this type at some point.
typedef struct hash_table hash_table_t;

hash_table_t* hash_table_init(int key_size, uint32_t(*in_hash_key)(const void*), int(*in_compare_key)(const void*, const void*), void(*in_value_free)(void* val));
void hash_table_insert(hash_table_t* hash_tbl, const void* key, void* val);
void hash_table_destroy(hash_table_t* hash_tbl);
void* hash_table_find(hash_table_t* hash_tbl, const void* key);
int hash_table_erase(hash_table_t* hash_tbl, const void* key);
int hash_table_size(hash_table_t* hash_tbl);
float average_probe_count(hash_table_t* hash_tbl);