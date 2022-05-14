#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <math.h>

bool check_increase_capacity(Stack* stack, int increase, int power)
{
	if (stack->capacity == INIT_SIZE * pow(increase, power))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool check_decrease_capacity(Stack* stack, int increase, int new_power, int old_power)
{
	if (stack->capacity == (INIT_SIZE * (int)pow(increase, old_power)) / (int)pow(increase, new_power))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	Stack stack;
	int count = -1;
	stack_create(&stack);
	int arr[100];
	for (int i = 0; i < 100; i++)//int test
	{
		arr[i] = i + 1;
	}
	for (int i = 0; i < 100; i++)
	{
		if ((&stack)->capacity == (&stack)->len)
		{
			count++;
		}
		assert(stack_size(&stack) == i);
		stack_push(&stack, &arr[i]);
		assert(stack.capacity >= 0);
		assert(check_increase_capacity(&stack, 3, count));
	}
	for (int i = 0; i < 100; i++)//reversing array
	{
		arr[i] = 100 - i;
	}
	int new_count = 0;
	for (int i = 0; i < 100; i++)
	{
		if ((&stack)->capacity >= 6 * (&stack)->len)
		{
			new_count++;
		}
		assert(stack.capacity >= 0);
		assert(stack_size(&stack) == 100 - i);
		assert(stack_peek(&stack) == &arr[99 - i]);
		assert(stack_pop(&stack) == &arr[99 - i]);
		assert(check_decrease_capacity(&stack, 3, new_count, count));
	}

	stack_destroy(&stack);



	stack_create(&stack);
	double arr1[100];
	count = -1;
	for (int i = 0; i < 100; i++)//double test
	{
		double j = i + 0.754;
		arr1[i] = j;

	}
	for (int i = 0; i < 100; i++)
	{
		if ((&stack)->capacity == (&stack)->len)
		{
			count++;
		}
		assert(stack.capacity >= 0);
		assert(stack_size(&stack) == i);
		stack_push(&stack, &arr1[i]);
		assert(check_increase_capacity(&stack, 3, count));
	}

	for (int i = 99; i >= 0; i--)//reversing array
	{
		double j = i + 0.754;
		arr1[i] = j;
	}
	new_count = 0;
	for (int i = 0; i < 100; i++)
	{
		if ((&stack)->capacity >= 6 * (&stack)->len)
		{
			new_count++;
		}
		assert(stack.capacity >= 0);
		assert(stack_size(&stack) == 100 - i);
		assert(stack_peek(&stack) == &arr1[99 - i]);
		assert(stack_pop(&stack) == &arr1[99 - i]);
		assert(check_decrease_capacity(&stack, 3, new_count, count));
	}

	stack_destroy(&stack);
	//пустой стак
	stack_create(&stack);
	assert(stack_pop(&stack) == NULL);
	assert(stack_peek(&stack) == NULL);
	assert(stack_size(&stack) == 0);
	stack_destroy(&stack);
	//краевые случаи
	stack_destroy(&stack);
	// 1-ый случай-размер задаваего массива совпадает с INIT_SIZE => должны увидеть увелидение capacity
	int arr2[20];
	int count2 = -1;
	for (int i = 0; i < 20; i++)
	{
		arr2[i] = i + 1;
	}
	for (int i = 0; i < 20; i++)
	{
		if ((&stack)->capacity == (&stack)->len)
		{
			count2++;
		}
		assert(stack_size(&stack) == i);
		stack_push(&stack, &arr2[i]);
		assert(stack.capacity >= 0);
		assert(check_increase_capacity(&stack, 3, count2));
	}
	
	stack_destroy(&stack);

	assert(_CrtDumpMemoryLeaks() == 0);
	return 0;
}