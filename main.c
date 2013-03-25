#include <stdio.h>

int main(int argc, char** argv)
{
	if(argc < 2) // inssuficient arguments
		exit(0);

	if(!open_input(argv[1])) // couldn't open input file
		exit(1);

	while(running)
	{
		token = yylex();
		printf("token: %d\n", token);
		if(!running)
			break;
	}

	printf("Your program has %d lines\n", getLineNumber());

	return 1;
}
