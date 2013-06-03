
%{

	// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

	#include <stdio.h>
	#include "tokens.h"
	#include "hash.h"

	int open_input(char* file_path);
	int getLineNumber(void);

	int running = 1;
	int token;

	int line_number = 1;

	#include "main.c"

%}

%x COMM

%%

"word"							{ return KW_WORD; 											}
"bool"							{ return KW_BOOL; 											}
"byte"							{ return KW_BYTE; 											}
"if"							{ return KW_IF; 											}	
"then"							{ return KW_THEN; 											}
"else"							{ return KW_ELSE; 											}
"loop"							{ return KW_LOOP; 											}
"input"							{ return KW_INPUT; 											}
"output"						{ return KW_OUTPUT; 										}
"return"						{ return KW_RETURN; 										}

"/*"							{ BEGIN(COMM);									}
"//"[^"\n"]*							{ 							}

[-,;:(){}*+/<>=!&$\]\[]			{ return (int)yytext[0]; 									}

"<="							{ return OPERATOR_LE; 										}
">="							{ return OPERATOR_GE; 										}
"=="							{ return OPERATOR_EQ; 										}
"!="							{ return OPERATOR_NE; 										}
"&&"							{ return OPERATOR_AND; 										}
"||"							{ return OPERATOR_OR; 										}

"FALSE"							{ return LIT_FALSE; 										}
"TRUE"							{ return LIT_TRUE; 											}
[0-9][0-9A-Fa-f]*				{ addSymbol(yytext, LIT_INTEGER	); return LIT_INTEGER; 		}
\'[^']\'						{ addSymbol(yytext, LIT_CHAR	); return LIT_CHAR; 		}
\"[^"]*\"						{ addSymbol(yytext, LIT_STRING	); return LIT_STRING; 		}

[a-zA-Z][a-zA-Z0-9_]*			{ addSymbol(yytext, TK_IDENTIFIER); return TK_IDENTIFIER; 	}

"\n"							{ line_number++; 						}
" "|"	"						{ 								}

.								{ return TOKEN_ERROR; 					}

<COMM>
"*/"							{ BEGIN(INITIAL);						}
<COMM>
"\n"							{ line_number++;						}	
<COMM>
. 								{ 							}

%%

int yywrap()
{
	running = 0;

	return 1;
}

int open_input(char* file_path)
{
	FILE* file = fopen(file_path,"r");
	int could_open = (file != NULL);

	if(!could_open)
	{
		return 0;
	}
	else
	{
		yyin = file;

		return 1;
	}
}

int getLineNumber()
{
	return line_number;
}
