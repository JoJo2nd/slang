/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
/* 
    returns type from symbol table
*/
int slang_sym_table_check(const char* );
void slang_sym_type_add(const char*);
void slang_sym_type_remove(const char*);

#ifdef __cplusplus
}; //extern "C"
#endif