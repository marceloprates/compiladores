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
		case TAC_SYMBOL: printf("SYMBOL"); break;
		case TAC_MOVE: printf("MOVE"); break;
		case TAC_ADD: printf("ADD"); break;
		case TAC_SUB: printf("SUB"); break;
		case TAC_MUL: printf("MUL"); break;
		case TAC_DIV: printf("DIV"); break;
		case TAC_LESS: printf("LESS"); break;
		case TAC_LESS_EQUAL: printf("LESS_EQUAL"); break;
		case TAC_GREATER: printf("GREATER"); break;
		case TAC_GREATER_EQUAL: printf("GREATER_EQUAL"); break;
		case TAC_EQUAL: printf("EQUAL"); break;
		case TAC_NOT_EQUAL: printf("NOT_EQUAL"); break;
		case TAC_AND: printf("AND"); break;
		case TAC_OR: printf("OR"); break;
		case TAC_REF: printf("REF"); break;
		case TAC_DEREF: printf("DEREF"); break;
		case TAC_LABEL: printf("LABEL"); break;
		case TAC_BEGINFUN: printf("BEGINFUN"); break;
		case TAC_ENDFUN: printf("ENDFUN"); break;
		case TAC_IFZ: printf("IFZ"); break;
		case TAC_JUMP: printf("JUMP"); break;
		case TAC_CALL: printf("CALL"); break;
		case TAC_ARG: printf("ARG"); break;
		case TAC_RET: printf("RET"); break;
		case TAC_PRINT: printf("PRINT"); break;
		case TAC_READ: printf("READ"); break;
		
		default: printf("??"); break;
	}
}

void printCode(TAC* myTac)
{
	TAC* aux;
	
	for(aux = myTac; aux != NULL; aux = aux->next)
	{
		if(aux->tac_type != TAC_SYMBOL)
		{
			printTypeTAC(aux->tac_type);
			printf(" %s %s %s\n",
				aux->destination ? aux->destination->symbol.text : "NULL",
				aux->source1 ? aux->source1->symbol.text : "NULL",
				aux->source2 ? aux->source2->symbol.text : "NULL");
		}
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

TAC* assignment_tac(TAC* id, TAC* expression)
{
	// TRATAR ARRAYS
	return append(expression, tac(TAC_MOVE, id->destination, expression->destination, NULL));
}

TAC* declaration_tac(TAC* id, TAC* literal)
{
	return tac(TAC_MOVE, id->destination, literal->destination, NULL);
}

/*TAC* output_tac(TAC* args)
{
	TAC* ptr = args;

	TAC* output = NULL;

	if(ptr != NULL)
	{
		output = tac(TAC_PRINT, ptr->destination, NULL, NULL);
		ptr = ptr->prev;
	}

	while(ptr != NULL)
	{
		output = append(tac(TAC_PRINT, ptr->destination, NULL, NULL), output);
		ptr = ptr->prev;
	}

	return append(args,output);
}*/

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
	
	//fprintf(stderr, "%s\n", NodeTypetoString(ast->node_type));

	switch(ast->node_type)
	{
		case LITERAL: result = tac(TAC_SYMBOL, ast->node, NULL, NULL); break;
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

		case ASSIGNMENT: result = assignment_tac(childTac[0], childTac[1]); break;
		
		case FUNCTIONCALL: result = call_tac(childTac[0], childTac[1]); break;
		case ARGUMENTLIST: result = args_tac(childTac); break;

		case DECLARATION: result = declaration_tac(childTac[1], childTac[2]); break;

		//case INPUT: result = tac(TAC_READ, childTac[0], NULL, NULL); break;
		//case OUTPUT: result = output_tac(childTac[0]); break;
		
		case BLOCK:
		case COMMANDLIST:
		case PROGRAM:
		default:
			result = append(append(append(childTac[0], childTac[1]), childTac[2]), childTac[3]);
			break;
	}
	
	return result;
}
