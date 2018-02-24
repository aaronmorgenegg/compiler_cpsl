#pragma once
#include <string>
#include "globals.hpp"
#include "expressions.hpp"
#include "type.hpp"

class Expression;

void SaveVariable(std::string, Type *);

std::string LoadVariable(std::string);

void Assignment(std::string, Expression *);

