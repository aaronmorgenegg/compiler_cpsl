#pragma once
#include <iostream>
#include <string>
#include "type.hpp"
#include "symbol_table.hpp"
#include "register_pool.hpp"

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

std::string LoadExpression(Expression * a);

Expression * Apply(Expression * a, Expression * b, std::string op, std::string mode);

void CheckExpression(Expression * a, Expression * b);

void Binop(std::string op, std::string d, std::string a, std::string b);

Expression * Add(Expression * a, Expression * b);

