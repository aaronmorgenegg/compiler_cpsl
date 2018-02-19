#pragma once
#include <map>
#include <string>
#include "expressions.hpp"

class Expression;

const bool DEBUG = true;

void StoreValue(char * i, Expression * v);

Expression * LookupValue(char * i);

