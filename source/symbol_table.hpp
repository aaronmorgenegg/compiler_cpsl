#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include "globals.hpp"
#include "expressions.hpp"

class Expression;

class SymbolTable{
public:
	SymbolTable() = default;
	void Initialize();
	Expression * Lookup(std::string);
	void Store(std::string, Expression *);
	Type * LookupType(std::string);
	void Store(std::string, Type *);
	void EnterScope();
	void ExitScope();
	int IncrementCounter(int);
private:
	std::vector<std::map<std::string, Expression *>> expression_table;
	std::vector<std::map<std::string, Type *>> type_table;
	int offset_counter;
};

