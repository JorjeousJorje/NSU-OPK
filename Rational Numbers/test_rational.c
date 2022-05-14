#define _CRT_SECURE_NO_WARNINGS
#include "rational.h"
#include <stdbool.h>
#include <assert.h>

int compare_test(int a_num, int a_den, int b_num, int b_den) {
	Rational a, b;
	rat_create(&a, a_num, a_den);
	rat_create(&b, b_num, b_den);

	return rat_compare(&a, &b);
}

bool arithmetic_test(int a_num, int a_den, int b_num, int b_den, int true_res_num, int true_res_den, void operation(Rational*, Rational*, Rational*)) 
{
	Rational a, b, res, true_res;

	rat_create(&a, a_num, a_den);
	rat_create(&b, b_num, b_den);

	operation(&res, &a, &b);

	rat_create(&true_res, true_res_num, true_res_den);

	if (rat_compare(&res, &true_res) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool power_test(int a_num, int a_den, int true_res_num, int true_res_den, int power)
{
	Rational a, res, true_res;

	rat_create(&a, a_num, a_den);
	rat_power(&res, &a, power);

	rat_create(&true_res, true_res_num, true_res_den);

	if (rat_compare(&res, &true_res) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool int_test(int a, int b, int true_res) 
{
	Rational r;
	rat_create(&r, a, b);
	if (rat_to_int(&r) == true_res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool double_test(int a, int b, double true_res)
{
	Rational r;
	rat_create(&r, a, b);
	if (rat_to_double(&r) == true_res)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool file_test(int a, int b)
{
	Rational res;
	FILE* fp = fopen("output.txt", "w");
	if (fp == NULL)
	{
		printf("File doesn't open!\n");
		return false;
	}
	rat_create(&res, a, b);
	rat_print(&res, fp);

	fclose(fp);
	return true;
}

int main() 
{

	assert(compare_test(3, 2, 2, 3) == 1);
	assert(compare_test(4, 8, 2, 3) == -1);
	assert(compare_test(4, 8, 10001, 20002) == 0);
	assert(compare_test(5, -8, -5, 8) == 0);
	assert(compare_test(5, -8, 5, 8) == -1);
	assert(compare_test(5, 1, 5, 8) == 1);// test for 0

	assert(arithmetic_test(3, 2, 2, 3, 13, 6, rat_add));
	assert(arithmetic_test(-3, 2, 2, 3, -5, 6, rat_add));
	assert(arithmetic_test(0, -2, 2, 3, 2, 3, rat_add));
	assert(arithmetic_test(0, -2, 2, 3, 2, 3, rat_add));
	assert(arithmetic_test(-3, -2, -2, -3, 13, 6, rat_add));
	assert(arithmetic_test(2, -3, -3, 5, -19, 15, rat_add));

	assert(arithmetic_test(3, 2, 2, 3, 5, 6, rat_sub));
	assert(arithmetic_test(3, -2, 2, -3, -5, 6, rat_sub));
	assert(arithmetic_test(55, 999, -1, 2, 1109, 1998, rat_sub));
	assert(arithmetic_test(3, -2, -2, -3, -13, 6, rat_sub));
	assert(arithmetic_test(0, 2, 2, -3, 2, 3, rat_sub));

	assert(arithmetic_test(3, 2, 2, 3, 1, 1, rat_mul));
	assert(arithmetic_test(-3, 2, 2, 3, -1, 1, rat_mul));
	assert(arithmetic_test(3, 2, 2, -3, -1, 1, rat_mul));
	assert(arithmetic_test(-3, -2, -2, -3, 1, 1, rat_mul));
	assert(arithmetic_test(0, 2, 2, 3, 0, 1, rat_mul));

	assert(arithmetic_test(3, 2, 2, 3, 9, 4, rat_div));
	assert(arithmetic_test(-3, 2, -2, 3, 9, 4, rat_div));
	assert(arithmetic_test(-3, 2, -2, -3, 9, -4, rat_div));
	assert(arithmetic_test(-3, -2, -2, -3, 9, 4, rat_div));
	assert(arithmetic_test(0, 2, 2, 3, 0, 1, rat_div));

	assert(power_test(3, 2, 27, 8, 3));
	assert(power_test(-3, 2, 4, 9, -2));
	assert(power_test(-3, 2, 9, 4, 2));
	assert(power_test(11, -5, 14641, 625, 4));
	assert(power_test(-3, 2, -2, 3, -1));

	assert(int_test(3, 2, 2));
	assert(int_test(-3, 2, -2));
	assert(int_test(11, 4, 3));
	assert(int_test(-123, 9, -14));
	assert(int_test(0, 11, 0));

	assert(double_test(3, 2, (double)3 / 2));
	assert(double_test(-3, 2, (double)-3 / 2));
	assert(double_test(11, 4, (double)11 / 4));
	assert(double_test(-123, 9, (double)-123 / 9));
	assert(double_test(0, 11, 0));

	assert(file_test(2, 6));

	Rational a, b, w, k;
	rat_create(&a, 2, -3);
	rat_create(&b, -3, 5);
	rat_create(&w, 3, 5);
	rat_create(&k, 3, -5);
	assert(rat_compare(&a, &b) == -1);
	assert(rat_compare(&w, &k) == 1);

	rat_create(&a, -2, -3);
	rat_print(&a, stdout);
	
	return 0;
}