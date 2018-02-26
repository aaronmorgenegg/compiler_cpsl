#include "variables.hpp"

void SaveVariable(std::string id, Type * type){
	int offset = SYMBOL_TABLE.IncrementCounter(type->GetSize());
	std::string address = std::string(std::to_string(offset) + "($gp)");
	Expression * e = new Expression(address, type);
	e->has_address = true;
	SYMBOL_TABLE.Store(id, e);
}

void SaveVariables(std::vector<std::string> * list, Type * type){
	for(int i = 0; i < list->size(); i++){
		SaveVariable(list->at(i), type);
	}
}

std::string LoadVariable(std::string location){
	std::string r = REGISTER_POOL.GetRegister();
	FOUT.Write(std::string("lw " + r + ", " + location));
	return r;
}

void Assignment(std::string id, Expression * e){
	std::string reg = LoadExpression(e);
	FOUT.Write(std::string("sw " + reg + ","  + SYMBOL_TABLE.Lookup(id)->location));
	REGISTER_POOL.ReleaseRegister(reg);
}

