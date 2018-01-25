%{
#include <cstdlib>

#include "parser.hpp"
%}
%option noyywrap
%%
array|ARRAY {return ARRAY;}
begin|BEGIN {return BEGIN;}
chr|CHR {return CHR;}
const|CONST {return CONST;}
do|DO {return DO;}
downto|DOWNTO {return DOWNTO;}
else|ELSE {return ELSE;}
elseif|ELSEIF {return ELSEIF;}
end|END {return END;}
for|FOR {return FOR;}
forward|FORWARD {return FORWARD;}
function|FUNCTION {return FUNCTION;}
if|IF {return IF;}
of|OF {return OF;}
ord|ORD {return ORD;}
pred|PRED {return PRED;}
procedure|PROCEDURE {return PROCEDURE;}
read|READ {return READ;}
record|RECORD {return RECORD;}
ref|REF {return REF;}
repeat|REPEAT {return REPEAT;}
return|RETURN {return RETURN;}
stop|STOP {return STOP;}
succ|SUCC {return SUCC;}
then|THEN {return THEN;}
to|TO {return TO;}
type|TYPE {return TYPE;}
until|UNTIL {return UNTIL;}
var|VAR {return VAL;}
while|WHILE {return WHILE;}
write|WRITE {return WRITE;}
\+ {return ADD;}
- {return SUB;}
\* {return MUL;}
\/ {return DIV;}
& {return AND;}
\| {return OR;}
~ {return NOT;}
= {return EQ;}
\<\> {return NEQ;}
\< {return LE;}
\<= {return LEQ;}
\> {return GE;}
\>= {return GEQ;}
\. {return DOT;}
, {return COMMA;}
: {return COLON;}
; {return SEMICOLON;}
\( {return OPAR;}
\) {return CPAR;}
\[ {return OBRACKET;}
\] {return CBRACKET;}
:= {return ASSIGN;}
% {return MOD;}
[0-9]x?[0-9a-fA-F]* {yylval.val = atof(yytext); return INT;}
'.' {yylval.val = yytext; return CHAR;}
\"[a-zA-Z0-9_\-=\+\[\{\]\};:'\,\<\.\>\/\?\\\|`~!@#\$%\^&\*\(\) \t\n]*\" {yylval.val = yyext; return STR;}
$.* {}
[a-zA-z][a-zA-z0-9_]* {return ID;}
\n {}
\r {}
\b {}
\t {}
\f {}
" " {}
"" {}

. {std::cout << "Lexical Error Detected"; exit(1);}
%%

int main(){
	yylex();
}

