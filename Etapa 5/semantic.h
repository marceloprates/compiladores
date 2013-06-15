
#include "hash.h"
#include "ast.h"

#define FALSE 0
#define TRUE 1

void first_pass(AST* ast);
int local_declarations(AST* fun_def);
int compatible(dataType_t t0, dataType_t t1);
int same_types(AST* parameter, AST* argument);
int check_parameters(AST* parameters, AST* arguments, int* expected, int* given);
int typecheck(AST* ast);
int verify(AST* ast);
void typeToString(int type, char* str);
void initSemanticAnalyzer();