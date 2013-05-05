%{
	// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "hash.h"
%}

%start program

%union{ linkedList_t* symbol; }

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
%token 			TK_IDENTIFIER
%token <symbol>	LIT_INTEGER
%token <symbol>	LIT_FALSE
%token <symbol>	LIT_TRUE
%token <symbol>	LIT_CHAR
%token <symbol>	LIT_STRING
%token 			TOKEN_ERROR

%left OPERATOR_AND OPERATOR_OR
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'

%nonassoc IFX
%nonassoc KW_ELSE

%%
	program:
		item program	|
		/* empty */
		;

	identifier:
		TK_IDENTIFIER	{ $$ = CreateAST0(IDENTIFIER, $1); }
		;

	item:
		global_type_dec ';' |
		fun_def
		;

	global_type_dec:
		type global_dec
		;

	global_dec:
		identifier scalar_init	|
		identifier '[' LIT_INTEGER ']' array_init |
		'$' identifier scalar_init
		;

	scalar_init:
		':' literal	{ $$ = $1; }
		;

	array_init:
		':' literal_list	{ $$ = CreateAST1(LITERALLIST, NULL, $1); }	|
		/* empty */
		;

	local_type_dec:
		type local_dec
		;

	local_dec:
		identifier scalar_init |
		'$' identifier scalar_init
		;

	type:
		KW_WORD	|
		KW_BOOL	|
		KW_BYTE
		;

	literal:
		LIT_INTEGER	{ $$ = CreateAST0(LITERAL, $1); }	|
		LIT_FALSE	{ $$ = CreateAST0(LITERAL, $1); }	|
		LIT_TRUE	{ $$ = CreateAST0(LITERAL, $1); }	|
		LIT_CHAR	{ $$ = CreateAST0(LITERAL, $1); }
		;

	literal_list:
		literal literal_list |
		/* empty */
		;

	fun_def:
		header local_type_decs block	{ $$ = CreateAST2(FUNCTIONDEFINITION, NULL, $1, $2, $3); }
		;

	local_type_decs:
		local_type_decs local_type_dec ';' |
		/* empty */
		;

	header:
		type identifier '(' type_parameter_list ')'	{ $$ = CreateAST3(FUNCTIONHEADER, NULL, $1, $2, $3); }
		;

	variable:
		identifier	|
		identifier '[' expr ']'	{ $$ = CreateAST2(ARRAYACCESS, NULL, $1, $3); }
		;

	parameter:
		variable 	|
		literal
		;	

	type_parameter_list:
		type identifier type_parameter_list_tail |
		/* empty */
		;

	type_parameter_list_tail:
		',' type identifier type_parameter_list_tail |
		/* empty */
		;

	parameter_list:
		parameter parameter_list_tail |
		/* empty */
		;

	parameter_list_tail:
		',' parameter parameter_list_tail |
		/* empty */
		;

	block:
		'{' command_list '}'	{ $$ = CreateAST1(BLOCK, NULL, $2); }
		;

	command_list:
		command ';' command_list |
		/* empty */
		;

	command:
		atr 			|
		flow_control 	|
		input 			|
		output 			|
		return 			|
		block
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
		expr
		;

	element_list:
		element element_list_tail
		;

	element_list_tail:
		',' element_list |
		/* empty */
		;

	return:
		KW_RETURN expr	{ $$ = CreateAST1(RETURN, NULL, $2); }
		;

	expr:
		variable						  		 |
		identifier '(' parameter_list ')'	{ $$ = CreateAST2(FUNCTIONCALL, NULL, $1, $3); }	 |
		literal 					  		 |
		'(' expr ')'							{ $$ = $2; }				  		 |
		expr '+' expr				 	{ $$ = CreateAST2(ADDITION, NULL, $1, $3); }						 |
		expr '-' expr				 	{ $$ = CreateAST2(SUBTRACTION, NULL, $1, $3); }						 |
		expr '*' expr				 	{ $$ = CreateAST2(MULTIPLICATION, NULL, $1, $3); }						 |
		expr '/' expr				 	{ $$ = CreateAST2(DIVISION, NULL, $1, $3); }						 |
		expr '<' expr				 	{ $$ = CreateAST2(LESSERTHAN, NULL, $1, $3); } 						 |
		expr '>' expr				 	{ $$ = CreateAST2(GREATERTHAN, NULL, $1, $3); }						 |
		expr OPERATOR_LE expr				 	{ $$ = CreateAST2(LESSEREQUAL, NULL, $1, $3); }				 |
		expr OPERATOR_GE expr				 	{ $$ = CreateAST2(GREATEREQUAL, NULL, $1, $3); }				 |
		expr OPERATOR_EQ expr				 	{ $$ = CreateAST2(EQUAL, NULL, $1, $3); }				 |
		expr OPERATOR_NE expr				 	{ $$ = CreateAST2(NOTEQUAL, NULL, $1, $3); }				 |
		expr OPERATOR_AND expr				 	{ $$ = CreateAST2(AND, NULL, $1, $3); }				 |
		expr OPERATOR_OR expr				 	{ $$ = CreateAST2(OR, NULL, $1, $3); }	|
		'&' expr %prec '*'			 		 	{ $$ = CreateAST1(REF, NULL, $2); }	|
		'*' expr %prec '*'						{ $$ = CreateAST1(DEREF, NULL, $2); }
		;

%%

yyerror(s)
char *s;
{
  fprintf(stderr, "%s in line %d\n",s,getLineNumber());

  exit(3);
}
