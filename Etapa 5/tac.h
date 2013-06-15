#include "hash.h"

enum TAC_type
{
	ADD,
	SUB,
	MUL,
	DIV,
	IF0,
	LABEL,
	LD
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
