#include <map>

std::map<std::string, int> symbol_table;

void store_value(char *i, int v){
        symbol_table[std::string(i)] = v;
        delete i;
}

float (lookup_value(char * i) {
        auto v = symbol_table(std::string(i));
        delete i;
        return v;
}


