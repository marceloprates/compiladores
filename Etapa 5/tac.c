#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "tac.h"

TAC* data_segment;
TAC* data_segment_end;

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

TAC* clone(TAC* original)
{
	TAC* tac_clone = tac(original->tac_type, original->destination, original->source1, original->source2);

	TAC* clone_ptr = tac_clone->prev;
	TAC* original_ptr = original->prev;

	while(original_ptr != NULL)
	{
		clone_ptr = tac(original_ptr->tac_type, original_ptr->destination, original_ptr->source1, original_ptr->source2);
		clone_ptr->prev = original_ptr->prev;

		original_ptr = original_ptr->prev;
		clone_ptr = clone_ptr->prev;
	}

	return tac_clone;
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

linkedList_t* function_start_label(linkedList_t* function)
{
	char* labelName = malloc(strlen("___") + strlen(function->symbol.text) + strlen("_start") + strlen("___") + 1);

	sprintf(labelName, "___%s_start___", function->symbol.text);

	return addSymbol(labelName, SYMBOL_IDENTIFIER);
}

linkedList_t* function_end_label(linkedList_t* function)
{
	char* labelName = malloc(strlen("___") + strlen(function->symbol.text) + strlen("_end") + strlen("___") + 1);

	sprintf(labelName, "___%s_end___", function->symbol.text);

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
		case TAC_SYMBOL: fprintf(stderr, "SYMBOL"); break;
		case TAC_MOVE: fprintf(stderr, "MOVE"); break;
		case TAC_MOVE_I: fprintf(stderr, "MOVE_I"); break;
		case TAC_ADD: fprintf(stderr, "ADD"); break;
		case TAC_SUB: fprintf(stderr, "SUB"); break;
		case TAC_MUL: fprintf(stderr, "MUL"); break;
		case TAC_DIV: fprintf(stderr, "DIV"); break;
		case TAC_LESS: fprintf(stderr, "LESS"); break;
		case TAC_LESS_EQUAL: fprintf(stderr, "LESS_EQUAL"); break;
		case TAC_GREATER: fprintf(stderr, "GREATER"); break;
		case TAC_GREATER_EQUAL: fprintf(stderr, "GREATER_EQUAL"); break;
		case TAC_EQUAL: fprintf(stderr, "EQUAL"); break;
		case TAC_NOT_EQUAL: fprintf(stderr, "NOT_EQUAL"); break;
		case TAC_AND: fprintf(stderr, "AND"); break;
		case TAC_OR: fprintf(stderr, "OR"); break;
		case TAC_REF: fprintf(stderr, "REF"); break;
		case TAC_DEREF: fprintf(stderr, "DEREF"); break;
		case TAC_LABEL: fprintf(stderr, "LABEL"); break;
		case TAC_BEGINFUN: fprintf(stderr, "BEGINFUN"); break;
		case TAC_ENDFUN: fprintf(stderr, "ENDFUN"); break;
		case TAC_IFZ: fprintf(stderr, "IFZ"); break;
		case TAC_JUMP: fprintf(stderr, "JUMP"); break;
		case TAC_CALL: fprintf(stderr, "CALL"); break;
		case TAC_ARG: fprintf(stderr, "ARG"); break;
		case TAC_RET: fprintf(stderr, "RET"); break;
		case TAC_PRINT: fprintf(stderr, "PRINT"); break;
		case TAC_READ: fprintf(stderr, "READ"); break;
		case TAC_ARRAYASSIGN: fprintf(stderr, "ARRAY_ASSIGN"); break;
		case TAC_OUTPUT_ARG: fprintf(stderr, "OUTPUT_ARG"); break;
		case TAC_GET_ARG: fprintf(stderr, "GET_ARG"); break;
		
		default: fprintf(stderr, "??"); break;
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

			fprintf(stderr, " ");

			if(aux->destination)
			{
				switch(aux->destination->symbol.type)
				{
					case SYMBOL_LIT_INTEGER: fprintf(stderr, "%d ", aux->destination->symbol.value.intLit); break;
					case SYMBOL_LIT_FALSE: fprintf(stderr, "%d ", aux->destination->symbol.value.boolLit); break;
					case SYMBOL_LIT_TRUE: fprintf(stderr, "%d ", aux->destination->symbol.value.boolLit); break;
					case SYMBOL_LIT_CHAR: fprintf(stderr, "%c ", aux->destination->symbol.value.charLit); break;
					case SYMBOL_LIT_STRING: fprintf(stderr, "%c%s%c ", 34, aux->destination->symbol.value.stringLit, 34); break;
					case SYMBOL_IDENTIFIER: fprintf(stderr, "%s ", aux->destination->symbol.value.identifier); break;
				}
			}
			else
			{
				fprintf(stderr, "NULL ");
			}

			if(aux->source1)
			{
				switch(aux->source1->symbol.type)
				{
					case SYMBOL_LIT_INTEGER: fprintf(stderr, "%d ", aux->source1->symbol.value.intLit); break;
					case SYMBOL_LIT_FALSE: fprintf(stderr, "%d ", aux->source1->symbol.value.boolLit); break;
					case SYMBOL_LIT_TRUE: fprintf(stderr, "%d ", aux->source1->symbol.value.boolLit); break;
					case SYMBOL_LIT_CHAR: fprintf(stderr, "%c ", aux->source1->symbol.value.charLit); break;
					case SYMBOL_LIT_STRING: fprintf(stderr, "%c%s%c ", 34, aux->source1->symbol.value.stringLit, 34); break;
					case SYMBOL_IDENTIFIER: fprintf(stderr, "%s ", aux->source1->symbol.value.identifier); break;
				}
			}
			else
			{
				fprintf(stderr, "NULL ");
			}

			if(aux->source2)
			{
				switch(aux->source2->symbol.type)
				{
					case SYMBOL_LIT_INTEGER: fprintf(stderr, "%d ", aux->source2->symbol.value.intLit); break;
					case SYMBOL_LIT_FALSE: fprintf(stderr, "%d ", aux->source2->symbol.value.boolLit); break;
					case SYMBOL_LIT_TRUE: fprintf(stderr, "%d ", aux->source2->symbol.value.boolLit); break;
					case SYMBOL_LIT_CHAR: fprintf(stderr, "%c ", aux->source2->symbol.value.charLit); break;
					case SYMBOL_LIT_STRING: fprintf(stderr, "%c%s%c ", 34, aux->source2->symbol.value.stringLit, 34); break;
					case SYMBOL_IDENTIFIER: fprintf(stderr, "%s ", aux->source2->symbol.value.identifier); break;
				}
			}
			else
			{
				fprintf(stderr, "NULL ");
			}

			fprintf(stderr, "\n");

			/*printf(" %s %s %s\n",
				aux->destination ? aux->destination->symbol.text : "NULL",
				aux->source1 ? aux->source1->symbol.text : "NULL",
				aux->source2 ? aux->source2->symbol.text : "NULL");*/
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

	TAC* new_test = clone(test);
	
	return
		append(
			append(
				append(
					append(
						test,
						append(	
							tac(TAC_LABEL, loopLabel, NULL, NULL),
							tac(TAC_IFZ, endLabel, testResult, NULL)
						)
					),
					loopBlock
				),
				append(
					new_test,
					tac(TAC_JUMP, loopLabel, NULL, NULL)
				)
			),
			tac(TAC_LABEL, endLabel, NULL, NULL)
		);
}

TAC* call_tac(TAC* funcId, TAC* args)
{
	return append(append(args, funcId), tac(TAC_CALL, newTemp(), function_start_label(funcId->destination), NULL));
}

TAC* output_tac(TAC* elements)
{
	return append(elements, tac(TAC_PRINT,NULL,NULL,NULL));
}

TAC* args_tac(TAC** children)
{
	if(children[0] == NULL)
	// A função não recebe argumentos
		return NULL;
	
	if(children[1] == NULL)
	// Último argumento (calculado em children[0])
	{
		return append(children[0], tac(TAC_ARG, NULL, children[0]->destination, NULL));
	}
	else
	// Mais de um argumento, argumentos anteriores empilhados em children[0] e último argumento calculado em children[1]
	{
		return append(children[0], append(children[1], tac(TAC_ARG, NULL, children[1]->destination, NULL)));
	}
}

TAC* output_args_tac(TAC** children)
{
	if(children[0] == NULL)
	// A função não recebe argumentos
		return NULL;
	
	if(children[1] == NULL)
	// Último argumento (calculado em children[0])
	{
		return append(children[0], append(children[1], append(children[2], append(children[3], tac(TAC_OUTPUT_ARG, NULL, children[0]->destination, NULL)))));
	}
	else
	// Mais de um argumento, argumentos anteriores empilhados em children[0] e último argumento calculado em children[1]
	{
		return append(children[0], append(children[1], append(children[2], append(children[3], tac(TAC_OUTPUT_ARG, NULL, children[1]->destination, NULL)))));
	}
}

TAC* return_tac(TAC* expr)
{

	return append(expr, tac(TAC_RET, NULL, expr->destination, NULL));
}

TAC* assignment_tac(TAC* variable, TAC* expression)
{
	switch(variable->tac_type)
	{
		case TAC_SYMBOL: return append(expression, tac(TAC_MOVE, variable->destination, expression->destination, NULL)); break;
		case TAC_ARRAYACCESS: return append(expression, tac(TAC_ARRAYASSIGN, variable->destination, variable->source1, expression->destination)); break;
		//case TAC_DEREF: return append(expression, append(variable, tac(TAC_MOVE_I, variable->destination, expression->destination, NULL))); break;
	}
}

TAC* declaration_tac(TAC* id, TAC* literal)
{

	return tac(TAC_MOVE, id->destination, literal->destination, NULL);
}

TAC* array_declaration_tac(TAC* id, AST* literal_list)
{
	if(literal_list == NULL)
		return NULL;

	if(literal_list->child[0] != NULL)
	{
		if(literal_list->child[0]->child[1] == NULL)
			return NULL;

		return append(array_declaration_tac(id,literal_list->child[0]), tac(TAC_ARRAYASSIGN, id->destination, literal_list->child[0]->child[1]->node, NULL));
	}
	else
	{
		return append(array_declaration_tac(id,literal_list->child[0]), tac(TAC_ARRAYASSIGN, id->destination, literal_list->child[1]->node, NULL));
	}
}

TAC* pointer_declaration_tac(TAC* id, TAC* literal)
{
	linkedList_t* temp = newTemp();

	return append(tac(TAC_DEREF,temp,id->destination,NULL),tac(TAC_MOVE_I,temp,literal->destination,NULL));
}

TAC* fun_def_tac(linkedList_t* node, TAC* header, TAC* local_defs, TAC* block)
{
	linkedList_t* start_label = function_start_label(node);
	linkedList_t* end_label = function_end_label(node);

	return
		append(
			append(
				append(
					append(
						append(
							append(
								append(
									tac(TAC_JUMP,end_label,NULL,NULL),
									tac(TAC_LABEL,start_label,NULL,NULL)
								),
								tac(TAC_BEGINFUN, node, NULL, NULL)
							),
							header
						),
						local_defs
					),
					block
				),
				tac(TAC_ENDFUN, node, NULL, NULL)
			),
			tac(TAC_LABEL,end_label,NULL,NULL)
		);
}

TAC* get_args_tac(TAC** children)
{
	if(children[0] == NULL && children[1] == NULL)
	// A função não recebe argumentos
		return NULL;
	
	if(children[2] == NULL)
	// Último parâmetro (calculado em children[1])
	{
		return append(children[1], tac(TAC_GET_ARG, children[1]->destination, NULL, NULL));
	}
	else
	// Mais de um parâmetro, parâmetros anteriores desempilhados em children[0] e último parâmetro calculado em children[2]
	{
		return append(tac(TAC_GET_ARG, children[2]->destination, NULL, NULL), append(children[0], children[2]));
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
	
	fprintf(stderr, "%s\n", NodeTypetoString(ast->node_type));

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
		
		case REF: result = tac(TAC_REF, newTemp(), childTac[0]->destination, NULL); break;
		case DEREF: result = tac(TAC_DEREF, newTemp(), childTac[0]->destination, NULL); break;
		
		case IFTHEN:
		case IFTHENELSE:
			result = ifZero_tac(childTac[0], childTac[1], childTac[2]);
			break;
			
		case LOOP: result = loop_tac(childTac[0], childTac[1]); break;

		case ARRAYACCESS: result = tac(TAC_ARRAYACCESS, childTac[0]->destination, childTac[1]->destination, NULL); break;

		case ASSIGNMENT: result = assignment_tac(childTac[0], childTac[1]); break;
		
		case FUNCTIONCALL: result = call_tac(childTac[0], childTac[1]); break;

		case ARGUMENTLIST: result = args_tac(childTac); break;

		case ELEMENTLIST: result = output_args_tac(childTac); break;

		case RETURN: result = return_tac(childTac[0]); break;

		case DECLARATION: result = declaration_tac(childTac[1], childTac[2]); break;
		case ARRAYDECLARATION: result = array_declaration_tac(childTac[1], ast->child[3]); break;
		case POINTERDECLARATION: result = pointer_declaration_tac(childTac[1],childTac[2]); break;

		case INPUT: result = tac(TAC_READ, NULL, childTac[0]->destination, NULL); break;
		case OUTPUT: result = output_tac(childTac[0]); break;

		case FUNCTIONDEFINITION: result = fun_def_tac(ast->child[0]->child[1]->node, childTac[0], childTac[1], childTac[2]); break;
		
		case PARAMETERLIST: result = get_args_tac(childTac); break;
		
		case BLOCK:
		case COMMANDLIST:
		case PROGRAM:
		default:
			result = append(append(append(childTac[0], childTac[1]), childTac[2]), childTac[3]);
			break;
	}
printTypeTAC(result->tac_type);
	return result;
}

void init_data_segment()
{

	data_segment = tac(TAC_SYMBOL, newLabel(), NULL, NULL);
}


