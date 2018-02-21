#include "io.hpp"

void WriteFunction(std::string msg){
	if(DEBUG) std::cout << "Writing <" << msg << ">\n";
	std::string reg = REGISTER_POOL.GetRegister();
	FOUT.Write("li $v0,4 # Load syscall : print_string");
	FOUT.Write("li " + reg + "," + msg);
	FOUT.Write("syscall");
	REGISTER_POOL.ReleaseRegister(reg);
}

void ReadFunction(){
	
}

