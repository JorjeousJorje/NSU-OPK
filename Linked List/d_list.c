#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <math.h>

static Node* dlist_find_bydata(Dlist* haystack, Pointer needle)
{
	Node* Ptr_head = haystack->head;
	for (; Ptr_head != NULL;)
	{
		if (Ptr_head->data == needle)
		{
			break;
		}
		Ptr_head = (Ptr_head)->next;
	}
	if (Ptr_head == NULL)
	{
		return NULL;
	}
	else
	{
		return Ptr_head;
	}
}
void dlist_create(Dlist* list)
{
	list->head = NULL;
	list->tail = NULL;
}
void dlist_delete(Dlist* list)
{
	if (list->head == NULL)
	{
		return;
	}
	Node* tmp_head = list->head;
	Node* next = NULL;
	while (tmp_head != NULL)
	{
		next = tmp_head->next;
		free(tmp_head);
		tmp_head = next;
	}
}

void dlist_prepend(Dlist* list, Pointer data)
{
	Node* insert = (Node*)malloc(sizeof(Node));
	if (insert == NULL)
	{
		return;
	}
	insert->data = data;
	insert->next = list->head;
	insert->prev = NULL;

	if (list->head != NULL)
	{
		list->head->prev = insert;
	}
	list->head = insert;
	if (list->tail == NULL) 
	{
		list->tail = insert;
	}
}
void dlist_append(Dlist* list, Pointer data)
{
	Node* insert = (Node*)malloc(sizeof(Node));
	if (insert == NULL)
	{
		return;
	}
	insert->data = data;
	insert->next = NULL;
	insert->prev = list->tail;

	if (list->tail != NULL) 
	{
		list->tail->next = insert;
	}
	list->tail = insert;
	if (list->head == NULL)
	{
		list->head = insert;
	}
}	
size_t dlist_size(Dlist* list)
{
	Node* Ptr_head = list->head;
	if (list->head == NULL)
	{
		return 0;
	}
	size_t size = 0;
	for (; Ptr_head != NULL;)
	{
		size++;
		Ptr_head = Ptr_head->next;
	}
	return size;
}
Pointer dlist_last(Dlist* list)
{
	if (list->tail == NULL)
	{
		return NULL;
	}
	return (list->tail)->data;
}
int dlist_position(Dlist* list, Pointer data)
{
	Node* Ptr_head = list->head;
	if (list->head == NULL)
	{
		return -1;
	}
	size_t count = 0;
	for (; Ptr_head != NULL;)
	{
		if (Ptr_head->data == data)
		{
			break;
		}
		count++;
		Ptr_head = Ptr_head->next;
	}
	if (Ptr_head == NULL)
	{
		return -1;
	}
	else
	{
		return count;
	}
}
Pointer dlist_nth(Dlist* list, int n)
{
	Node* Ptr_head = list->head;
	Node* Ptr_tail = list->tail;
	if (list->head == NULL)
	{
		return NULL;
	}
	if (n < 0)
	{
		for (int count = -1; count > n && Ptr_tail != NULL; count--)
		{
			Ptr_tail = (Ptr_tail)->prev;
		}
		if (Ptr_tail == NULL)
		{
			return NULL;
		}
		else
		{
			return Ptr_tail->data;
		}
	}
	if(n >= 0)
	{
		for(int count = 0; count < n && Ptr_head != NULL; count ++)
		{
			Ptr_head = (Ptr_head)->next;//перекидываю указатель с головы на предыдущий голове
		}
		if (Ptr_head == NULL)
		{
			return NULL;
		}
		else
		{
			return Ptr_head->data;
		}
	}
}
Pointer dlist_remove(Dlist* list, Pointer data)
{
	Node* dlt = dlist_find_bydata(list, data);
	if (dlt == NULL)
	{
		return NULL;
	}
	if (dlt->prev != NULL)
	{
		(dlt->prev)->next = dlt->next;
	}
	if (dlt->next != NULL)
	{
		(dlt->next)->prev = dlt->prev;
	}
	if (dlt->prev == NULL)
	{
		list->head = dlt->next;
	}
	if (dlt->next == NULL)
	{
		list->tail = dlt->prev;
	}
	free(dlt);
	if (list->head == NULL)
	{
		return NULL;
	}
	else
	{
		return list->head->data;
	}

}
void dlist_remove_all(Dlist* list, Pointer data)
{
	for (; dlist_remove(list, data) != NULL;)
	{
		dlist_remove(list, data);
	}
	return;
}
Dlist* dlist_copy(Dlist* list)
{
	Dlist* new_list = (Dlist*)malloc(sizeof(Dlist));
	if (new_list == NULL)
	{
		return;
	}
	dlist_create(new_list);
	if (list->head != NULL)
	{
		new_list->head = malloc(sizeof(Node));
		new_list->head->data = list->head->data;
		new_list->head->prev = NULL;
		new_list->head->next = NULL;
	}
	else
	{
		return new_list;
	}

	Node* index_head = list->head;
	Node* index_copy = new_list->head;
	for (; index_head->next != NULL;)
	{
		index_copy->next = (Node*)malloc(sizeof(Node));
		index_copy->next->data = index_head->next->data;
		index_copy->next->next = NULL;
		index_copy->next->prev = index_copy;
		index_head = index_head->next;
		index_copy = index_copy->next;
	}
	new_list->tail = index_copy;
	return new_list;
}
void dlist_insert(Node* node, Pointer data)
{
	assert(node != NULL);
	Node* insert = (Node*)malloc(sizeof(Node));
	if (insert == NULL)
	{
		return;
	}
	insert->prev = node;
	insert->next = node->next;
	node->next = insert;
	insert->next->prev = insert;
	insert->data = data;
}

Pointer dlist_find(Dlist* haystack, Pointer needle)
{
	Node* buffer = dlist_find_bydata(haystack, needle);
	if (buffer == NULL)
	{
		return NULL;
	}
	else
	{
		return buffer->data;
	}
}
Pointer dlist_concat(Dlist* list1, Dlist* list2)
{
	if (list1->head == NULL || list2->head == NULL)
	{
		return;
	}
	Node* Ptr_tail1 = list1->tail;
	Node* Ptr_head2 = list2->head;
	list1->tail->next = Ptr_head2;
	list2->head->prev = Ptr_tail1;
	list1->tail = list2->tail;
	list2->head = list1->head;

	return list1->head->data;

}
Pointer dlist_find_custom(Dlist* haystack, Pointer needle, int(*compare_func)(Pointer a, Pointer b))
{
	if (haystack->head == NULL)
	{
		return NULL;
	}
	Node* Ptr_head = haystack->tail;
	for (; Ptr_head != NULL;)
	{
		if (compare_func(Ptr_head->data, needle) == 0)
		{
			return Ptr_head->data;
		}
		Ptr_head = Ptr_head->prev;
	}

	return NULL;
	
}
void dlist_foreach(Dlist* list, void (*func)(Pointer data, Pointer user_data), Pointer user_data)
{
	if (list->head == NULL)
	{
		return;
	}
	Node* Ptr_head = list->head;
	for (; Ptr_head != NULL;)
	{
		func(Ptr_head->data, user_data);
		Ptr_head = Ptr_head->next;
	}
}
