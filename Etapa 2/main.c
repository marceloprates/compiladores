// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "y.tab.h"

extern char* found_literals;

int main(int argc, char** argv)
{
	
	if(argc < 2) // insuficient arguments
		exit(0);

	if(!open_input(argv[1])) // couldn't open input file
		exit(1);

	initMe();

	yyparse();

	close_input();

	/*
	fprintf(stderr,"Literals found:\n");
	PrintFoundLiterals()
	fprintf(stderr,"\nSymbol Table:\n");
	printSymbolTable();
	*/

	// If computation reached this point, no yyparse() errors ocurred. The input code is syntactically correct
	fprintf(stderr,"The input code is syntactically correct!\n");

	return 1;
}