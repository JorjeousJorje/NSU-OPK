#include "Bst.h"
#include <stdlib.h>

static void Bst_bypass(Node* node, void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data)
{
	if (node == NULL)
	{
		return;
	}
	Bst_bypass(node->left, foreach_func, extra_data);
	(*foreach_func)(node->data, extra_data);
	Bst_bypass(node->right, foreach_func, extra_data);
}

Bst* Bst_create(CmpFunc cmp_func)
{
	Bst* new_tree = malloc(sizeof(Bst));
	if (new_tree == NULL)
	{
		return NULL;
	}

	new_tree->root = NULL;
	new_tree->cmp_func = cmp_func;
	new_tree->count = 0;
	return new_tree;
}
void Bst_clear(Bst* tree)
{
	if (tree->root == NULL)
	{
		return;
	}

	Node** root = tree->root;
	Node* left = tree->root->left;
	Node* right = tree->root->right;
	tree->root = left;
	Bst_clear(tree);
	tree->root = right;
	Bst_clear(tree);
	free(root);
}
void Bst_destroy(Bst* tree) 
{
	Bst_clear(tree);
	free(tree);
}

size_t Bst_size(Bst* tree)
{
	return tree->count;
}
Pointer Bst_find(Bst* tree, Pointer data)
{
	Node* find_node = tree->root;

	for (;;)
	{
		if (find_node == NULL)
		{
			return NULL;
		}
		else if ((*tree->cmp_func)(find_node->data, data) == 0)
		{
			return find_node->data;
		}
		else if ((*tree->cmp_func)(find_node->data, data) == -1)
		{
			find_node = find_node->right;
		}
		else
		{
			find_node = find_node->left;
		}
	}
}
Pointer Bst_insert(Bst* tree, Pointer data)
{
	Node* find_node = tree->root;
	Node** insert_node = &tree->root;

	for (;;)
	{
		if (find_node == NULL)
		{
			*insert_node = (Node*)malloc(sizeof(Node));
			if (*insert_node == NULL)
			{
				return NULL;
			}
			find_node = *insert_node;
			find_node->data = data;
			find_node->left = NULL;
			find_node->right = NULL;
			tree->count++;

			return NULL;
		}
		else if ((*tree->cmp_func)(find_node->data, data) == 0)
		{
			Pointer found = find_node->data;
			find_node->data = data;
			return found;
		}
		else if ((*tree->cmp_func)(find_node->data, data) == -1)
		{
			insert_node = &find_node->right;
			find_node = find_node->right;
		}
		else
		{
			insert_node = &find_node->left;
			find_node = find_node->left;
		}
	}
}
Pointer Bst_delete(Bst* tree, Pointer data) 
{
	Node** replace_node = &tree->root;
	Node* delete_node = tree->root;

	for (;;)
	{
		if (delete_node == NULL)
		{
			return NULL;
		}
		else if ((*tree->cmp_func)(delete_node->data, data) == 0)
		{
			break;
		}
		else if ((*tree->cmp_func)(delete_node->data, data) == -1)
		{
			replace_node = &delete_node->right;
			delete_node = delete_node->right;
		}
		else
		{
			replace_node = &delete_node->left;
			delete_node = delete_node->left;
		}
	}

	if (delete_node->right == NULL)
	{
		*replace_node = delete_node->left;
	}
	else 
	{
		Node* sibling = delete_node->right;
		if (sibling->left == NULL)
		{
			sibling->left = delete_node->left;
			*replace_node = sibling;
		}
		else
		{
			Node* leftmost = sibling->left;
			for (; leftmost == NULL;)
			{
				sibling = leftmost;
				leftmost = sibling->left;
			}

			sibling->left = leftmost->right;
			leftmost->left = delete_node->left;
			leftmost->right = delete_node->right;
			*replace_node = leftmost;
		}
	}

	tree->count--;
	Pointer deleted_data = delete_node->data;
	free(delete_node);
	return deleted_data;
}
void Bst_foreach(Bst* tree, void(*foreach_func)(Pointer data, Pointer extra_data), Pointer extra_data) 
{
	Bst_bypass(tree->root, foreach_func, extra_data);
}
