#include "symbol_table.hpp"

// Needs to hold an expression based on an ID
// expression could have a value, memory location(offset + register),
// or a register that holds that value

// TODO need a stack of levels, 
// 1. predifined expressions(id->type, id->expr, id->function
// 2. global(const, var, type)
// 3. functions(const, var), due later
//
// then a global map
// 1. const, var, or type declarations go here
//
// when looking up, start at the top and look down

SymbolTable SYMBOL_TABLE;

void SymbolTable::Initialize(){
	
}

Expression * SymbolTable::Lookup(std::string id){
	for(auto cur = expression_table.rbegin(); cur!= expression_table.rend(); cur++){
		auto found = cur->find(id);
		if(found != cur->end()){
			return found->second;
		}
	}

	std::cerr << "Error: lookup on symbol table for <" << id << "> failed." << std::endl;
	exit(1);
}

void SymbolTable::Store(std::string id, Expression * e){
	// find on top level, err if found
	// insert at top level
	auto found = expression_table[0].find(id);
	if(found != expression_table[0].end()){
		expression_table[0][id] = e;
	} else {
		std::cerr << "Error: Redefinition of id <" << id << ">." << std::endl;
		exit(1);
	}
}

