#pragma once

#include <iostream>
#include <fstream>
#include <string>

class ASManager{
public:
	ASManager();
	ASManager(std::string);
	~ASManager();
	void Write(std::string msg);
	void WriteHeader();
private:
	std::ofstream file;
	std::string file_name;
};

extern ASManager FOUT;

