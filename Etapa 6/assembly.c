#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "y.tab.h"
#include "assembly.h"

FILE* file;

int functions_count = 0;

char* lvalue(linkedList_t* node)
{
	char* string = malloc(strlen(node->symbol.text) + 6 + 1);
	sprintf(string, "%s(%%rip)", node->symbol.text);

	return string;
}

char* rvalue(linkedList_t* node)
{
	char* string;

	if(node->symbol.type == SYMBOL_IDENTIFIER)
	{
		string = malloc(strlen(node->symbol.text) + 6 + 1);
		sprintf(string, "%s(%%rip)", node->symbol.text);
	}
	else
	{
		string = malloc(1 + strlen(node->symbol.text) + 1);
		sprintf(string, "$%s", node->symbol.text);
	}

	return string;
}

void generateAssembly_move(linkedList_t* destination, linkedList_t* source)
{
	char* destinationString = lvalue(destination);
	char* sourceString = rvalue(source);

	fprintf(file, "; STARTING MOVE\n");
	fprintf(file, "\tmovl %s, %s\n", sourceString, destinationString);
	fprintf(file, "; ENDING MOVE\n\n");

	free(destinationString);
	free(sourceString);
}

void generateAssembly_add(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING ADD\n");
	fprintf(file, "\tmovl %s, %s\n", source2String, destinationString);
	fprintf(file, "\taddl %s, %s\n", source1String, destinationString);
	fprintf(file, "; ENDING ADD\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_sub(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING SUB\n");
	fprintf(file, "\tmovl %s, %s\n", source1String, destinationString);
	fprintf(file, "\tsubl %s, %s\n", source2String, destinationString);
	fprintf(file, "; ENDING SUB\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_mul(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING MUL\n");
	fprintf(file, "\tmovl %s, %s\n", source2String, destinationString);
	fprintf(file, "\timull %s, %s\n", source1String, destinationString);
	fprintf(file, "; ENDING MUL\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_div(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING DIV\n");
	fprintf(file, "\tmovl %s, %%eax\n", source1String);
	fprintf(file, "\tmovl %s, %%edx\n", source2String);
	fprintf(file, "\tmovl %%edx, -4(%%rbp)\n");
	fprintf(file, "\tmovl %%eax, %%edx\n");
	fprintf(file, "\tsarl $31, %%edx\n");
	fprintf(file, "\tidivl -4(%%rbp)\n");
	fprintf(file, "\tmovl %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING DIV\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_less(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING LESS\n");
	fprintf(file, "\tmovl %s, %%edx\n", source1String);
	fprintf(file, "\tmovl %s, %%eax\n", source2String);
	fprintf(file, "\tcmpl %%eax, %%edx\n");
	fprintf(file, "\tsetl %%al\n");
	fprintf(file, "\tmovzbl %%al, %%eax\n");
	fprintf(file, "\tmovl %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING LESS\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_less_equal(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING LESS EQUAL\n");
	fprintf(file, "\tmovl %s, %%edx\n", source1String);
	fprintf(file, "\tmovl %s, %%eax\n", source2String);
	fprintf(file, "\tcmpl %%eax, %%edx\n");
	fprintf(file, "\tsetle %%al\n");
	fprintf(file, "\tmovzbl %%al, %%eax\n");
	fprintf(file, "\tmovl %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING LESS EQUAL\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_greater(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING GREATER\n");
	fprintf(file, "\tmovl %s, %%edx\n", source1String);
	fprintf(file, "\tmovl %s, %%eax\n", source2String);
	fprintf(file, "\tcmpl %%eax, %%edx\n");
	fprintf(file, "\tsetg %%al\n");
	fprintf(file, "\tmovzbl %%al, %%eax\n");
	fprintf(file, "\tmovl %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING GREATER\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_greater_equal(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING GREATER EQUAL\n");
	fprintf(file, "\tmovl %s, %%edx\n", source1String);
	fprintf(file, "\tmovl %s, %%eax\n", source2String);
	fprintf(file, "\tcmpl %%eax, %%edx\n");
	fprintf(file, "\tsetge %%al\n");
	fprintf(file, "\tmovzbl %%al, %%eax\n");
	fprintf(file, "\tmovl %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING GREATER EQUAL\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_equal(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING EQUAL\n");
	fprintf(file, "\tmovl %s, %%edx\n", source1String);
	fprintf(file, "\tmovl %s, %%eax\n", source2String);
	fprintf(file, "\tcmpl %%eax, %%edx\n");
	fprintf(file, "\tsete %%al\n");
	fprintf(file, "\tmovzbl %%al, %%eax\n");
	fprintf(file, "\tmovl %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING EQUAL\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_not_equal(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING NOT EQUAL\n");
	fprintf(file, "\tmovl %s, %%edx\n", source1String);
	fprintf(file, "\tmovl %s, %%eax\n", source2String);
	fprintf(file, "\tcmpl %%eax, %%edx\n");
	fprintf(file, "\tsetne %%al\n");
	fprintf(file, "\tmovzbl %%al, %%eax\n");
	fprintf(file, "\tmovl %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING NOT EQUAL\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_and(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING AND\n");
	fprintf(file, "\tmovl %s, %%edx\n", source1String);
	fprintf(file, "\tmovl %s, %%eax\n", source2String);
	fprintf(file, "\tandl %%edx, %%eax\n");
	fprintf(file, "\tmovl %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING AND\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_or(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING OR\n");
	fprintf(file, "\tmovl %s, %%edx\n", source1String);
	fprintf(file, "\tmovl %s, %%eax\n", source2String);
	fprintf(file, "\torl %%edx, %%eax\n");
	fprintf(file, "\tmovl %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING OR\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_ifz(linkedList_t* destination, linkedList_t* source)
{
	char* sourceString = rvalue(source);

	fprintf(file, "; STARTING IFZ\n");
	fprintf(file, "\tmovl %s, %%eax\n", sourceString);
	fprintf(file, "\ttestl %%eax, %%eax\n");
	fprintf(file, "\tje %s\n", destination->symbol.text);
	fprintf(file, "; ENDING IFZ\n\n");

	free(sourceString);
}

void generateAssembly_arrayAssign(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING ARRAYASSIGN\n");
	fprintf(file, "\tmovl %s, %%eax\n", source1String);
	fprintf(file, "\tmovl %s, %%edx\n", source2String);
	fprintf(file, "\tcltq\n");
	fprintf(file, "\tmovl %%edx, %s(,%%rax,4)\n", destination->symbol.text);
	fprintf(file, "; ENDING ARRAYASSIGN\n\n");

	free(source1String);
	free(source2String);
}

void generateAssembly_arrayAccess(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source2String = rvalue(source2);

	fprintf(file, "; STARTING ARRAYACCESS\n");
	fprintf(file, "\tmovl %s, %%eax\n", source2String);
	fprintf(file, "\tcltq\n");
	fprintf(file, "\tmovl %s(,%%rax,4), %%eax\n", source1->symbol.text);
	fprintf(file, "\tmovl %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING ARRAYACCESS\n\n");

	free(destinationString);
	free(source2String);
}

void generateAssembly_ref(linkedList_t* destination, linkedList_t* source)
{
	char* destinationString = lvalue(destination);

	fprintf(file, "; STARTING REF\n");
	fprintf(file, "\tmovq $%s, %s\n", source->symbol.text, destinationString);
	fprintf(file, "; ENDING REF\n\n");

	free(destinationString);
}

void generateAssembly_deref(linkedList_t* destination, linkedList_t* source)
{
	char* destinationString = lvalue(destination);
	char* sourceString = rvalue(source);

	fprintf(file, "; STARTING DEREF\n");
	fprintf(file, "\tmovq %s, %%rax\n", sourceString);
	fprintf(file, "\tmovq (%%rax), %%eax\n");
	fprintf(file, "\tmovq %%eax, %s\n", destinationString);
	fprintf(file, "; ENDING DEREF\n\n");

	free(sourceString);
	free(destinationString);
}

void generateAssembly_label(linkedList_t* destination)
{
	fprintf(file, "\t%s:\n", destination->symbol.text);
}

void generateAssembly_jump(linkedList_t* destination)
{
	fprintf(file, "; STARTING JUMP\n");
	fprintf(file, "\tjmp %s\n", destination->symbol.text);
	fprintf(file, "; ENDING JUMP\n\n");
}

void generateAssembly_ret(linkedList_t* source)
{
	char* sourceString = rvalue(source);

	fprintf(file, "; STARTING RET\n");
	fprintf(file, "\tmovl %s, %%eax\n", sourceString);
	fprintf(file, "; popq %%rbp\n");
	fprintf(file, "; .cfi_def_cfa 7, 8\n");
	fprintf(file, "; ret\n");
	fprintf(file, "; .cfi_endproc\n");
	fprintf(file, "; ENDING RET\n\n");

	free(sourceString);
}

void generateAssembly_begin_fun(linkedList_t* node)
{
	fprintf(file, "\t.globl	%s\n", node->symbol.text);
	fprintf(file, "\t.type	%s, @function\n", node->symbol.text);

	fprintf(file, "%s:\n", node->symbol.text);
	fprintf(file, ".LFB%d:\n", functions_count);
	fprintf(file, "\t.cfi_startproc\n");
	fprintf(file, "\tpushq	%%rbp\n");
	fprintf(file, "\t.cfi_def_cfa_offset 16\n");
	fprintf(file, "\t.cfi_offset 6, -16\n");
	fprintf(file, "\tmovq	%%rsp, %%rbp");
	fprintf(file, "\t.cfi_def_cfa_register 6\n");
}

void generateAssembly_end_fun(linkedList_t* node)
{
	fprintf(file, ".LFE%d:\n", functions_count);
	fprintf(file, "\t.size	%s, .-%s\n", node->symbol.text, node->symbol.text);

	functions_count++;
}

void generateAssembly_call(linkedList_t* node, linkedList_t* destination)
{
	fprintf(file, "; STARTING CALL\n");
	fprintf(file, "\tcall	%s\n", node->symbol.text);
	fprintf(file, "\tmovl	%%eax, %s\n", destination->symbol.text);
	fprintf(file, "; ENDING CALL\n\n");
}

int value(symbol_t symbol)
{
	switch(symbol.type)
	{
		case LIT_FALSE:
		case LIT_TRUE: return symbol.value.boolLit; break;
		case LIT_INTEGER: return symbol.value.intLit; break;
		case LIT_CHAR: return symbol.value.charLit; break;
	}
}

void generateAssembly_decl(linkedList_t* destination, linkedList_t* source)
{
	fprintf(file, "; STARTING DECL\n");
	fprintf(file, "\t.globl %s\n", destination->symbol.text);
	fprintf(file, "\t.data\n");
	fprintf(file, "\t.align 4\n");
	fprintf(file, "\t.type %s, @object\n", destination->symbol.text);
	fprintf(file, "\t.size %s, 4\n", destination->symbol.text);
	fprintf(file, "%s:\n", destination->symbol.text);
	fprintf(file, "\t.long %d\n", value(source->symbol));
	fprintf(file, "; ENDING DECL\n");
}

void generateAssembly_arrayDecl(linkedList_t* id, linkedList_t* size)
{
	fprintf(file, "; STARTING ARRAY_DECL\n");
	fprintf(file, "\t.globl %s\n", id->symbol.text);
	fprintf(file, "\t.data\n");
	fprintf(file, "\t.align 4\n");
	fprintf(file, "\t.type %s, @object\n", id->symbol.text);
	fprintf(file, "\t.size %s, %d\n", id->symbol.text, 4 * size->symbol.value.intLit);
	fprintf(file, "%s:\n", id->symbol.text);
	fprintf(file, "; ENDING ARRAY_DECL\n");
}

void generateAssembly_elemDecl(linkedList_t* source)
{
	fprintf(file, "; STARTING ELEM_DECL\n");
	fprintf(file, "\t.long %d\n", value(source->symbol));
	fprintf(file, "; ENDING ELEM_DECL\n");
}

void generateAssemblyOf(TAC* tac)
{
	switch(tac->tac_type)
	{
		case TAC_SYMBOL: break;
		case TAC_MOVE: 			generateAssembly_move(tac->destination, tac->source1); break;
		case TAC_MOVE_I: break;//TODO
		case TAC_ARRAYACCESS: 	generateAssembly_arrayAccess(tac->destination, tac->source1, tac->source2); break;
		case TAC_ARRAYASSIGN: 	generateAssembly_arrayAssign(tac->destination, tac->source1, tac->source2); break;
		case TAC_ADD: 			generateAssembly_add(tac->destination, tac->source1, tac->source2); break;
		case TAC_SUB: 			generateAssembly_sub(tac->destination, tac->source1, tac->source2); break;
		case TAC_MUL: 			generateAssembly_mul(tac->destination, tac->source1, tac->source2); break;
		case TAC_DIV: 			generateAssembly_div(tac->destination, tac->source1, tac->source2); break;
		case TAC_LESS: 			generateAssembly_less(tac->destination, tac->source1, tac->source2); break;
		case TAC_LESS_EQUAL: 	generateAssembly_less_equal(tac->destination, tac->source1, tac->source2); break;
		case TAC_GREATER: 		generateAssembly_greater(tac->destination, tac->source1, tac->source2); break;
		case TAC_GREATER_EQUAL: generateAssembly_greater_equal(tac->destination, tac->source1, tac->source2); break;
		case TAC_EQUAL: 		generateAssembly_equal(tac->destination, tac->source1, tac->source2); break;
		case TAC_NOT_EQUAL: 	generateAssembly_not_equal(tac->destination, tac->source1, tac->source2); break;
		case TAC_AND: 			generateAssembly_and(tac->destination, tac->source1, tac->source2); break;
		case TAC_OR: 			generateAssembly_or(tac->destination, tac->source1, tac->source2); break;
		case TAC_REF: 			generateAssembly_ref(tac->destination, tac->source1); break;
		case TAC_DEREF: 		generateAssembly_deref(tac->destination, tac->source1); break;
		case TAC_LABEL: 		generateAssembly_label(tac->destination); break;
		case TAC_BEGINFUN:		generateAssembly_begin_fun(tac->destination); break;
		case TAC_ENDFUN:		generateAssembly_end_fun(tac->destination); break;
		case TAC_IFZ: 			generateAssembly_ifz(tac->destination, tac->source1); break;
		case TAC_JUMP: 			generateAssembly_jump(tac->destination); break;
		case TAC_CALL:			generateAssembly_call(tac->source1, tac->destination); break;
		case TAC_ARG: break;//TODO
		case TAC_OUTPUT_ARG: break;//TODO
		case TAC_RET: 			generateAssembly_ret(tac->source1); break;
		case TAC_PRINT: break;//TODO
		case TAC_READ: break;//TODO
		case TAC_GET_ARG: break;//TODO
		case TAC_DECL: generateAssembly_decl(tac->destination, tac->source1); break;
		case TAC_ARRAY_DECL: generateAssembly_arrayDecl(tac->destination, tac->source1); break;
		case TAC_ELEM_DECL: generateAssembly_elemDecl(tac->source1); break;
	}
}

void generateAssembly(TAC* tacs, const char* filename)
{
	TAC* aux;
	file = fopen(filename, "w");

	for(aux = tacs; aux != NULL; aux = aux->next)
	{
		generateAssemblyOf(aux);
	}
}
