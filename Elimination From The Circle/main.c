#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <malloc.h>
#include <crtdbg.h>
#include <assert.h>
int getnum()
{
	float N = 0;
	while (scanf_s("%f", &N) != 1 || (N - (int)N != 0) || (N == 0) || N < 0 || N >= 100000 || getchar() != '\n')
	{
		while (getchar() != '\n') {
			;
		}
		printf("\tPlease input positive int number that is less than 100000\n");
	}
	return N;
}

int main()
{
	int N, K;
	printf("Enter the number of participants:\n");
	N = getnum();
	int* people = (int*)malloc(N * sizeof(double));
	if (people == NULL)
	{
		printf("Cannot allocate memory\n");
		return 1;
	}
	for (int i = 1; i <= N; i++)
	{
		people[i] = 1;
	}
	int amount = N, temp = 0;
	printf("Every <K> participant will leave\n");
	printf("Input K = ");
	K = getnum();
	while (K > N)
	{
		printf("Incorrect input try again\n");
		K = getnum();
	}
	while (amount > 1)
	{
		int temp_amount = 0;
		for (int i = temp + 1; i <= N + 1 ; i++)
		{
			if (i >= amount + (N - amount + 1))
			{
				i = 0;
				temp = 0;
			}
			if (people[i] == 1)
			{
				temp_amount++;
				temp = i;
				if (temp_amount == K)
				{
					people[temp] = 0;
					printf("Number %d is gone\n", temp);
					amount--;
					temp_amount = 0;
					if (amount == 1)
					{
						break;
					}
					
				}
			}
		}
	}
	for (int i = 1; i <= N; i++)
	{
		if (people[i] == 1)
		{
			printf("And the winner is number %d\n", i);
			break;
		}
	}
	free(people);
	_CrtDumpMemoryLeaks();
	return 0;
}
