%{
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../source/globals.hpp"
#include "../source/builtins.hpp"
#include "../source/variables.hpp"

extern int yylex();
void yyerror(const char*);
%}

%union
{
  const char * str_val;
  int int_val;
  char char_val;
  Expression * expression_val;
  Type * type_val;
  std::vector<std::string> * list_val;
  RecordField * field_val;
  std::vector<RecordField *> * field_list_val;
}

%error-verbose
%token ARRAYSY 
%token ASSIGNSY 
%token BEGINSY 
%token CHARCONSTSY 
%token CHRSY 
%token COLONSY 
%token COMMASY 
%token CONSTSY 
%token DIVSY 
%token DOSY 
%token DOTSY 
%token DOWNTOSY 
%token ELSEIFSY 
%token ELSESY 
%token ENDSY 
%token EQSY 
%token FORSY 
%token FORWARDSY 
%token FUNCTIONSY 
%token GTESY 
%token GTSY 
%token IDENTSY
%token IFSY 
%token INTSY 
%token LBRACKETSY 
%token LPARENSY 
%token LTESY 
%token LTSY 
%token MINUSSY 
%token MODSY 
%token MULTSY
%token NOTSY 
%token OFSY
%token ORDSY 
%token PLUSSY 
%token PREDSY 
%token PROCEDURESY 
%token RBRACKETSY
%token READSY 
%token RECORDSY 
%token REFSY 
%token REPEATSY 
%token RETURNSY 
%token RPARENSY 
%token SCOLONSY 
%token STOPSY 
%token STRINGSY 
%token SUCCSY
%token THENSY 
%token TOSY 
%token TYPESY 
%token UNTILSY 
%token VARSY 
%token WHILESY 
%token WRITESY

%left ANDSY ORSY
%right NOTSY
%nonassoc EQSY LTESY GTESY GTSY LTSY NEQSY 
%left PLUSSY MINUSSY 
%left DIVSY MODSY MULTSY
%right UMINUSSY 

%type <char_val> CHARCONSTSY
%type <int_val> Arguments 
%type <type_val> ArrayType 
%type <int_val> Assignment
%type <int_val> Block 
%type <int_val> Body  
%type <int_val> ElseClause 
%type <int_val> ElseIfHead 
%type <int_val> ElseIfList 
%type <expression_val> Expression 
%type <int_val> FSignature 
%type <field_val> FieldDecl 
%type <field_list_val> FieldDecls
%type <int_val> ForHead 
%type <int_val> ForStatement 
%type <int_val> FormalParameter
%type <int_val> FormalParameters  
%type <int_val> FunctionCall 
%type <int_val> INTSY 
%type <list_val> IdentList 
%type <int_val> OptVar 
%type <int_val> IfHead 
%type <int_val> IfStatement 
%type <str_val> LValue 
%type <int_val> OptArguments 
%type <int_val> OptFormalParameters  
%type <int_val> PSignature 
%type <int_val> ProcedureCall
%type <str_val> ReadArgs
%type <int_val> ReadStatement 
%type <type_val> RecordType 
%type <int_val> RepeatStatement 
%type <int_val> ReturnStatement 
%type <type_val> SimpleType 
%type <int_val> Statement 
%type <int_val> StatementList 
%type <int_val> StopStatement 
%type <int_val> ThenPart 
%type <int_val> ToHead 
%type <type_val> Type 
%type <int_val> WhileHead 
%type <int_val> WhileStatement 
%type <int_val> WriteArgs 
%type <int_val> WriteStatement  
%type <str_val> IDENTSY 
%type <str_val> STRINGSY 

%%
Program : ProgramHead Block DOTSY {YYACCEPT;}
				;

ProgramHead : OptConstDecls OptTypeDecls OptVarDecls PFDecls
            ;
OptConstDecls : CONSTSY ConstDecls
							|
							;

ConstDecls : ConstDecls ConstDecl
					 | ConstDecl
					 ;

ConstDecl : IDENTSY EQSY Expression SCOLONSY {SYMBOL_TABLE.Store(std::string($1), $3);}
					;

PFDecls : PFDecls ProcedureDecl
        | PFDecls FunctionDecl
        |
        ;

ProcedureDecl : PSignature SCOLONSY FORWARDSY SCOLONSY {}
              | PSignature SCOLONSY Body SCOLONSY {}
				    	;

PSignature : PROCEDURESY IDENTSY LPARENSY OptFormalParameters RPARENSY {}
           ;

FunctionDecl : FSignature SCOLONSY FORWARDSY SCOLONSY {}
						 | FSignature SCOLONSY Body SCOLONSY {}
						 ;

FSignature : FUNCTIONSY IDENTSY LPARENSY OptFormalParameters RPARENSY COLONSY Type {}
           ;

OptFormalParameters : FormalParameters {}
                    | {}
                    ;

FormalParameters : FormalParameters SCOLONSY FormalParameter {}
                 | FormalParameter {}
                 ;

FormalParameter : OptVar IdentList COLONSY Type {}
                ;

OptVar : VARSY {}
       | REFSY {}
       | {}
       ;

Body : OptConstDecls OptTypeDecls OptVarDecls Block {}
     ;

Block : BEGINSY StatementList ENDSY {}
      ;

StatementList : StatementList SCOLONSY Statement {}
              | Statement {}
              ;

OptTypeDecls : TYPESY TypeDecls
             |
             ;

TypeDecls    : TypeDecls TypeDecl
             | TypeDecl
             ;

TypeDecl : IDENTSY EQSY Type SCOLONSY {SYMBOL_TABLE.Store(std::string($1), $3);}
         ;

Type : SimpleType {}
     | RecordType {}
     | ArrayType {}
     ;

SimpleType : IDENTSY {$$ = SYMBOL_TABLE.LookupType(std::string($1));}
           ;

RecordType : RECORDSY FieldDecls ENDSY {$$ = dynamic_cast<Type *>(new RecordType($2));}
           ;

FieldDecls : FieldDecls FieldDecl {$1->push_back($2);}
           | {$$ = new std::vector<RecordField *>;}
           ;

FieldDecl : IdentList COLONSY Type SCOLONSY {$$ = new RecordField($1, $3);}
          ;

IdentList : IdentList COMMASY IDENTSY {$1->push_back(std::string($3));}
          | IDENTSY {$$ = new std::vector<std::string>(1, std::string($1));}
          ;

ArrayType : ARRAYSY LBRACKETSY Expression COLONSY Expression RBRACKETSY OFSY Type {$$ = dynamic_cast<Type *>(new ArrayType($3, $5, $8));}
          ;

OptVarDecls : VARSY VarDecls
            |
            ;

VarDecls    : VarDecls VarDecl
            | VarDecl
            ;

VarDecl : IdentList COLONSY Type SCOLONSY {SaveVariables($1, $3);}
        ;

Statement : Assignment {}
          | IfStatement {}
          | WhileStatement {}
          | RepeatStatement {}
          | ForStatement {}
          | StopStatement {}
          | ReturnStatement {}
          | ReadStatement {}
          | WriteStatement {}
          | ProcedureCall {}
          | {}
          ;

Assignment : LValue ASSIGNSY Expression {Assignment($1, $3);}
           ;

IfStatement : IfHead ThenPart ElseIfList ElseClause ENDSY {}
            ;

IfHead : IFSY Expression {}
       ;

ThenPart : THENSY StatementList {}
         ;

ElseIfList : ElseIfList ElseIfHead ThenPart {}
           |{}
           ;

ElseIfHead : ELSEIFSY Expression {}
           ;

ElseClause : ELSESY StatementList {}
           | {}
           ;

WhileStatement : WhileHead DOSY StatementList ENDSY {}
               ;

WhileHead : WHILESY Expression {}
          ;

RepeatStatement : REPEATSY StatementList UNTILSY Expression {}

ForStatement : ForHead ToHead DOSY StatementList ENDSY{}
             ;

ForHead : FORSY IDENTSY ASSIGNSY Expression {}
        ;

ToHead : TOSY Expression {}
       | DOWNTOSY Expression {}
       ;

StopStatement : STOPSY {StopFunction();}
              ;

ReturnStatement : RETURNSY Expression {}
                | RETURNSY {}
                ;

ReadStatement : READSY LPARENSY ReadArgs RPARENSY 
              ;

ReadArgs : ReadArgs COMMASY LValue {ReadFunction(std::string($3));}
         | LValue                  {ReadFunction(std::string($1));}
         ;

WriteStatement : WRITESY LPARENSY WriteArgs RPARENSY 
               ;

WriteArgs : WriteArgs COMMASY Expression {WriteFunction($3);}
          | Expression                   {WriteFunction($1);}
          ;

ProcedureCall : IDENTSY LPARENSY OptArguments RPARENSY {}
              ;
OptArguments : Arguments {}
             |           {}
             ;
Arguments : Arguments COMMASY Expression {}
          | Expression                   {}
          ;

Expression : CHARCONSTSY                         {$$ = new Expression($1, &TYPE_CHAR);}
           | CHRSY LPARENSY Expression RPARENSY  {$$ = ChrFunction($3);}
           | Expression ANDSY Expression         {$$ = And($1, $3);}
           | Expression DIVSY Expression         {$$ = Div($1, $3);}
           | Expression EQSY Expression          {$$ = Eq($1, $3);}
           | Expression GTESY Expression         {$$ = Gteq($1, $3);}
           | Expression GTSY Expression          {$$ = Gt($1, $3);}
           | Expression LTESY Expression         {$$ = Lteq($1, $3);}
           | Expression LTSY Expression          {$$ = Lt($1, $3);}
           | Expression MINUSSY Expression       {$$ = Sub($1, $3);}
           | Expression MODSY Expression         {$$ = Mod($1, $3);}
           | Expression MULTSY Expression        {$$ = Mult($1, $3);}
           | Expression NEQSY Expression         {$$ = Neq($1, $3);}
           | Expression ORSY Expression          {$$ = Or($1, $3);}
           | Expression PLUSSY Expression        {$$ = Add($1, $3);}
           | FunctionCall                        {}
           | INTSY                               {$$ = new Expression($1, &TYPE_INT);}
           | LPARENSY Expression RPARENSY        {$$ = $2;}
           | LValue                              {$$ = Lvalue(std::string($1));}
           | MINUSSY Expression %prec UMINUSSY   {$$ = Mult($2, new Expression(-1, &TYPE_INT));}
           | NOTSY Expression                    {$$ = Not($2);}
           | ORDSY LPARENSY Expression RPARENSY  {$$ = OrdFunction($3);}
           | PREDSY LPARENSY Expression RPARENSY {$$ = PredFunction($3);}
           | STRINGSY                            {$$ = new Expression(STRING_LIST.Store(std::string($1)), &TYPE_STR);}
           | SUCCSY LPARENSY Expression RPARENSY {$$ = SuccFunction($3);}
           ;

FunctionCall : IDENTSY LPARENSY OptArguments RPARENSY {}
             ;

LValue : LValue DOTSY IDENTSY {$$ = RecordAccess($1, $3).c_str();}
       | LValue LBRACKETSY Expression RBRACKETSY {$$ = ArrayAccess($1, $3).c_str();}
       | IDENTSY {$$ = $1;}
       ;
%%

void yyerror(const char* msg)
{
  std::cerr << msg;
}
