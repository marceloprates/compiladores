#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash.h"
#include "y.tab.h"
#include "assembly.h"

FILE* file;

int functions_count = 0;
int argCount = 0;
int strings_count = 0;

char* lvalue(linkedList_t* node)
{
	char* string = malloc(strlen(node->symbol.text) + 6 + 1);
	sprintf(string, "%s(%%rip)", node->symbol.text);

	return string;
}

char* rvalue(linkedList_t* node)
{
	char* string;

	switch(node->symbol.type)
	{
		case SYMBOL_IDENTIFIER:
		{
			string = malloc(strlen(node->symbol.text) + 6 + 1);
			sprintf(string, "%s(%%rip)", node->symbol.text);

			break;
		}
		case SYMBOL_LIT_STRING:
		{
			string = malloc(1 + strlen(node->symbol.text) + 1);
			sprintf(string, "$%s", node->symbol.text);
			break;
		}
		case SYMBOL_LIT_CHAR:
		{
			string = (char*)calloc(1 + 1 + 1, sizeof(char));
			sprintf(string, "$%d", node->symbol.value.charLit);
			break;
		}
		case SYMBOL_LIT_FALSE:
		case SYMBOL_LIT_TRUE:
		case SYMBOL_LIT_INTEGER:
		{
			int num_digits;

			if(node->symbol.value.intLit == 0)
				num_digits = 1;
			else
				num_digits = (int)log10(abs((double)node->symbol.value.intLit));

			string = (char*)calloc(1 + 1 + num_digits + 1, sizeof(char));
			sprintf(string, "$%d", node->symbol.value.intLit);
			break;
		}
	}

	//if(node->symbol.type == SYMBOL_IDENTIFIER)
	//{
	//	string = malloc(strlen(node->symbol.text) + 6 + 1);
	//	sprintf(string, "%s(%%rip)", node->symbol.text);
	//}
	//else
	//{
	//	string = malloc(1 + strlen(node->symbol.text) + 1);
	//	sprintf(string, "$%s", node->symbol.text);
	//}

	return string;
}

void generateAssembly_move(linkedList_t* destination, linkedList_t* source)
{
	char* destinationString = lvalue(destination);
	char* sourceString = rvalue(source);

	fprintf(file,"\t\t# STARTING MOVE\n");
	fprintf(file,"\t\t\tmovl %s, %%edx\n", sourceString);
	fprintf(file,"\t\t\tmovl %%edx, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING MOVE\n\n");

	free(destinationString);
	free(sourceString);
}

void generateAssembly_add(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING ADD\n");
	fprintf(file,"\t\t\tmovl	%s, %%edx\n", source1String);
	fprintf(file,"\t\t\tmovl	%s, %%eax\n", source2String);
	fprintf(file,"\t\t\taddl %%edx, %%eax\n");
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING ADD\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_sub(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING SUB\n");
	fprintf(file,"\t\t\tmovl	%s, %%eax\n", source1String);
	fprintf(file,"\t\t\tmovl	%s, %%edx\n", source2String);
	fprintf(file,"\t\t\tsubl	%%edx, %%eax\n");
	fprintf(file,"\t\t\tmovl	%%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING SUB\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_mul(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING MUL\n");
	fprintf(file,"\t\t\tmovl	%s, %%edx\n", source1String);
	fprintf(file,"\t\t\tmovl	%s, %%eax\n", source2String);
	fprintf(file,"\t\t\timul	%%edx, %%eax\n");
	fprintf(file,"\t\t\tmovl	%%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING MUL\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_div(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING DIV\n");
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source1String);
	fprintf(file,"\t\t\tmovl %s, %%edx\n", source2String);
	fprintf(file,"\t\t\tmovl %%edx, -4(%%rbp)\n");
	fprintf(file,"\t\t\tmovl %%eax, %%edx\n");
	fprintf(file,"\t\t\tsarl $31, %%edx\n");
	fprintf(file,"\t\t\tidivl -4(%%rbp)\n");
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING DIV\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_less(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING LESS\n");
	fprintf(file,"\t\t\tmovl %s, %%edx\n", source1String);
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source2String);
	fprintf(file,"\t\t\tcmpl %%eax, %%edx\n");
	fprintf(file,"\t\t\tsetl %%al\n");
	fprintf(file,"\t\t\tmovzbl %%al, %%eax\n");
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING LESS\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_less_equal(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING LESS EQUAL\n");
	fprintf(file,"\t\t\tmovl %s, %%edx\n", source1String);
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source2String);
	fprintf(file,"\t\t\tcmpl %%eax, %%edx\n");
	fprintf(file,"\t\t\tsetle %%al\n");
	fprintf(file,"\t\t\tmovzbl %%al, %%eax\n");
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING LESS EQUAL\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_greater(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING GREATER\n");
	fprintf(file,"\t\t\tmovl %s, %%edx\n", source1String);
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source2String);
	fprintf(file,"\t\t\tcmpl %%eax, %%edx\n");
	fprintf(file,"\t\t\tsetg %%al\n");
	fprintf(file,"\t\t\tmovzbl %%al, %%eax\n");
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING GREATER\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_greater_equal(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING GREATER EQUAL\n");
	fprintf(file,"\t\t\tmovl %s, %%edx\n", source1String);
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source2String);
	fprintf(file,"\t\t\tcmpl %%eax, %%edx\n");
	fprintf(file,"\t\t\tsetge %%al\n");
	fprintf(file,"\t\t\tmovzbl %%al, %%eax\n");
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING GREATER EQUAL\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_equal(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING EQUAL\n");
	fprintf(file,"\t\t\tmovl %s, %%edx\n", source1String);
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source2String);
	fprintf(file,"\t\t\tcmpl %%eax, %%edx\n");
	fprintf(file,"\t\t\tsete %%al\n");
	fprintf(file,"\t\t\tmovzbl %%al, %%eax\n");
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING EQUAL\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_not_equal(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING NOT EQUAL\n");
	fprintf(file,"\t\t\tmovl %s, %%edx\n", source1String);
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source2String);
	fprintf(file,"\t\t\tcmpl %%eax, %%edx\n");
	fprintf(file,"\t\t\tsetne %%al\n");
	fprintf(file,"\t\t\tmovzbl %%al, %%eax\n");
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING NOT EQUAL\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_and(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING AND\n");
	fprintf(file,"\t\t\tmovl %s, %%edx\n", source1String);
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source2String);
	fprintf(file,"\t\t\tandl %%edx, %%eax\n");
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING AND\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_or(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING OR\n");
	fprintf(file,"\t\t\tmovl %s, %%edx\n", source1String);
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source2String);
	fprintf(file,"\t\t\torl %%edx, %%eax\n");
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING OR\n\n");

	free(destinationString);
	free(source1String);
	free(source2String);
}

void generateAssembly_ifz(linkedList_t* destination, linkedList_t* source)
{
	char* sourceString = rvalue(source);

	fprintf(file,"\t\t# STARTING IFZ\n");
	fprintf(file,"\t\t\tmovl %s, %%eax\n", sourceString);
	fprintf(file,"\t\t\ttestl %%eax, %%eax\n");
	fprintf(file,"\t\t\tje %s\n", destination->symbol.text);
	fprintf(file,"\t\t# ENDING IFZ\n\n");

	free(sourceString);
}

void generateAssembly_arrayAssign(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* source1String = rvalue(source1);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING ARRAYASSIGN\n");
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source1String);
	fprintf(file,"\t\t\tmovl %s, %%edx\n", source2String);
	fprintf(file,"\t\t\tcltq\n");
	fprintf(file,"\t\t\tmovl %%edx, %s(,%%rax,4)\n", destination->symbol.text);
	fprintf(file,"\t\t# ENDING ARRAYASSIGN\n\n");

	free(source1String);
	free(source2String);
}

void generateAssembly_arrayAccess(linkedList_t* destination, linkedList_t* source1, linkedList_t* source2)
{
	char* destinationString = lvalue(destination);
	char* source2String = rvalue(source2);

	fprintf(file,"\t\t# STARTING ARRAYACCESS\n");
	fprintf(file,"\t\t\tmovl %s, %%eax\n", source2String);
	fprintf(file,"\t\t\tcltq\n");
	fprintf(file,"\t\t\tmovl %s(,%%rax,4), %%eax\n", source1->symbol.text);
	fprintf(file,"\t\t\tmovl %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING ARRAYACCESS\n\n");

	free(destinationString);
	free(source2String);
}

void generateAssembly_ref(linkedList_t* destination, linkedList_t* source)
{
	char* destinationString = lvalue(destination);

	fprintf(file,"\t\t# STARTING REF\n");
	fprintf(file,"\t\t\tmovq $%s, %s\n", source->symbol.text, destinationString);
	fprintf(file,"\t\t# ENDING REF\n\n");

	free(destinationString);
}

void generateAssembly_deref(linkedList_t* destination, linkedList_t* source)
{
	char* destinationString = lvalue(destination);
	char* sourceString = rvalue(source);

	fprintf(file,"\t\t# STARTING DEREF\n");
	fprintf(file,"\t\t\tmovq %s, %%rax\n", sourceString);
	fprintf(file,"\t\t\tmovq (%%rax), %%eax\n");
	fprintf(file,"\t\t\tmovq %%eax, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING DEREF\n\n");

	free(sourceString);
	free(destinationString);
}

void generateAssembly_label(linkedList_t* destination)
{

	fprintf(file,"\t\t\t%s:\n", destination->symbol.text);
}

void generateAssembly_jump(linkedList_t* destination)
{
	fprintf(file,"\t\t# STARTING JUMP\n");
	fprintf(file,"\t\t\tjmp %s\n", destination->symbol.text);
	fprintf(file,"\t\t# ENDING JUMP\n\n");
}

void generateAssembly_ret(linkedList_t* source)
{
	char* sourceString = rvalue(source);

	fprintf(file,"\t\t# STARTING RET\n");
	fprintf(file,"\t\t\tmovl	%s, %%eax\n", sourceString);
	fprintf(file,"\t\t\tpopq	%%rbp\n");
	fprintf(file,"\t\t\t.cfi_def_cfa 7, 8\n");
	fprintf(file,"\t\t\tret\n");
	fprintf(file,"\t\t\t.cfi_endproc\n");
	fprintf(file,"\t\t# ENDING RET\n\n");

	free(sourceString);
}

void generateAssembly_begin_fun(linkedList_t* node)
{
	fprintf(file,"\t.globl	%s\n", node->symbol.text);
	fprintf(file,"\t.type	%s, @function\n", node->symbol.text);

	fprintf(file,"\t%s:\n", node->symbol.text);
	fprintf(file,"\t.LFB%d:\n", functions_count);
	fprintf(file,"\t\t.cfi_startproc\n");
	fprintf(file,"\t\tpushq	%%rbp\n");
	fprintf(file,"\t\t.cfi_def_cfa_offset 16\n");
	fprintf(file,"\t\t.cfi_offset 6, -16\n");
	fprintf(file,"\t\tmovq	%%rsp, %%rbp\n");
	fprintf(file,"\t\t.cfi_def_cfa_register 6\n\n");
}

void generateAssembly_end_fun(linkedList_t* node)
{
	fprintf(file,"\t.LFE%d:\n", functions_count);
	fprintf(file,"\t\t.size	%s, .-%s\n\n", node->symbol.text, node->symbol.text);

	functions_count++;
}

void generateAssembly_call(linkedList_t* node, linkedList_t* destination)
{
	fprintf(file,"\t\t# STARTING CALL\n");
	fprintf(file,"\t\t\tsubq	$%d, %%rsp\n", argCount * 8);
	fprintf(file,"\t\t\tcall	%s\n", node->symbol.text);
	fprintf(file,"\t\t\tmovl	%%eax, %s\n", destination->symbol.text);
	fprintf(file,"\t\t# ENDING CALL\n\n");
}

void generateAssembly_arg(linkedList_t* source)
{
	char* sourceString = rvalue(source);

	fprintf(file,"\t\t# STARTING ARG\n");
	fprintf(file,"\t\t\tmovl %s, %%edx\n", sourceString);
	fprintf(file,"\t\t\tmovl %%edx, %d(%%rsp)\n", argCount * 8);
	fprintf(file,"\t\t# ENDING ARG\n\n");

	free(sourceString);
}

void generateAssembly_getarg(linkedList_t* destination)
{
	char* destinationString = lvalue(destination);

	fprintf(file,"\t\t# STARTING GET_ARG\n");
	fprintf(file,"\t\t\tmovl	%d(%%rsp), %%edx\n", argCount * 8);
	fprintf(file,"\t\t\tmovl	%%edx, %s\n", destinationString);
	fprintf(file,"\t\t# ENDING GET_ARG\n\n");

	free(destinationString);
}

int value(symbol_t symbol)
{
	switch(symbol.type)
	{
		case SYMBOL_LIT_FALSE:
		case SYMBOL_LIT_TRUE: return symbol.value.boolLit; break;
		case SYMBOL_LIT_INTEGER: return symbol.value.intLit; break;
		case SYMBOL_LIT_CHAR: return symbol.value.charLit; break;
	}
}

void generate_data_section(hashTable_ref symbol_table)
{
	int i;
	linkedList_t* aux;

	fprintf(file,"\t.LC%d:\n", strings_count);
	fprintf(file, "\t\t.string %c%%s %c\n", 34, 34);
	strings_count++;

	fprintf(file,"\t.LC%d:\n", strings_count);
	fprintf(file, "\t\t.string %c%%d %c\n", 34, 34);
	strings_count++;

	fprintf(file,"\t.LC%d:\n", strings_count);
	fprintf(file, "\t\t.string %c%%c %c\n", 34, 34);
	strings_count++;

	fprintf(file,"\t.LC%d:\n",strings_count);
	fprintf(file,"\t\t.string %c%c%c%c\n",34,92,110,34);
	strings_count++;

	fprintf(file, "\n");

	for(i = 0; i < SYMBOL_TABLE_SIZE; i++)
	{
		aux = symbol_table[i];

		while( !isEmpty( aux ) )
		{
			switch(aux->symbol.type)
			{
				case SYMBOL_IDENTIFIER:
				{
					switch(aux->symbol.nature)
					{
						case SCALAR:
						{
							fprintf(file,"\t.globl %s\n", aux->symbol.text);
							fprintf(file,"\t.data\n");
							fprintf(file,"\t.align 4\n");
							fprintf(file,"\t.type %s, @object\n", aux->symbol.text);
							fprintf(file,"\t.size %s, 4\n", aux->symbol.text);
							fprintf(file,"\t%s:\n", aux->symbol.text);
							fprintf(file,"\t\t.long %d\n", aux->symbol.initial_value.intLit);
							fprintf(file,"\n");
	
							break;
						}
						case ARRAY:
						{
							int size = aux->symbol.size;

							fprintf(file,"\t.comm	array,%d\n",size*4);

							//fprintf(file,"\t.globl %s\n", aux->symbol.text);
							//fprintf(file,"\t.data\n");
							//fprintf(file,"\t.align 4\n");
							//fprintf(file,"\t.type %s, @object\n", aux->symbol.text);
							//fprintf(file,"\t.size %s, %d\n", aux->symbol.text, 4 * aux->symbol.size);
							//fprintf(file,"\t%s:\n", aux->symbol.text);
							//fprintf(file,"\n");
	
							break;
						}
					}

					break;
				}
				case SYMBOL_LIT_STRING:
				{
					fprintf(file,"\t.LC%d:\n", strings_count);
					fprintf(file, "\t\t.string %c%s%c\n\n", 34, aux->symbol.value.stringLit, 34);

					aux->symbol.strings_count = strings_count;

					strings_count++;

					break;
				}
				
			}

			aux = aux->tail;
		}
	}

	fprintf(file,"\n");
}

void generateAssembly_output_arg(linkedList_t* source)
{
	switch(source->symbol.type)
	{
		case SYMBOL_LIT_STRING:
		{
			fprintf(file, "\t\t# STARTING OUTPUT ARG\n");
			fprintf(file, "\t\t\tmovl	$.LC%d, %%esi\n", source->symbol.strings_count);
			fprintf(file, "\t\t\tmovl	$.LC0, %%edi\n");
			fprintf(file, "\t\t\tmovl	$0, %%eax\n");
			fprintf(file, "\t\t\tcall	printf\n");
			fprintf(file, "\t\t# ENDING OUTPUT ARG\n\n");

			break;
		}
		case SYMBOL_LIT_INTEGER:
		{
			fprintf(file, "\t\t# STARTING OUTPUT ARG\n");
			fprintf(file, "\t\t\tmovl	$%d, %%esi\n", source->symbol.value.intLit);
			fprintf(file, "\t\t\tmovl	$.LC1, %%edi\n");
			fprintf(file, "\t\t\tmovl	$0, %%eax\n");
			fprintf(file, "\t\t\tcall	printf\n");
			fprintf(file, "\t\t# ENDING OUTPUT ARG\n\n");

			break;
		}
		case SYMBOL_LIT_CHAR:
		{
			fprintf(file, "\t\t# STARTING OUTPUT ARG\n");
			fprintf(file, "\t\t\tmovl	$%d, %%esi\n", source->symbol.value.charLit);
			fprintf(file, "\t\t\tmovl	$.LC2, %%edi\n");
			fprintf(file, "\t\t\tmovl	$0, %%eax\n");
			fprintf(file, "\t\t\tcall	printf\n");
			fprintf(file, "\t\t# ENDING OUTPUT ARG\n\n");

			break;
		}
		case SYMBOL_IDENTIFIER:
		{
			char* s = rvalue(source);

			fprintf(file, "\t\t# STARTING OUTPUT ARG\n");
			fprintf(file, "\t\t\tmovl	%s, %%esi\n", s);
			fprintf(file, "\t\t\tmovl	$.LC1, %%edi\n");
			fprintf(file, "\t\t\tmovl	$0, %%eax\n");
			fprintf(file, "\t\t\tcall	printf\n");
			fprintf(file, "\t\t# ENDING OUTPUT ARG\n\n");

			break;
		}
	}
}

void generateAssembly_print()
{
	fprintf(file, "\t\t\tmovl	$.LC3, %%edi\n");
	fprintf(file, "\t\t\tmovl	$0, %%eax\n");
	fprintf(file, "\t\t\tcall	printf\n");
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
		case TAC_ENDFUN:		generateAssembly_end_fun(tac->destination); argCount = 0; break;
		case TAC_IFZ: 			generateAssembly_ifz(tac->destination, tac->source1); break;
		case TAC_JUMP: 			generateAssembly_jump(tac->destination); break;
		case TAC_CALL:			generateAssembly_call(tac->source1, tac->destination); argCount = 0; break;
		case TAC_ARG: 			generateAssembly_arg(tac->source1); argCount++; break;
		case TAC_OUTPUT_ARG: 	generateAssembly_output_arg(tac->source1); break;
		case TAC_RET: 			generateAssembly_ret(tac->source1); break;
		case TAC_PRINT: 		generateAssembly_print(); break;
		case TAC_READ: 			break;//TODO
		case TAC_GET_ARG: 		generateAssembly_getarg(tac->destination); argCount++; break;
		//case TAC_DECL: 			generateAssembly_decl(tac->destination, tac->source1); break;//generateAssembly_decl(tac->destination, tac->source1); break;
		//case TAC_ARRAY_DECL: 	generateAssembly_arrayDecl(tac->destination, tac->source1); break;
		//case TAC_ELEM_DECL: 	generateAssembly_elemDecl(tac->source1); break;
	}
}

void generateAssembly(TAC* tacs, const char* filename)
{
	TAC* aux;
	file = fopen(filename, "w");

	fprintf(file,"# DATA SECTION\n\n");

	generate_data_section(symbolTable);

	fprintf(file,"# CODE SECTION:\n\n");

	for(aux = tacs; aux != NULL; aux = aux->next)
	{
		generateAssemblyOf(aux);
	}
}
