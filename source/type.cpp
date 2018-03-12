#include "type.hpp"

int Type::GetSize(){
	return size;
}

Type * Type::GetBaseType(){
	return this;
}

SimpleType::SimpleType(){
	size = 4;
}

ArrayType::ArrayType(Expression * lower_bound, Expression * upper_bound, Type * base_type){
	this->lower_bound = lower_bound->value;
	this->upper_bound = upper_bound->value;
	this->base_type = base_type;
	this->size = (this->upper_bound - this->lower_bound) * this->base_type->GetSize();
	if(this->lower_bound > this->upper_bound) {
		std::cout << "Error: Array lower bound greater than upper bound." << std::endl;
		exit(1);
	}
	// TODO: check types on bounds
}

Type * ArrayType::GetBaseType(){
	return this->base_type;
}

std::string ArrayAccess(std::string id, Expression * index){
	if(DEBUG) std::cout << "Accessing array <" << id << "> at index <" << *index << ">\n";
	// TODO: check if id is an array type
	
	try {
		// Array in symbol table
		SYMBOL_TABLE.Lookup(id);
		return id;
	}
	catch (int e){
		// Array not in symbol table
		Expression * array = SYMBOL_TABLE.Lookup(id);
		Type * array_base_type = array->type->GetBaseType();
		if(!array->has_address){
			std::cerr<<"Error: missing address during array access of<" << id << ">." << std::endl;
			exit(1);
		}
	
		std::string address = array->location;
		Expression * array_expr = new Expression(address, array_base_type);
		array_expr->has_address = true;
		SYMBOL_TABLE.Store(address, array_expr);
		
		if(DEBUG) std::cout << "  address <" << address << ">" << std::endl;
		return address;
	}
}

