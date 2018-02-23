#pragma once
#include "symbol_table.hpp"
#include "register_pool.hpp"
#include "assembly.hpp"
#include "string_list.hpp"
#include "type.hpp"
#include "expressions.hpp"

class SymbolTable;
class RegisterPool;
class ASManager;
class StringList;
class Type;
class SimpleType;
class Expression;

extern SymbolTable SYMBOL_TABLE;
extern RegisterPool REGISTER_POOL;
extern ASManager FOUT;
extern StringList STRING_LIST;

extern const bool DEBUG;
extern SimpleType TYPE_INT;
extern SimpleType TYPE_CHAR;
extern SimpleType TYPE_BOOL;
extern SimpleType TYPE_STR;
extern Expression EXPR_TRUE;
extern Expression EXPR_FALSE;

