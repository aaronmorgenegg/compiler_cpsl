#include "control_statements.hpp"

std::string LABEL_WHILE_START = "STARTWHILE";
std::string LABEL_WHILE_END = "ENDWHILE";
std::string LABEL_IF_START = "STARTIF";
std::string LABEL_IF_END = "ENDIF";
std::string LABEL_ELSE = "ELSE";
std::string LABEL_FOR_START = "STARTFOR";
std::string LABEL_FOR_END = "ENDFOR";

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

int GetIfCounter(){
	static int if_counter = 0;
	return if_counter++;
}

int GetElseCounter(){
	static int else_counter = 0;
	return else_counter++;
}

void IfStatement(int label_count){
	FOUT.Write(LABEL_IF_END + std::to_string(label_count) + ":");
}

std::vector<int> * IfHead(Expression * e){
	std::vector<int> * label_counts = new std::vector<int>();
	int label_count = GetElseCounter();
	std::string condition = LoadExpression(e);
	std::string else_label = LABEL_ELSE + std::to_string(label_count);
	FOUT.Write("beq " + condition + ", $zero, " + else_label);
	REGISTER_POOL.ReleaseRegister(condition);

	label_counts->push_back(label_count);
	label_counts->push_back(GetIfCounter());
	return label_counts;
}

int ThenStatement(int label_count){
	std::string end_if_label = LABEL_IF_END + std::to_string(label_count);
	FOUT.Write("j " + end_if_label);
	return label_count;
}

int ElseLabel(int label_count){
	FOUT.Write(LABEL_ELSE + std::to_string(label_count) + ":");
	return label_count;
}

int ElseIfHead(Expression * e){
	int label_count = GetElseCounter();
	std::string condition = LoadExpression(e);
	std::string else_label = LABEL_ELSE + std::to_string(label_count);
	FOUT.Write("beq " + condition + ", $zero, " + else_label);
	REGISTER_POOL.ReleaseRegister(condition);
	return label_count;
}

std::vector<int> * ElseIfList(int if_label, int else_label){
	ThenStatement(if_label);
	ElseLabel(else_label);

	std::vector<int> * labels = new std::vector<int>();
	labels->push_back(else_label);
	labels->push_back(if_label);
	return labels;
}

int GetForCounter(){
        static int for_counter = 0;
        return for_counter++;
}


void ForStatement(){
	// output end of loop label, exit scope
	
	SYMBOL_TABLE.ExitScope();
}

Expression * ForHead(std::string id, Expression * val){
	// Lookup id, if it exists assign it to val, if not create it
	FOUT.Write(LABEL_FOR_START + std::to_string(GetForCounter()));
	SYMBOL_TABLE.EnterScope();
	Expression * var;
	try{
		var = SYMBOL_TABLE.Lookup(id);
	} catch(int e) {
		std::string reg = LoadExpression(val);
		var = new Expression(reg, val->type);
	}
	Assignment(var, val);
	return var;
}

void ForStart(Expression * it, Expression * target){

}

