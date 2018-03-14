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
	std::string new_address = IncrementLocation(address, index->value * base_type->GetSize());
	return new_address;
}

RecordField::RecordField(std::vector<std::string> * members, Type * type){
	this->members = members;
	this->type = type;
}

RecordType::RecordType(std::vector<RecordField *> * members_list){
	// members_list is a vector containing vector of ID's and their associated types
	this->size = 0;
	for(int i = 0; i < members_list->size(); i++){
		RecordField * record = members_list->at(i);
		Type * type = record->type;
		for(int j = 0; j < record->members->size(); j++){
			AddMember(record->members->at(j), type);
			this->size += type->GetSize();
		}
	}
}

void RecordType::AddMember(std::string id, Type * type){
	// Add the given id of given type to internal map of members
	if(DEBUG) std::cout<<"Adding member<" << id << "> of type <" << type << ">\n";
	this->offset_table[id] = this->size;
	this->type_table[id] = type;
}

int RecordType::LookupOffset(std::string id){
	return this->offset_table.at(id);
}

Type * RecordType::LookupType(std::string id){
	return this->type_table.at(id);
}

std::string RecordAccess(std::string id, std::string member){
	// access member from inside id, ex id.member
	Expression * record = SYMBOL_TABLE.Lookup(id);
	// TODO: type check to make sure it is of RecordType
	std::string base_address = record->location;
	RecordType * base_type = dynamic_cast<RecordType *>(record->type);
	int member_offset = base_type->LookupOffset(member);
	int member_size = base_type->LookupType(member)->GetSize();

	return IncrementLocation(base_address, member_offset*member_size);
}

