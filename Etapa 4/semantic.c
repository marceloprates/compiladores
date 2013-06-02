
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