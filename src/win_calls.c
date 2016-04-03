/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */
#include <windows.h>

//
uintptr_t loadLibrary(const char* library) {
    HANDLE hLib = LoadLibrary(library);
    return hLib == INVALID_HANDLE_VALUE ? 0 : (uintptr_t)hLib;
}

uintptr_t findProcessAddress(uintptr_t lib, const char* proc_name) {
    return (uintptr_t)GetProcAddress((HANDLE)lib, proc_name);
}