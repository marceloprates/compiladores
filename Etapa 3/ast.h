// Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates

struct AST_struct
{
	char* node_type;
	int value;

	int numChildren;
	struct AST_struct** child;
};

typedef struct AST_struct AST;

void CreateNode(AST* ast, char* node_type, int value, AST* child_0, AST* child_1, AST* child_2, AST* child_3);
int HasAssociatedValue(char* node_type);
char* toString(AST* ast);