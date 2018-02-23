#pragma once
#include <iostream>
#include <string>
#include "type.hpp"
#include "symbol_table.hpp"
#include "register_pool.hpp"
#include "assembly.hpp"
#include "globals.hpp"

class Expression{
public:
	std::string reg;
	int value;
	bool is_const;
	SimpleType * type;

	Expression(std::string);

	Expression(int);
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

Expression * And(Expression * a, Expression * b);

Expression * Eq(Expression * a, Expression * b);

Expression * Gteq(Expression * a, Expression * b);

Expression * Gt(Expression * a, Expression * b);

Expression * Lteq(Expression * a, Expression * b);

Expression * Lt(Expression * a, Expression * b);

Expression * Neq(Expression * a, Expression * b);

Expression * Or(Expression * a, Expression * b);

