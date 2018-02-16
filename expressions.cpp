#include "expressions.hpp"

const bool DEBUG = true;

std::string RegisterPool::GetRegister(){
	std::cout<<"TODO: getting register..."<<std::endl;
}


std::string LoadExpression(Expression a){
    if(a.is_const){
        auto r = RegisterPool::GetRegister();
        // TODO this will actually go to a file
        std::cout << "li " << r << ", " << std::to_string(a.value) << " # Load constant" << std::endl;
        return r;
    } else{
        return a.reg;
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

Expression ExpressionAdd(Expression a, Expression b){
        std::string reg1 = LoadExpression(a);
        std::string reg2 = LoadExpression(b);
        std::string result = RegisterPool::GetRegister();
        Binop("add", result, reg1, reg2);
        return a; // TODO return the result?
}


/*
template <typename f>
Expression apply(Expression a, Expression b){
        std::string reg1 = loadExpression(a);
        std::string reg2 = loadExpression(b);
        std::string result = RegisterPool::getRegister();
        f(result, reg1, reg2);
}

void binop(std::string op, std::string d, std::string a, std::string b) {
    std::cout << op << " " << d << "," << a << "," << b << std::endl;
}

Expression add(Expression a, Expression b) {
        return apply(a, b, [](auto d, auto a, auto b){binop("add",d,a,b);});
}

Expression mult(Expression a, Expression b) {
        return apply(a, b, [](auto d, auto a, auto b){
                std::cout << "mult " << a << "," << b <<std::endl;
                std::cout << "mflo " << d << std::endl;
        });
}
*/

