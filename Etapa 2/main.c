
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	
	if(argc < 2) // insuficient arguments
		exit(0);

	if(!open_input(argv[1])) // couldn't open input file
		exit(1);

	initMe();

	yyparse();

	close_input();

	return 1;
}