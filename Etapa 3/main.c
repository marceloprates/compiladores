// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "y.tab.h"
#include "ast.h"

linkedList_t* createNode(char* text, type_t type)
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

	linkedList_t* node = (linkedList_t*)calloc(1,sizeof(linkedList_t));
	node->symbol = *symbol;
	node->tail = nil();

	return node;
}

int main(int argc, char** argv)
{
	AST* t1 = CreateAST("integer",createNode("42",SYMBOL_LIT_INTEGER),NULL,NULL,NULL,NULL);
	AST* t2 = CreateAST("integer",createNode("6",SYMBOL_LIT_INTEGER),NULL,NULL,NULL,NULL);
	AST* t3 = CreateAST("sum",NULL,t1,t2,NULL,NULL);
	AST* t4 = CreateAST("boolean",createNode("TRUE",SYMBOL_LIT_TRUE),NULL,NULL,NULL,NULL);
	AST* t5 = CreateAST("if-then-else",NULL,t4,t3,t1,NULL);

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