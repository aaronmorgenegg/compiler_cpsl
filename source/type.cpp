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
	this->size = this->upper_bound - this->lower_bound;
}

