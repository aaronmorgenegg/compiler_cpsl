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

ForContainer::ForContainer(std::string id, Expression * condition, int count){
	this->condition = condition;
	this->count = count;
	this->incr = 0;
	this->id = id;
}

int GetForCounter(){
        static int for_counter = 0;
        return for_counter++;
}

void ForStatement(ForContainer * for_start){
	// output end of loop label, exit scope
	int count = for_start->count;
	int incr = for_start->incr;
	std::string id = for_start->id;
	Expression * condition = for_start->condition;
	std::string condition_reg = LoadExpression(condition);
	std::string start_label = LABEL_FOR_START + std::to_string(count);
        std::string end_label = LABEL_FOR_END + std::to_string(count);

	FOUT.Write("addi " + condition_reg + ", " + condition_reg + ", " + std::to_string(incr));
	Expression * incr_expr = new Expression(condition_reg, condition->type);
	Assignment(SYMBOL_TABLE.Lookup(id), incr_expr);
        FOUT.Write("j " + start_label);
        FOUT.Write(end_label + ":");

	SYMBOL_TABLE.ExitScope();
}

ForContainer * ForHead(std::string id, Expression * val){
	// Lookup id, if it exists assign it to val, if not create it
	SYMBOL_TABLE.EnterScope();
	Expression * var;
	try{
		var = SYMBOL_TABLE.Lookup(id);
	} catch(int e) {
		SaveVariable(id, val->type);
		var = SYMBOL_TABLE.Lookup(id);
	}
	Assignment(var, val);
	int count = ForLabel();
	ForContainer * foo = new ForContainer(id, var, count);
	return foo;
}

ForContainer * ForTo(ForContainer * from, Expression * to){
	Expression * condition = Lt(from->condition, to);
	ForStart(from->count, condition); 
	from->incr = 1;
	return from;
}

ForContainer * ForDownTo(ForContainer * from, Expression * downto){
	Expression * condition = Gt(from->condition, downto);
	ForStart(from->count, condition); 
	from->incr = -1;
	return from;
}

void ForStart(int count, Expression * e){
	std::string condition = LoadExpression(e);
	std::string label = LABEL_FOR_END + std::to_string(count);
        FOUT.Write("beq $zero, " + condition + ", " + label);
	REGISTER_POOL.ReleaseRegister(condition);
}

int ForLabel(){
	int count = GetForCounter();
	FOUT.Write(LABEL_FOR_START + std::to_string(count) + ":");
	return count;
}

