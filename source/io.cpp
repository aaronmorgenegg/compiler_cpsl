#include "io.hpp"

void WriteFunction(std::string msg){
	if(DEBUG) std::cout << "Writing <" << msg << ">\n";
	FOUT.Write("li $v0,4 # Load syscall : print_string");
	FOUT.Write("li $a0," + msg);
	FOUT.Write("syscall");
}

void WriteFunction(int num){
	if(DEBUG) std::cout << "Writing <" << num <<">\n";
	FOUT.Write("li $v0,1 # Load syscall : print_int");
	FOUT.Write("li $a0," + std::to_string(num));
	FOUT.Write("syscall");
}

void ReadFunction(){
	
}

