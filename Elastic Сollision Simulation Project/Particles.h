#pragma once
#include "window.h"

typedef struct tParticle
{
	double rx, ry;
	double vx, vy;
	size_t collisions;
	double radius;
	double mass;
	int r, g, b, a;
}Particle;

Particle* init_Particle(double rx, double ry, double vx, double vy, double radius, double mass, int r, int g, int b, int a);

Particle* FILE_init_Particle(double rx, double ry, double vx, double vy, double radius, double mass, int r, int g, int b);

Particle* init_random_Particle();

void move(Particle* par, double dt);

size_t collusions(Particle* par);

double timetoHit(Particle* par1, Particle* par2);

double timetoHitVerticalWall(Particle* par);

double timetoHitHorisontalWall(Particle* par);

void bounceOff(Particle* par1, Particle* par2);

void bounceOffVerticalWall(Particle* par);

void bounceOffHorisontalWall(Particle* par);

void draw_particles(Window* win, Particle* par);