%{

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <yy.lex.c>	
%}

%union{int ivar, char cvar, char* svar}

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
%token <ivar>	LIT_INTEGER
%token <ivar>	LIT_FALSE
%token <ivar>	LIT_TRUE
%token <cvar>	LIT_CHAR
%token <svar>	LIT_STRING
%token 			TOKEN_ERROR

%%

	program:
		item program |
		/* empty */
		;

	item:
		global_dec ';' |
		fun_def
		;

	global_dec:
		unary_dec |
		array_dec
		;

	local_dec:
		unary_dec
		;

	type:
		KW_WORD |
		KW_BOOL |
		KW_BYTE
		;

	literal:
		LIT_INTEGER |
		LIT_FALSE 	|
		LIT_TRUE 	|
		LIT_CHAR
		;

	unary_dec:
		type 	 TK_IDENTIFIER ':' literal ';' |
		type '$' TK_IDENTIFIER ':' literal ';'
		;

	array_dec:
		type TK_IDENTIFIER '[' ']' ':' literal_list
		;

	literal_list:
		literal literal_list_tail
		;

	literal_list_tail:
		literal_list_tail ' ' literal_list |
		/* empty */
		;

	fun_def:
		header local_dec block
		;

	header:
		type TK_IDENTIFIER '(' parameter_list ')'
		;

	parameter_list:
		type TK_IDENTIFIER parameter_list_tail
		;

	parameter_list_tail:
		parameter_list_tail ',' parameter_list |
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
		TK_IDENTIFIER '=' expr
		TK_IDENTIFIER '[' expr ']' '=' expr
		;

	flow_control:
		KW_IF '(' expr ')' KW_THEN command |
		KW_IF '(' expr ')' KW_THEN command KW_ELSE command |
		KW_LOOP '(' expr ')' command
		;

	input:
		KW_INPUT TK_IDENTIFIER
		;

	output:
		KW_OUTPUT element_list
		;

	element:
		LIT_STRING |
		expr
		;

	element_list:
		element element_list_tail
		;

	element_list_tail:
		element_list_tail ',' element_list |
		/* empty */
		;

	return:
		KW_RETURN expr
		;

	expr:
		TK_IDENTIFIER 				|
		TK_IDENTIFIER '[' expr ']' 	|
		literal 					|
		'(' expr ')'				|
		expr op expr 				|
		'&' expr					|
		'*' expr
		;

	op:
		'+' 			|
		'-' 			|
		'*'				|
		'/'				|
		OPERATOR_LE  	|
		OPERATOR_GE  	|
		OPERATOR_EQ  	|
		OPERATOR_NE  	|
		OPERATOR_AND 	|
		OPERATOR_OR
		;

%%

int main(int argc, char** argv)
{

}