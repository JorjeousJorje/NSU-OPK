#include <stdio.h>
#include <assert.h>
#include <math.h>

double poly_sum(double x, double a[], int n)
{
		double s = a[n];
		for (int i = 0; i <= n; i++)
		{
			s *= x;
			s += a[n - i];
		}
		return s;
}

int main() 
{
	double a[6] = { 78.1, 2, 1, -45, 123 };
	printf("%g\n", poly_sum(1.2, a, 5));
	return 0;
}