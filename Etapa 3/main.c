// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "y.tab.h"
#include "ast.h"

symbol_t* createSymbol(char* text, type_t type)
{
	symbol_t* symbol = (symbol_t*)calloc(1,sizeof(symbol_t));
	symbol->text = (char*) calloc(strlen(text) + 1, sizeof(char));
	strcpy(symbol->text, text);
	symbol->type = type;

	switch(type)
	{
		case SYMBOL_LIT_INTEGER:
			symbol->value.intLit = atoi(text);
			break;
		case SYMBOL_LIT_TRUE:
			symbol->value.boolLit = 1;
			break;
		case SYMBOL_LIT_FALSE:
			symbol->value.boolLit = 0;
			break;
		case SYMBOL_LIT_CHAR:
			symbol->value.charLit = removeQuotes(text)[0];
			break;
		case SYMBOL_LIT_STRING:
			symbol->value.stringLit = removeQuotes(text);
			break;
		case SYMBOL_IDENTIFIER:
			symbol->value.identifier = text;
			break;
	}

	return symbol;
}

int main(int argc, char** argv)
{

	AST* t1 = (AST*)calloc(1,sizeof(AST)); t1->child = (AST**)calloc(4,sizeof(AST));
	AST* t2 = (AST*)calloc(1,sizeof(AST)); t2->child = (AST**)calloc(4,sizeof(AST));
	AST* t3 = (AST*)calloc(1,sizeof(AST)); t3->child = (AST**)calloc(4,sizeof(AST));
	AST* t4 = (AST*)calloc(1,sizeof(AST)); t4->child = (AST**)calloc(4,sizeof(AST));
	AST* t5 = (AST*)calloc(1,sizeof(AST)); t5->child = (AST**)calloc(4,sizeof(AST));

	CreateNode(t1,"integer",createSymbol("42",SYMBOL_LIT_INTEGER),NULL,NULL,NULL,NULL);
	CreateNode(t2,"integer",createSymbol("6",SYMBOL_LIT_INTEGER),NULL,NULL,NULL,NULL);
	CreateNode(t3,"sum",NULL,t1,t2,NULL,NULL);
	CreateNode(t4,"boolean",createSymbol("TRUE",SYMBOL_LIT_TRUE),NULL,NULL,NULL,NULL);
	CreateNode(t5,"if-then-else",NULL,t4,t3,t1,NULL);

	PrintNode(t5);
	PrintTree(t5);

	/*
	if(argc < 2) // insuficient arguments
		exit(0);

	if(!open_input(argv[1])) // couldn't open input file
		exit(1);

	initMe();

	yyparse();

	close_input();

	// If computation reached this point, no yyparse() errors ocurred. The input code is syntactically correct
	fprintf(stderr,"The input code is syntactically correct!\n");

	exit(0);
	*/
}