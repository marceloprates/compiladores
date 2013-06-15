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
	if(tac1 == NULL)
		return tac2;

	if(tac2 == NULL)
		return tac1;

	TAC* aux = tac2;

	while(aux->prev != NULL)
	{
		aux = aux->prev;
	}

	aux->prev = tac1;
	tac1->next = aux;

	return tac2;
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
	
	sprintf(labelName, "___label%d___", count);
	count++;
	
	return addSymbol(labelName, SYMBOL_IDENTIFIER);
}

TAC* reverse(TAC* myTac)
{
	if(myTac == NULL)
		return NULL;
		
	TAC* aux = myTac;
	
	while(aux->prev != NULL)
	{
		aux = aux->prev;
	}
	
	return aux;
}

void printTypeTAC(tacType_t type)
{
	switch(type)
	{
		TAC_SYMBOL: printf("SYMBOL"); break;
		TAC_MOVE: printf("MOVE"); break;
		TAC_ADD: printf("ADD"); break;
		TAC_SUB: printf("SUB"); break;
		TAC_MUL: printf("MUL"); break;
		TAC_DIV: printf("DIV"); break;
		TAC_LESS: printf("LESS"); break;
		TAC_LESS_EQUAL: printf("LESS_EQUAL"); break;
		TAC_GREATER: printf("GREATER"); break;
		TAC_GREATER_THAN: printf("GREATER_THAN"); break;
		TAC_EQUAL: printf("EQUAL"); break;
		TAC_NOT_EQUAL: printf("NOT_EQUAL"); break;
		TAC_AND: printf("AND"); break;
		TAC_OR: printf("OR"); break;
		TAC_REF: printf("REF"); break;
		TAC_DEREF: printf("DEREF"); break;
		TAC_LABEL: printf("LABEL"); break;
		TAC_BEGINFUN: printf("BEGINFUN"); break;
		TAC_ENDFUN: printf("ENDFUN"); break;
		TAC_IFZ: printf("IFZ"); break;
		TAC_JUMP: printf("JUMP"); break;
		TAC_CALL: printf("CALL"); break;
		TAC_ARG: printf("ARG"); break;
		TAC_RET: printf("RET"); break;
		TAC_PRINT: printf("PRINT"); break;
		TAC_READ: printf("READ"); break;
		
		default: printf("??"); break;
	}
}

void printCode(TAC* myTac)
{
	TAC* aux;
	
	for(aux = myTac; aux != NULL; aux = aux->next)
	{
		printTypeTAC(aux->tac_type);
		printf(" %s %s %s\n", aux->destination->symbol.text, aux->source1->symbol.text, aux->source2->symbol.text);
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
	TAC* result;
	linkedList_t* testResult = test->destination;
	linkedList_t* elseLabel = newLabel();
	
	TAC* ifThen = append(append(test, tac(TAC_IFZ, elseLabel, testResult, NULL)), thenBlock);
	
	if(elseBlock == NULL)
	{
		result = append(ifThen, tac(TAC_LABEL, elseLabel, NULL, NULL));
	}
	else
	{
		linkedList_t* endLabel = newLabel();
		
		result =
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
	
	return result;
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
	return append(append(args, funcId), tac(TAC_CALL, newTemp(), funcId->destination, NULL));
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

TAC* generateCode(AST* ast)
{
	if(ast == NULL)
		return NULL;

	TAC* childTac[4];
	childTac[0] = generateCode(ast->child[0]);
	childTac[1] = generateCode(ast->child[1]);
	childTac[2] = generateCode(ast->child[2]);
	childTac[3] = generateCode(ast->child[3]);
	
	TAC* result;
	
	switch(ast->node_type)
	{
		case IDENTIFIER: result = tac(TAC_SYMBOL, ast->node, NULL, NULL); break;
		
		case ADDITION: result = binaryOp_tac(TAC_ADD, childTac); break;
		case SUBTRACTION: result = binaryOp_tac(TAC_SUB, childTac); break;
		case MULTIPLICATION: result = binaryOp_tac(TAC_MUL, childTac); break;
		case DIVISION: result = binaryOp_tac(TAC_DIV, childTac); break;
		case LESSERTHAN: result = binaryOp_tac(TAC_LESS, childTac); break;
		case GREATERTHAN: result = binaryOp_tac(TAC_GREATER, childTac); break;
		case LESSEREQUAL: result = binaryOp_tac(TAC_LESS_EQUAL, childTac); break;
		case GREATEREQUAL: result = binaryOp_tac(TAC_GREATER_EQUAL, childTac); break;
		case EQUAL: result = binaryOp_tac(TAC_EQUAL, childTac); break;
		case NOTEQUAL: result = binaryOp_tac(TAC_NOT_EQUAL, childTac); break;
		case AND: result = binaryOp_tac(TAC_AND, childTac); break;
		case OR: result = binaryOp_tac(TAC_OR, childTac); break;
		
		case REF: result = unaryOp_tac(TAC_REF, childTac[0]); break;
		case DEREF: result = unaryOp_tac(TAC_REF, childTac[0]); break;
		
		case IFTHEN:
		case IFTHENELSE:
			result = ifZero_tac(childTac[0], childTac[1], childTac[2]);
			break;
			
		case LOOP: result = loop_tac(childTac[0], childTac[1]); break;
		
		case FUNCTIONCALL: result = call_tac(childTac[0], childTac[1]); break;
		case ARGUMENTLIST: result = args_tac(childTac); break;
		
		case BLOCK:
		case COMMANDLIST:
		case PROGRAM:
		default:
			result = append(append(append(childTac[0], childTac[1]), childTac[2]), childTac[3]);
			break;
	}
	
	return result;
}
