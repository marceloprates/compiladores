// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>

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
	ARGUMENTLIST,
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
	PARAMETERLIST,
	FUNCTIONHEADER,
	DECLARATION,
	POINTERDECLARATION,
	LITERALLIST,
	ARRAYDECLARATION,
	DECLARATIONLIST,
	FUNCTIONDEFINITION,
	PROGRAM
};

enum dataType_e
{
	INTEGER,
	BOOL,
	INTEGER_POINTER,
	BOOL_POINTER,
	NO_TYPE,
	FUNCTION_TYPE,
};

typedef enum dataType_e dataType_t;

typedef enum nodeType_e nodeType_t;

struct AST_struct
{
	nodeType_t node_type;
	struct linkedList_s* node;

	dataType_t dataType;

	int numChildren;
	struct AST_struct** child;
};

typedef struct AST_struct AST;

#include "hash.h"

AST* CreateAST(nodeType_t node_type,  struct linkedList_s* node, AST* child_0, AST* child_1, AST* child_2, AST* child_3);
AST* CreateAST0(nodeType_t node_type, struct linkedList_s* node);
AST* CreateAST1(nodeType_t node_type, struct linkedList_s* node, AST* child_0);
AST* CreateAST2(nodeType_t node_type, struct linkedList_s* node, AST* child_0, AST* child_1);
AST* CreateAST3(nodeType_t node_type, struct linkedList_s* node, AST* child_0, AST* child_1, AST* child_2);
AST* CreateAST4(nodeType_t node_type, struct linkedList_s* node, AST* child_0, AST* child_1, AST* child_2, AST* child_3);
char* NodeTypetoString(enum nodeType_e n);
char* ASTtoString(AST* ast, int level);
char* toSource(AST* ast);
void PrintTree(AST* ast);

#endif
