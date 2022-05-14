#pragma once

#define INIT_SIZE 20

typedef void* Pointer;

typedef struct tStack
{
	size_t len;
	size_t capacity;//емкость
	Pointer* data;

} Stack;

void* stack_create(void);
void stack_destroy(Stack* pstack);
void stack_push(Stack* pstack, Pointer value);

size_t stack_size(Stack* pstack);
Pointer stack_pop(Stack* pstack);
Pointer stack_peek(Stack* pstack);