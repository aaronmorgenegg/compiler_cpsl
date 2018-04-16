#pragma once
#include "globals.hpp"
#include <string>
#include <vector>

// Register t9 is reserved for return values

class Function{
public:
	Function(std::string, std::vector<Expression *>);
	std::string name;
	std::vector<Expression *> parameters;
};

