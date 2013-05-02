// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"

void CreateNode(AST* ast, char* node_type, int value, AST* child_0, AST* child_1, AST* child_2, AST* child_3)
{
	ast->node_type = node_type;
	ast->value = value;

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
}

int HasAssociatedValue(char* node_type)
{
	if((strcmp(node_type,"integer") == 0) | (strcmp(node_type,"char") == 0) | (strcmp(node_type,"byte") == 0) )
		return 1;
	else
		return 0;
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
				if(HasAssociatedValue(ast->node_type))
				{
					sprintf(fatherString,"(%s %d)",ast->node_type, ast->value);
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

void PrintNode(AST* ast)
{
	fprintf(stderr,"(node_type: %s, value: %d)\n", ast->node_type, ast->value);
}

void PrintTree(AST* ast)
{
	fprintf(stderr,"%s\n",toString(ast));
}

int main(int argc, char** argv)
{
	AST* t1 = (AST*)calloc(1,sizeof(AST)); t1->child = (AST**)calloc(4,sizeof(AST));
	AST* t2 = (AST*)calloc(1,sizeof(AST)); t2->child = (AST**)calloc(4,sizeof(AST));
	AST* t3 = (AST*)calloc(1,sizeof(AST)); t3->child = (AST**)calloc(4,sizeof(AST));
	AST* t4 = (AST*)calloc(1,sizeof(AST)); t4->child = (AST**)calloc(4,sizeof(AST));
	AST* t5 = (AST*)calloc(1,sizeof(AST)); t5->child = (AST**)calloc(4,sizeof(AST));

	CreateNode(t1,"integer",42,NULL,NULL,NULL,NULL);
	CreateNode(t2,"integer",3,NULL,NULL,NULL,NULL);
	CreateNode(t3,"sum",0,t1,t2,NULL,NULL);
	CreateNode(t4,"TRUE",0,NULL,NULL,NULL,NULL);
	CreateNode(t5,"if-then-else",0,t4,t3,t1,NULL);

	PrintNode(t5);
	PrintTree(t5);
}