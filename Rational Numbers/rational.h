#ifndef RATIONAL_H
#define RATIONAL_H
#include <stdio.h>

typedef struct _Rational
{
	int numer;
	int denom;

} Rational;

void rat_create(Rational* res, int a, int b);

void rat_add(Rational* result, Rational* a, Rational* b);
void rat_sub(Rational* result, Rational* a, Rational* b);
void rat_mul(Rational* result, Rational* a, Rational* b);
void rat_div(Rational* result, Rational* a, Rational* b);

void rat_power(Rational* result, Rational* r, int n);

int rat_to_int(Rational *a);
double rat_to_double(Rational* a);

int rat_compare(Rational *a, Rational* b);
void rat_print(Rational* a, FILE* fp);

#endif
