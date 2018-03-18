#pragma once
#include <string>
#include <iostream>
#include <map>

#include "globals.hpp"
#include "expressions.hpp"
#include "utils.hpp"

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

Expression * ArrayAccess(Expression *, Expression *);

Expression * UpdateArrayAddress(std::string, Expression *, Type *);

struct RecordField{
public:
        RecordField(std::vector<std::string> *, Type *);
        std::vector<std::string> * members;
        Type * type;
};

class RecordType: public Type {
public:
	RecordType(std::vector<RecordField *> *);
	void AddMember(std::string, Type*);
	int LookupOffset(std::string);
	Type * LookupType(std::string);

	std::map<std::string, int> offset_table;
	std::map<std::string, Type *> type_table;
};

Expression * RecordAccess(Expression *, std::string);

