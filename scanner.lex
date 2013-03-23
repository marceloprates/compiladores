
%{

	#include <stdio.h>
	#include "tokens.h"
	//#include "symbol_table.h"

	int getLineNumber();

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

[-,;:(){}*+/<>=!&$]		{ return (int)yytext[0]; 	}
"["						{ return (int)yytext[0]; 	}
"]"						{ return (int)yytext[0]; 	}	
"<="					{ return OPERATOR_LE; 		}
">="					{ return OPERATOR_GE; 		}
"=="					{ return OPERATOR_EQ; 		}
"!="					{ return OPERATOR_NE; 		}
"&&"					{ return OPERATOR_AND; 		}
"||"					{ return OPERATOR_OR; 		}

"FALSE"					{ return LIT_FALSE; 		}
"TRUE"					{ return LIT_TRUE; 			}
[0-9][0-9ABCDE]*		{ return LIT_INTEGER; 		}
['][a-zA-Z][']			{ return LIT_CHAR; 			} 	// REVER
["][a-zA-Z]*["]			{ return LIT_STRING; 		}	// REVER
 
[a-zA-Z][a-zA-Z0-9_]*	{ return TK_IDENTIFIER; 	}

" "|"	"				{ 							}
"\n"					{ line_number++; 			}
.						{ return TOKEN_ERROR; 		}

%%

int main(int argc, char** argv)
{
	if(argc < 2) // inssuficient arguments
	{
		exit(0);
	}

	char* file_path = argv[1]; 
	FILE *file = fopen(file_path,"r"); 
	int could_open = (file != NULL);

	if(!could_open)
	{
		exit(1);
	}
	else
	{		
		yyin = file;

		while(running)
		{
			token = yylex();

			printf("token: %d\n", token);

			if(!running)
				break;
		}

		printf("Your program has %d lines\n", getLineNumber());
	}
}

int yywrap()
{
	running = 0;

	return 1;
}

int getLineNumber()
{
	return line_number;
}