#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>

Stack* stack_create()
{
	Stack* pstack = (Stack*)malloc(sizeof(Stack));
	if (pstack == NULL) {
		return NULL;
	}
	pstack->len = 0;
	pstack->capacity = 0;
	pstack->data = NULL;

	return pstack;

}

void stack_destroy(Stack* pstack)
{
	free(pstack->data);
}

void stack_push(Stack* pstack, Pointer value)
{
	if (pstack->capacity == 0)
	{
		size_t new_size = INIT_SIZE;
		pstack->data = malloc(new_size * sizeof(Pointer));

		if (pstack->data == NULL)
		{
			return;
		}
		else
		{
			pstack->capacity = new_size;
		}
	}

	if(pstack->len == pstack->capacity)
	{
		size_t new_capacity = pstack->capacity * 3;
		Pointer* new_data = malloc(new_capacity * sizeof(Pointer));

		if (new_data == NULL)
		{
			return;
		}
		memcpy(new_data, pstack->data, pstack->len * sizeof(Pointer));
		free(pstack->data);  

		pstack->data = new_data;
		pstack->capacity = new_capacity;
	}

	assert(pstack->len < pstack->capacity);
	pstack->data[pstack->len] = value;
	pstack->len++;
}

size_t stack_size(Stack* pstack)
{
	assert(pstack->len <= pstack->capacity);
	return pstack->len;
}
 
Pointer stack_pop(Stack* pstack)
{
	assert(pstack->len <= pstack->capacity);
	if (pstack->len != 0)
	{
		if (pstack->capacity >= 6 * pstack->len)
		{
			size_t new_capacity = pstack->capacity / 3;
			Pointer *new_data = malloc(new_capacity * sizeof(Pointer));
			if (new_data == NULL)
			{
				return NULL;
			}
			memcpy(new_data, pstack->data, pstack->len * sizeof(Pointer));
			free(pstack->data);

			pstack->data = new_data;
			pstack->capacity = new_capacity;
			
		}
		pstack->len--;
		return pstack->data[pstack->len];
	}
	else
	{
		return 0;
	}
}

Pointer stack_peek(Stack* pstack)
{
	assert(pstack->len <= pstack->capacity);
	if (pstack->len != 0)
	{
		return pstack->data[pstack->len - 1];
	}
	else
	{
		return 0;
	}
}