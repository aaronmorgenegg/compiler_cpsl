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

	offset_counter = 0;

	EnterScope();
	
	SYMBOL_TABLE.Store("INTEGER", &TYPE_INT);
	SYMBOL_TABLE.Store("integer", &TYPE_INT);

	SYMBOL_TABLE.Store("CHAR", &TYPE_CHAR);
        SYMBOL_TABLE.Store("char", &TYPE_CHAR);

	SYMBOL_TABLE.Store("STRING", &TYPE_STR);
        SYMBOL_TABLE.Store("string", &TYPE_STR);

	SYMBOL_TABLE.Store("BOOLEAN", &TYPE_BOOL);
        SYMBOL_TABLE.Store("boolean", &TYPE_BOOL);
	
	SYMBOL_TABLE.Store("true", &EXPR_TRUE);
	SYMBOL_TABLE.Store("false", &EXPR_FALSE);
	
	EnterScope();
}

Expression * SymbolTable::Lookup(std::string id){
	if(DEBUG) std::cout<<"LookupExpr: id<" << id << ">" << std::endl;
	for(int i = expression_table.size() - 1; i >= 0; i--){
		try {return expression_table[i].at(id);}
	       	catch (const std::out_of_range& e){}
	}

	if(DEBUG)std::cerr << "Error: lookup expr on symbol table for <" << id << "> failed." << std::endl;
	throw(4);
}

void SymbolTable::Store(std::string id, Expression * e){
	// find on top level, err if found
	// insert at top level
	if(DEBUG) std::cout << "Storing: id<" << id << "> expression<" << *e <<">" << std::endl;
	if(expression_table.back().count(id) == 0){
		expression_table.back()[id] = e;
	} else {
		// Error("Error: Redefinition of id <" + id + ">.");
		if(DEBUG)std::cerr << "Error: Redefinition of id <" << id << ">.\n";
		throw(3);
	}
}

Type * SymbolTable::LookupType(std::string id){
	if(DEBUG) std::cout<<"LookupType: id<" << id << ">" << std::endl;
        for(int i = type_table.size() - 1; i >= 0; i--){
                try {return type_table[i].at(id);}
                catch (const std::out_of_range& e){}
        }

        if(DEBUG)Error("Error: lookup type on symbol table for <" + id + "> failed.");

}

void SymbolTable::Store(std::string id, Type * t){
	if(DEBUG) std::cout << "Storing: id<" << id << "> type" << std::endl;
        if(type_table.back().count(id) == 0){
	        type_table.back()[id] = t;
        } else {
                Error("Error: Redefinition of id <" + id + ">.");
        }

}

int SymbolTable::IncrementCounter(int size){
	// Returns the old offset, and increments the offset by given size
	int temp = offset_counter;
	offset_counter += size;
	return temp;
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

