#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

hashTable_ref symbolTable;

// Symbol module

void printSymbol(symbol_ref symbol)
{
	printf("%s", symbol);
}

// LinkedList module

linkedList_t* nil(void)
{
	linkedList_t* list = (linkedList_t*) malloc( sizeof(linkedList_t) );

	list->head = NULL;
	list->tail = NULL;

	return list;
}

int isEmpty(linkedList_t list)
{
	return list.head == NULL;
}

linkedList_t* cons(symbol_ref symbol, linkedList_t* list)
{
	if(list == NULL)
	{
		return NULL;
	}
	else
	{
		linkedList_t* newList = (linkedList_t*) malloc( sizeof(linkedList_t) );

		newList->head = (symbol_ref) malloc( strlen(symbol) );
		strcpy(newList->head, symbol);

		newList->tail = list;

		return newList;
	}
}

symbol_ref find(symbol_ref symbol, linkedList_t list)
{
	linkedList_t* aux = &list;

	while( !isEmpty(*aux) )
	{
		if(strcmp(aux->head, symbol) == 0)
		{
			return aux->head;
		}
		else
		{
			aux = aux->tail;
		}
	}

	return NULL;
}

void printList(linkedList_t list)
{
	linkedList_t* aux = &list;

	while( !isEmpty(*aux) )
	{
		printSymbol(aux->head);
		printf(" :: ");
		
		aux = aux->tail;
	}

	printf("[]");
}

// HashTable module

int hashFunction(symbol_ref symbol, int tableSize)
{
	int index = 1;
	int i;

	for(i = 0; i < strlen(symbol); i++)
	{
		index = ( (index * symbol[i]) % tableSize ) + 1;
	}	

	return index - 1;
}

hashTable_ref newHashTable(int size)
{
	hashTable_ref table = (hashTable_ref) calloc(size, sizeof(linkedList_t*));
	int i;

	for(i = 0; i < size; i++)
	{
		table[i] = nil();
	}

	return table;
}

symbol_ref addToTable(symbol_ref symbol, hashTable_ref table, int tableSize)
{
	int index = hashFunction(symbol, tableSize);

	symbol_ref pointer = find(symbol, *(table[index]));

	if(pointer != NULL)
	{
		return pointer;
	}
	else
	{
		table[index] = cons(symbol, table[index]);

		return table[index]->head;
	}
}

symbol_ref findInTable(symbol_ref symbol, hashTable_ref table, int tableSize)
{
	int index = hashFunction(symbol, tableSize);

	symbol_ref pointer = find(symbol, *(table[index]));

	return pointer;
}

void printTable(hashTable_ref table, int tableSize)
{
	int i;

	printf("{\n");

	for(i = 0; i < tableSize; i++)
	{
		printf("\t");
		printList( *(table[i]) );
		printf("\n");
	}

	printf("}");
}

// SymbolTable module

void initMe(void)
{
	symbolTable = newHashTable(SYMBOL_TABLE_SIZE);
}

symbol_ref addSymbol(symbol_ref symbol)
{
	return addToTable(symbol, symbolTable, SYMBOL_TABLE_SIZE);
}

symbol_ref findSymbol(symbol_ref symbol)
{
	return findInTable(symbol, symbolTable, SYMBOL_TABLE_SIZE);
}

void printSymbolTable(void)
{
	printTable(symbolTable, SYMBOL_TABLE_SIZE);
}

/*
int main()
{
	linkedList_t list = *cons("4", cons("1", cons("7", nil())));
	printList(list);
	printf("\n");
	hashTable_ref table = newHashTable(10);
	printSymbol(addToTable("666", table, 10));
	printf("\n");
	printSymbol(addToTable("42", table, 10));
	printf("\n");
	printSymbol(addToTable("1984", table, 10));
	printf("\n");
	printSymbol(addToTable("666", table, 10));
	printf("\n");

	printTable(table, 10);

	initMe();
	
	addSymbol("the");
	addSymbol("quick");
	addSymbol("brown");
	addSymbol("fox");
	addSymbol("jumps");
	addSymbol("over");
	addSymbol("the");
	addSymbol("lazy");
	addSymbol("dog");

	printSymbolTable();
	printf("\n");
}
*/
