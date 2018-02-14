%{
#include <iostream>

extern int yylex();
void yyerror(const char*);
%}

%union
{
int number;
char letter;
char * word;
};

%token ARRAY
%token BEGINTOKEN
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

%left ADD
%left SUB
%left MUL
%left DIV
%left AND
%left OR
%right NOT
%nonassoc EQ
%nonassoc NEQ
%nonassoc LE
%nonassoc LEQ
%nonassoc GE
%nonassoc GEQ
%%
program : decl_const_opt decl_type_opt decl_var_opt decl_proc_funct_list block DOT
	;
decl_const_opt : empty
	       | decl_const
	       ;
decl_type_opt : empty
	      | decl_type
	      ;
decl_var_opt : empty
	     | decl_var
	     ;
decl_proc_funct_list : empty
		     | decl_proc
		     | decl_funct
		     | decl_proc_funct_list empty
		     | decl_proc_funct_list decl_proc
                     | decl_proc_funct_list decl_funct
		     ;
block : BEGINTOKEN statement_sequence END
      ;
empty : 
      ;
parameters : empty
	   | var_ref_opt ident_list COLON type parameters_list
	   ;
parameters_list : empty
		| SEMICOLON var_ref_opt ident_list COLON type
		;
var_ref_opt : empty
	    | VAR
	    | REF
	    ;
ident : ID
      | INT
      | CHAR
      | STR
      ;
ident_list : ident
	   | ident_list COMMA ident
	   ;
type : type_simple
     | type_record
     | type_array
     ;
type_simple : ident
	    ;
type_record : RECORD type_record_list END
	    ;
type_record_list : empty
		 | ident_list COLON type SEMICOLON
		 | type_record_list ident_list COLON type SEMICOLON
		 ;
type_array : ARRAY OBRACKET expression COLON expression CBRACKET OF type
	   ;
body : block
     | decl_const block
     | decl_const decl_type block
     | decl_const decl_var block
     | decl_const decl_type decl_var block
     | decl_type block
     | decl_type decl_var block
     | decl_var block
     ;
expression : expression OR expression
	   | expression AND expression
	   | NOT expression
	   | expression EQ expression
	   | expression NEQ expression
	   | expression LEQ expression
	   | expression GEQ expression
	   | expression LE expression
	   | expression GE expression
	   | expression ADD expression
	   | expression SUB expression
	   | expression MUL expression
	   | expression DIV expression
	   | expression MOD expression
	   | SUB expression
	   | OPAR expression CPAR
	   | ident OPAR expression_list CPAR
	   | CHR OPAR expression CPAR
	   | ORD OPAR expression CPAR
	   | PRED OPAR expression CPAR
	   | SUCC OPAR expression CPAR
	   | lvalue
	   ;
expression_list : expression
		| expression_list COMMA expression
lvalue : ident member_list
       ;
member_list : empty
	    | DOT ident
	    | OBRACKET expression CBRACKET
	    | member_list empty
            | member_list DOT ident
            | member_list OBRACKET expression CBRACKET
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
statement_if : IF expression THEN statement_sequence elseif_list else_list END
	     ;
elseif_list : empty
	    | ELSEIF expression THEN statement_sequence
	    | elseif_list empty
            | elseif_list ELSEIF expression THEN statement_sequence
	    ;
else_list : empty
	  | ELSE statement_sequence
	  ;
statement_while : WHILE expression DO statement_sequence END
		;
statement_repeat : REPEAT statement_sequence UNTIL expression
		 ;
statement_for : FOR ident ASSIGN expression TO expression DO statement_sequence END
	      | FOR ident ASSIGN expression DOWNTO expression DO statement_sequence END
	      ;
statement_stop : STOP
	       ;
statement_return : RETURN empty
		 | RETURN expression
		 ;
statement_read : READ OPAR lvalue_list CPAR
	       ;
lvalue_list : lvalue
	    | lvalue_list COMMA lvalue
	    ;
statement_write : WRITE OPAR expression_list CPAR
		;
expression_list : expression
		| expression_list COMMA expression
		;
procedure_call : ident OPAR expression_list CPAR
	       | ident OPAR empty CPAR
	       ;
statement_null : empty
	       ;
statement_sequence : statement 
		   | statement_sequence SEMICOLON statement
		   ;
decl_const : CONST decl_const_list
	   ;
decl_const_list : ident EQ expression SEMICOLON
		| decl_const_list ident EQ expression SEMICOLON
		;
decl_proc  : PROCEDURE ident OPAR parameters CPAR SEMICOLON FORWARD SEMICOLON
	   | PROCEDURE ident OPAR parameters CPAR SEMICOLON body SEMICOLON
	   ;
decl_funct : FUNCTION ident OPAR parameters CPAR COLON type SEMICOLON FORWARD SEMICOLON
           | FUNCTION ident OPAR parameters CPAR COLON type SEMICOLON body SEMICOLON
	   ;
decl_type : TYPE decl_type_list
	  ;
decl_type_list : ident EQ type SEMICOLON
	       | decl_type_list ident EQ type SEMICOLON
	       ;
decl_var : VAR decl_var_list
	 ;
decl_var_list : ident_list COLON type SEMICOLON
	      | decl_var_list ident_list COLON type SEMICOLON
	      ;

%%

void yyerror(const char * s){
	std::cerr << s << std::endl;
	exit(1);
}
