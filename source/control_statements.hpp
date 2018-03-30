#pragma once
#include <string>
#include <vector>

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

std::vector<int> * IfHead(Expression *);

int ThenStatement(int);

int ElseLabel(int);

int ElseIfHead(Expression *);

std::vector<int> * ElseIfList(int, int);

int ElseStatement();

struct ForContainer {
        Expression * condition;
        int count;
        ForContainer(Expression *, int);
};

int GetForCounter();

void ForStatement(int);

ForContainer * ForHead(std::string, Expression *, int count);

int ForTo(ForContainer *, Expression *);

int ForDownTo(ForContainer *, Expression *);

void ForStart(int, Expression *, int);

int ForLabel();

