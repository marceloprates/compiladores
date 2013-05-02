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

%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'
%left OPERATOR_AND OPERATOR_OR

%%
	program:
		item program |
		/* empty */
		;

	item:
		global_type_dec ';' |
		fun_def
		;

	global_type_dec:
		type global_dec
		;

	global_dec:
		TK_IDENTIFIER value_init |
		'$' TK_IDENTIFIER scalar_init
		;

	value_init:
		scalar_init |
		'[' LIT_INTEGER ']' array_init
		;

	scalar_init:
		':' literal
		;

	array_init:
		':' literal_list |
		/* empty */
		;

	local_type_dec:
		type local_dec
		;

	local_dec:
		TK_IDENTIFIER scalar_init |
		'$' TK_IDENTIFIER scalar_init
		;

	type:
		KW_WORD |
		KW_BOOL |
		KW_BYTE
		;

	literal:
		LIT_INTEGER		
		LIT_FALSE		
		LIT_TRUE		
		LIT_CHAR		
		;

	literal_list:
		literal literal_list |
		/* empty */
		;

	fun_def:
		header local_type_decs block
		;

	local_type_decs:
		local_type_decs local_type_dec ';' |
		/* empty */
		;

	header:
		type TK_IDENTIFIER '(' type_parameter_list ')'
		;

	parameter:
		TK_IDENTIFIER |
		literal
		;	

	type_parameter_list:
		type TK_IDENTIFIER type_parameter_list_tail |
		/* empty */
		;

	type_parameter_list_tail:
		',' type TK_IDENTIFIER type_parameter_list_tail |
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
		'{' command_list '}'
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
		TK_IDENTIFIER ass
		;

	ass:
		'=' expr |
		'[' expr ']' '=' expr
		;

	flow_control:
		if_then |
		if_then_else |
		KW_LOOP '(' expr ')' command
		;

	if_then:
		KW_IF '(' expr ')' KW_THEN command

	if_then_else:
		KW_IF '(' expr ')' KW_THEN command KW_ELSE command
		
	input:
		KW_INPUT TK_IDENTIFIER
		;

	output:
		KW_OUTPUT element_list
		;

	element:
		LIT_STRING	{ char aux[1024]; sprintf(aux,"Found string: %s\n", $1->symbol.value.stringLit); strcat(found_literals,aux); /*fprintf(stderr,"Found string: %s\n", $1->symbol.value.stringLit);*/ }		|
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
		KW_RETURN expr
		;

	expr:
		TK_IDENTIFIER access		  		 |
		TK_IDENTIFIER '(' parameter_list ')' |
		literal 					  		 |
		'(' expr ')'				  		 |
		expr op expr 				  		 |
		'&' expr					  		 |
		'*' expr
		;

	access:
		'[' expr ']' |
		/* empty */
		;

	op:
		'+' 			|
		'-' 			|
		'*'				|
		'/'				|
		'<'				|
		'>'				|
		OPERATOR_LE  	|
		OPERATOR_GE  	|
		OPERATOR_EQ  	|
		OPERATOR_NE  	|
		OPERATOR_AND 	|
		OPERATOR_OR
		;

%%

yyerror(s)
char *s;
{
  fprintf(stderr, "%s in line %d\n",s,getLineNumber());

  exit(3);
}