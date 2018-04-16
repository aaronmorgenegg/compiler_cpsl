#include "functions.hpp"

Function::Function(std::string name, std::vector<Expression *> parameters){
	this->name = name;
	this->parameters = parameters;
}

Function * ProcedureBegin(std::string id, std::vector<Expression *> * parameters){
	Function * sig = new Function(id, *parameters); 
	FOUT.Write(sig->name + ":");
	return sig;
}

void ProcedureEnd(Function * sig){
	FOUT.Write("jr $ra");
}

void ProcedureDecl(Function * sig){
	ProcedureEnd(sig);
}

void ProcedureCall(std::string id, std::vector<Expression*> *parameters){
	FOUT.Write("jal " + id);
}

