#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "PQueue.h"

#define MIN_SIZE 20
static void swap(Pointer son, Pointer parent)
{
	Pointer buffer = son;
	son = parent;
	parent = buffer;
}
static void diving(PriorityQueue* pq)
{
	int parent_pos = 0, son1_pos = 1, son2_pos = 2, i;

	while (son1_pos <= pq->pq_size - 1)
	{
		if ((son2_pos > pq->pq_size - 1) || ((*pq->cmp_func)(pq->pq_array[son1_pos], pq->pq_array[parent_pos]) == 0))
		{
			pq->pq_array[parent_pos] = pq->pq_array[son1_pos];
			parent_pos = son1_pos;
		}
		else
		{
			pq->pq_array[parent_pos] = pq->pq_array[son2_pos];
			parent_pos = son2_pos;
		}
		son1_pos = 2 * parent_pos + 1;
		son2_pos = 2 * parent_pos + 2;
	}

	size_t size = pq->pq_size;
	size_t current_size = parent_pos + 1;
	while (current_size != size)
	{
		pq->pq_size = current_size - 1;
		pq_insert(pq, pq->pq_array[current_size]);
	}

	pq->pq_size = size - 1;

	if (4 * pq->pq_size < pq->capacity)
	{
		size_t new_capacity = pq->capacity / 2;
		Pointer* new_array = (Pointer*)realloc(pq->pq_array, sizeof(Pointer) * new_capacity);
		if (new_array == NULL)
		{
			return;
		}
		pq->pq_array = new_array;
		pq->capacity = new_capacity;
	}
}


PriorityQueue* pq_create(CmpFunc cmp)
{
	PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	if (pq == NULL)
	{
		return;
	}

	pq->cmp_func = cmp;
	pq->pq_size = 0;
	pq->capacity = MIN_CAPACITY;
	pq->pq_array = malloc(MIN_SIZE * sizeof(Pointer));
	if (pq->pq_array == NULL)
	{
		return;
	}
	return pq;
}

void pq_destroy(PriorityQueue* pq)
{
	if (pq != NULL)
	{
		free(pq->pq_array);
		free(pq);
	}
}

void pq_insert(PriorityQueue* pq, Pointer data)
{
	pq->pq_size++;
	int son_pos, parent_pos;

	if (pq->pq_size >= pq->capacity)
	{
		size_t new_capacity = pq->capacity * 2;
		Pointer* new_array = (Pointer*)realloc(pq->pq_array, sizeof(Pointer) * new_capacity);
		if (new_array == NULL)
		{
			return;
		}
		pq->capacity = new_capacity;
		pq->pq_array = new_array;
		assert(pq->capacity > pq->pq_size);
	}

	son_pos = pq->pq_size - 1;
	parent_pos = (son_pos - 1) / 2;

	while ((son_pos > 0) && ((*pq->cmp_func)(pq->pq_array[son_pos], pq->pq_array[parent_pos]) == 0))
	{
		swap(pq->pq_array[son_pos], pq->pq_array[parent_pos]);
		son_pos = parent_pos;
		parent_pos = (son_pos - 1) / 2;
	}
	pq->pq_array[son_pos] = data;
}

Pointer pq_delete_minimum(PriorityQueue* pq)
{
	if (pq->pq_size == 0)
	{
		return NULL;
	}
	Pointer deleted;
	deleted = pq->pq_array[0];
	if (pq->pq_size == 1)
	{
		pq->pq_size = 0;
	}
	else
	{
		diving(pq);
	}

	return deleted;
}

int pq_is_empty(PriorityQueue* pq)
{
	return (pq->pq_size != 0) ? pq->pq_size : 0;
}