#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <crtdbg.h>
#include "CollisionSystem.h"

size_t Particle_count(const char* filename)
{
	size_t count = 0;
	int symbol = 0;
	FILE* f = fopen(filename, "r");
	if (f == NULL)
	{
		return 0;
	}

	symbol = fgetc(f);
	while (symbol == ' ')
	{
		symbol = fgetc(f);
	}
	while (symbol == '\n')
	{
		symbol = fgetc(f);
	}

	bool lines_after = false;
	while (symbol != EOF)
	{
		if (symbol == '\n')
		{
			count++;
			symbol = fgetc(f);
			while (symbol == '\n')
			{
				lines_after = true;
				symbol = fgetc(f);
			}
			ungetc(symbol, f);
		}
		symbol = fgetc(f);
		lines_after = false;
	}
	if (!lines_after)
	{
		count++;
	}
	fclose(f);
	return count;
}

int main()
{
	srand(time(NULL));
	Window* win = create_window();
	assert(win != NULL);
	assert(init_SDL(win) == true);

	CollisionSystem* sys = NULL;

	if (sys = Init_System_From_File(Particle_count, "C:/Users/User/Desktop/учеба/Программирование/Прога. 3 семестр(С)/Mercy/Mercy/Simulation/3 partticles.txt"))
	{
		system_simulate(sys, win, (double)SIMULATION_TIME);
	}
	else
	{
		return 1;
	}

	clean_up(win);
	free(win);
	destroy_CollSyst(sys);
	assert(_CrtDumpMemoryLeaks() == 0);
	return 0;
}
