#include "assembly.hpp"

ASManager FOUT;

ASManager::ASManager(){
	file_name = "code.asm";
	file.open(file_name);
}

ASManager::ASManager(std::string file_name){
        this->file_name = file_name;
        file.open(file_name);
}


ASManager::~ASManager(){
	file.close();
}

void ASManager::Write(std::string msg){
	// Output the msg to the asm file
	std::cout << "  Outputing: " << msg << std::endl;
	file << msg << std::endl;
}

void ASManager::WriteHeader(){
	// This is what goes at the beginning of every asm file
	Write(".text");
	Write(".globl main");
	Write("main:");
}

void ASManager::WriteFooter(){
	// This is what goes at the end of every asm file
	
}

