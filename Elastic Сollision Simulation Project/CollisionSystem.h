#pragma once
#include "Particles.h"
#include "PQueue.h"
#include "settings.h"


typedef struct tCollisionSystem
{
	PriorityQueue* pq;
	double system_time;
	Particle** Particle_arr;
	size_t par_count;
}CollisionSystem;

typedef struct tEvent
{
	double event_time;
	Particle* a;
	Particle* b;
	int countA, countB;
}Event;

Event* create_event(double time, Particle* a, Particle* b);
CollisionSystem* init_collisionSyst();
CollisionSystem* FILE_init_collisionSyst(size_t Particle_count);
CollisionSystem* Init_System_From_File(size_t(*Part_count)(const char*), const char* filename);
void system_simulate(CollisionSystem* syst, Window* win, double simulation_time);

int double_event_cmp(Pointer s, Pointer p);
void destroy_CollSyst(CollisionSystem* syst);