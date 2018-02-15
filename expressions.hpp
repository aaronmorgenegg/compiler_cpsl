#pragma once
#include <iostream>
#include <string>

struct Expression{
	std::string reg;
	int value;
	bool is_const;
};

class RegisterPool {
public:
	static std::string getRegister();
};

std::string LoadExpression(Expression a);

