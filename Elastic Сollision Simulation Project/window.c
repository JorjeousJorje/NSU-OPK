#include "window.h"
#include <stdio.h>


static void window_init()
{
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
}

bool init_SDL(Window* win)
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = 0;

	window_init();

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	win->window = SDL_CreateWindow("Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (win->window == NULL)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		return false;
	}

	win->renderer = SDL_CreateRenderer(win->window, -1, rendererFlags);

	if (win->window == NULL)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		return false;
	}

	return true;
}
void clean_up(Window* win)
{
	SDL_DestroyRenderer(win->renderer);
	win->renderer = NULL;
	SDL_DestroyWindow(win->window);
	win->window = NULL;

	SDL_Quit();
}
Window* create_window()
{
	Window* win = (Window*)malloc(sizeof(Window));
	if (win == NULL)
	{
		return NULL;
	}
	return win;
}

void prepareScene(Window* win)
{
	SDL_SetRenderDrawColor(win->renderer, 255, 228, 225, 255);
	SDL_RenderClear(win->renderer);
}
void presentScene(Window* win)
{
	SDL_RenderPresent(win->renderer);
	SDL_SetRenderDrawColor(win->renderer, 255, 228, 225, 255);
	SDL_RenderClear(win->renderer);
}