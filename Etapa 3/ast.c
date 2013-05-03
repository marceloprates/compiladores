// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"

void CreateNode(AST* ast, char* node_type, symbol_t* symbol, AST* child_0, AST* child_1, AST* child_2, AST* child_3)
{
	ast->node_type = node_type;
	ast->symbol = symbol;

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
					sprintf(fatherString,"(%s %d)",ast->node_type, ast->symbol->value.intLit);
				}
				else if (strcmp(ast->node_type,"boolean") == 0)
				{
					if(ast->symbol->value.boolLit)
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
					sprintf(fatherString,"(%s %d)",ast->node_type, ast->symbol->value.charLit);
				}
				else if (strcmp(ast->node_type,"string") == 0)
				{
					sprintf(fatherString,"(%s %s)",ast->node_type, ast->symbol->value.stringLit);
				}
				else if (strcmp(ast->node_type,"identifier") == 0)
				{
					sprintf(fatherString,"(%s %s)",ast->node_type, ast->symbol->value.identifier);
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
	if(strcmp(ast->node_type,"integer") == 0)
	{
		fprintf(stderr,"(node_type: %s, value: %d)\n", ast->node_type, ast->symbol->value.intLit);
		return;
	}
	
	if(strcmp(ast->node_type,"boolean") == 0)
	{
		if(ast->symbol->value.boolLit)
		{
			fprintf(stderr,"(node_type: %s, value: %s)\n", ast->node_type, "TRUE");
		}
		else
		{
			fprintf(stderr,"(node_type: %s, value: %s)\n", ast->node_type, "FALSE");
		}

		return;
	}
	
	if(strcmp(ast->node_type,"char") == 0)
	{
		fprintf(stderr,"(node_type: %s, value: %c)\n", ast->node_type, ast->symbol->value.charLit);
		return;
	}
	
	if(strcmp(ast->node_type,"string") == 0)
	{
		fprintf(stderr,"(node_type: %s, value: %s)\n", ast->node_type, ast->symbol->value.stringLit);
		return;
	}

	if(strcmp(ast->node_type,"identifier") == 0)
	{
		fprintf(stderr, "(node_type: %s, value: %s)\n", ast->node_type, ast->symbol->value.identifier );
		return;
	}

	fprintf(stderr, "(node_type: %s)\n", ast->node_type);
	return;
}

void PrintTree(AST* ast)
{
	fprintf(stderr,"%s\n",toString(ast));
}

/*char* toSource(AST* ast)
{
	if(strcmp(ast->node_type,"seq") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s;%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"add") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s+%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"sub") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s-%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"mul") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s*%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"div") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s/%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"<") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s<%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,">") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s<%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"<=") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s<=%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,">=") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s>=%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"==") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s==%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"!=") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s!=%s",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"ref") == 0)
	{
		char* e0_string = toSource(ast->child[0]);

		int fatherStringLength = strlen(e0_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"&%s",e0_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"deref") == 0)
	{
		char* e0_string = toSource(ast->child[0]);

		int fatherStringLength = strlen(e0_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"*%s",e0_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"parenthesis") == 0)
	{
		char* e0_string = toSource(ast->child[0]);

		int fatherStringLength = strlen(e0_string) + 1;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"(%s)",e0_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"access") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 2;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s[%s]",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"function_call") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 2;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s(%s)",e0_string,e1_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"integer") == 0)
	{
		char* value_string = (char*)calloc((int)ceil(log10(ast->int_value)),sizeof(char));

		sprintf(value_string,"%d",ast->value);

		int fatherStringLength = strlen(value_string);
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"%s",value_string);

		return fatherString;
	}

	if(strcmp(ast->node_type,"identifier") == 0)
	{
		//?
	}

	if(strcmp(ast->node_type,"if-then") == 0)
	{
		char* e0_string = toSource(ast->child[0]);
		char* e1_string = toSource(ast->child[1]);

		int fatherStringLength = strlen(e0_string) + strlen(e1_string) + 2;
		char* fatherString = (char*)calloc(fatherStringLength,sizeof(char));

		sprintf(fatherString,"if(%s)then%s",e0_string,e1_string);

		return fatherString;
	}
}*/