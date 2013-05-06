// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "ast.h"
#include "y.tab.h"

extern AST* root;

int WriteToFile(char* path, char* content)
{
	FILE* file;

	file = fopen(path,"w");

	if(file == NULL)
	{
		fprintf(stderr,"ERROR: Couldn't open %s\n",path);
		exit(1);
	}

	fprintf(file,"%s",content);

	return 1;
}

int main(int argc, char** argv)
{
	if(argc < 3) // insuficient arguments
		exit(1);

	if(!open_input(argv[1])) // couldn't open input file
		exit(1);

	initMe();

	yyparse();

	close_input();

	char* decompiledAST = toSource(root);

	WriteToFile(argv[2],decompiledAST);

	// If computation reached this point, no yyparse() errors ocurred. The input code is syntactically correct
	fprintf(stderr,"The input code is syntactically correct!\n");

	exit(0);
}
