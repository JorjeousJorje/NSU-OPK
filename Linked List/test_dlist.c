#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "dlist.h"

Pointer give_head(Dlist* list)
{
	if (list->head == NULL)
	{
		return NULL;
	}
	else
	{
		return list->head->data;
	}
}
int int_cmp(Pointer a, Pointer b)
{
	if (*(int*)a > *(int*)b)
	{
		return 0;
	}
}
int double_cmp(Pointer a, Pointer b)
{
	if (*(double*)a > * (double*)b)
	{
		return 0;
	}
}
void func_foreach_int(Pointer data, Pointer user_data)
{
	*(int*)data = (*(int*)data) * (*(int*)user_data);
}
void func_foreach_double(Pointer data, Pointer user_data)
{
	*(double*)data = (*(double*)data) * (*(double*)user_data);
}

int main()
{
	Dlist dl, dll, list1;
	dlist_create(&dl);
	//test 1 - empty list;
	int a = 4;
	assert(dlist_find(&dl, &a) == NULL);
	assert(dlist_nth(&dl, 2345) == NULL);
	assert(dlist_last(&dl) == NULL);
	assert(dlist_size(&dl) == 0);
	assert(dlist_remove(&dl, &a) == NULL);
	dlist_delete(&dl);
	//test 2 - prepend 
	dlist_create(&dl);
	int arr[100];
	for (size_t i = 0; i < 100; i++)
	{
		arr[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(int*)dlist_prepend(&dl, &arr[i]) == arr[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(int*)dlist_last(&dl) == arr[0]);
	}

	dlist_delete(&dl);
	//test 3 append
	dlist_create(&dl);
	int arr1[100];
	for (size_t i = 0; i < 100; i++)
	{
		arr1[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(int*)dlist_append(&dl, &arr[i]) == arr[i]);
		assert(*(int*)dlist_last(&dl) == arr[i]);
		assert(*(int*)give_head(&dl) == arr1[0]);
		assert(dlist_size(&dl) == i + 1);
	}
	dlist_delete(&dl);
	//test 4 N-th element, find by data, insert element
	dlist_create(&dl);
	int arr2[10000];
	for (size_t i = 0; i < 10000; i++)
	{
		arr2[i] = i;
	}
	for (size_t i = 0; i < 10000; i++)
	{
		assert(*(int*)dlist_prepend(&dl, &arr2[i]) == arr2[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(int*)dlist_last(&dl) == arr2[0]);
	}
	//N-th element tests
	assert(*(int*)dlist_nth(&dl, 0) == 9999);
	assert(*(int*)dlist_nth(&dl, -1) == 0);
	assert(*(int*)dlist_nth(&dl, -10) == 9);
	assert(dlist_nth(&dl, 34959509) == NULL);
	//find by data tests
	assert(*(int*)dlist_find(&dl, &arr2[0]) == 0);
	assert(*(int*)dlist_find(&dl, &arr2[7]) == 7);
	assert(*(int*)dlist_find(&dl, &arr2[4356]) == 4356);
	int f = 5454545;
	assert(dlist_find(&dl, &f) == NULL);
	//insert elem after pointer tests
	int arr3[100];
	int q = 552;
	dlist_insert(dl.head, &q);
	assert(dlist_size(&dl) == 10001);
	assert(*(int*)dlist_nth(&dl, 0) == 9999);
	assert(*(int*)dlist_nth(&dl, 1) == 552);
	assert(*(int*)dlist_nth(&dl, 2) == 9998);
	assert(*(int*)dlist_nth(&dl, 10000) == 0);
	for (size_t i = 0; i < 100; i++)
	{
		arr3[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		size_t j = 2;
		dlist_insert(dl.head->next, &arr3[i]);
		assert(*(int*)dlist_nth(&dl, j) == arr3[i]);
		j++;
	}
	assert(dlist_size(&dl) == 10101);
	assert(*(int*)dlist_nth(&dl, 0) == 9999);
	assert(*(int*)dlist_nth(&dl, 1) == 552);
	assert(*(int*)dlist_nth(&dl, 10100) == 0);
	//remove tests
	dlist_remove(&dl, &q);
	assert(*(int*)dlist_nth(&dl, 1) == 99);
	for (size_t i = 0; i < 100; i++)
	{
		dlist_remove(&dl, &arr3[i]);
	}
	assert(dlist_size(&dl) == 10000);
	for (size_t i = 9999, j = 0; i >= 0 && j < 1000; i--, j++)
	{
		assert(*(int*)dlist_nth(&dl, j) == i);
	}
	dlist_remove(&dl, &arr2[9999]);
	dlist_remove(&dl, &arr2[0]);
	assert(*(int*)give_head(&dl) == arr2[9998]);
	assert(*(int*)dlist_last(&dl) == arr2[1]);
	dlist_delete(&dl);
	//test 4 remove all
	dlist_create(&dl);
	int arr4[100];
	for (size_t i = 0; i < 99; i++)
	{
		arr4[i] = 1;
	}
	arr4[99] = 1818;
	for (size_t i = 0; i < 99; i++)
	{
		assert(*(int*)dlist_prepend(&dl, &arr4[0]) == arr4[0]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(int*)dlist_last(&dl) == arr4[0]);
	}
	assert(*(int*)dlist_prepend(&dl, &arr4[99]) == arr4[99]);
	assert(dlist_size(&dl) == 100);
	assert(*(int*)dlist_last(&dl) == arr4[0]);

	dlist_remove_all(&dl, &arr4[0]);
	assert(dlist_size(&dl) == 1);
	assert(*(int*)dlist_last(&dl) == 1818);
	assert(*(int*)give_head(&dl) == 1818);
	dlist_delete(&dl);
	//test 5 list copy
	//empty copy
	dlist_create(&dl);
	Dlist* copy = dlist_copy(&dl);
	assert(dlist_size(copy) == 0);
	assert(give_head(copy) == NULL);
	assert(dlist_last(copy) == NULL);
	dlist_delete(copy);
	dlist_delete(&dl);
	free(copy);
	//not empty copy
	dlist_create(&dl);
	int arr5[100];
	for (size_t i = 0; i < 100; i++)
	{
		arr5[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(int*)dlist_prepend(&dl, &arr5[i]) == arr5[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(int*)dlist_last(&dl) == arr5[0]);
	}
	assert(dlist_size(&dl) == 100);
	Dlist* copy1 = dlist_copy(&dl);
	assert(dlist_size(copy1) == dlist_size(&dl));
	assert(give_head(copy1) == give_head(&dl));
	assert(dlist_last(copy1) == dlist_last(&dl));
	assert(*(int*)give_head(copy1) == *(int*)give_head(&dl));
	assert(*(int*)dlist_last(copy1) == *(int*)dlist_last(&dl));
	for (size_t i = 0, j = 99; i < 100 && j >= 0; i++, j--)
	{
		assert(*(int*)dlist_nth(&dl, i) == j);
		assert(*(int*)dlist_nth(&dl, i) == *(int*)dlist_nth(copy1, i));
	}
	//remove copy test, but initial list must be unchanged
	for (size_t i = 0; i < 99; i++)
	{
		dlist_remove(copy1, &arr5[i]);
	}
	assert(give_head(copy1) == &arr5[99]);
	assert(dlist_last(copy1) == &arr5[99]);
	for (size_t i = 0, j = 99; i < 100 && j >= 0; i++, j--)
	{
		assert(*(int*)dlist_nth(&dl, i) == j);
	}
	dlist_delete(copy1);
	dlist_delete(&dl);
	free(copy1);

	//test 6 concat lists
	dlist_create(&dl);
	dlist_create(&dll);
	int arr7[100];
	int arr8[100];
	for (size_t i = 0; i < 100; i++)
	{
		arr7[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		arr8[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(int*)dlist_prepend(&dl, &arr7[i]) == arr7[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(int*)dlist_last(&dl) == arr7[0]);
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(int*)dlist_prepend(&dll, &arr8[i]) == arr8[i]);
		assert(dlist_size(&dll) == i + 1);
		assert(dlist_last(&dll) == &arr8[0]);
	}
	dlist_concat(&dl, &dll);
	assert(dlist_size(&dl) == 200);
	assert(dlist_last(&dl) == &arr8[0]);
	assert(give_head(&dl) == &arr7[99]);
	assert(dlist_nth(&dl, 100) == &arr8[99]);
	dlist_delete(&dl);
	//concat full and empty list
	dlist_create(&dl);
	dlist_create(&dll);
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(int*)dlist_prepend(&dl, &arr7[i]) == arr7[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(int*)dlist_last(&dl) == arr7[0]);
	}
	dlist_concat(&dl, &dll);
	assert(dlist_size(&dl) == 100);
	assert(give_head(&dl) == &arr7[99]);
	assert(dlist_last(&dl) == &arr7[0]);
	dlist_delete(&dl);
	//tets 7 find custome
	dlist_create(&dl);
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(int*)dlist_prepend(&dl, &arr7[i]) == arr7[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(int*)dlist_last(&dl) == arr7[0]);
	}
	int l = 56;
	int df = 2942030;
	assert(*(int*)dlist_find_custom(&dl, &arr7[67], int_cmp) == arr7[68]);
	assert(*(int*)dlist_find_custom(&dl, &l, int_cmp) == arr[57]);
	assert(dlist_find_custom(&dl, &df, int_cmp) == NULL);
	dlist_delete(&dl);
	//test 8 foreach
	dlist_create(&dl);
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(int*)dlist_prepend(&dl, &arr7[i]) == arr7[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(int*)dlist_last(&dl) == arr7[0]);
	}
	int gg1 = 11;
	dlist_foreach(&dl, func_foreach_int, &gg1);
	assert(*(int*)dlist_nth(&dl, 0) == 1089);
	assert(*(int*)dlist_nth(&dl, 99) == 0);
	assert(*(int*)dlist_nth(&dl, 98) == 11);
	dlist_delete(&dl);

	///DOUBLE TEST///
	dlist_create(&dl);
	//test 1 - empty list;
	double b = 4.5;
	assert(dlist_find(&dl, &b) == NULL);
	assert(dlist_nth(&dl, 2345.344566) == NULL);
	assert(dlist_last(&dl) == NULL);
	assert(dlist_size(&dl) == 0);
	assert(dlist_remove(&dl, &b) == NULL);
	dlist_delete(&dl);
	//test 2 - prepend and find position
	dlist_create(&dl);
	double arr9[100];
	for (size_t i = 0; i < 100; i++)
	{
		arr9[i] = i + 0.1;
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(double*)dlist_prepend(&dl, &arr9[i]) == arr9[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(double*)dlist_last(&dl) == arr9[0]);
	}
	dlist_delete(&dl);
	//test 3 append
	dlist_create(&dl);
	double arr91[100];
	for (size_t i = 0; i < 100; i++)
	{
		arr91[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(double*)dlist_append(&dl, &arr91[i]) == arr91[i]);
		assert(*(double*)dlist_last(&dl) == arr91[i]);
		assert(*(double*)give_head(&dl) == arr91[0]);
		assert(dlist_size(&dl) == i + 1);
	}
	dlist_delete(&dl);
	//test 4 N-th element, find by data, insert element
	dlist_create(&dl);
	double arr92[10000];
	for (size_t i = 0; i < 10000; i++)
	{
		arr92[i] = i + 0.1;
	}
	for (size_t i = 0; i < 10000; i++)
	{
		assert(*(double*)dlist_prepend(&dl, &arr92[i]) == arr92[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(double*)dlist_last(&dl) == arr92[0]);
	}
	//N-th element tests
	assert(*(double*)dlist_nth(&dl, 0) == 9999.1);
	assert(*(double*)dlist_nth(&dl, -1) == 0.1);
	assert(*(double*)dlist_nth(&dl, -10) == 9.1);
	assert(dlist_nth(&dl, 34959509) == NULL);
	//find by data tests
	assert(*(double*)dlist_find(&dl, &arr92[0]) == 0.1);
	assert(*(double*)dlist_find(&dl, &arr92[7]) == 7.1);
	assert(*(double*)dlist_find(&dl, &arr92[4356]) == 4356.1);
	double ff = 5454545;
	assert(dlist_find(&dl, &ff) == NULL);
	//insert elem after pointer tests
	double arr93[100];
	double qq = 552.1;
	dlist_insert(dl.head, &qq);
	assert(dlist_size(&dl) == 10001);
	assert(*(double*)dlist_nth(&dl, 0) == 9999.1);
	assert(*(double*)dlist_nth(&dl, 1) == 552.1);
	assert(*(double*)dlist_nth(&dl, 2) == 9998.1);
	assert(*(double*)dlist_nth(&dl, 10000) == 0.1);
	for (size_t i = 0; i < 100; i++)
	{
		arr93[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		size_t j = 2;
		dlist_insert(dl.head->next, &arr93[i]);
		assert(*(double*)dlist_nth(&dl, j) == arr93[i]);
		j++;
	}
	assert(dlist_size(&dl) == 10101);
	assert(*(double*)dlist_nth(&dl, 0) == 9999.1);
	assert(*(double*)dlist_nth(&dl, 1) == 552.1);
	assert(*(double*)dlist_nth(&dl, 10100) == 0.1);
	//remove tests
	dlist_remove(&dl, &qq);
	assert(*(double*)dlist_nth(&dl, 1) == 99);
	for (size_t i = 0; i < 100; i++)
	{
		dlist_remove(&dl, &arr93[i]);
	}
	assert(dlist_size(&dl) == 10000);
	for (size_t i = 9999, j = 0; i >= 0 && j < 1000; i--, j++)
	{
		assert(*(double*)dlist_nth(&dl, j) == i + 0.1);
	}
	dlist_remove(&dl, &arr92[9999]);
	dlist_remove(&dl, &arr92[0]);
	assert(*(double*)give_head(&dl) == arr92[9998]);
	assert(*(double*)dlist_last(&dl) == arr92[1]);
	dlist_delete(&dl);
	//test 4 remove all
	dlist_create(&dl);
	double arr94[100];
	for (size_t i = 0; i < 99; i++)
	{
		arr94[i] = 1;
	}
	arr94[99] = 1818.87;
	for (size_t i = 0; i < 99; i++)
	{
		assert(*(double*)dlist_prepend(&dl, &arr94[0]) == arr94[0]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(double*)dlist_last(&dl) == arr94[0]);
	}
	assert(*(double*)dlist_prepend(&dl, &arr94[99]) == arr94[99]);
	assert(dlist_size(&dl) == 100);
	assert(*(double*)dlist_last(&dl) == arr94[0]);

	dlist_remove_all(&dl, &arr94[0]);
	assert(dlist_size(&dl) == 1);
	assert(*(double*)dlist_last(&dl) == 1818.87);
	assert(*(double*)give_head(&dl) == 1818.87);
	dlist_delete(&dl);
	//test 5 list copy
	//empty copy
	dlist_create(&dl);
	Dlist* copy2 = dlist_copy(&dl);
	assert(dlist_size(copy2) == 0);
	assert(give_head(copy2) == NULL);
	assert(dlist_last(copy2) == NULL);
	dlist_delete(copy2);
	dlist_delete(&dl);
	free(copy2);
	//not empty copy
	dlist_create(&dl);
	double arr95[100];
	for (size_t i = 0; i < 100; i++)
	{
		arr95[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(double*)dlist_prepend(&dl, &arr95[i]) == arr95[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(double*)dlist_last(&dl) == arr95[0]);
	}
	assert(dlist_size(&dl) == 100);
	Dlist* copy12 = dlist_copy(&dl);
	assert(dlist_size(copy12) == dlist_size(&dl));
	assert(give_head(copy12) == give_head(&dl));
	assert(dlist_last(copy12) == dlist_last(&dl));
	assert(*(double*)give_head(copy12) == *(double*)give_head(&dl));
	assert(*(double*)dlist_last(copy12) == *(double*)dlist_last(&dl));
	for (size_t i = 0, j = 99; i < 100 && j >= 0; i++, j--)
	{
		assert(*(double*)dlist_nth(&dl, i) == j);
		assert(*(double*)dlist_nth(&dl, i) == *(double*)dlist_nth(copy12, i));
	}
	//remove copy test, but initial list must be unchanged
	for (size_t i = 0; i < 99; i++)
	{
		dlist_remove(copy12, &arr95[i]);
	}
	assert(give_head(copy12) == &arr95[99]);
	assert(dlist_last(copy12) == &arr95[99]);
	for (size_t i = 0, j = 99; i < 100 && j >= 0; i++, j--)
	{
		assert(*(double*)dlist_nth(&dl, i) == j);
	}
	dlist_delete(copy12);
	dlist_delete(&dl);
	free(copy12);

	//test 6 concat lists
	dlist_create(&dl);
	dlist_create(&list1);
	double arr97[100];
	double arr98[100];
	for (size_t i = 0; i < 100; i++)
	{
		arr97[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		arr98[i] = i;
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(double*)dlist_prepend(&dl, &arr97[i]) == arr97[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(double*)dlist_last(&dl) == arr97[0]);
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(double*)dlist_prepend(&list1, &arr98[i]) == arr98[i]);
		assert(dlist_size(&list1) == i + 1);
		assert(dlist_last(&list1) == &arr98[0]);
	}
	dlist_concat(&dl, &list1);
	assert(dlist_size(&dl) == 200);
	assert(dlist_last(&dl) == &arr98[0]);
	assert(give_head(&dl) == &arr97[99]);
	assert(dlist_nth(&dl, 100) == &arr98[99]);
	dlist_delete(&dl);
	//concat full and empty list
	dlist_create(&dl);
	dlist_create(&list1);
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(double*)dlist_prepend(&dl, &arr97[i]) == arr97[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(double*)dlist_last(&dl) == arr97[0]);
	}
	dlist_concat(&dl, &list1);
	assert(dlist_size(&dl) == 100);
	assert(give_head(&dl) == &arr97[99]);
	assert(dlist_last(&dl) == &arr97[0]);
	dlist_delete(&dl);
	//tets 7 find custome
	dlist_create(&dl);
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(double*)dlist_prepend(&dl, &arr97[i]) == arr97[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(double*)dlist_last(&dl) == arr97[0]);
	}
	double gg = 56;
	double huge = 24234234;
	assert(*(double*)dlist_find_custom(&dl, &arr97[67], double_cmp) == arr97[68]);
	assert(*(double*)dlist_find_custom(&dl, &gg, double_cmp) == arr97[57]);
	assert(dlist_find_custom(&dl, &huge, double_cmp) == NULL);
	dlist_delete(&dl);
	//test 8 do for each
	dlist_create(&dl);
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(double*)dlist_prepend(&dl, &arr97[i]) == arr97[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(double*)dlist_last(&dl) == arr97[0]);
	}
	double gg12 = 56;
	dlist_foreach(&dl, func_foreach_double, &gg12);
	assert(*(double*)dlist_nth(&dl, 0) == 5544);
	assert(*(double*)dlist_nth(&dl, 99) == 0);
	assert(*(double*)dlist_nth(&dl, 98) == 56);
	dlist_delete(&dl);
	////STRINGS TESTS///

	char* string = "abcde";
	dlist_create(&dl);
	//test 1 - empty list;
	assert(dlist_find(&dl, &string) == NULL);
	assert(dlist_nth(&dl, 2345) == NULL);
	assert(dlist_last(&dl) == NULL);
	assert(dlist_size(&dl) == 0);
	assert(dlist_remove(&dl, &string) == NULL);
	dlist_delete(&dl);
	//test 2 - prepend 
	dlist_create(&dl);
	char mas[100];
	for (size_t i = 0; i < 100; i++)
	{
		mas[i] = "efef";
	}
	for (size_t i = 0; i < 100; i++)
	{
		assert(*(char*)dlist_prepend(&dl, &mas[i]) == mas[i]);
		assert(dlist_size(&dl) == i + 1);
		assert(*(char*)dlist_last(&dl) == mas[0]);
	}
	//test 2 - insert an find by number
	char str = "a(*&^(*&)(){()_(_)()_(#)_#(_)$()_#($)_#($)_(#_$@_#*)(@&*%)(*_@#";
	dlist_insert(dl.head, &str);
	assert(dlist_size(&dl) == 101);
	assert(*(char*)dlist_nth(&dl, 0) == mas[0]);
	assert(*(char*)dlist_nth(&dl, 1) == str);
	assert(*(char*)dlist_nth(&dl, 99) == mas[0]);

	dlist_delete(&dl);
	assert(_CrtDumpMemoryLeaks() == 0);
	return 0;
}
