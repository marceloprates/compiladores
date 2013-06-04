#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"

struct symbol_s globalScope;

struct symbol_s* currentScope;

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
					variable_entry->nature = SCALAR;
					variable_entry->scope = &globalScope;

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
						char t1str[80];
						char t2str[80];
						typeToString(variable_entry->dataType,t1str);
						typeToString(literal_entry->dataType,t2str);

						fprintf(stderr, "(SEMANTIC) Incompatible types in declaration: %s %s: %s\n", t1str, variable_entry->text, t2str);
					}
				}

				break;
			}
			case ARRAYDECLARATION:
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
					variable_entry->nature = ARRAY;
					variable_entry->scope = &globalScope;

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

					AST* ptr = ast->child[3];
	
					while(ptr != NULL)
					{
						if(ptr->child[0] == NULL)
						{
							break;
						}
	
						if(ptr->child[1]->child[0]->node->symbol.dataType != variable_entry->dataType)
						{
							char t0str[80];
							char t1str[80];

							//typeToString(variable_entry->dataType, t0str);
							//typeToString(ptr->child[1]->child[0]->node->symbol.dataType, t1str);
	
							//fprintf(stderr,"(SEMANTIC) Expected only %s values on %s array >%s< initializer, but found %s instead\n", t0str, t0str, variable_entry->text, t1str);
						}
	
						ptr = ptr->child[1];
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
					function_entry->scope = &globalScope;

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

					local_declarations(ast);	
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

int local_declarations(AST* fun_def)
{
	AST* parameters = fun_def->child[0]->child[2];
	AST* local_decs = fun_def->child[1];

	AST* type;
	AST* identifier;
	AST* literal;

	symbol_t* variable_entry;
	symbol_t* literal_entry;

	// formal parameters
	while(TRUE)
	{
		if(parameters->child[0] == NULL)
		{
			break;
		}

		if(parameters->child[2] == NULL)
		{
			type = parameters->child[0];
			identifier = parameters->child[1];
		}
		else
		{
			type = parameters->child[1];
			identifier = parameters->child[2];
		}
		
		variable_entry = &(identifier->node->symbol);

		if(variable_entry->marked == TRUE)// && exists_in_scope(variable_entry,currentScope))
		{
			fprintf(stderr,"(SEMANTIC) Variable > %s < is already defined\n", variable_entry->text);
		}
		else
		{
			variable_entry->marked = TRUE;
			variable_entry->scope = &(fun_def->child[0]->child[1]->node->symbol);

			switch(type->node_type)
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

		parameters = parameters->child[0];		
	}

	// local declarations
	while(TRUE)
	{
		if(local_decs->child[0] == NULL)
		{
			break;
		}

		type = local_decs->child[1]->child[0];
		identifier = local_decs->child[1]->child[1];
		literal = local_decs->child[1]->child[2];

		variable_entry = &(identifier->node->symbol);
		literal_entry = &(literal->node->symbol);

		variable_entry->marked = TRUE;
		variable_entry->scope = &(fun_def->child[0]->child[1]->node->symbol);

		switch(type->node_type)
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

		if(variable_entry->dataType != literal_entry->dataType)
		{
			char t1str[80];
			char t2str[80];
			typeToString(variable_entry->dataType,t1str);
			typeToString(literal_entry->dataType,t2str);

			fprintf(stderr, "(SEMANTIC) Incompatible types in declaration: %s %s: %s\n", t1str, variable_entry->text, t2str);
		}

		local_decs = local_decs->child[0];
	}
}

int compatible(dataType_t t0, dataType_t t1)
{
	int t0_is_pointer = t0 == INTEGER_POINTER || t0 == BOOL_POINTER;
	int t1_is_pointer = t1 == INTEGER_POINTER || t1 == BOOL_POINTER;
	
	return t0 == t1 || (t0_is_pointer && t1_is_pointer);
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
			
		parameter = parameter->child[0]; argument = argument->child[0];
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
				if(ast->node->symbol.marked == FALSE)// || !exists_in_scope(&(ast->node->symbol),currentScope) )
				{
					fprintf(stderr,"(SEMANTIC) Variable > %s < is not yet defined\n", ast->node->symbol.text);

					return NO_TYPE;
				}
				else if(ast->node->symbol.nature != SCALAR)
				{
					fprintf(stderr,"(SEMANTIC) Value > %s < is not a scalar variable\n", ast->node->symbol.text);

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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for aritimetic operation: %s + %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for aritimetic operation: %s - %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for aritimetic operation: %s * %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for aritimetic operation: %s / %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %s < %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %s > %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %s <= %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %s >= %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %s == %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for relational operation: %s != %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for boolean operation: %s && %s\n", t0str, t1str);
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
					char t0str[80];
					char t1str[80];
					typeToString(t0,t0str);
					typeToString(t1,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible types for boolean operation: %s || %s\n", t0str, t1str);
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
					char t0str[80];
					typeToString(dataType,t0str);

					fprintf(stderr,"(SEMANTIC) Attempting to make reference out of non-scalar variable: &%s\n", t0str);
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
					char t0str[80];
					typeToString(dataType,t0str);

					fprintf(stderr,"(SEMANTIC) Attempting to dereference a non-pointer type: *%s\n", t0str);
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

				break;
			}
			//case ARGUMENTLIST: //nunca entra aqui
			case RETURN:
			{
				int return_type = typecheck(ast->child[0]);

				if(return_type != currentScope->returnType)
				{
					char t0str[80];
					char t1str[80];

					typeToString(return_type,t0str);
					typeToString(currentScope->returnType,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible return type for %s function >%s< : %s\n", t1str, currentScope->text, t0str);
				}

				currentScope = &globalScope;

				break;
			}
			//case ELEMENTLIST: //nunca entra aqui
			case OUTPUT:
			{
				AST* elementList = ast->child[0];

				if(elementList->child[0] == NULL)
					return TRUE;
				else if(elementList->child[1] == NULL)
					return typecheck(elementList->child[0]) != NO_TYPE;
				else
				{
					dataType_t t = typecheck(elementList->child[1]);
					int restIsCorrect = verify(elementList->child[0]);

					return t != NO_TYPE && restIsCorrect;
				}

				break;
			}
			case INPUT:
			{
				dataType_t t = typecheck(ast->child[0]);

				return t == INTEGER || T == BOOL;
				break;
			}
			case IFTHEN:
			case IFTHENELSE:
			case LOOP:
			{
				dataType_t t = typecheck(ast->child[0]);
				
				if(t != BOOL)
				{
					char tstr[80];
					typeToString(t, tstr);

					fprintf(stderr,"(SEMANTIC) Expected boolean expression in condition, got %s instead\n", tstr);
					return FALSE;
				}
				
				return TRUE;

				break;
			}
			case ASSIGNMENT:
			{
				dataType_t varType = typecheck(ast->child[0]);
				dataType_t valType = typecheck(ast->child[1]);
				
				if(varType != NO_TYPE && valType != NO_TYPE && !compatible(varType, valType))
				{
					char t0str[80];
					char t1str[80];
					typeToString(varType,t0str);
					typeToString(valType,t1str);

					fprintf(stderr,"(SEMANTIC) Incompatible type in assignment: %s = %s\n", t0str, t1str);
					return FALSE;
				}
				
				return TRUE;

				break;
			}
			case COMMANDLIST:
			{
				if(ast->child[0] == NULL)
					return TRUE;
				else if(ast->child[1] == NULL)
					return verify(ast->child[0]);
				else
				{
					int firstAreCorrect = verify(ast->child[0]);
					int lastIsCorrect = verify(ast->child[1]);

					return firstAreCorrect && lastIsCorrect;
				}
				break;
			}
			case BLOCK:
			{
				return verify(ast->child[0]);
				break;
			}
			//case PARAMETERLIST: //nunca entra aqui
			//case FUNCTIONHEADER:
			//case DECLARATION:
			//case POINTERDECLARATION:
			//case LITERALLIST:
			//case ARRAYDECLARATION:
			//case DECLARATIONLIST:
			case FUNCTIONDEFINITION:
			{
				currentScope = &(ast->child[0]->child[1]->node->symbol);

				verify(ast->child[2]);

				break;
			}
			//case PROGRAM:
			default:
			{
				verify(ast->child[0]);
				verify(ast->child[1]);
				verify(ast->child[2]);
				verify(ast->child[3]);

				break;
			}
		}
	}
}

void initSemanticAnalyzer()
{
	globalScope.text = (char*)calloc(80,sizeof(char));
	sprintf(globalScope.text, "@global");
	addToTable(globalScope,symbolTable,SYMBOL_TABLE_SIZE);

	currentScope = &globalScope;
}

void typeToString(int type, char* str)
{
	switch(type)
	{
		case INTEGER:
		{
			sprintf(str,"INTEGER");
			break;
		}
		case BOOL:
		{
			sprintf(str,"BOOL");
			break;
		}
		case INTEGER_POINTER:
		{
			sprintf(str,"INTEGER POINTER");
			break;
		}
		case BOOL_POINTER:
		{
			sprintf(str,"BOOL POINTER");
			break;
		}
		case NO_TYPE:
		{
			sprintf(str,"NO TYPE");
			break;
		}
		case FUNCTION_TYPE:
		{
			sprintf(str,"FUNCTION TYPE");
			break;
		}
	}
}
