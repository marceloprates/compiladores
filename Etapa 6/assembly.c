#include <stdio.h>
#include <stlib.h>
#include <string.h>
#include <file.h>
#include "tac.h"

FILE* file;

char* lvalue(linkedList_t* node)
{
	char* string = malloc(strlen(node->symbol.text) + 6 + 1);
	sprintf(string, "%s(%%rip)", node->symbol.text);

	return string;
}

char* rvalue(linkedList_t* node)
{
	char* string;

	if(node->symbol.type == SYMBOL_IDENTIFIER)
	{
		string = malloc(strlen(node->symbol.text) + 6 + 1);
		sprintf(string, "%s(%rip)", node->symbol.text);
	}
	else
	{
		string = malloc(1 + strlen(node->symbol.text) + 1);
		sprintf(string, "$%s", node->symbol.text);
	}

	return string;
}

void generateAssembly_move(linkedList_t* destination, linkedList_t* source)
{
	char* destinationString = lvalue(destination);
	char* sourceString = rvalue(source);

	fprintf(file, "movl %s %s\n", sourceString, destinationString);

	free(destinationString);
	free(sourceString);
}

void generateAssembly_add(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "movl %s %s\n", source2String, destinationString);
	fprintf(file, "addl %s %s\n", source1String, destinationString);

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_sub(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "movl %s %s\n", source1String, destinationString);
	fprintf(file, "subl %s %s\n", source2String, destinationString);

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_mul(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "movl %s %s\n", source2String, destinationString);
	fprintf(file, "imull %s %s\n", source1String, destinationString);

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_div(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	movl	x(%rip), %eax
	movl	y(%rip), %edx
	movl	%edx, -4(%rbp)
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	-4(%rbp)
	movl	%eax, z(%rip)

	fprintf(file, "movl %s %%eax\n", source1String);
	fprintf(file, "movl %s %%edx\n", source2String);
	fprintf(file, "movl %%edx -4(%%rbp)\n");
	fprintf(file, "movl %%eax %%edx\n");
	fprintf(file, "sarl $31 %%edx\n");
	fprintf(file, "idivl -4(%%rbp)\n");
	fprintf(file, "movl %%eax %s\n", destinationString);

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssemblyOf(TAC* tac)
{
	switch(tac->tac_type)
	{
		case TAC_SYMBOL = break;
		case TAC_MOVE = generateAssembly_move(tac->destination, tac->source1); break;
		case TAC_MOVE_I = break;//TODO
		case TAC_ARRAYACCESS = break;//TODO
		case TAC_ARRAYASSIGN = break;//TODO
		case TAC_ADD = generateAssembly_add(tac->destination, tac->source1, tac->source2); break;
		case TAC_SUB = generateAssembly_sub(tac->destination, tac->source1, tac->source2); break;
		case TAC_MUL = generateAssembly_mul(tac->destination, tac->source1, tac->source2); break;
		case TAC_DIV = generateAssembly_div(tac->destination, tac->source1, tac->source2); break;
		case TAC_LESS,
		case TAC_LESS_EQUAL,
		case TAC_GREATER,
		case TAC_GREATER_EQUAL,
		case TAC_EQUAL,
		case TAC_NOT_EQUAL,
		case TAC_AND,
		case TAC_OR,
		case TAC_REF,
		case TAC_DEREF,
		case TAC_LABEL,
		case TAC_BEGINFUN,
		case TAC_ENDFUN,
		case TAC_IFZ,
		case TAC_JUMP,
		case TAC_CALL,
		case TAC_ARG,
		case TAC_OUTPUT_ARG,
		case TAC_RET,
		case TAC_PRINT,
		case TAC_READ,
		case TAC_GET_ARG
	}
}

void generateAssembly(TAC* tacs, const char* filename)
{
	TAC* aux;
	file = fopen(filename, "w");

	for(aux = tacs; aux != NULL; aux = aux->next)
	{
		generateAssemblyOf(aux, file);
	}
}
