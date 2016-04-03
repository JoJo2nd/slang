
// Temp code until I write something better

#include "sym_table.h"
#include "slang.h"
#include "slang.tab.h"
#include <string>
#include <unordered_set>

static std::unordered_set<std::string> syms;

extern "C"
int slang_sym_table_check(const char* in_sym) {
    auto symbol = syms.find(in_sym);
    if (symbol == syms.end())
        return IDENTIFIER;
    else
        return TYPE_NAME;
}

extern "C"
void slang_sym_type_add(const char* in_sym) {
    syms.insert(in_sym);
}

extern "C"
void slang_sym_type_remove(const char* in_sym) {
    syms.erase(in_sym);
}