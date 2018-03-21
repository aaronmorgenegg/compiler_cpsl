#pragma once
#include <string>

#include "globals.hpp"
#include "expressions.hpp"

extern std::string LABEL_WHILE_START;
extern std::string LABEL_WHILE_END;

int GetWhileCounter();

int WhileStart();

int WhileHead(int, Expression *);

void WhileStatement(int);

