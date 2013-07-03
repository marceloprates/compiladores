#include <stdio.h>

int foo(int n0, int n1, int n2, int n3, int n4, int n5/*, int n6, int n7, int n8, int n9, int n10*/)
{
	printf("%d\n", n0);
	printf("%d\n", n1);
	printf("%d\n", n2);
	printf("%d\n", n3);
	printf("%d\n", n4);
	printf("%d\n", n5);

	/*int n01 = n0 + n1;
	int n23 = n2 + n3;
	int n45 = n4 + n5;

	int n0123 = n01 + n23;
	
	int n012345 = n0123 + n45*/

	int r = n0 + n1 + n2 + n3 + n4 + n5/* + n6 + n7 + n8 + n9 + n10*/;

	printf("%d\n", r);

	return r;
}

int bar()
{
	return foo(0, 1, 2, 3, 4, 5/*, 6, 7, 8, 9, 10*/);
}

int main()
{
	printf("%d\n", bar());
}
