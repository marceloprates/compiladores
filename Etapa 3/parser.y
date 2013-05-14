%{
	// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "hash.h"
	#include "ast.h"

	AST* root;
%}

%start S

%union{ linkedList_t* symbol; AST* ast; }

%token 			KW_WORD
%token 			KW_BOOL
%token 			KW_BYTE
%token 			KW_IF
%token 			KW_THEN
%token 			KW_ELSE
%token 			KW_LOOP
%token 			KW_INPUT
%token 			KW_RETURN
%token 			KW_OUTPUT
%token 			OPERATOR_LE
%token 			OPERATOR_GE
%token 			OPERATOR_EQ
%token 			OPERATOR_NE
%token 			OPERATOR_AND
%token 			OPERATOR_OR
%token <symbol>	TK_IDENTIFIER
%token <symbol>	LIT_INTEGER
%token <symbol>	LIT_FALSE
%token <symbol>	LIT_TRUE
%token <symbol>	LIT_CHAR
%token <symbol>	LIT_STRING
%token 			TOKEN_ERROR

%type <ast> program
%type <ast> identifier
%type <ast> item
%type <ast> global_dec
%type <ast> scalar_init
%type <ast> array_init
%type <ast> local_dec
%type <ast> type
%type <ast> literal
%type <ast> literal_list
%type <ast> fun_def
%type <ast> local_type_decs
%type <ast> header
%type <ast> variable
%type <ast> parameter_list
%type <ast> nonempty_parameter_list
%type <ast> argument_list
%type <ast> nonempty_argument_list
%type <ast> block
%type <ast> command_list
%type <ast> command
%type <ast> atr
%type <ast> flow_control
%type <ast> input
%type <ast> output
%type <ast> element
%type <ast> element_list
%type <ast> nonempty_element_list
%type <ast> return
%type <ast> expr

%left OPERATOR_AND OPERATOR_OR
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'

%nonassoc IFX
%nonassoc KW_ELSE

%%
	S: program { root = $1; }
	;

	program:
		program item { $$ = CreateAST2(PROGRAM, NULL, $1, $2); } |
		/* empty */ { $$ = CreateAST0(PROGRAM, NULL); }
		;

	identifier:
		TK_IDENTIFIER	{ $$ = CreateAST0(IDENTIFIER, $1); }
		;

	item:
		global_dec ';' |
		fun_def
		;

	global_dec:
		local_dec	|
		type identifier '[' LIT_INTEGER ']' array_init	{ $$ = CreateAST4(ARRAYDECLARATION, NULL, $1, $2, CreateAST0(LITERAL, $4), $6); }
		;

	scalar_init:
		':' literal	{ $$ = $2; }
		;

	array_init:
		':' literal_list	{ $$ = CreateAST1(LITERALLIST, NULL, $2); }	|
		/* empty */			{ $$ = NULL; }
		;

	local_dec:
		type identifier scalar_init		{ $$ = CreateAST3(DECLARATION, NULL, $1, $2, $3); }			|
		type '$' identifier scalar_init	{ $$ = CreateAST3(POINTERDECLARATION, NULL, $1, $3, $4); }
		;

	type:
		KW_WORD	{ $$ = CreateAST0(TYPEWORD, NULL); }	|
		KW_BOOL	{ $$ = CreateAST0(TYPEBOOL, NULL); }	|
		KW_BYTE	{ $$ = CreateAST0(TYPEBYTE, NULL); }
		;

	literal:
		LIT_INTEGER	{ $$ = CreateAST0(LITERAL, $1); }	|
		LIT_FALSE	{ $$ = CreateAST0(LITERAL, $1); }	|
		LIT_TRUE	{ $$ = CreateAST0(LITERAL, $1); }	|
		LIT_CHAR	{ $$ = CreateAST0(LITERAL, $1); }
		;

	literal_list:
		literal_list literal { $$ = CreateAST2(LITERALLIST, NULL, $1, $2); } |
		/* empty */ 		 { $$ = CreateAST0(LITERALLIST, NULL); }
		;

	fun_def:
		header local_type_decs block	{ $$ = CreateAST3(FUNCTIONDEFINITION, NULL, $1, $2, $3); }
		;

	local_type_decs:
		local_type_decs local_dec ';' { $$ = CreateAST2(DECLARATIONLIST, NULL, $1, $2); } |
		/* empty */ { $$ = CreateAST0(DECLARATIONLIST, NULL); }
		;

	header:
		type identifier '(' parameter_list ')'	{ $$ = CreateAST3(FUNCTIONHEADER, NULL, $1, $2, $4); }
		;

	variable:
		identifier	|
		identifier '[' expr ']'	{ $$ = CreateAST2(ARRAYACCESS, NULL, $1, $3); }
		;

	parameter_list:
		nonempty_parameter_list |
		/* empty */ { $$ = CreateAST0(PARAMETERLIST, NULL); }
		;

	nonempty_parameter_list:
		nonempty_parameter_list ',' type identifier { $$ = CreateAST3(PARAMETERLIST, NULL, $1, $3, $4); } |
		type identifier { $$ = CreateAST2(PARAMETERLIST, NULL, $1, $2); }
		;

	argument_list:
		nonempty_argument_list |
		/* empty */ { $$ = CreateAST0(ARGUMENTLIST, NULL); }
		;

	nonempty_argument_list:
		nonempty_argument_list ',' expr { $$ = CreateAST2(ARGUMENTLIST, NULL, $1, $3); } |
		expr { $$ = CreateAST1(ARGUMENTLIST, NULL, $1); }
		;

	block:
		'{' command_list '}'	{ $$ = CreateAST1(BLOCK, NULL, $2); }
		;

	command_list:
		command_list command ';' { $$ = CreateAST2(COMMANDLIST, NULL, $1, $2); } |
		/* empty */ { $$ = CreateAST0(COMMANDLIST, NULL); }
		;

	command:
		atr 			|
		flow_control 	|
		input 			|
		output 			|
		return 			|
		block			|
		/* empty */		{ $$ = NULL; }
		;

	atr:
		variable '=' expr	{ $$ = CreateAST2(ASSIGNMENT, NULL, $1, $3); }
		;

	flow_control:
		KW_IF '(' expr ')' KW_THEN command %prec IFX		{ $$ = CreateAST2(IFTHEN, NULL, $3, $6); } |
		KW_IF '(' expr ')' KW_THEN command KW_ELSE command	{ $$ = CreateAST3(IFTHENELSE, NULL, $3, $6, $8); } |
		KW_LOOP '(' expr ')' command						{ $$ = CreateAST2(LOOP, NULL, $3, $5); }
		;
		
	input:
		KW_INPUT identifier	{ $$ = CreateAST1(INPUT, NULL, $2); }
		;

	output:
		KW_OUTPUT element_list	{ $$ = CreateAST1(OUTPUT, NULL, $2); }
		;

	element:
		LIT_STRING	{ $$ = CreateAST0(LITERAL, $1); }		|
		expr { $$ = $1; }
		;

	element_list:
		nonempty_element_list |
		/* empty */ { $$ = CreateAST0(ELEMENTLIST, NULL); }
		;

	nonempty_element_list:
		nonempty_element_list ',' element { $$ = CreateAST2(ELEMENTLIST, NULL, $1, $3); } |
		element { $$ = CreateAST1(ELEMENTLIST, NULL, $1); }
		;

	return:
		KW_RETURN expr	{ $$ = CreateAST1(RETURN, NULL, $2); }
		;

	expr:
		variable						  		 													|
		identifier '(' argument_list ')'		{ $$ = CreateAST2(FUNCTIONCALL, NULL, $1, $3); }	|
		literal 					  		 														|
		'(' expr ')'							{ $$ = $2; }				  		 				|
		expr '+' expr				 			{ $$ = CreateAST2(ADDITION, NULL, $1, $3); }		|
		expr '-' expr				 			{ $$ = CreateAST2(SUBTRACTION, NULL, $1, $3); }		|
		expr '*' expr				 			{ $$ = CreateAST2(MULTIPLICATION, NULL, $1, $3); }	|
		expr '/' expr				 			{ $$ = CreateAST2(DIVISION, NULL, $1, $3); }		|
		expr '<' expr				 			{ $$ = CreateAST2(LESSERTHAN, NULL, $1, $3); } 		|
		expr '>' expr				 			{ $$ = CreateAST2(GREATERTHAN, NULL, $1, $3); }		|
		expr OPERATOR_LE expr				 	{ $$ = CreateAST2(LESSEREQUAL, NULL, $1, $3); }		|
		expr OPERATOR_GE expr				 	{ $$ = CreateAST2(GREATEREQUAL, NULL, $1, $3); }	|
		expr OPERATOR_EQ expr				 	{ $$ = CreateAST2(EQUAL, NULL, $1, $3); }			|
		expr OPERATOR_NE expr				 	{ $$ = CreateAST2(NOTEQUAL, NULL, $1, $3); }		|
		expr OPERATOR_AND expr				 	{ $$ = CreateAST2(AND, NULL, $1, $3); }				|
		expr OPERATOR_OR expr				 	{ $$ = CreateAST2(OR, NULL, $1, $3); }				|
		'&' expr %prec '*'			 		 	{ $$ = CreateAST1(REF, NULL, $2); }					|
		'*' expr %prec '*'						{ $$ = CreateAST1(DEREF, NULL, $2); }
		;

%%

yyerror(s)
char *s;
{
  fprintf(stderr, "%s in line %d\n",s,getLineNumber());

  exit(3);
}
