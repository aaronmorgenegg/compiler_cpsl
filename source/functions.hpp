#pragma once
#include "globals.hpp"
#include <string>
#include <vector>

class FormalParameters{
public:
	FormalParameters();
        FormalParameters(std::vector<std::string> *, Type *);
        std::vector<std::string> * ident_list;
        Type * type;
};

class Function{
public:
	Function(std::string, FormalParameters *);
	Function(std::string, FormalParameters *, Type*);
	std::string name;
	FormalParameters * parameters;
	Type * return_type;
};

Function * ProcedureBegin(std::string, FormalParameters *);

void ProcedureEnd(Function *);

void ProcedureDecl(Function *);

void ProcedureCall(std::string, std::vector<Expression *>*);

Function * FunctionBegin(std::string, FormalParameters *, Type* return_type);

void FunctionDecl(Function *);

Expression * FunctionCall(std::string, std::vector<Expression *>*);

void SaveParameters(std::vector<Expression *>*, Function *);

void LoadParameters(FormalParameters *, Function *);

void ReturnStatement(Expression*);

