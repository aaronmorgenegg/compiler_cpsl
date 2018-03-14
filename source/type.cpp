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
	if(lower_bound->type != upper_bound->type) {
		Error("Error: Array bounds are not of the same type.");
	}
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
	address = UpdateArrayAddress(address, index, array_base_type);
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

std::string UpdateArrayAddress(std::string address, Expression * index, Type * base_type){
	// Returns a new address with the updated size, ex converts 12($gp) at index 3 to 24($gp)
	auto offset_index = address.find("(");
	int offset = std::stoi(address.substr(0, offset_index));
	std::string location = address.substr(offset_index, address.length());
	offset += index->value * base_type->GetSize();
	std::string new_address = std::to_string(offset) + location;
	return new_address;
}

RecordField::RecordField(std::vector<std::string> * members, Type * type){
	this->members = members;
	this->type = type;
}

RecordType::RecordType(std::vector<RecordField *> * members_list){

}

