#pragma once
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include "settings.h"
#undef main


typedef struct tWindow
{
	SDL_Renderer* renderer;
	SDL_Window* window;
}Window;

Window* create_window();
bool init_SDL(Window* win);
void clean_up(Window* win);
void prepareScene(Window* win);
void presentScene(Window* win);
