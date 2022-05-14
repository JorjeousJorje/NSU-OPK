#pragma once
#include <stdio.h>

typedef void* Pointer;

typedef int (*CmpFunc)(Pointer data1, Pointer data2);

typedef struct tNode 
{
	Pointer data;
	struct tNode* left;
	struct tNode* right;
} Node;

typedef struct tBst
{
	Node* root;
	CmpFunc cmp_func;
	size_t count;
} Bst;

// Create empty tree
Bst* Bst_create(CmpFunc cmp_func);
// Clear tree but do not destroy tree struct
void Bst_clear(Bst* tree);
// Completely destroy tree
void Bst_destroy(Bst* tree);

size_t Bst_size(Bst* tree);
// Find element with equal data and return its data if any else NULL
Pointer Bst_find(Bst* tree, Pointer data);
// Return data which was replaced by this insertion if any else NULL
Pointer Bst_insert(Bst* tree, Pointer data);
// Delete node with equal data and return its data if any else NULL
Pointer Bst_delete(Bst* tree, Pointer data);
// Call foreach_func for every node's data in tree passing given extra_data
void Bst_foreach(Bst* tree, void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data);