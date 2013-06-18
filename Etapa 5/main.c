// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "ast.h"
#include "y.tab.h"
#include "semantic.h"
#include "tac.h"

extern AST* root;

int main(int argc, char** argv)
{
	if(argc < 2) // insuficient arguments
		exit(1);

	if(!open_input(argv[1])) // couldn't open input file
		exit(1);

	initMe();

	yyparse();

	initSemanticAnalyzer();
	first_pass(root);
	verify(root);

	int eCount = getErrorCount();

	if(eCount > 0)
	{
		fprintf(stderr,"%d semantic errors\n", eCount);

		exit(3);
	}

	init_data_segment();
	printCode(reverse(generateCode(root)));

	close_input();

	exit(0);
}
