
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
			//case REF:
			//case DEREF:
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

					int types_are_correct = check_parameters(function_entry->declaration, ast->child[1], &expected, &given);

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
