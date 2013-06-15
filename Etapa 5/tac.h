#include "hash.h"

enum TAC_type
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

struct TAC_struct
{
	enum TAC_type type;
	linkedList_t* result;
	linkedList_t* op1;
	linkedList_t* op2;
	struct TAC_struct* prev;
	struct TAC_struct* next;
};

typedef struct TAC_struct TAC;

TAC* tac_join(TAC* tac1, TAC* tac2);
