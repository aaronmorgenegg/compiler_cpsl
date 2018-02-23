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
private:
	std::ofstream file;
	std::string file_name;
};

std::ostream& operator<<(std::ostream &strm, ASManager & a);

