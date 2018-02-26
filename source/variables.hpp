#pragma once
#include <string>
#include <vector>
#include "globals.hpp"
#include "expressions.hpp"
#include "type.hpp"

class Expression;

void SaveVariable(std::string, Type *);

void SaveVariables(std::vector<std::string> *, Type *);

std::string LoadVariable(std::string);

void Assignment(std::string, Expression *);

