#pragma once
#include <string>
#include <iostream>

#include "globals.hpp"
#include "expressions.hpp"

class Expression;

//Type.size -> (virtual) how much space the type needs
//inherited by simple type(int, char, string, bool), array, and record
class Type{
public:
	int GetSize();
	virtual Type * GetBaseType();
protected:
	int size;
};

class SimpleType: public Type {
public:
	SimpleType();
};

class ArrayType: public Type {
public:
	Type * GetBaseType();

	Type * base_type;
	int lower_bound;
	int upper_bound;
	
	ArrayType(Expression *, Expression *, Type *);
};

std::string ArrayAccess(std::string, Expression *);

std::string UpdateArrayAddress(std::string, Expression *, Type *);

