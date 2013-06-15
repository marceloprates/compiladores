#include "hash.h"

enum tacType_e
{
	TAC_SYMBOL,
	TAC_MOVE,
	TAC_ADD,
	TAC_SUB,
	TAC_MUL,
	TAC_DIV,
	TAC_LESS,
	TAC_LESS_EQUAL,
	TAC_GREATER,
	TAC_GREATER_THAN,
	TAC_EQUAL,
	TAC_NOT_EQUAL,
	TAC_AND,
	TAC_OR,
	TAC_REF,
	TAC_DEREF,
	TAC_LABEL,
	TAC_BEGINFUN,
	TAC_ENDFUN,
	TAC_IFZ,
	TAC_JUMP,
	TAC_CALL,
	TAC_ARG,
	TAC_RET,
	TAC_PRINT,
	TAC_READ
};

struct TAC_s
{
	tacType_t tac_type;

	linkedList_t* destination;
	linkedList_t* source1;
	linkedList_t* source2;

	struct TAC_s* prev;
	struct TAC_s* next;
};

typedef struct TAC_s TAC;

TAC* append(TAC* tac1, TAC* tac2);