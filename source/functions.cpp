#include "functions.hpp"

Function::Function(std::string name, std::vector<Expression *> parameters){
	this->name = name;
	this->parameters = parameters;
}

