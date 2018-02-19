#include "symbol_table.hpp"

// Needs to hold an expression based on an ID
// expression could have a value, memory location(offset + register),
// or a register that holds that value

std::map<std::string, Expression *> SYMBOL_TABLE;

void StoreValue(char *i, Expression * v){
        SYMBOL_TABLE[std::string(i)] = v;
        delete i;
}

Expression * LookupValue(char * i) {
        Expression * v = SYMBOL_TABLE[std::string(i)];
        delete i;
        return v;
}

