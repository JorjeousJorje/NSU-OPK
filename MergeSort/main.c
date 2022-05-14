#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>

int char_cmp(void* x, void* y)
{
	double x_value = *(char*)x;
	double y_value = *(char*)y;

	if (x_value > y_value)
	{
		return 1;
	}
	else if (x_value < y_value)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int int_cmp(void* x, void* y)
{
	double x_value = *(int*)x;
	double y_value = *(int*)y;

	if (x_value > y_value)
	{
		return 1;
	}
	else if (x_value < y_value)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int double_cmp(void* x, void* y)
{
	double x_value = *(double*)x;
	double y_value = *(double*)y;

	if (x_value > y_value)
	{
		return 1;
	}
	else if (x_value < y_value)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void copy_elem(size_t elem_size, void* old_arr, void* new_arr)
{

	for (int i = 0; i < elem_size; i++)
	{
		*((char*)new_arr + i) = *((char*)old_arr + i);
	}

}
void merge(void* arr, size_t elem_size, size_t start, size_t end, int(*cmp)(void*, void*), void* buffer)
{
	size_t left = start, mid = (start + end) / 2, right = mid + 1;

	for (size_t i = start; i <= end; i++)
	{

		if ((left <= mid) && (right > end || cmp((char*)arr + left * elem_size, (char*)arr + right * elem_size) < 0))
		{
			copy_elem(elem_size, (char*)arr + left * elem_size, (char*)buffer + i * elem_size);
			left++;

		}
		else
		{
			copy_elem(elem_size, (char*)arr + right * elem_size, (char*)buffer + i * elem_size);
			right++;

		}
	}

	for (size_t i = start; i <= end; i++)
	{
		copy_elem(elem_size, (char*)buffer + (i - start) * elem_size, (char*)arr + i * elem_size);
	}

}
void merge_sort(void* arr, size_t elem_size, size_t start, size_t end, int(*cmp)(void*, void*), void* buffer)
{
	if (start < end)
	{
		merge_sort(arr, elem_size, start, start + (end - start)/2, cmp, buffer);
		merge_sort(arr, elem_size, start + (end - start) / 2 + 1, end, cmp, buffer);
		merge(arr, elem_size, start, end, cmp, buffer);
	}
}

void mergesort(void* arr, size_t elem_size, size_t count, int(*cmp)(void*, void*))
{
	
	void* buffer = malloc(elem_size * count);
	
	if (buffer == NULL)
	{
		printf("Cannot allocate memory");
		return false;
	}
	merge_sort(arr, elem_size, 0, count - 1, cmp, buffer);

	free(buffer);
}

bool checking(void* arr, size_t elem_size, size_t count, int(*cmp)(void*, void*))
{
	if (count == 1)
	{
		return true;
	}
	if (count == 0)
	{
		return false;
	}
	clock_t start = clock();
	mergesort(arr, elem_size, count, cmp);
	clock_t end = clock();

	double time = (double)(end - start) / CLOCKS_PER_SEC;

	printf("%zd elements are sorted in %.6lf seconds\n", count, time);

	for (size_t i = 0; i < count - 1; i++)
	{
		if (cmp((char*)arr + i * elem_size, (char*)arr + (i + 1) * elem_size) > 0)
		{
			return false;
		}
	}
}

double* genrt(double* arr, size_t n)
{
	srand(time(NULL));
	for (size_t i = 0; i < n; i++)
	{
		arr[i] = rand() + 0.6;
	}
	return arr;
}
double* reversed(double* arr, size_t n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = n - i;
	}
	return arr;
}
double* halfsorted(double* arr, size_t n)
{
	for (int i = 0; i < n / 2; i++)
	{
		arr[i] = i + 0.6;
	}
	srand(time(NULL));
	for (int i = n / 2; i < n; i++)
	{
		arr[i] = rand() + 0.6;
	}
	return arr;
}
double* sortedarr(double* arr, size_t n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = i;
	}
	return arr;
}



int main()
{
	double* arr1 = (double*)malloc(100000 * sizeof(double));
	assert(checking(sortedarr(arr1, 100000), sizeof(arr1[0]), 100000, double_cmp));
	free(arr1);

	double* arr2 = (double*)malloc(100000 * sizeof(double));
	assert(checking(genrt(arr2, 100000), sizeof(arr2[0]), 100000, double_cmp));
	free(arr2);

	double* arr3 = (double*)malloc(100000 * sizeof(double));
	assert(checking(reversed(arr3, 100000), sizeof(arr3[0]), 100000, double_cmp));
	free(arr3);

	double* arr4 = (double*)malloc(100000 * sizeof(double));
	assert(checking(halfsorted(arr4, 100000), sizeof(arr4[0]), 100000, double_cmp));
	free(arr4);

	printf("\n\n\n");

	double* arr5 = (double*)malloc(1000000 * sizeof(double));
	assert(checking(sortedarr(arr5, 1000000), sizeof(arr5[0]), 1000000, double_cmp));
	free(arr5);

	double* arr6 = (double*)malloc(1000000 * sizeof(double));
	assert(checking(genrt(arr6, 1000000), sizeof(arr6[0]), 1000000, double_cmp));
	free(arr6);

	double* arr7 = (double*)malloc(1000000 * sizeof(double));
	assert(checking(reversed(arr7, 1000000), sizeof(arr7[0]), 1000000, double_cmp));
	free(arr7);

	double* arr8 = (double*)malloc(1000000 * sizeof(double));
	assert(checking(halfsorted(arr8, 1000000), sizeof(arr8[0]), 1000000, double_cmp));
	free(arr8);

	char arr9[] = { 'a', 'B', 'B', '123'};
	assert(checking(arr9, sizeof(arr9[0]), 4, char_cmp));

	double arr10[] = { 12.5, 9.354, -1, 12, 4.54, 1.222, -1.2, 5.7876, 5.7, 5 , 5};
	assert(checking(arr10, sizeof(arr10[0]), 9, double_cmp));

	double arr11[] = { 1 };
	assert(checking(arr11, sizeof(arr11[0]), 1, double_cmp));

	char arr12[] = { 'A' };
	assert(checking(arr12, sizeof(arr12[0]), 1, char_cmp));



	_CrtDumpMemoryLeaks();
	return 0;

}