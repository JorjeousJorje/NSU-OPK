#include "rational.h"
#include <math.h>
#include <assert.h>
#include <limits.h>

int power(int x, int n)
{
	if (n == 0)
	{
		return 1;
	}

	int count = 1;

	while (n != 0)
	{
		if (n % 2 == 0)
		{
			n /= 2;
			x *= x;
		}
		else
		{
			if (n < 0)
			{
				n++;
				count *= x;
			}
			else
			{

				n--;
				count *= x;
			}
		
		}
	}
	return count;
}
int nod(int a, int b)
{
	a = fabs(a);
	b = fabs(b);
	while (a != 0 && b != 0)
	{
		if (a > b)
		{
			a %= b;
		}
		else
		{
			b %= a;
		}
	}

	return a + b;
}
static void normalize(Rational* rat)
{
	int g = nod(rat->numer, rat->denom);
	rat->numer /= g;
	rat->denom /= g;
}

void  rat_create(Rational* res, int a, int b)
{
	res->numer = a;
	res->denom = b;
	if (res->denom == 0)
	{
		//printf("Denominator is 0! This is undefined\n");
		assert(res->denom != 0);
	}
	else
	{
		if (res->denom < 0)
		{
			assert(res->denom != INT_MIN);
			res->numer *= -1;
			res->denom *= -1;
		}
		normalize(res);
	}
}


void rat_add(Rational* result, Rational* a, Rational* b) 
{
	result->numer = a->numer * b->denom + b->numer * a->denom;
	result->denom = a->denom * b->denom;

	normalize(result);
}
void rat_sub(Rational* result, Rational* a, Rational* b) 
{
	result->numer = a->numer * b->denom - b->numer * a->denom;
	result->denom = a->denom * b->denom;

	normalize(result);
}
void rat_mul(Rational* result, Rational* a, Rational* b)
{
	result->numer = a->numer * b->numer;
	result->denom = a->denom * b->denom;

	normalize(result);
}
void rat_div(Rational* result, Rational* a, Rational* b) 
{
	result->numer = a->numer * b->denom;
	result->denom = a->denom * b->numer;

	normalize(result);
}
void rat_power(Rational* result, Rational* rat, int n)
{ 
	
	rat->numer = power(rat->numer, n);
	rat->denom = power(rat->denom, n);
	if (n < 0)
	{
		result->numer = rat->denom;
		result->denom = rat->numer;

		normalize(result);
	}
	else
	{
		result->numer = rat->numer;
		result->denom = rat->denom;
	}

	normalize(result);
}

int rat_compare(Rational* a, Rational* b) 
{
	if (a->numer * b->denom > b->numer * a->denom)
	{
		return 1;
	}
	if (a->numer * b->denom < b->numer * a->denom)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int rat_to_int(Rational* a) 
{
	double rat = (double)a->numer / (double)a->denom;

	return (rat >= 0) ? (int)(rat + 0.5) : (int)(rat - 0.5);
}
double rat_to_double(Rational* a)
{
	return (double)a->numer / (double)a->denom;
}

void rat_print(Rational* a, FILE* fp) 
{
	//fprintf(stdout, "%d/%d\n", a->numer, a->denom);
	fprintf(fp, "%d/%d\n", a->numer, a->denom);
}