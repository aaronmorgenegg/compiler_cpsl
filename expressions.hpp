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
	static std::string GetRegister();
};

std::string LoadExpression(Expression a);

Expression ExpressionAdd(Expression a, Expression b);

void Binop(std::string op, std::string d, std::string a, std::string b);

