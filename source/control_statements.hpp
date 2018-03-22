#pragma once
#include <string>

#include "globals.hpp"
#include "expressions.hpp"

extern std::string LABEL_WHILE_START;
extern std::string LABEL_WHILE_END;
extern std::string LABEL_IF_START;
extern std::string LABEL_IF_END;

int GetWhileCounter();

int WhileStart();

int WhileHead(int, Expression *);

void WhileStatement(int);

int GetIfCounter(bool);

int GetElseCounter();

int IfHead(Expression *);

int ThenStatement();

int ElseIfHead(Expression *);

int ElseStatement();

