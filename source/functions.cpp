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
	Function * sig = new Function(id, parameters, return_type);
	FOUT.Write(sig->name + ":");
	SYMBOL_TABLE.EnterScope();
	LoadParameters(parameters, sig);
	SYMBOL_TABLE.Store(id, sig);
	return sig;
}

void FunctionDecl(Function * sig){
	ProcedureEnd(sig);
}

Expression * FunctionCall(std::string id, std::vector<Expression *>* parameters){
	SYMBOL_TABLE.EnterScope();
	Function * sig = SYMBOL_TABLE.LookupFunction(id);
	SaveParameters(parameters, sig);
	FOUT.Write("jal " + id);
	SYMBOL_TABLE.ExitScope();
	return new Expression("$t9", sig->return_type);
}

void SaveParameters(std::vector<Expression *>* parameters, Function * sig){
	for(int i = 0; i < parameters->size(); i++){
		std::string id = sig->parameters->ident_list->at(i);
		Type * type = sig->parameters->type;
		Expression * expr = new Expression(PARAM_REGISTERS[i], type);
		SYMBOL_TABLE.Store(id, expr);

		std::string reg = LoadExpression(parameters->at(i));
		FOUT.Write("move " + PARAM_REGISTERS[i] + ", " + reg);
		REGISTER_POOL.ReleaseRegister(reg);
	}
}

void LoadParameters(FormalParameters * parameters, Function * sig){
	for(int i = 0; i < parameters->ident_list->size(); i++){
		std::string id = sig->parameters->ident_list->at(i);
		Type * type = sig->parameters->type;
		Expression * expr = new Expression(PARAM_REGISTERS[i], type);
		SYMBOL_TABLE.Store(id, expr);
	}
}

void ReturnStatement(Expression * ret_val){
	std::string reg = LoadExpression(ret_val);
	FOUT.Write("move $t9, " + reg);
}

