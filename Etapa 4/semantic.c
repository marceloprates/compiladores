
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
				symbol_t* variable_entry = &((ast->child[1])->node->symbol);

				if(variable_entry->marked == TRUE)
				{
					fprintf(stderr,"(SEMANTIC) variable > %s < is already defined\n", variable_entry->text);
				}
				else
				{
					variable_entry->marked = TRUE;
				}
			}
			case FUNCTIONCALL:
			{
				symbol_t symbol = ast->child[1]->node->symbol;

				if(symbol.nature == FUNCTION)
				{
					checkParameters(symbol.declaration, ast->child[2]);
				}
				else
				{
					fprintf(stderr,"(SEMANTIC) value > %s < is not a function\n", symbol->text);
				}
			}
			default:
			{
				first_pass(ast->child[0]);
				first_pass(ast->child[1]);
				first_pass(ast->child[2]);
				first_pass(ast->child[3]);
			}
		}
	}
}
