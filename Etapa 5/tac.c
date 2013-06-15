#include "tac.h"

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

	return tac2;
}

TAC* codeGeneration(AST* ast)
{
	if(ast == NULL)
		return NULL;

	TAC* childTAC[4];
	childTAC[0] = ast->child[0];
	childTAC[1] = ast->child[1];
	childTAC[2] = ast->child[2];
	childTAC[3] = ast->child[3];
}
