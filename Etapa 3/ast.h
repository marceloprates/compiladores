// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

enum nodeType_e
{
	IDENTIFIER,
	TYPEWORD,
	TYPEBOOL,
	TYPEBYTE,
	LITERAL,
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	LESSERTHAN,
	GREATERTHAN,
	LESSEREQUAL,
	GREATEREQUAL,
	EQUAL,
	NOTEQUAL,
	AND,
	OR,
	REF,
	DEREF,
	FUNCTIONCALL,
	ARRAYACCESS,
	PARAMETERLIST,
	RETURN,
	ELEMENTLIST,
	OUTPUT,
	INPUT,
	IFTHEN,
	IFTHENELSE,
	LOOP,
	ASSIGNMENT,
	COMMANDLIST,
	BLOCK,
	TYPEPARAMETERLIST,
	FUNCTIONHEADER,
	DECLARATION,
	POINTERDECLARATION,
	LITERALLIST,
	ARRAYDECLARATION,
	DECLARATIONLIST,
	FUNCTIONDEFINITION,
	PROGRAM
};

typedef enum nodeType_e nodeType_t;

struct AST_struct
{
	nodeType_t node_type;
	linkedList_t* node;

	int numChildren;
	struct AST_struct** child;
};

typedef struct AST_struct AST;

AST* CreateAST(nodeType_t node_type, linkedList_t* node, AST* child_0, AST* child_1, AST* child_2, AST* child_3);
AST* CreateAST0(nodeType_t node_type, linkedList_t* node);
AST* CreateAST1(nodeType_t node_type, linkedList_t* node, AST* child_0);
AST* CreateAST2(nodeType_t node_type, linkedList_t* node, AST* child_0, AST* child_1);
AST* CreateAST3(nodeType_t node_type, linkedList_t* node, AST* child_0, AST* child_1, AST* child_2);
int HasAssociatedValue(char* node_type);
char* toString(AST* ast);
void PrintTree(AST* ast);
