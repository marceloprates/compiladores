int n = 5;
int* p = 0;

int foo()
{
	p = &n;
	n = *p;
}
