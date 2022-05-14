#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

void sort(int* parr, size_t size)
{

	int optmz = 0;
	for (int i = 1; i < size; i++)
	{
		optmz = 0;
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
void genrt(int* arr, size_t n) 
{
	srand(time(NULL));
	for (size_t i = 0; i < n; i++)
	{
		arr[i] = rand();
	}
}
int cheking(int* parr, size_t size)
{
	for (size_t i = 0; i < size; i++) 
	{
		if (parr[i - 1] > parr[i]) 
		{
			return 0;
		}
	}
	return 1;
}
int main()
{
	int arr1[] = { 9, 2, 10000, 1, 22, 2, -999, -400000, 45 };
	sort(arr1, 0);
	assert(cheking(arr1, 0) == 1);

	int arr2[] = { 10, -99999, 100000, 0, 100000 };
	sort(arr2, 5);
	assert(cheking(arr2, 5) == 1);

	int arr3[] = { -1 };
	sort(arr3, 1);
	assert(cheking(arr3, 1) == 1);
	
	int arr4[] = { 0 };
	sort(arr4, 1);
	assert(cheking(arr4, 1) == 1);

	int arr5[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1 };
	sort(arr5, 22);
	assert(cheking(arr5, 20) == 1);

	int arr6[] = { 300, 295, 68, 213, -777, -7, 864, -978, 57222, 1048, -5643, 16654, 2, 2345, 1212 };
	sort(arr6, 15);
	assert(cheking(arr6, 11) == 1);

	int arr7[] = { 7, -7 };
	sort(arr7, 2);
	assert(cheking(arr7, 2) == 1);

	int arr8[430];
	genrt(arr8, 430);
	sort(arr8, 430);
	assert(cheking(arr8, 10) == 1);

	int arr9[100];
	genrt(arr9, 100);
	sort(arr9, 100);
	assert(cheking(arr9, 100) == 1);
	
	int arr10[1];
	genrt(arr10, 1);
	sort(arr10, 1);
	assert(cheking(arr10, 1) == 1);

	return 0;
}


