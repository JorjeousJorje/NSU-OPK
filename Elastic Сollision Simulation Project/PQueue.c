#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "PQueue.h"

static void swap(PriorityQueue* pq, size_t son_pos, size_t parent_pos)
{
	Pointer buffer = pq->pq_array[son_pos];
	pq->pq_array[son_pos] = pq->pq_array[parent_pos];
	pq->pq_array[parent_pos] = buffer;
}
static void diving(PriorityQueue* pq, size_t position)
{
	while (2 * position <= pq->pq_size)
	{
		size_t j = 2 * position;
		if (j < pq->pq_size && ((*pq->cmp_func)(pq->pq_array[j], pq->pq_array[j + 1])))
		{
			j++;
		}
		if (!(*pq->cmp_func)(pq->pq_array[position], pq->pq_array[j]))
		{
			break;
		}
		swap(pq, position, j);
		position = j;
	}
}
static void resize(PriorityQueue* pq)
{
	size_t new_capacity = pq->capacity / 2;
	Pointer* new_array = (Pointer*)realloc(pq->pq_array, sizeof(Pointer) * new_capacity);
	if (new_array == NULL)
	{
		return;
	}

	pq->pq_array = new_array;
	pq->capacity = new_capacity;
	assert(pq->capacity > pq->pq_size);
}
static void increase_size(PriorityQueue* pq)
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
static void swim(PriorityQueue* pq, size_t k)
{
	while (k > 1 && !(*pq->cmp_func)(pq->pq_array[k], pq->pq_array[k / 2]))
	{
		swap(pq, k, k / 2);
		k = k / 2;
	}
}
static bool isMinHeapOrdered(PriorityQueue* pq, size_t k)
{
	if (k > pq->pq_size)
	{
		return true;
	}
	size_t left = 2 * k;
	size_t right = 2 * k + 1;
	if (left <= pq->pq_size && (*pq->cmp_func)(pq->pq_array[k], pq->pq_array[left]))
	{
		return false;
	}
	if (right <= pq->pq_size && (*pq->cmp_func)(pq->pq_array[k], pq->pq_array[right]))
	{
		return false;
	}
	return isMinHeapOrdered(pq, left) && isMinHeapOrdered(pq, right);

}
static bool isMinHeap(PriorityQueue* pq)
{
	for (size_t i = 1; i <= pq->pq_size; i++)
	{
		if (pq->pq_array[i] == NULL)
		{
			return false;
		}
	}
	if (pq->pq_array[0] != NULL)
	{
		return false;
	}
	return isMinHeapOrdered(pq, 1);
}

PriorityQueue* pq_create(CmpFunc cmp)
{
	PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	if (pq == NULL)
	{
		return NULL;
	}

	pq->cmp_func = cmp;
	pq->pq_size = 0;
	pq->capacity = INIT_CAPACITY;

	pq->pq_array = (Pointer*)malloc(INIT_CAPACITY * sizeof(Pointer));
	if (pq->pq_array == NULL)
	{
		return NULL;
	}

	pq->pq_array[0] = NULL;//Зануляем нулевой 

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
	if (pq->pq_size == pq->capacity - 1)
	{
		increase_size(pq);
	}
	pq->pq_size++;
	pq->pq_array[pq->pq_size] = data;
	swim(pq, pq->pq_size);
	assert(isMinHeap(pq));
}

Pointer pq_delete_minimum(PriorityQueue* pq)
{
	if (!pq_is_empty(pq))
	{
		return NULL;
	}
	Pointer min = pq->pq_array[1];
	swap(pq, 1, pq->pq_size--);
	diving(pq, 1);

	pq->pq_array[pq->pq_size + 1] = NULL;
	if (pq->pq_size == (pq->capacity - 1) / 4)
	{
		resize(pq);
	}
	assert(isMinHeap(pq));
	return min;
}

int pq_is_empty(PriorityQueue* pq)
{
	return pq->pq_size != 0;
}