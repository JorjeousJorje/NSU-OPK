#pragma once
#include "Particles.h"
#define NUM_OF_PARTICLES 1
#define HZ 0.1
#define MIN_CAPACITY 20

typedef int (*CmpFunc1)(double data1, double data2);

typedef struct tEvent
{
	double time;
	Particle* a;
	Particle* b;
	int countA, countB;
}Event;

typedef struct tPQ
{
	Event** event_arr;
	size_t pq_size;
	size_t capacity;
	CmpFunc1 cmp_func;
}PQ;

typedef struct tCollisionSystem
{
	PQ* pq;
	double t;
	Particle* Particle_arr[NUM_OF_PARTICLES];
	int par_count;
}CollisionSystem;

/* Create empty priority queue. */
PQ* pqe_create(CmpFunc1 cmp);

/* Destroy priority queue and free its memory. */
void pqe_destroy(PQ* pq);

/* Add new value into the priority queue. */
void pqe_insert(PQ* pq, Event* data);

/* Delete maximum value from the priority queue and return it. */
Event* pqe_delete_minimum(PQ* pq);

/* Return non-zero value if the priority queue is not empty. */
int pqe_is_empty(PQ* pq);
