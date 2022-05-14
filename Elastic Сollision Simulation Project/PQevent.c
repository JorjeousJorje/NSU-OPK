#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "PQevent.h"

#define INIT_CAPACITY 20
static void e_swap(PQ* pq, int son_pos, int parent_pos)
{
	Event* buffer = pq->event_arr[son_pos];
	pq->event_arr[son_pos] = pq->event_arr[parent_pos];
	pq->event_arr[parent_pos] = buffer;
}
static void e_diving(PQ* pq, int position)
{
	int  son1_pos = 2 * position + 1, son2_pos = 2 * position + 2;

	while (son1_pos < pq->pq_size && ((*pq->cmp_func)(pq->event_arr[position]->time, pq->event_arr[son1_pos]->time) == 1))
	{
		if (((*pq->cmp_func)(pq->event_arr[son2_pos]->time, pq->event_arr[son1_pos]->time) == 1))
		{
			e_swap(pq, position, son1_pos);
			e_diving(pq, son1_pos);
		}
		else
		{
			e_swap(pq, position, son2_pos);
			e_diving(pq, son2_pos);
		}
	}
}
static void e_resize(PQ* pq)
{
	size_t new_capacity = pq->capacity / 2;
	Event** new_array = (Event**)realloc(pq->event_arr, sizeof(Event*) * new_capacity);
	if (new_array == NULL)
	{
		return;
	}
	pq->event_arr = new_array;
	pq->capacity = new_capacity;
}
static void e_increase_size(PQ* pq)
{
	size_t new_capacity = pq->capacity * 2;
	Event** new_array = (Event**)realloc(pq->event_arr, sizeof(Event*) * new_capacity);
	if (new_array == NULL)
	{
		return;
	}

	pq->capacity = new_capacity;
	pq->event_arr = new_array;
	assert(pq->capacity > pq->pq_size);
}

PQ* pqe_create(CmpFunc1 cmp)
{
	PQ* pq = (PQ*)malloc(sizeof(PQ));
	if (pq == NULL)
	{
		return NULL;
	}

	pq->cmp_func = cmp;
	pq->pq_size = 0;
	pq->capacity = INIT_CAPACITY;

	pq->event_arr = (Event**)malloc(INIT_CAPACITY * sizeof(Event));
	if (pq->event_arr == NULL)
	{
		return NULL;
	}

	return pq;
}

void pqe_destroy(PQ* pq)
{
	if (pq != NULL)
	{
		free(pq->event_arr);
		free(pq);
	}
}

void pqe_insert(PQ* pq, Event* data)
{
	int son_pos = pq->pq_size, parent_pos = (son_pos - 1) / 2;

	pq->event_arr[son_pos] = data;

	while (parent_pos > 0 && (*pq->cmp_func)(pq->event_arr[son_pos]->time, pq->event_arr[parent_pos]->time) == 0)
	{
		e_swap(pq, son_pos, parent_pos);
		son_pos = parent_pos;
		parent_pos = (son_pos - 1) / 2;
	}

	pq->pq_size++;
	if (pq->pq_size >= pq->capacity)
	{
		e_increase_size(pq);
	}
}

Event* pqe_delete_minimum(PQ* pq)
{
	if (pqe_is_empty(pq) == 0)
	{
		return NULL;
	}
	Event* deleted;
	deleted = pq->event_arr[0];

	pq->event_arr[0] = pq->event_arr[pq->pq_size - 1];
	pq->pq_size--;
	e_diving(pq, 0);

	if (4 * pq->pq_size < pq->capacity)
	{
		e_resize(pq);
	}
	return deleted;
}

int pqe_is_empty(PQ* pq)
{
	return (pq->pq_size != 0) ? pq->pq_size : 0;
}
