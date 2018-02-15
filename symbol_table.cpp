#pragma once 
#include <map>
#include "expressions.cpp"

std::map<std::string, Expression> symbol_table;

// Needs to hold an expression based on an ID
// expression could have a value, memory location(offset + register),
// or a register that holds that value

void store_value(char *i, Expression v){
        symbol_table[std::string(i)] = v;
        delete i;
}

float lookup_value(char * i) {
        auto v = symbol_table(std::string(i));
        delete i;
        return v;
}


