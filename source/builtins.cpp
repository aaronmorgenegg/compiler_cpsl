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

void WriteFunctionLocation(Expression * e){
	if(DEBUG) std::cout << "  Writing value from location<" << e->location << ">\n";
	std::string reg = LoadExpression(e);
	FOUT.Write(std::string("move $a0," + reg));
	if(e->type == &TYPE_INT || e->type == &TYPE_BOOL){
		FOUT.Write("li $v0,1 # Load syscall : print_int");
	} else if (e->type == &TYPE_CHAR){
		FOUT.Write("li $v0,11 # Load syscall : print_char");
	}
	FOUT.Write("syscall");

}

void WriteFunction(Expression * e){
	if(DEBUG) std::cout << "Writing <" << *e << ">\n";
	if(e->location.length()){
		WriteFunctionLocation(e);
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

void ReadFunctionInt(Expression * e){
	FOUT.Write("li $v0, 5");
	FOUT.Write("syscall");
	FOUT.Write("sw $v0," + e->location);
}

void ReadFunctionChar(Expression * e){
	FOUT.Write("li $v0, 12");
        FOUT.Write("syscall");
        FOUT.Write("sw $v0," + e->location);
}

void ReadFunction(std::string id){
	if(DEBUG) std::cout << "Reading into <" << id << ">\n";
	Expression * e = SYMBOL_TABLE.Lookup(id);
	if(e->is_const) {
		std::cerr << "Error: Attempted read into constant." << std::endl;
		exit(1);
	} else if(e->type == &TYPE_INT){
                ReadFunctionInt(e);
        } else if(e->type == &TYPE_CHAR){
                ReadFunctionChar(e);
        } else if(e->type == &TYPE_BOOL){
                ReadFunctionInt(e);
	} else {
		std::cerr << "Error: Attempted read of invalid type." << std::endl;
		exit(1);
	}									
}

void StopFunction(){
	if(DEBUG) std::cout << "Stopping..." << std::endl;
	FOUT.Write("li $v0,10 # Load syscall : exit");
	FOUT.Write("syscall");
}

Expression * ChrFunction(Expression * e){
	// TODO
}

Expression * OrdFunction(Expression * e){
	// TODO
}

Expression * PredFunction(Expression * e){
	// TODO
}

Expression * SuccFunction(Expression * e){
	// TODO
}

