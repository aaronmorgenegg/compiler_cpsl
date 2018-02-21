#include "io.hpp"

void WriteFunction(std::string msg){
	if(DEBUG) std::cout << "Writing <" << msg << ">\n";
	std::string reg1 = REGISTER_POOL.GetRegister();
	std::string reg2 = REGISTER_POOL.GetRegister();
	FOUT.Write("li " + reg1 + ",4 # Load syscall : print_string");
	FOUT.Write("li " + reg2 + "," + msg);
	FOUT.Write("syscall");
	REGISTER_POOL.ReleaseRegister(reg1);
	REGISTER_POOL.ReleaseRegister(reg2);
}

void ReadFunction(){
	
}

