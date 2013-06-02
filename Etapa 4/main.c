// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "ast.h"
#include "y.tab.h"
#include "semantic.h"

extern AST* root;

int main(int argc, char** argv)
{
	if(argc < 2) // insuficient arguments
		exit(1);

	if(!open_input(argv[1])) // couldn't open input file
		exit(1);

	initMe();

	yyparse();

	first_pass(root);

	close_input();

	exit(0);
}
