#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "type.hpp"

struct Expression{
	std::string reg;
	int value;
	bool is_const;
	int type; // TODO: make this a Type object

	Expression(std::string reg){
		this->reg = reg;
	}

	Expression(int value){
		this->value = value;
		this->is_const = true;
	}
};

class RegisterPool {
public:
	static std::string GetRegister();
	static std::string ReleaseRegister(std::string reg);
};

std::string LoadExpression(Expression * a);

Expression * Apply(Expression * a, Expression * b, std::string op, std::string mode);

void CheckExpression(Expression * a, Expression * b);

Expression * Add(Expression * a, Expression * b);

void Binop(std::string op, std::string d, std::string a, std::string b);

