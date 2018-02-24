#include "builtins.hpp"

void WriteFunction(std::string msg){
	if(DEBUG) std::cout << "Writing <" << msg << ">\n";
	FOUT.Write("li $v0,4 # Load syscall : print_string");
	FOUT.Write("la $a0," + msg);
	FOUT.Write("syscall");
}

void WriteFunction(int num){
	if(DEBUG) std::cout << "Writing <" << num <<">\n";
	FOUT.Write("li $v0,1 # Load syscall : print_int");
	FOUT.Write("li $a0," + std::to_string(num));
	FOUT.Write("syscall");
}

void WriteFunction(Expression * e){
	if(DEBUG) std::cout << "Writing <" << *e << ">\n";
	if(e->reg.length()){
		// TODO: handle expression stored in register
	} else if(e->type == &TYPE_INT){
		// TODO: handle int type
	} else if(e->type == &TYPE_CHAR){
		// TODO: handle char type
	} else if(e->type == &TYPE_BOOL){
		// TODO: handle bool type
	} else if(e->type == &TYPE_STR){
		std::string s = std::string("STR" + std::to_string(e->value));
		WriteFunction(s);
	} else {
		std:: cerr << "Error: attempted to write invalid expression." << std::endl;
		exit(1);
	}
}

void ReadFunction(){
	
}

void StopFunction(){
	if(DEBUG) std::cout << "Stopping..." << std::endl;
	FOUT.Write("li $v0,10 # Load syscall : exit");
	FOUT.Write("syscall");
}

Expression * ChrFunction(Expression * e){

}

Expression * OrdFunction(Expression * e){

}

Expression * PredFunction(Expression * e){

}

Expression * SuccFunction(Expression * e){

}

