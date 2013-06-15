#include "tac.h"

TAC* tac_join(TAC* tac1, TAC* tac2)
{
	if(tac1 == NULL)
		return tac2;

	if(tac2 == NULL)
		return NULL;

	TAC* p = tac1;

	while(p->prev != NULL)
	{
		p = p->prev;
	}

	p->prev = tac2;

	return tac1;
}
