// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"

AST* CreateAST(nodeType_t node_type, linkedList_t* node, AST* child_0, AST* child_1, AST* child_2, AST* child_3)
{
	AST* ast = (AST*)calloc(1,sizeof(AST));
	ast->child = (AST**)calloc(4,sizeof(AST));

	ast->node_type = node_type;
	ast->node = node;

	ast->child[0] = child_0;
	ast->child[1] = child_1;
	ast->child[2] = child_2;
	ast->child[3] = child_3;

	int i;
	for(i = 0; i < 4; i++)
	{
		if(ast->child[i] != NULL)
			ast->numChildren++;
	}

	return ast;
}

AST* CreateAST0(nodeType_t node_type, linkedList_t* node)
{
	return CreateAST(node_type, node, NULL, NULL, NULL, NULL);
}

AST* CreateAST1(nodeType_t node_type, linkedList_t* node, AST* child_0)
{
	return CreateAST(node_type, node, child_0, NULL, NULL, NULL);
}

AST* CreateAST2(nodeType_t node_type, linkedList_t* node, AST* child_0, AST* child_1)
{
	return CreateAST(node_type, node, child_0, child_1, NULL, NULL);
}

AST* CreateAST3(nodeType_t node_type, linkedList_t* node, AST* child_0, AST* child_1, AST* child_2)
{
	return CreateAST(node_type, node, child_0, child_1, child_2, NULL);
}

char* toString(AST* ast)
{
	if(ast == NULL)
	{
		return "";
	}
	else
	{
		char** childrenStrings = (char**)calloc(ast->numChildren,sizeof(char*));

		int i;

		for(i = 0; i < ast->numChildren; i++)
		{
			childrenStrings[i] = toString(ast->child[i]);
		}

		int fatherStringLength = strlen(ast->node_type);

		for(i = 0; i < ast->numChildren; i++)
		{
			fatherStringLength += 1 + strlen(childrenStrings[i]);
		}

		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char*));

		switch(ast->numChildren)
		{
			case 0:
				if(strcmp(ast->node_type,"integer") == 0)
				{
					sprintf(fatherString,"(%s %d)",ast->node_type, ast->node->symbol.value.intLit);
				}
				else if (strcmp(ast->node_type,"boolean") == 0)
				{
					if(ast->node->symbol.value.boolLit)
					{
						sprintf(fatherString,"(%s %s)",ast->node_type, "TRUE");
					}
					else
					{
						sprintf(fatherString,"(%s %s)",ast->node_type, "FALSE");
					}					
				}
				else if (strcmp(ast->node_type,"char") == 0)
				{
					sprintf(fatherString,"(%s %d)",ast->node_type, ast->node->symbol.value.charLit);
				}
				else if (strcmp(ast->node_type,"string") == 0)
				{
					sprintf(fatherString,"(%s %s)",ast->node_type, ast->node->symbol.value.stringLit);
				}
				else if (strcmp(ast->node_type,"identifier") == 0)
				{
					sprintf(fatherString,"(%s %s)",ast->node_type, ast->node->symbol.value.identifier);
				}
				else
				{
					sprintf(fatherString,"(%s)",ast->node_type);
				}
				break;
			case 1:
				sprintf(fatherString,"(%s %s)",ast->node_type,childrenStrings[0]);
				break;
			case 2:
				sprintf(fatherString,"(%s %s %s)",ast->node_type,childrenStrings[0],childrenStrings[1]);
				break;
			case 3:
				sprintf(fatherString,"(%s %s %s %s)",ast->node_type,childrenStrings[0],childrenStrings[1],childrenStrings[2]);
				break;
			case 4:
				sprintf(fatherString,"(%s %s %s %s %s)",ast->node_type,childrenStrings[0],childrenStrings[1],childrenStrings[2],childrenStrings[3]);
				break;
		}

		return fatherString;
	}
}

void PrintTree(AST* ast)
{
	fprintf(stderr,"%s\n",toString(ast));
}

