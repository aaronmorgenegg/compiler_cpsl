#include "symbol_table.hpp"

extern int yyparse();

int main()
{
	SYMBOL_TABLE.Initialize();
	yyparse();
};
