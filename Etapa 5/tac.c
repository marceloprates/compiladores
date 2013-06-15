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
		case ADDITION: binaryOp(TAC_ADD, childTac); break;
		case SUBTRACTION: binaryOp(TAC_SUB, childTac); break;
		case MULTIPLICATION: binaryOp(TAC_MUL, childTac); break;
		case DIVISION: binaryOp(TAC_DIV, childTac); break;
		case LESSERTHAN: binaryOp(TAC_LESS, childTac); break;
		case GREATERTHAN: binaryOp(TAC_GREATER, childTac); break;
		case LESSEREQUAL: binaryOp(TAC_LESS_EQUAL, childTac); break;
		case GREATEREQUAL: binaryOp(TAC_GREATER_EQUAL, childTac); break;
		case EQUAL: binaryOp(TAC_EQUAL, childTac); break;
		case NOTEQUAL: binaryOp(TAC_NOT_EQUAL, childTac); break;
		case AND: binaryOp(TAC_AND, childTac); break;
		case OR: binaryOp(TAC_OR, childTac); break;
		
		case REF: unaryOp(TAC_REF, childTac[0]); break;
		case DEREF: unaryOp(TAC_REF, childTac[0]); break;
		
		case IFTHEN:
		case IFTHENELSE:
			ifZero(childTac[0], childTac[1], childTac[2]);
			break;
			
		case LOOP: loop(childTac[0], childTac[1]); break;
	}
}

TAC* binaryOp(tacType_t type, TAC** children)
{
	linkedList_t* temp1 = children[0]->destination;
	linkedList_t* temp2 = children[1]->destination;
	
	return append(append(children[0], children[1]), tac(type, newTemp(), temp1, temp2));
}

TAC* unaryOp(tacType_t type, TAC* op)
{
	return append(op, tac(type, newTemp(), op->destination, NULL));
}

TAC* ifZero(TAC* test, TAC* thenBlock, TAC* elseBlock)
{
	TAC* tac;
	linkedList_t* testResult = test->destination;
	linkedList_t* elseLabel = newLabel();
	
	TAC* ifThen = append(append(test, tac(TAC_IFZ, elseLabel, testResult, NULL)), thenBlock);
	
	if(elseBlock == NULL)
	{
		tac = append(ifThen, tac(TAC_LABEL, elseLabel, NULL, NULL));
	}
	else
	{
		linkedList_t* endLabel = newLabel();
		
		tac =
			append(
				append(
					append(
						append(
							ifThen,
							tac(TAC_JUMP, endLabel, NULL, NULL)
						),
						tac(TAC_LABEL, elseLabel, NULL, NULL)
					),
					elseBlock
				),
				tac(TAC_LABEL, endLabel, NULL, NULL)
			);
	}
	
	return tac;
}

TAC* loop(TAC* test, TAC* loopBlock)
{
	linkedList_t* testResult = test->destination;
	linkedList_t* loopLabel = newLabel();
	linkedList_t* endLabel = newLabel();
	
	return
		append(
			append(
				append(
					append(
						tac(TAC_LABEL, loopLabel, NULL, NULL),
						tac(TAC_IFZ, endLabel, testResult, NULL)
					),
					loopBlock
				),
				tac(TAC_JUMP, loopLabel, NULL, NULL)
			),
			tac(TAC_LABEL, endLabel, NULL, NULL)
		);
}

linkedList_t* newTemp()
{
	static int count = 0;
	char* tempName = malloc(10 + sizeof(int) * 8 + 1);
	
	sprintf(tempName, "___temp%d___", count);
	count++;
	
	return addSymbol(tempName, SYMBOL_IDENTIFIER);
}

linkedList_t* newLabel()
{
	static int count = 0;
	char* labelName = malloc(11 + sizeof(int) * 8 + 1);
	
	sprintf(tempName, "___label%d___", count);
	count++;
	
	return addSymbol(tempName, SYMBOL_LABEL);
}
