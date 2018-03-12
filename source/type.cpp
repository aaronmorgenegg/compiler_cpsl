#include "type.hpp"

int Type::GetSize(){
	return size;
}

Type * Type::GetBaseType(){
	if(DEBUG) std::cout << "Warning: accessing base type of parent Type class." << std::endl;
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
		Error("Error: Array lower bound greater than upper bound.");
	}
	// TODO: check types on bounds
}

Type * ArrayType::GetBaseType(){
	return this->base_type;
}

std::string ArrayAccess(std::string id, Expression * index){
	// Returns the location of the given array, given id[index]
	if(DEBUG) std::cout << "Accessing array <" << id << "> at index <" << *index << ">\n";
	// TODO: check if id is an array type
	Expression * array = SYMBOL_TABLE.Lookup(id);
	Type * array_base_type = array->type->GetBaseType();
	if(!array->has_address){
		Error("Error: missing address during array access of<" + id + ">.");
	}
	std::string address = array->location;
	Expression * array_expr = new Expression(address, array_base_type);
	array_expr->has_address = true;

	try {
		SYMBOL_TABLE.Store(address, array_expr);
	} catch(int e){
		// Do nothing since it's already in the symbol table
	}
	
	if(DEBUG) std::cout << "  address <" << address << ">" << std::endl;
	return address;
}


