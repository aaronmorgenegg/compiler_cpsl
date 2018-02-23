#pragma once 
#include <vector>
#include <string>
#include "globals.hpp"

class StringList{
public:
	void Store(std::string); 
	std::string Lookup(int);
	int GetSize();
private:
	std::vector<std::string> strings;
};

