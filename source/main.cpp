#include "symbol_table.hpp"

extern int yyparse();

int main()
{
	FOUT.WriteHeader();
	SYMBOL_TABLE.Initialize();
	yyparse();
};
