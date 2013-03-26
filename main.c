// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc < 2) // insuficient arguments
		exit(0);

	if(!open_input(argv[1])) // couldn't open input file
		exit(1);

	initMe();

	while(running)
	{
		token = yylex();
		
		if(!running)
			break;
		
		printf("token: %d (line %d)\n", token, getLineNumber());
	}

	printf("Your program has %d lines\n", getLineNumber());

	//printSymbolTable();

	return 1;
}
