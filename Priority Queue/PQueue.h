#pragma once

#define MIN_CAPACITY 20

typedef void* Pointer;
typedef int (*CmpFunc)(Pointer data1, Pointer data2);

typedef struct tPriorityQueue
{
	Pointer* pq_array;
	size_t pq_size;
	size_t capacity;
	CmpFunc cmp_func;
} PriorityQueue;

/* Create empty priority queue. */
PriorityQueue* pq_create(CmpFunc cmp);

/* Destroy priority queue and free its memory. */
void pq_destroy(PriorityQueue* pq);

/* Add new value into the priority queue. */
void pq_insert(PriorityQueue* pq, Pointer data);

/* Delete maximum value from the priority queue and return it. */
Pointer pq_delete_minimum(PriorityQueue* pq);

/* Return non-zero value if the priority queue is not empty. */
int pq_is_empty(PriorityQueue* pq);
