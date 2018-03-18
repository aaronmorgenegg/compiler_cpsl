#pragma once
#include "globals.hpp"
#include "assembly.hpp"
#include "register_pool.hpp"
#include "symbol_table.hpp"
#include "expressions.hpp"
#include "utils.hpp"

void WriteFunction(std::string);

std::string HandleEscapedCharacters(std::string);

void WriteFunction(char);

void WriteFunction(int);

void WriteFunctionLocation(Expression *);

void WriteFunction(Expression *);

void ReadFunctionInt(Expression *);

void ReadFunctionChar(Expression *);

void ReadFunction(Expression *);

void StopFunction();

Expression * ChrFunction(Expression *);

Expression * OrdFunction(Expression *);

Expression * PredFunction(Expression *);

Expression * SuccFunction(Expression *);

