#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"

void first_pass(AST* ast)
{
	if(ast == NULL)
	{
		return;
	}
	else
	{
		switch(ast->node_type)
		{
			case DECLARATION:
			{
				symbol_t* variable_entry = &(ast->child[1]->node->symbol);

				if(variable_entry->marked == TRUE)
				{
					fprintf(stderr,"(SEMANTIC) Variable > %s < is already defined\n", variable_entry->text);
				}
				else
				{
					variable_entry->marked = TRUE;
					variable_entry->declaration = ast;

					switch(ast->child[0]->node_type)
					{
						case TYPEWORD:
						{
							variable_entry->dataType = INTEGER;

							break;
						}
						case TYPEBYTE:
						{
							variable_entry->dataType = INTEGER;

							break;
						}
						case TYPEBOOL:
						{
							variable_entry->dataType = BOOL;

							break;
						}
					}

					symbol_t* literal_entry = &(ast->child[2]->node->symbol);

					if(literal_entry->dataType != variable_entry->dataType)
					{
						fprintf(stderr, "(SEMANTIC) Incompatible types in declaration: %d %s: %d\n", variable_entry->dataType, variable_entry->text, literal_entry->dataType);
					}
				}

				break;
			}
			case FUNCTIONDEFINITION:
			{
				AST* headerAST = ast->child[0];

				symbol_t* function_entry = &(headerAST->child[1]->node->symbol);

				if(function_entry->marked == TRUE)
				{
					fprintf(stderr,"(SEMANTIC) Function > %s < is already defined\n", function_entry->text);
				}
				else
				{
					function_entry->marked = TRUE;
					function_entry->dataType = FUNCTION_TYPE;
					function_entry-> declaration = ast;
					function_entry->nature = FUNCTION;

					AST* returnTypeAST = headerAST->child[0];
					
					switch(returnTypeAST->node_type)
					{
						case TYPEWORD:
						{
							function_entry->returnType = INTEGER;

							break;
						}
						case TYPEBYTE:
						{
							function_entry->returnType = INTEGER;

							break;
						}
						case TYPEBOOL:
						{
							function_entry->returnType = BOOL;

							break;
						}
					}

					declare_parameters(ast);	
				}

				break;
			}
			default:
			{
				first_pass(ast->child[0]);
				first_pass(ast->child[1]);
				first_pass(ast->child[2]);
				first_pass(ast->child[3]);

				break;
			}
		}
	}
}

int declare_parameters(AST* fun_def)
{
	//char* function_name = fun_def->child[0]->child[0]->node->symbol.text;
	AST* parameter = fun_def->child[0]->child[2];
	AST* identifier;
	symbol_t* variable_entry;

	while(TRUE)
	{
		if(parameter->child[0] == NULL)
		{
			break;
		}

		if(parameter->child[2] == NULL)
		{
			identifier = parameter->child[1];
		}
		else
		{
			identifier = parameter->child[2];
		}

		
		variable_entry = &(identifier->node->symbol);

		if(variable_entry->marked == TRUE)
		{
			fprintf(stderr,"(SEMANTIC) Variable > %s < is already defined\n", variable_entry->text);
		}
		else
		{
			variable_entry->marked = TRUE;
			variable_entry->declaration = fun_def;
			//variable_entry->scope = (char*)malloc(sizeof(function_name));
			//sprintf(variable_entry->scope,"%s",function_name);

			switch(fun_def->child[0]->child[0]->node_type)
			{
				case TYPEWORD:
				{
					variable_entry->dataType = INTEGER;

					break;
				}
				case TYPEBYTE:
				{
					variable_entry->dataType = INTEGER;

					break;
				}
				case TYPEBOOL:
				{
					variable_entry->dataType = BOOL;

					break;
				}
			}
		}

		parameter = parameter->child[0];		
	}
}

int compatible(dataType_t t0, dataType_t t1)
{
	int t0_is_pointer = t0 == INTEGER_POINTER || t0 == BOOL_POINTER;
	int t1_is_pointer = t1 == INTEGER_POINTER || t1 == BOOL_POINTER;
	
	return t0 == t1 || (t0_is_pointer && t1_is_pointer)
}

int same_types(AST* parameter, AST* argument)
{
	AST* identifier;
	AST* expr;
	
	if(parameter->child[2] == NULL)
	{
		identifier = parameter->child[1];
	}
	else
	{
		identifier = parameter->child[2];
	}
	
	if(argument->child[1] == NULL)
	{
		expr = argument->child[0];
	}
	else
	{
		expr = argument->child[1];
	}
	
	dataType_t tpar = identifier->node->symbol.dataType;
	dataType_t targ = typecheck(expr);
	
	return compatible(tpar, targ);
}

int check_parameters(AST* parameters, AST* arguments, int* expected, int* given)
{
	if(arguments->node_type != ARGUMENTLIST || parameters->node_type != PARAMETERLIST)
	{
		fprintf(stderr, "ASSERTION FAILURE!!");
		exit(3);
	}

	AST* parameter = parameters;
	AST* argument = arguments;
	*expected = 0;
	*given = 0;
	int types_are_correct = 1;	
	
	while(1)
	{
		if(parameter->child[0] == NULL || argument->child[0] == NULL)
			break;
			
		if(!same_types(parameter, argument))
		{
			types_are_correct = 0;
			break;
		}
			
		(*expected)++; (*given)++;
			
		parameter = parameter->child[2]; argument = argument->child[1];
	}
	
	if(parameter->child[0] != NULL)
	{
		while(parameter->child[0] != NULL)
		{
			(*expected)++; parameter = parameter->child[0];
		}
	}
	
	if(argument->child[0] != NULL)
	{
		while(argument->child[0] != NULL)
		{
			(*given)++; argument = argument->child[0];
		}
	}
	
	return types_are_correct;
}

int typecheck(AST* ast)
{
	if(ast == NULL)
	{
		return NO_TYPE;
	}
	else
	{
		switch(ast->node_type)
		{
			case IDENTIFIER:
			{
				if(ast->node->symbol.marked == FALSE)
				{
					fprintf(stderr,"(SEMANTIC) Variable > %s < is not yet defined\n", ast->node->symbol.text);

					return NO_TYPE;
				}
				else
				{
					return ast->node->symbol.dataType;
				}

				break;
			}
			case LITERAL:
			{
				return ast->node->symbol.dataType;

				break;
			}
			case ADDITION:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != INTEGER || t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for aritimetic operation: %d + %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return INTEGER;
				}

				break;
			}
			case SUBTRACTION:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != INTEGER || t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for aritimetic operation: %d - %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return INTEGER;
				}

				break;
			}
			case MULTIPLICATION:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != INTEGER || t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for aritimetic operation: %d * %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return INTEGER;
				}

				break;
			}
			case DIVISION:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != INTEGER || t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for aritimetic operation: %d / %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return INTEGER;
				}

				break;
			}
			case LESSERTHAN:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != INTEGER || t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %d < %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return BOOL;
				}

				break;
			}
			case GREATERTHAN:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != INTEGER || t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %d > %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return BOOL;
				}

				break;
			}
			case LESSEREQUAL:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != INTEGER || t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %d <= %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return BOOL;
				}

				break;
			}
			case GREATEREQUAL:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != INTEGER || t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %d >= %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return BOOL;
				}

				break;
			}
			case EQUAL:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != INTEGER || t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %d == %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return BOOL;
				}

				break;
			}
			case NOTEQUAL:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != INTEGER || t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %d != %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return BOOL;
				}

				break;
			}
			case AND:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != BOOL || t1 != BOOL)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for boolean operation: %d && %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return BOOL;
				}

				break;
			}
			case OR:
			{
				int t0 = typecheck(ast->child[0]);
				int t1 = typecheck(ast->child[1]);

				if(t0 != BOOL || t1 != BOOL)
				{
					fprintf(stderr,"(SEMANTIC) Incompatible types for boolean operation: %d || %d\n", t0, t1);
					return NO_TYPE;
				}
				else
				{
					return BOOL;
				}

				break;
			}
			case REF:
			{
				dataType_t dataType = typecheck(ast->child[0]);

				if(dataType == INTEGER)
				{
					return INTEGER_POINTER;
				}
				else if(dataType == BOOL)
				{
					return BOOL_POINTER;
				}
				else
				{
					fprintf(stderr,"(SEMANTIC) Attempting to make reference out of non-scalar variable: &%d\n", dataType);
					return NO_TYPE;
				}

				break;
			}
			case DEREF:
			{
				dataType_t dataType = typecheck(ast->child[0]);

				if(dataType == INTEGER_POINTER)
				{
					return INTEGER;
				}
				else if(dataType == BOOL_POINTER)
				{
					return BOOL;
				}
				else
				{
					fprintf(stderr,"(SEMANTIC) Attempting to dereference a non-pointer type: *%d\n", dataType);
					return NO_TYPE;
				}

				break;
			}
			case FUNCTIONCALL:
			{
				symbol_t* function_entry = &(ast->child[0]->node->symbol);

				if(function_entry->nature != FUNCTION)
				{
					fprintf(stderr,"(SEMANTIC) Value > %s < is not a function\n", function_entry->text);
					return NO_TYPE;
				}
				else
				{
					int expected; int given;

					int types_are_correct = check_parameters(function_entry->declaration->child[0]->child[2], ast->child[1], &expected, &given);

					if(expected != given)
					{
						fprintf(stderr,"(SEMANTIC) Function > %s < expected %d parameters, but given %d\n", function_entry->text, expected, given);
					}
					else if(!types_are_correct)
					{
						fprintf(stderr,"(SEMANTIC) Incorrect types for parameters of function > %s <\n", function_entry->text);
					}

					return function_entry->returnType;
				}

				break;
			}
			case ARRAYACCESS:
			{
				symbol_t* array_entry = &(ast->child[0]->node->symbol);

				if(array_entry->nature != ARRAY)
				{
					fprintf(stderr,"(SEMANTIC) Value > %s < is not an array\n", array_entry->text);
					return NO_TYPE;
				}

				int t1 = typecheck(ast->child[1]);

				if(t1 != INTEGER)
				{
					fprintf(stderr,"(SEMANTIC) Array indices must be integer types");
				}
				
				return array_entry->dataType;

				break;
			}
			//case ARGUMENTLIST:
			//case RETURN:
			//case ELEMENTLIST:
			//case OUTPUT:
			//case INPUT:
			//case IFTHEN:
			//case IFTHENELSE:
			//case LOOP:
			//case ASSIGNMENT:
			//case COMMANDLIST:
			//case BLOCK:
			//case PARAMETERLIST:
			//case FUNCTIONHEADER:
			//case DECLARATION:
			//case POINTERDECLARATION:
			//case LITERALLIST:
			//case ARRAYDECLARATION:
			//case DECLARATIONLIST:
			//case FUNCTIONDEFINITION:
			//case PROGRAM:
			default:
			{
				typecheck(ast->child[0]);
				typecheck(ast->child[1]);
				typecheck(ast->child[2]);
				typecheck(ast->child[3]);

				break;
			}
		}
	}
}

int verify(AST* ast)
{
	if(ast == NULL)
	{
		return FALSE;
	}
	else
	{
		switch(ast->node_type)
		{
			case IDENTIFIER:
			case LITERAL:
			case ADDITION:
			case SUBTRACTION:
			case MULTIPLICATION:
			case DIVISION:
			case LESSERTHAN:
			case GREATERTHAN:
			case LESSEREQUAL:
			case GREATEREQUAL:
			case EQUAL:
			case NOTEQUAL:
			case AND:
			case OR:
			case REF:
			case DEREF:
			case FUNCTIONCALL:
			case ARRAYACCESS:
			{
				return typecheck(ast) != NO_TYPE;
			}
			//case ARGUMENTLIST:
			//case RETURN:
			//case ELEMENTLIST:
			//case OUTPUT:
			//case INPUT:
			case IFTHEN:
			case IFTHENELSE:
			case LOOP:
			{
				dataType_t t = typecheck(ast->child[0]);
				
				if(t != BOOL)
				{
					fprintf(stderr,"(SEMANTIC) Expected boolean type in condition\n");
					return FALSE;
				}
				
				return TRUE;
			}
			case ASSIGNMENT:
			{
				dataType_t varType = typecheck(ast->child[0]);
				dataType_t valType = typecheck(ast->child[1]);
				
				if(ast->child[0]->node_type == IDENTIFIER && varType != NO_TYPE && ast->child[0]->node->symbol.nature != SCALAR)
				{
					fprintf(stderr,"(SEMANTIC) Value > %s < is not a variable\n", ast->child[0]->node->symbol.text);
					return FALSE;
				}
				
				if(varType != NO_TYPE && valType != NO_TYPE && !compatible(varType, valType))
				{
					fprintf(stderr,"(SEMANTIC) Incompatible type in assignment: %d = %d\n", varType, valType);
					return FALSE;
				}
				
				return TRUE;
			}
			//case COMMANDLIST:
			//case BLOCK:
			//case PARAMETERLIST:
			//case FUNCTIONHEADER:
			//case DECLARATION:
			//case POINTERDECLARATION:
			//case LITERALLIST:
			//case ARRAYDECLARATION:
			//case DECLARATIONLIST:
			//case FUNCTIONDEFINITION:
			//case PROGRAM:
			//default:
		}
	}
} 
