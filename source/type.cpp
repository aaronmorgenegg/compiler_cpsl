#include "type.hpp"

int Type::GetSize(){
	return size;
}

SimpleType::SimpleType(){
	size = 4;
}

ArrayType::ArrayType(Expression * lower_bound, Expression * upper_bound, Type * base_type){
	this->lower_bound = lower_bound;
	this->upper_bound = upper_bound;
	this->base_type = base_type;
	// TODO: subtract upper bound from lower bound and get the size
	// TODO: get the values from the expressions for lower/upper bounds, save as ints
}

