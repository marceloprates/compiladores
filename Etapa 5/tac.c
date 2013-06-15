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
		case ADDITION: binaryOp_tac(TAC_ADD, childTac); break;
		case SUBTRACTION: binaryOp_tac(TAC_SUB, childTac); break;
		case MULTIPLICATION: binaryOp_tac(TAC_MUL, childTac); break;
		case DIVISION: binaryOp_tac(TAC_DIV, childTac); break;
		case LESSERTHAN: binaryOp_tac(TAC_LESS, childTac); break;
		case GREATERTHAN: binaryOp_tac(TAC_GREATER, childTac); break;
		case LESSEREQUAL: binaryOp_tac(TAC_LESS_EQUAL, childTac); break;
		case GREATEREQUAL: binaryOp_tac(TAC_GREATER_EQUAL, childTac); break;
		case EQUAL: binaryOp_tac(TAC_EQUAL, childTac); break;
		case NOTEQUAL: binaryOp_tac(TAC_NOT_EQUAL, childTac); break;
		case AND: binaryOp_tac(TAC_AND, childTac); break;
		case OR: binaryOp_tac(TAC_OR, childTac); break;
		
		case REF: unaryOp_tac(TAC_REF, childTac[0]); break;
		case DEREF: unaryOp_tac(TAC_REF, childTac[0]); break;
		
		case IFTHEN:
		case IFTHENELSE:
			ifZero_tac(childTac[0], childTac[1], childTac[2]);
			break;
			
		case LOOP: loop_tac(childTac[0], childTac[1]); break;
		
		case FUNCTIONCALL: call_tac(childTac[0], childTac[1]); break;
		case ARGUMENTLIST: args_tac(childTac); break;
	}
}

TAC* binaryOp_tac(tacType_t type, TAC** children)
{
	linkedList_t* temp1 = children[0]->destination;
	linkedList_t* temp2 = children[1]->destination;
	
	return append(append(children[0], children[1]), tac(type, newTemp(), temp1, temp2));
}

TAC* unaryOp_tac(tacType_t type, TAC* op)
{
	return append(op, tac(type, newTemp(), op->destination, NULL));
}

TAC* ifZero_tac(TAC* test, TAC* thenBlock, TAC* elseBlock)
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

TAC* loop_tac(TAC* test, TAC* loopBlock)
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

TAC* call_tac(TAC* funcId, TAC* args)
{
	return append(append(args, funcId), tac(TAC_CALL, newTemp(), funcId->destination, NULL))
}

TAC* args_tac(TAC** children)
{
	if(children[0] == NULL)
	// A função não recebe argumentos
		return NULL;
	
	if(children[1] == NULL)
	// Último argumento (calculado em children[0])
	{
		return tac(TAC_ARG, newTemp(), children[0]->destination, NULL);
	}
	else
	// Mais de um argumento, argumentos anteriores empilhados em children[0] e último argumento calculado em children[1]
	{
		return append(children[0], tac(TAC_ARG, newTemp(), children[1]->destination, NULL));
	}
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
