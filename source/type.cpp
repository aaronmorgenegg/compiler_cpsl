#include "type.hpp"

int Type::GetSize(){
	return size;
}

SimpleType::SimpleType(){
	size = 4;
}

ArrayType::ArrayType(Expression * lower_bound, Expression * upper_bound, Type * base_type){
	this->lower_bound = lower_bound->value;
	this->upper_bound = upper_bound->value;
	this->base_type = base_type;
	this->size = (this->upper_bound - this->lower_bound) * this->base_type->GetSize();
}

std::string ArrayAccess(std::string id, Expression * index){
	if(DEBUG) std::cout << "Accessing array <" << id << "> at index <" << *index << ">\n";
	// TODO: check if id is an array type
	Expression * array = SYMBOL_TABLE.Lookup(id);
	if(!array->has_address){
		std::cerr<<"Error: missing address during array access of<" << id << ">." << std::endl;
		exit(1);
	}
	std::string address = array->location;
	if(DEBUG) std::cout << "  address <" << address << ">" << std::endl;
	return address;
}

