#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "globals.hpp"

class ASManager{
public:
	ASManager();
	ASManager(std::string);
	~ASManager();
	void Write(std::string msg);
	void WriteHeader();
	void WriteFooter();
	void WriteStrings();
	void WriteGlobalArea();
private:
	std::ofstream file;
	std::string file_name;
};

