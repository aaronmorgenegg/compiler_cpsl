#include "functions.hpp"

std::string PARAM_REGISTERS[] = {"$a0", "$a1", "$a2", "$a3"};

Function::Function(std::string name, FormalParameters * parameters){
	this->name = name;
	this->parameters = parameters;
}

Function::Function(std::string name, FormalParameters * parameters, Type* return_type){
	this->name = name;
	this->parameters = parameters;
	this->return_type = return_type;
}

FormalParameters::FormalParameters(){
	this->ident_list = new std::vector<std::string>;
}

FormalParameters::FormalParameters(std::vector<std::string> * ident_list, Type * type){
	this->ident_list = ident_list;
	this->type = type;
}

Function * ProcedureBegin(std::string id, FormalParameters * parameters){
	SYMBOL_TABLE.EnterScope();
	Function * sig = new Function(id, parameters); 
	FOUT.Write(sig->name + ":");
	return sig;
}

void ProcedureEnd(Function * sig){
	FOUT.Write("jr $ra");
	SYMBOL_TABLE.ExitScope();
}

void ProcedureDecl(Function * sig){
	ProcedureEnd(sig);
}

void ProcedureCall(std::string id, std::vector<Expression*> *parameters){
	FOUT.Write("jal " + id);
}

Function * FunctionBegin(std::string id, FormalParameters * parameters, Type* return_type){
	SYMBOL_TABLE.EnterScope();
	Function * sig = new Function(id, parameters, return_type);
	FOUT.Write(sig->name + ":");
	LoadParameters(parameters);
	SYMBOL_TABLE.Store(id, sig);
	return sig;
}

void FunctionDecl(Function * sig){
	ProcedureEnd(sig);
}

Expression * FunctionCall(std::string id, std::vector<Expression *>* parameters){
	SYMBOL_TABLE.EnterScope();
	SaveParameters(parameters);
	FOUT.Write("jal " + id);
	SYMBOL_TABLE.ExitScope();
	Function * function = SYMBOL_TABLE.LookupFunction(id);
	return new Expression("$t9", function->return_type);
}

void SaveParameters(std::vector<Expression *>* parameters){
	for(int i = 0; i < parameters->size(); i++){
		std::string reg = LoadExpression(parameters->at(i));
		FOUT.Write("move " + PARAM_REGISTERS[i] + ", " + reg);
		REGISTER_POOL.ReleaseRegister(reg);
	}
}

void LoadParameters(FormalParameters * parameters){
	for(int i = 0; i < parameters->ident_list->size(); i++){
		
	}
}

