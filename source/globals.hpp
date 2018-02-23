#pragma once
#include "symbol_table.hpp"
#include "register_pool.hpp"
#include "assembly.hpp"
#include "string_list.hpp"

class SymbolTable;
class RegisterPool;
class ASManager;
class StringList;

extern SymbolTable SYMBOL_TABLE;
extern RegisterPool REGISTER_POOL;
extern ASManager FOUT;
extern StringList STRING_LIST;

extern const bool DEBUG;


