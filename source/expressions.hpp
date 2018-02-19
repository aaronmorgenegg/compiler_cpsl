#pragma once
#include <iostream>
#include <string>
#include "type.hpp"
#include "symbol_table.hpp"
#include "register_pool.hpp"

class Expression{
public:
	std::string reg;
	int value;
	bool is_const;
	int type; // TODO: make this a Type object

	Expression(std::string reg);

	Expression(int value);
};

std::ostream& operator<<(std::ostream &strm, Expression & e);

std::string LoadExpression(Expression * a);

Expression * Apply(Expression * a, Expression * b, std::string op, std::string mode);

void CheckExpression(Expression * a, Expression * b);

void Binop(std::string op, std::string d, std::string a, std::string b);

Expression * Add(Expression * a, Expression * b);

Expression * Sub(Expression * a, Expression * b);

Expression * Mult(Expression * a, Expression * b);

Expression * Div(Expression * a, Expression * b);

Expression * Mod(Expression * a, Expression * b);

