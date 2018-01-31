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
%token VAR
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

%type <number> INT
%type <character> CHAR
%type <word> STR

%%
program : statement { std::cout << $1 << "\n"; }
	;

empty : 
      ;
parameters : empty
	   | ident_list
	   ;
ident : ID
      ;
ident_list : ident COMMA ident *
	   ;
type : type_simple
     | type_record
     | type_array
     ;
type_simple : ident
	    ;
type_record : RECORD ident_list COLON type SEMICOLON END
	    ;
type_array : ARRAY OBRACKET expression COLON expression CBRACKET OF type
	   ;
block : BEGIN statement_sequence END
      ;
body : block
     : decl_const body
     : decl_type body
     : decl_var body
     ;
expression : expression OR expression
	   : expression AND expression
	   : expression EQ expression
	   : expression NEQ expression
	   : expression LEQ expression
	   : expression GEQ expression
	   : expression LE expression
	   : expression GE expression
	   : expression ADD expression
	   : expression SUB expression
	   : expression MUL expression
	   : expression DIV expression
	   : expression MOD expression
	   : NOT expression
	   : SUB expression
	   : OPAR expression CPAR
	   : ident OPAR expression COMMA expression * ? CPAR
	   : CHR expression
	   : ORD expression
	   : PRED expression
	   : SUCC expression
	   : lvalue
	   ;
lvalue : ident 
       ;
statement : assignment
	  | statement_if
	  | statement_while
	  | statement_repeat
	  | statement_for
	  | statement_stop
	  | statement_return
	  | statement_read
	  | statement_write
	  | statement_null
	  | procedure_call
	  ;
assignment : lvalue ASSIGN expression
	   ;
statement_if : IF expression THEN statement_sequence ELSEIF expression THEN statement_sequence * ELSE statement_sequence ? END
	     ;
statement_while : WHILE expression DO statement_sequence END
		;
statement_repeat : REPEAT statement_sequence UNTIL expression
		 ;
statement_for : FOR ident ASSIGN expression TO expression DO statement_sequence END
	      | for ident ASSIGN expression downto expression DO statement_sequence END
	      ;
statement_stop : STOP
	       ;
statement_return : RETURN expression ?
		 ;
statement_read : READ OPAR lval COMMA lval * CPAR
	       ;
statement_write : WRITE OPAR expression COMMA expression * CPAR
		;
procedure_call : ident OPAR expression COMMA expression * CPAR
	       ;
statement_null : empty
	       ;
statement_sequence : statement SEMICOLON statement * 
		   ;
decl_const : CONST ident EQ expression SEMICOLON
	   ;
decl_proc  : PROCEDURE ident OPAR parameters CPAR SEMICOLON FORWARD SEMICOLON
	   | PROCEDURE ident OPAR parameters CPAR SEMICOLON body SEMICOLON
	   ;
decl_funct : FUNCTION ident OPAR parameters CPAR COLON type SEMICOLON FORWARD SEMICOLON
           | FUNCTION ident OPAR parameters CPAR COLON type SEMICOLON body SEMICOLON
	   ;
decl_type : TYPE ident = type SEMICLON
	  ;
decl_var : VAR ident_list COLON type SEMICOLON

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

