#include "control_statements.hpp"

std::string LABEL_WHILE_START = "SW";
std::string LABEL_WHILE_END = "EW";
std::string LABEL_IF_START = "SI";
std::string LABEL_IF_END = "EI";
std::string LABEL_ELSE = "E";

int GetWhileCounter(){
	static int while_counter = 0;
	return while_counter++;
}

int WhileStart(){
	int label_count = GetWhileCounter();
	FOUT.Write(LABEL_WHILE_START + std::to_string(label_count) + ":");
	return label_count;
}

int WhileHead(int counter, Expression * e){
	std::string condition = LoadExpression(e);
	std::string label = LABEL_WHILE_END + std::to_string(counter);
	FOUT.Write("beq $zero, " + condition + ", " + label);
	REGISTER_POOL.ReleaseRegister(condition);
	return counter;
}

void WhileStatement(int counter){
	std::string start_label = LABEL_WHILE_START + std::to_string(counter);
	std::string end_label = LABEL_WHILE_END + std::to_string(counter);
	FOUT.Write("j " + start_label);
	FOUT.Write(end_label + ":");
}

int GetIfCounter(bool increment){
	static int if_counter = 0;
	if(increment) return if_counter++;
	else return if_counter - 1;
}

int GetElseCounter(bool increment){
	static int else_counter = 0;
	if(increment) return else_counter++;
	else return else_counter - 1;
}

int IfHead(Expression * e){
	int label_count = GetIfCounter(true);
	label_count = GetElseCounter(true);
	std::string condition = LoadExpression(e);
	std::string else_label = LABEL_ELSE + std::to_string(label_count);
	FOUT.Write("beq " + condition + ", $zero, " + else_label);
	REGISTER_POOL.ReleaseRegister(condition);
	return label_count;
}

int ThenStatement(){
	int label_count = GetIfCounter(false);
	std::string end_if_label = LABEL_IF_END + std::to_string(label_count);
	FOUT.Write("j " + end_if_label);
	return label_count;
}

int ElseIfHead(Expression * e){
	int label_count = GetElseCounter(true);
	FOUT.Write(LABEL_ELSE + std::to_string(label_count-1) + ":");
	std::string condition = LoadExpression(e);
	std::string else_label = LABEL_ELSE + std::to_string(label_count);
	FOUT.Write("beq " + condition + ", $zero, " + else_label);
	REGISTER_POOL.ReleaseRegister(condition);
	return label_count;
}


int ElseStatement(){
	int label_count = GetElseCounter(false);
	FOUT.Write(LABEL_ELSE + std::to_string(label_count) + ":");
	label_count = GetIfCounter(false);
	FOUT.Write(LABEL_IF_END + std::to_string(label_count) + ":");
	return label_count;
}

