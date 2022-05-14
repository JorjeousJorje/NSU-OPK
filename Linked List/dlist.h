#pragma once

typedef void* Pointer;

typedef struct tNode 
{
	Pointer data;
	struct tNode* next;
	struct tNode* prev;
} Node;

typedef struct tDlist
{
	size_t size;
	Node* head;
	Node* tail;
} Dlist;

void dlist_create(Dlist* list);
void dlist_delete(Dlist* list);

void dlist_prepend(Dlist* list, Pointer value);
void dlist_append(Dlist* list, Pointer value);
size_t dlist_size(Dlist* list);
Pointer dlist_last(Dlist* list);
Pointer dlist_nth(Dlist* list, int n);
int dlist_position(Dlist* list, Pointer data);
void dlist_insert(Node* node, Pointer data);
Pointer dlist_find(Dlist* haystack, Pointer needle);
Pointer dlist_remove(Dlist* list, Pointer data);
void dlist_remove_all(Dlist* list, Pointer data);
Dlist* dlist_copy(Dlist* list);
Pointer dlist_concat(Dlist* list1, Dlist* list2);
Pointer dlist_find_custom(Dlist* haystack, Pointer needle, int(*compare_func)(Pointer a, Pointer b));
void dlist_foreach(Dlist* list, void (*func)(Pointer data, Pointer user_data), Pointer user_data);

