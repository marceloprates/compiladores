#include "tac.h"

TAC* tac_join(TAC* tac1, TAC* tac2)
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
