%{
	// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "hash.h"

	char found_literals[65536];
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
		LIT_INTEGER		{ char aux[1024]; sprintf(aux,"Found integer: %d\n", $1->symbol.value.intLit); strcat(found_literals,aux);  /*fprintf(stderr,"Found integer: %d\n", $1->symbol.value.intLit); 		*/}		|
		LIT_FALSE		{ char aux[1024]; sprintf(aux,"Found false: %d\n", $1->symbol.value.boolLit); strcat(found_literals,aux);	/*fprintf(stderr,"Found false: %d\n", $1->symbol.value.boolLit); 		*/}		|
		LIT_TRUE		{ char aux[1024]; sprintf(aux,"Found true: %d\n", $1->symbol.value.boolLit); strcat(found_literals,aux);	/*fprintf(stderr,"Found true: %d\n", $1->symbol.value.boolLit); 		*/}		|
		LIT_CHAR		{ char aux[1024]; sprintf(aux,"Found char: %c\n", $1->symbol.value.charLit); strcat(found_literals,aux);	/*fprintf(stderr,"Found character: %c\n", $1->symbol.value.charLit); 	*/}
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
		TK_IDENTIFIER 			|
		TK_IDENTIFIER '[' expr ']' 	|
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
		KW_IF '(' expr ')' KW_THEN command else_block |
		KW_LOOP '(' expr ')' command
		;

	else_block:
		KW_ELSE command |
		/* empty */
		;

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

int PrintFoundLiterals()
{
	fprintf(stderr,"\n%s",found_literals);
}
