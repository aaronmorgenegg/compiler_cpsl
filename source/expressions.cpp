#include "expressions.hpp"

std::string LoadExpression(Expression * a){
	if(a->is_const){
		auto r = RegisterPool::GetRegister();
		// TODO this will actually go to a file
		std::cout << "li " << r << ", " << std::to_string(a->value) << " # Load constant" << std::endl;
		return r;
	} else{
		return a->reg;
	}
}

void Binop(std::string op, std::string d, std::string a, std::string b) {
	// op = operator, d = destination register, a = reg1, b = reg2
	if(DEBUG) {
		std::cout << "binop op: " << op << ", dest reg: " << d << ", reg1: " << a << ", reg2: " << b << std::endl;
	}
	// TODO: this will actually go to a file
	std::cout << op << " " << d << "," << a << "," << b << " # Binop " << std::endl;
}

Expression * Apply(Expression * a, Expression * b, std::string op, std::string mode){
	std::string reg1 = LoadExpression(a);
	std::string reg2 = LoadExpression(b);

	if(mode == "binop") Binop(op, reg1, reg1, reg2);

	RegisterPool::ReleaseRegister(reg2);
	return new Expression(reg1);
}

void CheckExpression(Expression * a, Expression * b){
	if(!a || !b){ 
                std::cerr << "Error: nullptr during expression apply." << std::endl;
                exit(1);
        }
        if(a->type != b->type) { // Type error
                std::cerr << "Error: Type error during expression apply." << std::endl;
                exit(1);
        }
	
}

Expression * Add(Expression * a, Expression * b){
	CheckExpression(a, b);
	if(a->is_const && b->is_const) return new Expression(a->value + b->value); // constant folding
	else return Apply(a, b, "add", "binop");
}


