#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <crtdbg.h>
#include <memory.h>
#include "PQueue.h"

int double_cmp(Pointer data1, Pointer data2)
{
	double xx = *(double*)data1;
	double yy = *(double*)data2;
	if (xx > yy)
	{
		return 1;
	}
	if (xx < yy)
	{
		return 0;
	}
}

int main()
{
	PriorityQueue* pq = pq_create(double_cmp);
	int m = 5;
	m = m + 1;




	assert(_CrtDumpMemoryLeaks() == 0);
	return 0;
}