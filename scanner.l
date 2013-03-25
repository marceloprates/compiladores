
%{

	#include <stdio.h>
	#include "tokens.h"
	#include "hash.h"

	int open_input(char* file_path);
	int getLineNumber(void);

	#include "main.c"

	int running = 1;
	int line_number = 1;
	int token;

%}

%%

"word"					{ return KW_WORD; 			}
"bool"					{ return KW_BOOL; 			}
"byte"					{ return KW_BYTE; 			}
"if"					{ return KW_IF; 			}	
"then"					{ return KW_THEN; 			}
"else"					{ return KW_ELSE; 			}
"loop"					{ return KW_LOOP; 			}
"input"					{ return KW_INPUT; 			}
"output"				{ return KW_OUTPUT; 		}
"return"				{ return KW_RETURN; 		}

[-,;:(){}*+/<>=!&$]			{ return (int)yytext[0]; 	}
"["					{ return (int)yytext[0]; 	}
"]"					{ return (int)yytext[0]; 	}
	
"<="					{ return OPERATOR_LE; 		}
">="					{ return OPERATOR_GE; 		}
"=="					{ return OPERATOR_EQ; 		}
"!="					{ return OPERATOR_NE; 		}
"&&"					{ return OPERATOR_AND; 		}
"||"					{ return OPERATOR_OR; 		}

"FALSE"					{ return LIT_FALSE; 		}
"TRUE"					{ return LIT_TRUE; 			}
[0-9][0-9ABCDE]*			{ addSymbol(yytext); return LIT_INTEGER; 		}
['][^'][']				{ addSymbol(yytext); return LIT_CHAR; 			} 	// REVER
["][^"]*["]				{ addSymbol(yytext); return LIT_STRING; 		}	// REVER
 
[a-zA-Z][a-zA-Z0-9_]*			{ addSymbol(yytext); return TK_IDENTIFIER; 	}

.						{ return TOKEN_ERROR; 		}

"\n"					{ line_number++; 			}
" "|"	"				{ 							}

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
