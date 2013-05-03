// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

struct AST_struct
{
	char* node_type;
	linkedList_t* node;

	int numChildren;
	struct AST_struct** child;
};

typedef struct AST_struct AST;

AST* CreateAST(char* node_type, linkedList_t* node, AST* child_0, AST* child_1, AST* child_2, AST* child_3);
int HasAssociatedValue(char* node_type);
char* toString(AST* ast);
void PrintTree(AST* ast);