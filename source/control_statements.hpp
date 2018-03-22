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

int GetIfCounter();

int GetElseCounter();

void IfStatement(int);

int IfHead(Expression *);

int ThenStatement();

int ElseLabel(int);

int ElseIfHead(Expression *);

int ElseStatement();

