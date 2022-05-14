#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include "Particles.h"

Particle* init_Particle(double rx, double ry, double vx, 
	double vy, double radius, double mass, int r, int g, int b, int a)
{
	Particle* par = (Particle*)malloc(sizeof(Particle));
	if (par == NULL)
	{
		return NULL;
	}

	par->vx = vx;
	par->vy = vy;
	par->rx = rx;
	par->ry = ry;
	par->radius = radius;
	par->mass = mass;
	par->r = r;
	par->g = g;
	par->b = b;
	par->a = a;
	par->collisions = 0;

	return par;
}

Particle* FILE_init_Particle(double rx, double ry, double vx, 
	double vy, double radius, double mass, int r, int g, int b)
{
	Particle* par = (Particle*)malloc(sizeof(Particle));
	if (par == NULL)
	{
		return NULL;
	}

	par->vx = vx;
	par->vy = vy;
	par->rx = rx * 1000;
	par->ry = ry * 1000;
	par->radius = radius * 1000;
	par->mass = mass;
	par->r = 35;
	par->g = 18;
	par->b = 200;
	par->a = 200;

	par->collisions = 0;

	return par;
}

Particle* init_random_Particle()
{
	Particle* par = (Particle*)malloc(sizeof(Particle));
	if (par == NULL)
	{
		return NULL;
	}

	par->vx = 0.5;
	par->vy = 0;
	par->radius = 1;
	par->mass = 1;
	par->rx = (double)rand() / RAND_MAX * 882 + 1;
	par->ry = (double)rand() / RAND_MAX * 882 + 1;
	par->r = 43;
	par->g = 35;
	par->b = 255;
	par->a = 255;
	par->collisions = 0;

	return par;
}

void move(Particle* par, double dt)
{
	par->rx += par->vx * dt;
	par->ry += par->vy * dt;
}

size_t collusions(Particle* par)
{
	return par->collisions;
}

double timetoHit(Particle* par1, Particle* par2)
{
	if (par1 == par2)
	{
		return INFINITY;
	}
	double dx = par1->rx - par2->rx;
	double dy = par1->ry - par2->ry;
	double dvx = par1->vx - par2->vx;
	double dvy = par1->vy - par2->vy;
	double dvdr = dx * dvx + dy * dvy;
	if (dvdr > 0)
	{
		return INFINITY;
	}
	double dvdv = dvx * dvx + dvy * dvy;
	if (dvdv == 0)
	{
		return INFINITY;
	}
	double drdr = dx * dx + dy * dy;
	double sigma = par1->radius + par2->radius;
	double d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma);
	if (d < 0)
	{
		return INFINITY;
	}

	return -(dvdr + sqrt(d)) / dvdv;

}

double timetoHitVerticalWall(Particle* par)
{
	if (par->vx > 0)
	{
		return (SCREEN_WIDTH - par->rx - par->radius) / par->vx;
	}
	else if (par->vx < 0)
	{
		return (par->radius - par->rx) / par->vx;
	}
	else
	{
		return INFINITY;
	}
}

double timetoHitHorisontalWall(Particle* par)
{
	if (par->vy > 0)
	{
		return (SCREEN_HEIGHT - par->ry - par->radius) / par->vy;
	}
	else if (par->vy < 0)
	{
		return (par->radius - par->ry) / par->vy;
	}
	else
	{
		return INFINITY;
	}
}

void bounceOff(Particle* par1, Particle* par2)
{
	double dx = par1->rx - par2->rx;
	double dy = par1->ry - par2->ry;
	double dvx = par1->vx - par2->vx;
	double dvy = par1->vy - par2->vy;
	double dvdr = dx * dvx + dy * dvy;       
	double dist = par2->radius + par1->radius; 

	double magnitude = 2 * par2->mass * par1->mass * dvdr / ((par2->mass + par1->mass) * dist);

	double fx = magnitude * dx / dist;
	double fy = magnitude * dy / dist;

	par2->vx += fx / par2->mass;
	par2->vy += fy / par2->mass;
	par1->vx -= fx / par1->mass;
	par1->vy -= fy / par1->mass;

	par2->collisions++;
	par1->collisions++;
}

void bounceOffVerticalWall(Particle* par)
{
	par->vx = -par->vx;
	par->collisions++;
}

void bounceOffHorisontalWall(Particle* par)
{
	par->vy = -par->vy;
	par->collisions++;
}

void draw_particles(Window* win, Particle* par)
{
	filledCircleRGBA(win->renderer, par->rx, par->ry, par->radius, par->r, par->g, par->a, par->b);
}