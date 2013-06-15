#include <stdlib.h>

#include "hash.h"
#include "tac.h"

TAC* tac(tacType_t type, linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	TAC* myTac = malloc(sizeof(TAC));
	
	myTac->tac_type = type;
	myTac->destination = destination;
	myTac->source1 = source1;
	myTac->source2 = source2;
	myTac->prev = NULL;
	myTac->next = NULL;
	
	return myTac;
}

TAC* append(TAC* tac1, TAC* tac2)
{
	if(tac2 == NULL)
		return tac1;

	if(tac1 == NULL)
		return NULL;

	TAC* p = tac2;

	while(p->prev != NULL)
	{
		p = p->prev;
	}

	p->prev = tac1;
	tac1->next = p;

	return tac2;
}

TAC* generateCode(AST* ast)
{
	if(ast == NULL)
		return NULL;

	TAC* childTac[4];
	childTac[0] = generateCode(ast->child[0]);
	childTac[1] = generateCode(ast->child[1]);
	childTac[2] = generateCode(ast->child[2]);
	childTac[3] = generateCode(ast->child[3]);
	
	switch(ast->node_type)
	{
		case ADDITION: binaryOp(TAC_ADD, childTac[0], childTac[1]); break;
		case SUBTRACTION: binaryOp(TAC_SUB, childTac[0], childTac[1]); break;
		case MULTIPLICATION: binaryOp(TAC_MUL, childTac[0], childTac[1]); break;
		case DIVISION: binaryOp(TAC_DIV, childTac[0], childTac[1]); break;
		case LESSERTHAN: binaryOp(TAC_LESS, childTac[0], childTac[1]); break;
		case GREATERTHAN: binaryOp(TAC_GREATER, childTac[0], childTac[1]); break;
		case LESSEREQUAL: binaryOp(TAC_LESS_EQUAL, childTac[0], childTac[1]); break;
		case GREATEREQUAL: binaryOp(TAC_GREATER_EQUAL, childTac[0], childTac[1]); break;
		case EQUAL: binaryOp(TAC_EQUAL, childTac[0], childTac[1]); break;
		case NOTEQUAL: binaryOp(TAC_NOT_EQUAL, childTac[0], childTac[1]); break;
		case AND: binaryOp(TAC_AND, childTac[0], childTac[1]); break;
		case OR: binaryOp(TAC_OR, childTac[0], childTac[1]); break;
	}
}

TAC* binaryOp(tacType_t type, TAC* op1, TAC* op2)
{
	linkedList_t* temp1 = op1->destination;
	linkedList_t* temp2 = op2->destination;
	
	return append(append(op1, op2), tac(type, newTemp(), temp1, temp2));
}

linkedList_t* newTemp()
{
	static int count = 0;
	char* tempName = malloc(10 + sizeof(int) * 8 + 1);
	
	sprintf(tempName, "___temp%d___", count);
	count++;
	
	return addSymbol(tempName, SYMBOL_IDENTIFIER);
}
