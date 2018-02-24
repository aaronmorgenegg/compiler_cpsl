#include "builtins.hpp"

void WriteFunction(std::string msg){
	if(DEBUG) std::cout << "Writing string<" << msg << ">\n";
	FOUT.Write("li $v0,4 # Load syscall : print_string");
	FOUT.Write("la $a0," + msg);
	FOUT.Write("syscall");
}

void WriteFunction(int num){
	if(DEBUG) std::cout << "  Writing int<" << num <<">\n";
	FOUT.Write("li $v0,1 # Load syscall : print_int");
	FOUT.Write("li $a0," + std::to_string(num));
	FOUT.Write("syscall");
}

void WriteFunction(char c){
	if(DEBUG) std::cout << "  Writing char<" << c << ">\n";
	FOUT.Write("li $v0,11 # Load syscall : print_char");
	std::string temp = "li $a0,'";
	temp += c;
	temp += "'";
	FOUT.Write(std::string(temp));
	FOUT.Write("syscall");
}

void WriteFunction(Expression * e){
	if(DEBUG) std::cout << "Writing <" << *e << ">\n";
	if(e->location.length()){
		// TODO: handle expression stored in register, or in a variable address
	} else if(e->type == &TYPE_INT){
		WriteFunction(e->value);
	} else if(e->type == &TYPE_CHAR){
		WriteFunction(char(e->value));
	} else if(e->type == &TYPE_BOOL){
		WriteFunction(e->value);
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

