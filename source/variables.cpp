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

void Assignment(Expression * lvalue, Expression * e){
	if(DEBUG) std::cout << "Assignment of lvalue<" << lvalue << "> to expr<" << *e << ">\n";
	std::string reg = LoadExpression(e);
	FOUT.Write(std::string("sw " + reg + ","  + lvalue->location));
	REGISTER_POOL.ReleaseRegister(reg);
}

int GetOffset(std::string location){
	// Returns the offset from a given location, ex given 12($gp), returns 12
	int offset_index = location.find("(");
	try {
		return std::stoi(location.substr(0, offset_index));
	} catch(std::invalid_argument e){
		return 0;
	}
}

std::string GetAddress(std::string location){
	// Returns the address from a given location, ex given 12($gp), returns ($gp)
	int offset_index = location.find("(");
	return location.substr(offset_index, location.length());
}

std::string IncrementLocation(std::string location, int value){
	// returns a new string with given value, ex given 12($gp) and 8, returns 20($gp)
        int offset = GetOffset(location);
        std::string mem_loc = GetAddress(location);
        offset += value;
        std::string new_address = std::to_string(offset) + mem_loc;
        return new_address;		
}

