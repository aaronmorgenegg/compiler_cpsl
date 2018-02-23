#include "globals.hpp"

extern int yyparse();

int main()
{
	FOUT.WriteHeader();
	SYMBOL_TABLE.Initialize();
	yyparse();
	FOUT.WriteFooter();
};
