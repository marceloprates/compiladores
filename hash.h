// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

#ifndef HASH_H
#define HASH_H

#define SYMBOL_TABLE_SIZE 997

//#define SYMBOL_UNDEFINED 0
#define SYMBOL_LIT_INTEGER 1
//#define SYMBOL_LIT_FLOATING 2
#define SYMBOL_LIT_TRUE 3
#define SYMBOL_LIT_FALSE 4
#define SYMBOL_LIT_CHAR 5
#define SYMBOL_LIT_STRING 6
#define SYMBOL_IDENTIFIER 7

#define FALSE 0
#define TRUE 1

#include "ast.h"

/*enum dataType_e
{
	INTEGER,
	BOOL,
	INTEGER_POINTER,
	BOOL_POINTER,
	NO_TYPE,
	FUNCTION_TYPE,
};*/

enum nature_e
{
	SCALAR,
	ARRAY,
	FUNCTION
};

typedef int type_t;

//typedef enum dataType_e dataType_t;

typedef enum nature_e nature_t;

union value_s
{
	int intLit;
	char charLit;
	int boolLit;
	char* stringLit;
	char* identifier;
};

struct symbol_s
{
	union value_s value;
	char* text;
	type_t type;
	dataType_t dataType;
	nature_t nature;
	dataType_t returnType;
	int marked;
	AST* declaration;
	char* scope;
};

struct linkedList_s
{
	struct symbol_s symbol;
	struct linkedList_s* tail;
};

typedef struct symbol_s symbol_t;

typedef struct linkedList_s linkedList_t;

typedef linkedList_t** hashTable_ref;



// Symbol module

int equal(symbol_t symbol1, symbol_t symbol2);

void printSymbol(symbol_t symbol);

// Type module

void printType(type_t type);

// LinkedList module

linkedList_t* nil(void);

int isEmpty(linkedList_t* list);

linkedList_t* cons(symbol_t symbol, linkedList_t* list);

linkedList_t* find(symbol_t symbol, linkedList_t* list);

void printList(linkedList_t* list);

// HashTable module

int hashFunction(char* text, int tableSize);

hashTable_ref newHashTable(int size);

linkedList_t* addToTable(symbol_t symbol, hashTable_ref table, int tableSize);

linkedList_t* findInTable(symbol_t symbol, hashTable_ref table, int tableSize);

void printTable(hashTable_ref table, int tableSize);

// SymbolTable module

void initMe(void);

char* removeQuotes(char* s);

linkedList_t* addSymbol(char* text, type_t type);

linkedList_t* findSymbol(symbol_t symbol);

linkedList_t* search(char* text);

void printSymbolTable(void);

#endif
