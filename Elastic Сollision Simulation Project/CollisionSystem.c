#define _CRT_SECURE_NO_WARNINGS
#include "CollisionSystem.h"
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>


static bool isValid(Event* event)
{
	if (event->a != NULL && collusions(event->a) != event->countA)
	{
		return false;
	}
	if (event->b != NULL && collusions(event->b) != event->countB)
	{
		return false;
	}
	return true;
}
static void predict(CollisionSystem* syst, Particle* a, double limit)
{
	if (a == NULL)
	{
		return;
	}

	for (size_t i = 0; i < syst->par_count; i++)
	{
		double dt = timetoHit(a, syst->Particle_arr[i]);
		if (syst->system_time + dt <= limit)
		{
			pq_insert(syst->pq, create_event(syst->system_time + dt, a, syst->Particle_arr[i]));
		}
	}

	double dtX = timetoHitVerticalWall(a);
	double dtY = timetoHitHorisontalWall(a);
	if (syst->system_time + dtX <= limit)
	{
		pq_insert(syst->pq, create_event(syst->system_time + dtX, a, NULL));
	}
	if (syst->system_time + dtY <= limit)
	{
		pq_insert(syst->pq, create_event(syst->system_time + dtY, NULL, a));
	}
}
static bool redraw(CollisionSystem* syst, Window* win, double limit)
{
	prepareScene(win);
	for (size_t i = 0; i < syst->par_count; i++)
	{
		SDL_Event event1;
		draw_particles(win, syst->Particle_arr[i]);
		while (SDL_PollEvent(&event1))
		{
			if (event1.type == SDL_QUIT)
			{
				return false;
			}
		}
	}
	presentScene(win);
	SDL_Delay(5);

	if (syst->system_time < limit)
	{
		pq_insert(syst->pq, create_event(syst->system_time + 1.0 / HZ, NULL, NULL));//Ёвент с нул€ми-эвент отрисовки
	}
}

Event* create_event(double time, Particle* a, Particle * b)
{
	Event* event = (Event*)malloc(sizeof(Event));
	if (event == NULL)
	{
		return NULL;
	}

	event->event_time = time;
	event->a = a;
	event->b = b;
	if (a != NULL)
	{
		event->countA = collusions(a);
	}
	else
	{
		event->countA = -1;
	}
	if (b != NULL)
	{
		event->countB = collusions(b);
	}
	else
	{
		event->countB = -1;
	}

	return event;
}

int double_event_cmp(Pointer s, Pointer p)
{
	Event* son = (Event*)s;
	Event* parent = (Event*)p;

	return son->event_time > parent->event_time;
}

CollisionSystem* init_collisionSyst()
{
	CollisionSystem* sys = (CollisionSystem*)malloc(sizeof(CollisionSystem));
	if (sys == NULL)
	{
		return NULL;
	}

	sys->pq = pq_create(double_event_cmp);
	sys->system_time = 0.0;
	sys->par_count = NUM_OF_PARTICLES;//By default

	sys->Particle_arr = (Particle**)malloc(sizeof(Particle) * NUM_OF_PARTICLES);
	if (sys->Particle_arr == NULL)
	{
		return NULL;
	}

	return sys;
}
CollisionSystem* FILE_init_collisionSyst(size_t Particle_count)
{
	CollisionSystem* sys = (CollisionSystem*)malloc(sizeof(CollisionSystem));
	if (sys == NULL)
	{
		return NULL;
	}

	sys->pq = pq_create(double_event_cmp);
	sys->system_time = 0.0;
	sys->par_count = Particle_count;//By default

	sys->Particle_arr = (Particle**)malloc(sizeof(Particle) * Particle_count);
	if (sys->Particle_arr == NULL)
	{
		return NULL;
	}

	return sys;
}
CollisionSystem* Init_System_From_File(size_t(*Part_count)(const char*), const char* filename)
{
	//type == 0 - reading before point
	//type == 1 - reading after point
	//type == 2 - E type
	FILE* mf;
	size_t Par_count = Part_count(filename);
	mf = fopen(filename, "r");

	CollisionSystem* sys = FILE_init_collisionSyst(Par_count);

	double mas[NUM_OF_PARAMS];
	size_t NUMBERS_COUNT = Par_count * NUM_OF_PARAMS;

	for (size_t i = 0, count = 0, j = 0; i <= Par_count * NUM_OF_PARAMS; i++, count++)
	{
		long long int symbol = 0, before_point = 0, after_point = 0;
		int power = 0, type = 0, after_point_counter = 0, is_minus = 0;


		symbol = getc(mf);
		while (symbol == ' ')
		{
			symbol = getc(mf);
		}
		while (symbol == '\n')
		{
			symbol = fgetc(mf);
			while (symbol == ' ')
			{
				symbol = fgetc(mf);
			}
		}
		while (symbol == ' ')
		{
			symbol = getc(mf);
		}
		if (symbol == '-')
		{
			is_minus = 1;
			symbol = fgetc(mf);
		}
		
		while (true)
		{
			if (isspace(symbol))
			{
				break;
			}
			else if ((symbol == '.') && (type == 0))
			{
				type = 1;
				symbol = fgetc(mf);
				continue;
			}
			else if ((symbol == 'E') && (type == 1))
			{
				type = 2;
				symbol = fgetc(mf);
				assert(symbol == '-');
				symbol = fgetc(mf);
				continue;
			}
			else if (symbol == EOF)
			{
				break;
			}
			else if (!isdigit(symbol))
			{
				printf("File is broken!");
				return NULL;
			}
			switch (type)
			{
			case 0:
				before_point = before_point * 10 + (symbol - 48);
				break;
			case 1:
				after_point = after_point * 10 + (symbol - 48);
				after_point_counter++;
				break;
			case 2:
				power = power * 10 + (symbol - 48);
				break;
			default:
				break;
			}
			symbol = fgetc(mf);
		}

		double num = 0;
		num = after_point;
		while (after_point_counter > 0)
		{
			num /= 10;
			after_point_counter--;
		}
		num += before_point;
		while (power > 0)
		{
			num /= 10;
			power--;
		}
		if (is_minus)
		{
			num *= -1;
		}

		if (count != 0 && (count % NUM_OF_PARAMS == 0) && j < Par_count)
		{
			sys->Particle_arr[j] = FILE_init_Particle(mas[0], mas[1], mas[2], mas[3], mas[4], mas[5], mas[6], mas[7], mas[8]);
			j++;
			count = 0;
		}
		mas[count % NUM_OF_PARAMS] = num;
	}
	return sys;
}

void destroy_CollSyst(CollisionSystem* syst)
{
	if (syst != NULL)
	{
		for (size_t i = 0; i < syst->par_count; i++)
		{
			free(syst->Particle_arr[i]);
			syst->Particle_arr[i] = NULL;
		}
		pq_destroy(syst->pq);
		syst->pq = NULL;
		free(syst->Particle_arr);
		syst->Particle_arr = NULL;
		free(syst);
		syst = NULL;
	}
}

void system_simulate(CollisionSystem* syst, Window* win, double limit)
{

	for (size_t i = 0; i < syst->par_count; i++)
	{
		predict(syst, syst->Particle_arr[i], limit);
	}
	pq_insert(syst->pq, create_event(0, NULL, NULL));//Ёвент перерисовки

	bool quit_event = true;
	while (pq_is_empty(syst->pq) && quit_event != false)
	{
		Event* event = pq_delete_minimum(syst->pq);
		if (!isValid(event))
		{
			free(event);//Particles чистить до конца симул€ции ни в коем случае нельз€!
			event = NULL;
			continue;
		}

		for (size_t i = 0; i < syst->par_count; i++)
		{
			move(syst->Particle_arr[i], event->event_time - syst->system_time);
		}
		syst->system_time = event->event_time;

		if (event->a != NULL && event->b != NULL)
		{
			bounceOff(event->a, event->b);
		}
		else if (event->a != NULL && event->b == NULL)
		{
			bounceOffVerticalWall(event->a);
		}
		else if (event->a == NULL && event->b != NULL)
		{
			bounceOffHorisontalWall(event->b);
		}
		else if (event->a == NULL && event->b == NULL)
		{
			quit_event = redraw(syst, win, limit);
		}
		predict(syst, event->a, limit);
		predict(syst, event->b, limit);

		free(event);
		event = NULL;
	}
}
