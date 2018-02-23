#pragma once
#include "assembly.hpp"
#include "register_pool.hpp"
#include "symbol_table.hpp"

void WriteFunction(std::string);

void WriteFunction(int);

void ReadFunction();

void StopFunction();

void ChrFunction();

void OrdFunction();

void PredFunction();

void SuccFunction();
