#include "symbol_table.hpp"

std::map<std::string, Expression * > symbol_table;
const bool DEBUG = true;

// Needs to hold an expression based on an ID
// expression could have a value, memory location(offset + register),
// or a register that holds that value

void StoreValue(char *i, Expression * v){
        symbol_table[std::string(i)] = v;
        delete i;
}

Expression * LookupValue(char * i) {
        Expression * v = symbol_table[std::string(i)];
        delete i;
        return v;
}

