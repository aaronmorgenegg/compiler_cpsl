#pragma once
#include <string>
#include "globals.hpp"

class Expression;

void SaveVariable(std::string, Type *);

std::string LoadVariable(std::string);

void Assignment(Expression *, Expression *);

