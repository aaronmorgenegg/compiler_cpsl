#include "assembly.hpp"

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
	if(DEBUG) std::cout << "  Outputing: " << msg << std::endl;
	if(STDOUT){
		std::cout << msg << std::endl;
	} else {
		file << msg << std::endl;
	}
}

void ASManager::WriteHeader(){
	// This is what goes at the beginning of every asm file
	Write(".text");
	Write(".globl main");
	Write("main:");
	Write("j GA");
}

void ASManager::WriteFooter(){
	// This is what goes at the end of every asm file
	Write("li $v0, 10");
	Write("syscall");
	Write(".data");
	WriteStrings();
	WriteVariables();
	//WriteGlobalArea(); // TODO
}

void ASManager::WriteStrings(){
	for(int i = 0; i < STRING_LIST.GetSize(); i++){
		Write(std::string("STR"+std::to_string(i)+": .asciiz " + STRING_LIST.Lookup(i)));
	}
}

void ASManager::WriteVariables(){
	// TODO
}

void ASManager::WriteGlobalArea(){
	Write("GA:");
}

