#include <memory.h>
#include "Stack.h"

const Stack MakeStack()
{
	Stack stack;

	memset(stack.data, 0, MAX_STACK_SIZE);

	stack.count = 0;

	return stack;
}

void Push(Stack* stack, unsigned char value)
{
	if (stack->count >= MAX_STACK_SIZE)
	{
		return;
	}

	stack->data[stack->count++] = value;
}

unsigned char Pop(Stack* stack)
{
	if (stack->count == 0)
	{
		return 0;
	}

	unsigned char value = stack->data[--stack->count];
	
	stack->data[stack->count] = 0;

	return value;
}