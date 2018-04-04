#include "globals.hpp"

RegisterPool REGISTER_POOL;
ASManager FOUT;
StringList STRING_LIST;
SymbolTable SYMBOL_TABLE;

const bool DEBUG = false;
const bool STDOUT = false;
SimpleType TYPE_INT;
SimpleType TYPE_CHAR;
SimpleType TYPE_BOOL;
SimpleType TYPE_STR;
Expression EXPR_TRUE(1, &TYPE_BOOL);
Expression EXPR_FALSE(0, &TYPE_BOOL);

