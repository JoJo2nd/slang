/*
* Copyright 2016 James Moran. All rights reserved.
* License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
*/
#pragma once

#include <stdint.h>

uintptr_t loadLibrary(const char* library);
uintptr_t findProcessAddress(uintptr_t lib, const char* proc_name);
int runProcess(const char* cmd_line, 
    const char* stdin_buffer, uint32_t stdin_size, 
    char** o_stdout_buffer, size_t* o_stdout_size, 
    char** o_stderr_buffer, size_t* o_stderr_size);