#include "expressions.hpp"

Expression::Expression(std::string reg){
        this->reg = reg;
}

Expression::Expression(int value){
	this->value = value;
	this->is_const = true;
	this->reg = "";
}


std::ostream& operator<<(std::ostream &strm, Expression & e){
        return strm << "Expression: reg(" << e.reg << ") value(" << e.value << ")";
}

std::string LoadExpression(Expression * a){
	if(a->is_const){
		std::string r = REGISTER_POOL.GetRegister();
		FOUT.Write(std::string("li " + r + ", " + std::to_string(a->value) + " # Load constant"));
		return r;
	} else{
		return a->reg;
	}
}

void Binop(std::string op, std::string d, std::string a, std::string b) {
	// op = operator, d = destination register, a = reg1, b = reg2
	FOUT.Write(std::string(op + " " + d + "," + a + "," + b + " # Binop"));
}

void BinopLo(std::string op, std::string d, std::string a, std::string b){
	FOUT.Write(std::string(op + " " + a + "," + b));
	FOUT.Write(std::string("mflo " + d));
}

void BinopHi(std::string op, std::string d, std::string a, std::string b){
        FOUT.Write(std::string(op + " " + a + "," + b));
        FOUT.Write(std::string("mfhi " + d));
}


Expression * Apply(Expression * a, Expression * b, std::string op, std::string mode){
	std::string reg1 = LoadExpression(a);
	std::string reg2 = LoadExpression(b);

	if(mode == "binop") Binop(op, reg1, reg1, reg2);
	if(mode == "hi") BinopHi(op, reg1, reg1, reg2);
	if(mode == "lo") BinopLo(op, reg1, reg1, reg2);

	REGISTER_POOL.ReleaseRegister(reg2);
	return new Expression(reg1);
}

void CheckExpression(Expression * a, Expression * b){
	if(DEBUG) std::cout << "Checking Expressions: a: " << *a << ". b: " << *b << "." << std::endl;
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

Expression * Sub(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value - b->value); // constant folding
        else return Apply(a, b, "sub", "binop");
}

Expression * Mult(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value * b->value); // constant folding
        else return Apply(a, b, "mult", "hi");
}

Expression * Div(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value / b->value); // constant folding
        else return Apply(a, b, "div", "lo");
}

Expression * Mod(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value % b->value); // constant folding
        else return Apply(a, b, "div", "hi");
}

Expression * And(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value && b->value); // constant folding
        else return Apply(a, b, "and", "binop");
}

Expression * Eq(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value == b->value); // constant folding
        else return Apply(a, b, "seq", "binop");
}

Expression * Gteq(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value >= b->value); // constant folding
        else return Apply(a, b, "sge", "binop");
}

Expression * Gt(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value > b->value); // constant folding
        else return Apply(a, b, "sgt", "binop");
}

Expression * Lteq(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value <= b->value); // constant folding
        else return Apply(a, b, "sle", "binop");
}

Expression * Lt(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value < b->value); // constant folding
        else return Apply(a, b, "slt", "binop");
}

Expression * Neq(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value != b->value); // constant folding
        else return Apply(a, b, "sne", "binop");
}

Expression * Or(Expression * a, Expression * b){
        CheckExpression(a, b);
        if(a->is_const && b->is_const) return new Expression(a->value || b->value); // constant folding
        else return Apply(a, b, "or", "binop");
}



