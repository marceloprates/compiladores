// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"

#define TEST fprintf(stderr, "%s\n", buffer);
#define PRINT(x) fprintf(stderr, "%s\n", x);
#define ECHO fprintf(stderr, "HELLO\n");

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

AST* CreateAST4(nodeType_t node_type, linkedList_t* node, AST* child_0, AST* child_1, AST* child_2, AST* child_3)
{

	return CreateAST(node_type, node, child_0, child_1, child_2, child_3);
}

char* NodeTypetoString(enum nodeType_e n)
{
	char** strings = (char*[]){
		"IDENTIFIER",
		"TYPEWORD",
		"TYPEBOOL",
		"TYPEBYTE",
		"LITERAL",
		"ADDITION",
		"SUBTRACTION",
		"MULTIPLICATION",
		"DIVISION",
		"LESSERTHAN",
		"GREATERTHAN",
		"LESSEREQUAL",
		"GREATEREQUAL",
		"EQUAL",
		"NOTEQUAL",
		"AND",
		"OR",
		"REF",
		"DEREF",
		"FUNCTIONCALL",
		"ARRAYACCESS",
		"ARGUMENTLIST",
		"RETURN",
		"ELEMENTLIST",
		"OUTPUT",
		"INPUT",
		"IFTHEN",
		"IFTHENELSE",
		"LOOP",
		"ASSIGNMENT",
		"COMMANDLIST",
		"BLOCK",
		"PARAMETERLIST",
		"FUNCTIONHEADER",
		"DECLARATION",
		"POINTERDECLARATION",
		"LITERALLIST",
		"ARRAYDECLARATION",
		"DECLARATIONLIST",
		"FUNCTIONDEFINITION",
		"PROGRAM"
	};

	return strings[(int)n];
}

char* ASTtoString(AST* ast, int level)
{
	if(ast == NULL)
	{
		return "";
	}
	else
	{
		char* identation = (char*)calloc(level,sizeof(char));

		int i;

		for(i = 0; i < level; i++)
			identation[i] = ' ';

		char* child0_string = ASTtoString(ast->child[0],level+1);
		char* child1_string = ASTtoString(ast->child[1],level+1);
		char* child2_string = ASTtoString(ast->child[2],level+1);
		char* child3_string = ASTtoString(ast->child[3],level+1);

		char* buffer = (char*)calloc(100 + 2 + strlen(identation) + strlen(NodeTypetoString(ast->node_type)) + 1 + strlen(child0_string) + 1 + strlen(child1_string) + 1 + strlen(child2_string) + 1 + strlen(child3_string) + 1,sizeof(char));

		sprintf(buffer,"%d: %s%s\n%s\n%s\n%s\n%s\n",level,identation,NodeTypetoString(ast->node_type),child0_string,child1_string,child2_string,child3_string);

		return buffer;
	}
}

char* toSource(AST* ast)
{
	if(ast == NULL)
	{
		return "";
	}
	else
	{
		switch(ast->node_type)
		{
			case IDENTIFIER:
			{
				char* s = (char*)calloc(strlen(ast->node->symbol.value.identifier) + 1,sizeof(char));
				strcpy(s,ast->node->symbol.value.identifier);
				return s;
				break;
			}
			case TYPEWORD:
			{
				return "word";
				break;
			}
			case TYPEBOOL:
			{
				return "bool";
				break;
			}
			case TYPEBYTE:
			{
				return "byte";
				break;
			}
			case LITERAL:
			{
				switch(ast->node->symbol.type)
				{
					case SYMBOL_LIT_INTEGER:
					{
						char* buffer = (char*)calloc(30,sizeof(char));
						sprintf(buffer,"0%x",ast->node->symbol.value.intLit);
						return buffer;
						break;
					}
					case SYMBOL_LIT_TRUE:
					{
						return "TRUE";
						break;
					}
					case SYMBOL_LIT_FALSE:
					{
						return "FALSE";
						break;
					}
					case SYMBOL_LIT_CHAR:
					{
						char* buffer = (char*)calloc(3,sizeof(char));
						sprintf(buffer,"'%c'",ast->node->symbol.value.charLit);
						return buffer;
						break;
					}
					case SYMBOL_LIT_STRING:
					{
						char* s = (char*)calloc(1 + strlen(ast->node->symbol.value.identifier) + 1 + 1,sizeof(char));
						sprintf(s,"%c%s%c",(char)34,ast->node->symbol.value.stringLit,(char)34);
						return s;
						break;
					}
				}
				break;
			}
			case ADDITION:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s+%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case SUBTRACTION:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s-%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case MULTIPLICATION:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s*%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case DIVISION:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s/%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case LESSERTHAN:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s<%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case GREATERTHAN:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s>%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case LESSEREQUAL:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s<=%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case GREATEREQUAL:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s>=%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case EQUAL:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s==%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case NOTEQUAL:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s!=%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case AND:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s&&%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case OR:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"(%s||%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case REF:
			{
				char* child0_source = toSource(ast->child[0]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1,sizeof(char));
				sprintf(buffer,"&%s",child0_source);
				return buffer;
				break;
			}
			case DEREF:
			{
				char* child0_source = toSource(ast->child[0]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1,sizeof(char));
				sprintf(buffer,"*%s",child0_source);
				return buffer;
				break;
			}
			case FUNCTIONCALL:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s(%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case ARRAYACCESS:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s[%s]",child0_source,child1_source);
				return buffer;
				break;
			}
			case ARGUMENTLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else if(ast->child[1] == NULL)
				{
					char* child0_source = toSource(ast->child[0]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1,sizeof(char));

					sprintf(buffer,"%s",child0_source);

					return buffer;
				}
				else
				{
					char* child0_source = toSource(ast->child[0]);
					char* child1_source = toSource(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1,sizeof(char));

					sprintf(buffer,"%s,%s",child0_source,child1_source);

					return buffer;
				}
				break;
			}
			case RETURN:
			{
				char* child0_source = toSource(ast->child[0]);
				char* buffer = (char*)calloc(strlen("return") + 1 + strlen(child0_source) + 1,sizeof(char));
				sprintf(buffer,"return %s",child0_source);
				return buffer;
				break;
			}
			case ELEMENTLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else if(ast->child[1] == NULL)
				{
					char* child0_source = toSource(ast->child[0]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1,sizeof(char));

					sprintf(buffer,"%s",child0_source);

					return buffer;
				}
				else
				{
					char* child0_source = toSource(ast->child[0]);
					char* child1_source = toSource(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1,sizeof(char));

					sprintf(buffer,"%s,%s",child0_source,child1_source);

					return buffer;
				}
				break;
			}
			case OUTPUT:
			{
				char* child0_source = toSource(ast->child[0]);
				char* buffer = (char*)calloc(strlen("output") + 1 + strlen(child0_source) + 1,sizeof(char));
				sprintf(buffer,"output %s",child0_source);
				return buffer;
				break;
			}
			case INPUT:
			{
				char* child0_source = toSource(ast->child[0]);
				char* buffer = (char*)calloc(strlen("input") + 1 + strlen(child0_source) + 1,sizeof(char));
				sprintf(buffer,"input %s",child0_source);
				return buffer;
				break;
			}
			case IFTHEN:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(strlen("if") + 1 + strlen(child0_source) + 1 + 1 + strlen("then") + 1 + strlen(child1_source) + 1,sizeof(char));
				sprintf(buffer,"if(%s) then\n%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case IFTHENELSE:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* child2_source = toSource(ast->child[2]);
				char* buffer = (char*)calloc(strlen("if") + 1 + strlen(child0_source) + 1 + 1 + strlen("then") + 1 + strlen(child1_source) + 1 + strlen("else") + 1 + strlen(child2_source) + 1,sizeof(char));
				sprintf(buffer,"if(%s) then\n%s\nelse\n%s",child0_source,child1_source,child2_source);
				return buffer;
				break;
			}
			case LOOP:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(strlen("loop") + 1 + strlen(child0_source) + 1 + 1 + strlen(child1_source) + 1,sizeof(char));
				sprintf(buffer,"loop(%s)\n%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case ASSIGNMENT:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1,sizeof(char));
				sprintf(buffer,"%s=%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case COMMANDLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else
				{
					char* child0_source = toSource(ast->child[0]);
					char* child1_source = toSource(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + strlen(child1_source) + 1 + 1 + 1,sizeof(char));

					if(strcmp(child0_source,"") == 0)
						sprintf(buffer,"%s;",child1_source);
					else
						sprintf(buffer,"%s\n%s;",child0_source,child1_source);

					return buffer;
				}
				break;
			}
			case BLOCK:
			{
				char* child0_source = toSource(ast->child[0]);
				char* buffer = (char*)calloc(1 + 1 + strlen(child0_source) + 1 + 1 + 1,sizeof(char));
				sprintf(buffer,"{\n%s\n}",child0_source);
				return buffer;
				break;
			}
			case PARAMETERLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else if(ast->child[2] == NULL)
				{
					char* child0_source = toSource(ast->child[0]);
					char* child1_source = toSource(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1,sizeof(char));

					sprintf(buffer,"%s %s",child0_source,child1_source);

					return buffer;
				}
				else
				{
					char* child0_source = toSource(ast->child[0]);
					char* child1_source = toSource(ast->child[1]);
					char* child2_source = toSource(ast->child[2]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1,sizeof(char));

					sprintf(buffer,"%s, %s %s",child0_source,child1_source,child2_source);

					return buffer;
				}
				break;
			}
			case FUNCTIONHEADER:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* child2_source = toSource(ast->child[2]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s %s(%s)",child0_source,child1_source,child2_source);
				return buffer;
				break;
			}
			case DECLARATION:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* child2_source = toSource(ast->child[2]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1,sizeof(char));
				sprintf(buffer,"%s %s:%s",child0_source,child1_source,child2_source);
				return buffer;
				break;
			}
			case POINTERDECLARATION:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* child2_source = toSource(ast->child[2]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1,sizeof(char));
				sprintf(buffer,"%s $%s:%s",child0_source,child1_source,child2_source);
				return buffer;
				break;
			}
			case LITERALLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else
				{
					char* child0_source = toSource(ast->child[0]);
					char* child1_source = toSource(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1,sizeof(char));

					if(strcmp(child0_source,"") == 0)
						sprintf(buffer,"%s",child1_source);
					else
						sprintf(buffer,"%s %s",child0_source,child1_source);

					return buffer;
				}

				break;
			}
			case ARRAYDECLARATION:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* child2_source = toSource(ast->child[2]);
				char* child3_source;
				char* buffer;

				if(ast->child[3] != NULL)
				{
					child3_source = toSource(ast->child[3]);

					buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1 + 1 + strlen(child3_source) + 1,sizeof(char));
					sprintf(buffer,"%s %s[%s]:%s",child0_source,child1_source,child2_source,child3_source);
				}
				else
				{
					buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1 + 1,sizeof(char));
					sprintf(buffer,"%s %s[%s]",child0_source,child1_source,child2_source);
				}

				return buffer;
				break;
			}
			case DECLARATIONLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else
				{
					char* child0_source = toSource(ast->child[0]);
					char* child1_source = toSource(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + strlen(child1_source) + 1 + 1 + 1,sizeof(char));

					if(strcmp(child0_source,"") == 0)
						sprintf(buffer,"%s;",child1_source);
					else
						sprintf(buffer,"%s\n%s;",child0_source,child1_source);

					return buffer;
				}
			}
			case FUNCTIONDEFINITION:
			{
				char* child0_source = toSource(ast->child[0]);
				char* child1_source = toSource(ast->child[1]);
				char* child2_source = toSource(ast->child[2]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1,sizeof(char));

				if(strcmp(child1_source,"") != 0)
					sprintf(buffer,"%s\n%s\n%s",child0_source,child1_source,child2_source);
				else
					sprintf(buffer,"%s\n%s",child0_source,child2_source);

				return buffer;
				break;
			}
			case PROGRAM:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else
				{
					char* child0_source = toSource(ast->child[0]);
					char* child1_source = toSource(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + 1 + strlen(child1_source) + 1,sizeof(char));

					if(ast->child[1]->node_type == DECLARATION || ast->child[1]->node_type == ARRAYDECLARATION || ast->child[1]->node_type == POINTERDECLARATION)
						sprintf(buffer,"%s%s;\n",child0_source,child1_source);
					else
						sprintf(buffer,"%s%s\n",child0_source,child1_source);

					return buffer;
				}

				break;
			}
		}
	}
}

void PrintTree(AST* ast)
{

	fprintf(stderr,"%s\n",ASTtoString(ast,0));
}

int verify(AST* ast)
{
	switch(ast->node_type)
	{
		case IDENTIFIER:
		{

		}
		case TYPEWORD:
		{

		}
		case TYPEBOOL:
		{

		}
		case TYPEBYTE:
		{

		}
		case LITERAL:
		{

		}
		case ADDITION:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != INTEGER || t1 != INTEGER)
			{
				fprintf(stderr,"Incompatible types for aritimetic operation: %s + %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return INTEGER;
			}
		}
		case SUBTRACTION:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != INTEGER || t1 != INTEGER)
			{
				fprintf(stderr,"Incompatible types for aritimetic operation: %s - %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return INTEGER;
			}
		}
		case MULTIPLICATION:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != INTEGER || t1 != INTEGER)
			{
				fprintf(stderr,"Incompatible types for aritimetic operation: %s * %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return INTEGER;
			}
		}
		case DIVISION:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != INTEGER || t1 != INTEGER)
			{
				fprintf(stderr,"Incompatible types for aritimetic operation: %s / %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return INTEGER;
			}
		}
		case LESSERTHAN:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != INTEGER || t1 != INTEGER)
			{
				fprintf(stderr,"Incompatible types for relational operation: %s < %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return BOOL;
			}
		}
		case GREATERTHAN:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != INTEGER || t1 != INTEGER)
			{
				fprintf(stderr,"Incompatible types for relational operation: %s > %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return BOOL;
			}
		}
		case LESSEREQUAL:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != INTEGER || t1 != INTEGER)
			{
				fprintf(stderr,"Incompatible types for relational operation: %s <= %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return BOOL;
			}
		}
		case GREATEREQUAL:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != INTEGER || t1 != INTEGER)
			{
				fprintf(stderr,"Incompatible types for relational operation: %s >= %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return BOOL;
			}
		}
		case EQUAL:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != t1)
			{
				fprintf(stderr,"Incompatible types for relational operation: %s == %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return BOOL;
			}
		}
		case NOTEQUAL:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != t1)
			{
				fprintf(stderr,"Incompatible types for relational operation: %s != %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return BOOL;
			}
		}
		case AND:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != BOOL || t1 != BOOL)
			{
				fprintf(stderr,"Incompatible types for boolean operation: %s && %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return BOOL;
			}
		}
		case OR:
		{
			int t0 = verify(ast->child[0]);
			int t1 = verify(ast->child[1]);

			if(t0 != BOOL || t1 != BOOL)
			{
				fprintf(stderr,"Incompatible types for boolean operation: %s || %s\n", t0, t1);
				exit(3);
			}
			else
			{
				return BOOL;
			}
		}
		case REF:
		{

		}
		case DEREF:
		{

		}
		case FUNCTIONCALL:
		{

		}
		case ARRAYACCESS:
		{

		}
		case ARGUMENTLIST:
		{

		}
		case RETURN:
		{

		}
		case ELEMENTLIST:
		{

		}
		case OUTPUT:
		{

		}
		case INPUT:
		{

		}
		case IFTHEN:
		{

		}
		case IFTHENELSE:
		{

		}
		case LOOP:
		{

		}
		case ASSIGNMENT:
		{

		}
		case COMMANDLIST:
		{

		}
		case BLOCK:
		{

		}
		case PARAMETERLIST:
		{

		}
		case FUNCTIONHEADER:
		{

		}
		case DECLARATION:
		{

		}
		case POINTERDECLARATION:
		{

		}
		case LITERALLIST:
		{

		}
		case ARRAYDECLARATION:
		{

		}
		case DECLARATIONLIST:
		{

		}
		case FUNCTIONDEFINITION:
		{

		}
		case PROGRAM:
		{

		}
	}
}

