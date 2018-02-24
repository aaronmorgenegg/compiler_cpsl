#pragma once
#include "globals.hpp"
#include "assembly.hpp"
#include "register_pool.hpp"
#include "symbol_table.hpp"

void WriteFunction(std::string);

void WriteFunction(char);

void WriteFunction(int);

void WriteFunction(Expression *);

void ReadFunction();

void StopFunction();

Expression * ChrFunction(Expression *);

Expression * OrdFunction(Expression *);

Expression * PredFunction(Expression *);

Expression * SuccFunction(Expression *);

