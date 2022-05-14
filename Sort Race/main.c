#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <crtdbg.h>

void bubble(int* parr, size_t size)
{

	for (int i = 1; i < size; i++)
	{
		int optmz = 0;
		for (int j = 1; j < size - (i - 1); j++)
		{
			if (parr[j - 1] > parr[j])
			{
				optmz = 1;
				int t = parr[j - 1];
				parr[j - 1] = parr[j];
				parr[j] = t;
			}
		}
		if (optmz == 0)
		{
			break;
		}
	}
}
void select(int* parr, size_t size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
	for (int j = i + 1; j < size; j++)
	{
		if (parr[j] < parr[min])
		{
			min = j;
		}
	}
	int t = parr[i];
	parr[i] = parr[min];
	parr[min] = t;
	}

}
void coctail(int* parr, size_t size)
{
	for (int i = 1; i < size; i++)
	{
		int optz = 0;
		for (int j = 1; j < size - (i - 1); j++)
		{
			if (parr[j - 1] > parr[j])
			{
				optz = 1;
				int t = parr[j - 1];
				parr[j - 1] = parr[j];
				parr[j] = t;
	
			}
		}
		for (int j = size - i - 1; j > size - j; j--)
		{
			if (parr[j - 1] > parr[j])
			{
				int t = parr[j];
				parr[j] = parr[j - 1];
				parr[j - 1] = t;
			}
		}
		if (optz == 0)
		{
			break;
		}
	}
}
void insert(int* parr, size_t size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0 && (parr[j - 1] > parr[j]); j--)
		{
			int t = parr[j - 1];
			parr[j - 1] = parr[j];
			parr[j] = t;
		}
	}

}

int* genrt(int* arr, size_t n)
{
	srand(time(NULL));
	for (size_t i = 0; i < n; i++)
	{
		arr[i] = rand();
	}
	return arr;
}
bool checking(int* parr, size_t size)
{
	for (size_t i = 0; i < size -1; i++)
	{
		if (parr[i] > parr[i+1])
		{
			return false;
		}
	}
	return true;
}
int* reverse(int* arr, size_t n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = n - i;
	}
	return arr;
}
int* halfsorted(int* arr, size_t n)
{
	for (int i = 0; i < n / 2; i++)
	{
		arr[i] = i + 1;
	}
	srand(time(NULL));
	for (int i = n / 2; i < n; i++)
	{
		arr[i] = rand();
	}
}
int* sortedarr(int* arr, size_t n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = i;
	}

}

void timing(int* arr, size_t size, void sort(int*,size_t), char* nameofsort)
{
	clock_t start = clock();
	sort(arr, size);
	assert(checking(arr, size) == true);
	clock_t end = clock();

	double time = (double)(end - start) / CLOCKS_PER_SEC;

	printf("%s: %zd elements are sorted in %.6lf seconds\n", nameofsort, size, time);
}
int get_elem()
{
	float N = 0;
	printf("Enter number of elements\n");
	while (scanf_s("%f", &N) != 1 || (N - (int)N != 0) || (N == 0) || N < 0 || getchar() != '\n')
	{
		while (getchar() != '\n') 
		{
			printf("\tPlease input positive int number\n");
		}
	}
	return N;
}

int main()
{
	int N;
	N = get_elem();
	printf("There are random arrays\n");
	int* arr = (int*)malloc(N * sizeof(int));
	if (arr == NULL)
	{
		printf("Cannot allocate memory\n");
		return 0;

	}
	arr = genrt(arr, N);
	timing(arr, N, select, "Select Sort");
	arr = genrt(arr, N);
	timing(arr, N, bubble, "Bubble Sort");
	arr = genrt(arr, N);
	timing(arr, N, coctail, "Coctail Srt");
	arr = genrt(arr, N);
	timing(arr, N, insert, "Insert Sort");
	free(arr);
	printf("\n\n\nThere are reversed arrays\n");
	int* mas = (int*)malloc(N * sizeof(int));
	if (mas == NULL)
	{
		printf("Cannot allocate memory\n");
		return 0;

	}
	reverse(mas, N);
	timing(mas, N, select, "Select Sort");
	reverse(mas, N);
	timing(mas, N, bubble, "Bubble Sort");
	reverse(mas, N);
	reverse(mas, N);
	timing(mas, N, coctail, "Coctail Srt");
	reverse(mas, N);
	timing(mas, N, insert, "Insert Sort");
	free(mas);
	printf("\n\n\nThere are halfsorted(first half) arrays\n");
	int* rrr = (int*)malloc(N * sizeof(int));
	if (rrr == NULL)
	{
		printf("Cannot allocate memory\n");
		return 0;

	}
	halfsorted(rrr, N);
	timing(rrr, N, select, "Select Sort");
	halfsorted(rrr, N);
	timing(rrr, N, bubble, "Bubble Sort");
	halfsorted(rrr, N);
	timing(rrr, N, coctail, "Coctail Srt");
	halfsorted(rrr, N);
	timing(rrr, N, insert, "Insert Sort");
	free(rrr);
	printf("\n\n\nThere are sorted arrays\n");
	int* sorted = (int*)malloc(N * sizeof(int));
	if (sorted == NULL)
	{
		printf("Cannot allocate memory\n");
		return 0;

	}
	sortedarr(sorted, N);
	timing(sorted, N, select, "Select Sort");
	sortedarr(sorted, N);
	timing(sorted, N, bubble, "Bubble Sort");
	sortedarr(sorted, N);
	timing(sorted, N, coctail, "Coctail Srt");
	sortedarr(sorted, N);
	timing(sorted, N, insert, "Insert Sort");
	free(sorted);

	_CrtDumpMemoryLeaks();
	return 0;
}