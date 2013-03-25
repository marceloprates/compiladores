#define SYMBOL_TABLE_SIZE 992

typedef char* symbol_ref;

struct linkedList_s
{
	symbol_ref head;
	struct linkedList_s* tail;
};

typedef struct linkedList_s linkedList_t;

typedef linkedList_t** hashTable_ref;

// Symbol module

void printSymbol(symbol_ref symbol);

// LinkedList module

linkedList_t* nil(void);

int isEmpty(linkedList_t list);

linkedList_t* cons(symbol_ref symbol, linkedList_t* list);

symbol_ref find(symbol_ref symbol, linkedList_t list);

void printList(linkedList_t list);

// HashTable module

int hashFunction(symbol_ref symbol, int tableSize);

hashTable_ref newHashTable(int size);

symbol_ref addToTable(symbol_ref symbol, hashTable_ref table, int tableSize);

symbol_ref findInTable(symbol_ref symbol, hashTable_ref table, int tableSize);

void printTable(hashTable_ref table, int tableSize);

// SymbolTable module

void initMe(void);

symbol_ref addSymbol(symbol_ref symbol);

symbol_ref findSymbol(symbol_ref symbol);

void printSymbolTable(void);
