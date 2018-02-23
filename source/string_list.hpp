#pragma once 
#include <vector>
#include <string>
#include "globals.hpp"

class StringList{
public:
	void Store(std::string); 
private:
	std::vector<std::string> strings;
};

