#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <malloc.h>
#include <crtdbg.h>

int fib(int n)
{
	int *Fib = (int*)malloc((n+2)* sizeof(n));//память под хранение чисел с 1 по n включительно
	if (Fib == NULL)
	{
		printf("Cannot allocate memory\n");

	}
	Fib[0] = 0;
	Fib[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		Fib[i] = Fib[i - 1] + Fib[i - 2];
	}
	int a = Fib[n];
	assert(a > 0);
	free(Fib);
	return a;
}


int main()
{
	assert(0 == fib(0));
	assert(1 == fib(1));
	assert(1 == fib(2));
	assert(2 == fib(3));
	assert(2 == fib(46));
	printf("%d\n", fib(46));
	printf("%d\n", fib(0));
	printf("%d\n", fib(1));
	printf("%d\n", fib(2));
	printf("%d\n", fib(3));
	printf("%d\n", fib(5));
	printf("%d\n", fib(7));
	printf("%d\n", fib(20));
	printf("%d\n", fib(46));
	
_CrtDumpMemoryLeaks();
	return 0;
}
