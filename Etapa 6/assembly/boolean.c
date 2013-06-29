int x = 6;
int y = 9;

int p = 0;
int q = 1;

int t = 0;

void foo()
{
	t = x > y;
	t = x < y;
	t = x >= y;
	t = x <= y;
	t = x == y;
	t = x != y;

	t = p & q;
	t = p | q;
}
