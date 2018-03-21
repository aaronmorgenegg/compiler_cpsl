#include "control_statements.hpp"

std::string LABEL_WHILE_START = "SW";
std::string LABEL_WHILE_END = "EW";

int GetWhileCounter(){
	static int w = 0;
	return w++;
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
	return counter;
}

void WhileStatement(int counter){
	std::string start_label = LABEL_WHILE_START + std::to_string(counter);
	std::string end_label = LABEL_WHILE_END + std::to_string(counter);
	FOUT.Write("j " + start_label);
	FOUT.Write(end_label + ":");
}

