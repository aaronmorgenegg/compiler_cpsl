#pragma once
#include <iostream>
#include <string>
#include "symbol_table.cpp"

struct Expression {
    std::string reg;
    int value;
    bool is_const;
};

class RegisterPool {
public:
    static std::string getRegister();
};

std::string LoadExpression(Expression a){
    if(a.is_const){
        auto r = RegisterPool::getRegister();
        // TODO this will actually go to a file
        std::cout << "li " << r << ", " << std::to_string(a.value) << " # Load constant" << std::endl;
        return r;
    } else{
        return a.reg;
    }
}

template <typename f>
Expression apply(Expression a, Expression b){
        std::string reg1 = loadExpression(a);
        std::string reg2 = loadExpression(b);
        std::string result = RegisterPool::getRegister();
        f(result, reg1, reg2);
}

void binop(std::string op, std::string dest, std::string a, std::string b) {
    std::cout << op << " " << dest << "," << a << "," << b << std::endl;
}

Expression add(Expression a, Expression b) {
        return apply(a, b, [](auto d, a, b){binop("add",d,a,b})
}

Expression mult(Expression a, Expression b) {
        return apply(a, b, [](auto d, auto a, auto b){
                std::cout << "mult " << a << "," << b <<std::endl;
                std::cout << "mflo " << dest << std::endl;
        }
}

