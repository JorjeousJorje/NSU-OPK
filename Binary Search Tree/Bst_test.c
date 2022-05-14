#include "Bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct tEntry 
{
	Pointer key;
	Pointer value;
} Entry;

int int_cmp(Pointer a, Pointer b) 
{
	int a1 = *(int*)a;
	int b1 = *(int*)b;

	if (a1 > b1)
	{
		return 1;
	}
	else if (a1 < b1)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int double_cmp(Pointer a, Pointer b)
{
	double a1 = *(double*)a;
	double b1 = *(double*)b;

	if (a1 > b1)
	{
		return 1;
	}
	else if (a1 < b1)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
void int_mult(Pointer a, Pointer b) 
{
	*(int*)a *= *(int*)b;
}
void double_mult(Pointer a, Pointer b) 
{
	*(double*)a *= *(double*)b;
}

int Entry_cmp(Entry* a, Entry* b)
{
	return strcmp(*(char**)a->key, *(char**)b->key);
}
void int_Entry_print_Tree(Node* node, int level) 
{
	if (node) 
	{
		int_Entry_print_Tree(node->right, level + 1);
		for (int i = 0; i < level; i++)
			printf("    ");
		Node* x = (Node*)node->data;
		printf("%d\n", *(int*)x);
		int_Entry_print_Tree(node->left, level + 1);
	}
}
void double_Entry_print_Tree(Node* node, int level)
{
	if (node)
	{
		double_Entry_print_Tree(node->right, level + 1);
		for (int i = 0; i < level; i++)
		{
			printf("    ");
		}
		Node* x = (Node*)node->data;
		printf("%g\n", *(double*)x);
		double_Entry_print_Tree(node->left, level + 1);
	}
}
void Entry_print_Tree(Node* node, int level) 
{
	if (node)
	{
		Entry_print_Tree(node->right, level + 1);
		for (int i = 0; i < level; i++)
		{
			printf("         ");
		}
		Entry* x = (Entry*)node->data;
		printf("%s %d\n", *(char**)x->key, *(int*)x->value);
		Entry_print_Tree(node->left, level + 1);
	}
}

void print_int(Pointer data, Pointer user_data) {
	printf("%d\n", *(int*)data);
}

int main() 
{
	////  INT TESTS  ////
	Bst* int_tree = Bst_create(&int_cmp);

	int arr[] = { 242, 9934, 33, 7, 4251, 6, 71, 8, 9099, 21, 10000, 900000};
	int equal_arr[] = { 242, 9934, 33, 7, 4251, 6, 71, 8, 9099, 21, 10000, 900000};
	int s = 9934;
	// INSERT test.
	for (int k = 0; k < 12; k++)
	{
		assert(Bst_insert(int_tree, &arr[k]) == NULL);
	}
	Bst_foreach(int_tree, print_int, NULL);
	printf("Print int_tree:\n\n\n");
	int_Entry_print_Tree(int_tree->root, 0);
	//Вставка существующего
	assert(Bst_insert(int_tree, &s) == &arr[1]);
	assert(Bst_insert(int_tree, &arr[1]) == &s);

	//SIZE test.
	assert(Bst_size(int_tree) == 12);

	//FIND test.
	for (int k = 0; k < 10; k++)
	{
		assert(Bst_find(int_tree, &arr[k]) == &arr[k]);
	}

	//DELETE test
	for (int k = 0; k < 5; k++)
	{
		assert(Bst_delete(int_tree, &arr[k]) == &arr[k]);
	}
	printf("Print deleted_tree:\n\n\n");
	int_Entry_print_Tree(int_tree->root, 0);

	assert(Bst_size(int_tree) == 7);

	for (int k = 0; k < 5; k++)
	{
		assert(Bst_find(int_tree, &arr[k]) == NULL);
	}

	//FOREACH test.
	int c = 45;
	Bst_foreach(int_tree, &int_mult, &c);

	for (int k = 5; k < 12; k++)
	{
		assert(*(int*)Bst_find(int_tree, &arr[k]) == c * equal_arr[k]);
	}
	printf("Print foreach_tree:\n\n\n");
	int_Entry_print_Tree(int_tree->root, 0);

	Bst_clear(int_tree);
	assert(int_tree->root == NULL);
	Bst_destroy(int_tree);

	////  DOUBLE TEST  ////
	printf("DOUBLE TEST\n\n\n");
	Bst* double_tree = Bst_create(&double_cmp);
	double arr1[] = { 5.7, 0.566, 346, 4, 1.4, 667, 7, 8888, 9.78, 2999 };
	double equal_mas1[] = { 5.7, 0.56, 346, 4, 1.4, 667, 7, 8888, 9.78, 2999 };

	//INSERT test.
	for (int k = 0; k < 10; k++)
	{
		assert(Bst_insert(double_tree, &arr1[k]) == NULL);
	}
	//SIZE test.
	printf("Print double_tree:\n\n\n");
	double_Entry_print_Tree(double_tree->root, 0);
	assert(Bst_size(double_tree) == 10);

	//FIND test.
	for (int k = 0; k < 10; k++)
	{
		assert(Bst_find(double_tree, &arr1[k]) == &arr1[k]);
	}

	//DELETE test.
	for (int k = 0; k < 5; k++)
	{
		assert(Bst_delete(double_tree, &arr1[k]) == &arr1[k]);
	}

	assert(Bst_size(double_tree) == 5);
	for (int k = 0; k < 5; k++)
	{
		assert(Bst_find(double_tree, &arr1[k]) == NULL);
	}

	//FOREACH test.
	double d = 2.2;
	Bst_foreach(double_tree, &double_mult, &d);
	for (int k = 5; k < 10; k++) 
	{
		assert(*(double*)Bst_find(double_tree, &arr1[k]) == d * equal_mas1[k]);
	}

	Bst_clear(double_tree);
	assert(double_tree->root == NULL);
	Bst_destroy(double_tree);

	//STRESS TEST
	Bst* big_tree = Bst_create(&int_cmp);

	int b_arr[5000];
	int	equal_b_arr[5000];

	for (int k = 0, q = 500, p = 501; k < 5000; k++, q--, p++)
	{
		if (k % 2 == 0)
		{
			equal_b_arr[k] = b_arr[k] = q;
		}
		if (k % 2 == 1)
		{
			equal_b_arr[k] = b_arr[k] = p;
		}
	}
	//INSERT test.
	for (int k = 0; k < 5000; k++)
	{
		assert(Bst_insert(big_tree, &b_arr[k]) == NULL);
	}
	
	//SIZE test.
	assert(Bst_size(big_tree) == 5000);

	//FIND test.
	for (int k = 0; k < 5000; k++)
	{
		assert(Bst_find(big_tree, &b_arr[k]) == &b_arr[k]);
	}

	//DELETE test.
	for (int k = 0; k < 500; k++)
	{
		assert(Bst_delete(big_tree, &b_arr[k]) == &b_arr[k]);
	}

	assert(Bst_size(big_tree) == 4500);

	for (int k = 0; k < 500; k++)
	{
		assert(Bst_find(big_tree, &b_arr[k]) == NULL);
	}

	//FOREACH test.
	c = 34;
	Bst_foreach(big_tree, &int_mult, &c);
	for (int k = 500; k < 1000; k++)
	{
		assert(*(int*)Bst_find(big_tree, &b_arr[k]) == c * equal_b_arr[k]);
	}

	Bst_clear(big_tree);
	assert(big_tree->root == NULL);
	Bst_destroy(big_tree);
	

	//Representation test. Here the comparison is done by comparing the length of the strings
	char* key_1 = "A";
	char* key_2 = "BA"; 
	char* key_3 = "BBA";
	char* key_4 = "BBBA";
	char* key_5 = "BBBBA";
	char* key_6 = "BBBBBA";
	char* key_7 = "BBBBBBA";

	int key_1_val = -1; 
	int key_2_val = 5; 
	int key_3_val = 24; 
	int key_4_val = 4; 
	int key_5_val = 15;
	int key_6_val = 32;
	int key_7_val = 0;

	Entry root;
	Entry A, B, C, D, E, F;

	root.key = &key_4;
	root.value = &key_4_val;

	A.key = &key_2;
	A.value = &key_2_val;

	B.key = &key_3;
	B.value = &key_3_val;

	C.key = &key_1; 
	C.value = &key_1_val;

	D.key = &key_5; 
	D.value = &key_5_val;

	E.key = &key_6; 
	E.value = &key_6_val;

	F.key = &key_7;
	F.value = &key_7_val;

	Bst* Rprs_tree = Bst_create(&Entry_cmp);

	assert(Bst_insert(Rprs_tree, &root) == NULL);
	assert(Bst_insert(Rprs_tree, &A) == NULL);
	assert(Bst_insert(Rprs_tree, &B) == NULL);
	assert(Bst_insert(Rprs_tree, &C) == NULL);
	assert(Bst_insert(Rprs_tree, &D) == NULL);
	assert(Bst_insert(Rprs_tree, &E) == NULL);
	assert(Bst_insert(Rprs_tree, &F) == NULL);
	//assert(Bst_insert(Rprs_tree, &Five) == NULL);
	printf("\nRepresentation test:\n\n\n\n");
	Entry_print_Tree(Rprs_tree->root, 0);

	Bst_destroy(Rprs_tree);


	//assert(_CrtDumpMemoryLeaks() == 0);
	return 0;
}