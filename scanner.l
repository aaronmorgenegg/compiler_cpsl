%{
#include <iostream>
%}
%option noyywrap
%%
array|ARRAY {std::cout << "Found an ARRAY keyword: " << yytext << "\n";}
begin|BEGIN {std::cout << "Found a BEGIN keyword: " << yytext << "\n";}
chr|CHR {std::cout << "Found a CHR keyword: " << yytext << "\n";}
const|CONST {std::cout << "Found a CONST keyword: " << yytext << "\n";}
do|DO {std::cout << "Found a DO keyword: " << yytext << "\n";}
downto|DOWNTO {std::cout << "Found a DOWNTO keyword: " << yytext << "\n";}
else|ELSE {std::cout << "Found an ELSE keyword: " << yytext << "\n";}
elseif|ELSEIF {std::cout << "Found a ELSEIF keyword: " << yytext << "\n";}
end|END {std::cout << "Found a END keyword: " << yytext << "\n";}
for|FOR {std::cout << "Found a FOR keyword: " << yytext << "\n";}
forward|FORWARD {std::cout << "Found a FORWARD keyword: " << yytext << "\n";}
function|FUNCTION {std::cout << "Found a FUNCTION keyword: " << yytext << "\n";}
if|IF {std::cout << "Found an IF keyword: " << yytext << "\n";}
of|OF {std::cout << "Found an OF keyword: " << yytext << "\n";}
ord|ORD {std::cout << "Found an ORD keyword: " << yytext << "\n";}
pred|PRED {std::cout << "Found a PRED keyword: " << yytext << "\n";}
procedure|PROCEDURE {std::cout << "Found a PROCEDURE keyword: " << yytext << "\n";}
read|READ {std::cout << "Found a READ keyword: " << yytext << "\n";}
record|RECORD {std::cout << "Found a RECORD keyword: " << yytext << "\n";}
ref|REF {std::cout << "Found a REF keyword: " << yytext << "\n";}
repeat|REPEAT {std::cout << "Found a REPEAT keyword: " << yytext << "\n";}
return|RETURN {std::cout << "Found a RETURN keyword: " << yytext << "\n";}
stop|STOP {std::cout << "Found a STOP keyword: " << yytext << "\n";}
succ|SUCC {std::cout << "Found a SUCC keyword: " << yytext << "\n";}
then|THEN {std::cout << "Found a THEN keyword: " << yytext << "\n";}
to|TO {std::cout << "Found a TO keyword: " << yytext << "\n";}
type|TYPE {std::cout << "Found a TYPE keyword: " << yytext << "\n";}
until|UNTIL {std::cout << "Found a UNTIL keyword: " << yytext << "\n";}
var|VAR {std::cout << "Found a VAR keyword: " << yytext << "\n";}
while|WHILE {std::cout << "Found a WHILE keyword: " << yytext << "\n";}
write|WRITE {std::cout << "Found a WRITE keyword: " << yytext << "\n";}
\+ {std::cout << "Found a + operator: " << yytext << "\n";}
- {std::cout << "Found a - operator: " << yytext << "\n";}
\* {std::cout << "Found a * operator: " << yytext << "\n";}
\/ {std::cout << "Found a / operator: " << yytext << "\n";}
& {std::cout << "Found a & operator: " << yytext << "\n";}
\| {std::cout << "Found a | operator: " << yytext << "\n";}
~ {std::cout << "Found a ~ operator: " << yytext << "\n";}
= {std::cout << "Found a = operator: " << yytext << "\n";}
\<\> {std::cout << "Found a <> operator: " << yytext << "\n";}
\< {std::cout << "Found a < operator: " << yytext << "\n";}
\<= {std::cout << "Found a <= operator: " << yytext << "\n";}
\> {std::cout << "Found a > operator: " << yytext << "\n";}
\>= {std::cout << "Found a >= operator: " << yytext << "\n";}
\. {std::cout << "Found a . operator: " << yytext << "\n";}
, {std::cout << "Found a , operator: " << yytext << "\n";}
: {std::cout << "Found a : operator: " << yytext << "\n";}
; {std::cout << "Found a ; operator: " << yytext << "\n";}
\( {std::cout << "Found a ( operator: " << yytext << "\n";}
\) {std::cout << "Found a ) operator: " << yytext << "\n";}
\[ {std::cout << "Found a [ operator: " << yytext << "\n";}
\] {std::cout << "Found a ] operator: " << yytext << "\n";}
:= {std::cout << "Found a := operator: " << yytext << "\n";}
% {std::cout << "Found a % operator: " << yytext << "\n";}
[0-9]x?[0-9a-fA-F]* {std::cout << "Found an INTEGER constant: " << yytext << "\n";}
'.' {std::cout << "Found a CHARACTER constant: " << yytext << "\n";}
\"[a-zA-Z0-9_\-+\+\[\{\]\};:'\,\<\.\>\/\?\\\|`~!@#\$%\^&\*\(\) \t\n]*\" {std::cout << "Found a STRING constant: " << yytext << "\n";}
$.* {std::cout << "Found a COMMENT: " << yytext << "\n";}
[a-zA-z][a-zA-z0-9_]* {std::cout << "Found an identifier: " << yytext << "\n";}
\n {std::cout << "Found a NEWLINE escape: " << yytext << "\n";}
\r {std::cout << "Found a CARRIAGE RETURN escape: " << yytext << "\n";}
\b {std::cout << "Found a BACKSPACE escape: " << yytext << "\n";}
\t {std::cout << "Found a TAB escape: " << yytext << "\n";}
\f {std::cout << "Found a NEWLINE escape: " << yytext << "\n";}
" " {std::cout << "Found a SPACE: " << yytext << "\n";}
"" {std::cout << "Found a BLANK: " << yytext << "\n";}
. {std::cout << "Lexical Error Detected"; exit(1);}
%%

int main(){
	yylex();
}

