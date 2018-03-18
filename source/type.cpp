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

Expression * ArrayAccess(Expression * array, Expression * index){
	// Returns the location of the given array, given id[index]
	if(DEBUG) std::cout << "Accessing array <" << *array << "> at index <" << *index << ">\n";
	// TODO: check if id is an array type
	Type * array_base_type = array->type->GetBaseType();
	if(!array->has_address){
		Error("Error: missing address during array access of<" + to_string(array) + ">.");
	}
	std::string address = array->location;
	Expression * address_expr = new Expression(address, array_base_type);
	address_expr->has_address = true;

	return UpdateArrayAddress(address, index, array_base_type);
}

Expression * UpdateArrayAddress(std::string address, Expression * index, Type * base_type){
	// Returns a new address with the updated size, ex converts 12($gp) at index 3 to 24($gp)
	std::string index_offset = LoadExpression(Mult(index, new Expression(base_type->GetSize(), base_type)));
	std::string address_no_parenthesis = address.substr(2, address.size() - 3);
	FOUT.Write("add " + index_offset + "," + address_no_parenthesis + "," + index_offset);
	index_offset.insert(0, "(");
	index_offset.insert(index_offset.size(), ")");
	Expression * updated_expression = new Expression(index_offset, base_type);
	updated_expression->has_address = true;
	return updated_expression;
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

Expression * RecordAccess(Expression * record, std::string member){
	// access member from inside id, ex id.member
	if(DEBUG) std::cout << "Record access of member<" << member << ">\n";
	// TODO: type check to make sure it is a record
	std::string base_address = record->location;
        RecordType * base_type = dynamic_cast<RecordType *>(record->type);
        int member_offset = base_type->LookupOffset(member);
	std::string new_address = IncrementLocation(base_address, member_offset);

	Type * new_type = base_type->LookupType(member);
	Expression * new_expression = new Expression(new_address, new_type);
	new_expression->has_address = true;

	return new_expression;
}

