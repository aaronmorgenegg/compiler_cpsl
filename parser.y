%{
#include <iostream>
#include <string>

extern int yylex();
extern int yyparse();
%}

%union
{
int number;
char character;
std::string word;
}

%token ARRAY
%token BEGIN
%token CHR
%token CONST
%token DO
%token DOWNTO
%token ELSE
%token ELSEIF
%token END
%token FOR
%token FORWARD
%token FUNCTION
%token IF
%token OF
%token ORD
%token PRED
%token PROCEDURE
%token READ
%token RECORD
%token REF
%token REPEAT
%token RETURN
%token STOP
%token SUCC
%token THEN
%token TO
%token TYPE
%token UNTIL
%token VAL
%token WHILE
%token WRITE
%token ADD
%token SUB
%token MUL
%token DIV
%token AND
%token OR
%token NOT
%token EQ
%token NEQ
%token LE
%token LEQ
%token GE
%token GEQ
%token DOT
%token COMMA
%token COLON
%token SEMICOLON
%token OPAR
%token CPAR
%token OBRACKET
%token CBRACKET
%token ASSIGN
%token MOD
%token INT
%token CHAR
%token STR
%token ID

%type <val> NUMBER
%type <val> Expression
%type <val> Factor
%type <val> Term

%%
Statement : Expression DONE {std::cout << $1 << "\n";}
Expression : Expression ADD Term {$$ = $1 + $3;} 
	   | Expression SUB Term {$$ = $1 - $3;}
	   | Term { $$ = $1;}
           ;
Term : Term MULT Factor {$$ = $1 * $3;}
     | Term DIV Factor {$$ = $1 / $3;}
     | Factor {$$ = $1;}
     ;
Factor : OPEN Expression CLOSE {$$ = $2;}
       | NUMBER { $$ = $1;}
       ;

int main(){
	yyparse();
};

