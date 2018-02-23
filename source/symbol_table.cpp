#include "symbol_table.hpp"

// Needs to hold an expression based on an ID
// expression could have a value, memory location(offset + register),
// or a register that holds that value
//
// need a stack of levels, 
// 1. predifined expressions(id->type, id->expr, id->function
// 2. global(const, var, type)
// 3. functions(const, var), due later
//
// then a global map
// 1. const, var, or type declarations go here
//
// when looking up, start at the top and look down

void SymbolTable::Initialize(){
	if(DEBUG)std::cout<<"Initializing Symbol Table..." << std::endl;
	EnterScope();
	// TODO: define default types and such
	// Integer
	// Char
	// String
	// Boolean
	// True
	// False
	EnterScope();
}

Expression * SymbolTable::Lookup(std::string id){
	if(DEBUG) std::cout<<"Lookup: id<" << id << ">" << std::endl;
	for(int i = expression_table.size() - 1; i >= 0; i--){
		try {return expression_table[i].at(id);}
	       	catch (const std::out_of_range& e){}
	}

	std::cerr << "Error: lookup on symbol table for <" << id << "> failed." << std::endl;
	exit(1);
}

void SymbolTable::Store(std::string id, Expression * e){
	// find on top level, err if found
	// insert at top level
	if(DEBUG) std::cout << "Storing: id<" << id << "> expression<" << *e <<">" << std::endl;
	if(expression_table.back().count(id) == 0){
		expression_table.back()[id] = e;
	} else {
		std::cerr << "Error: Redefinition of id <" << id << ">." << std::endl;
		exit(1);
	}
}

void SymbolTable::EnterScope(){
	std::map<std::string, Expression*> e;
	std::map<std::string, Type*> t;
	expression_table.push_back(e);
	type_table.push_back(t);
}

void SymbolTable::ExitScope(){
	expression_table.pop_back();
	type_table.pop_back();
}

