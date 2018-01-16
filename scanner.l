%{
#include <iostream>
%}
%option noyywrap
%%
array|ARRAY {std::cout << "Found an ARRAY keyword.\n";}
begin|BEGIN {std::cout << "Found a BEGIN keyword.\n";}
chr|CHR {std::cout << "Found a CHR keyword.\n";}
const|CONST {std::cout << "Found a CONST keyword.\n";}
do|DO {std::cout << "Found a DO keyword.\n";}
downto|DOWNTO {std::cout << "Found a DOWNTO keyword.\n";}
else|ELSE {std::cout << "Found an ELSE keyword.\n";}
elseif|ELSEIF {std::cout << "Found a ELSEIF keyword.\n";}
end|END {std::cout << "Found a END keyword.\n";}
for|FOR {std::cout << "Found a FOR keyword.\n";}
forward|FORWARD {std::cout << "Found a FORWARD keyword.\n";}
function|FUNCTION {std::cout << "Found a FUNCTION keyword.\n";}
if|IF {std::cout << "Found an IF keyword.\n";}
of|OF {std::cout << "Found an OF keyword.\n";}
ord|ORD {std::cout << "Found an ORD keyword.\n";}
pred|PRED {std::cout << "Found a PRED keyword.\n";}
procedure|PROCEDURE {std::cout << "Found a PROCEDURE keyword.\n";}
read|READ {std::cout << "Found a READ keyword.\n";}
record|RECORD {std::cout << "Found a RECORD keyword.\n";}
ref|REF {std::cout << "Found a REF keyword.\n";}
repeat|REPEAT {std::cout << "Found a REPEAT keyword.\n";}
return|RETURN {std::cout << "Found a RETURN keyword.\n";}
stop|STOP {std::cout << "Found a STOP keyword.\n";}
succ|SUCC {std::cout << "Found a SUCC keyword.\n";}
then|THEN {std::cout << "Found a THEN keyword.\n";}
to|TO {std::cout << "Found a TO keyword.\n";}
type|TYPE {std::cout << "Found a TYPE keyword.\n";}
until|UNTIL {std::cout << "Found a UNTIL keyword.\n";}
var|VAR {std::cout << "Found a VAR keyword.\n";}
while|WHILE {std::cout << "Found a WHILE keyword.\n";}
write|WRITE {std::cout << "Found a WRITE keyword.\n";}
+ {std::cout << "Found a + operator.\n";}
- {std::cout << "Found a - operator.\n";}
* {std::cout << "Found a * operator.\n";}
/ {std::cout << "Found a / operator.\n";}
& {std::cout << "Found a & operator.\n";}
| {std::cout << "Found a | operator.\n";}
~ {std::cout << "Found a ~ operator.\n";}
= {std::cout << "Found a = operator.\n";}
<> {std::cout << "Found a <> operator.\n";}
< {std::cout << "Found a < operator.\n";}
<= {std::cout << "Found a <= operator.\n";}
> {std::cout << "Found a > operator.\n";}
>= {std::cout << "Found a >= operator.\n";}
. {std::cout << "Found a . operator.\n";}
, {std::cout << "Found a , operator.\n";}
: {std::cout << "Found a : operator.\n";}
; {std::cout << "Found a ; operator.\n";}
( {std::cout << "Found a ( operator.\n";}
) {std::cout << "Found a ) operator.\n";}
[ {std::cout << "Found a [ operator.\n";}
] {std::cout << "Found a ] operator.\n";}
:= {std::cout << "Found a := operator.\n";}
% {std::cout << "Found a % operator.\n";}
[0-9]x?[0-9a-fA-F]* {std::cout << "Found an INTEGER constant.\n";}
'.' {std::cout << "Found a CHARACTER constant.\n";}
".*" {std::cout << "Found a STRING constant.\n";}
$.* {std::cout << "Found a COMMENT.\n";}
[a-zA-z][a-zA-z0-9_]* {std::cout << "Found an identifier.\n";}


. {std::cout << "Lexical Error Detected";}
%%

int main(){
	yylex();
}
