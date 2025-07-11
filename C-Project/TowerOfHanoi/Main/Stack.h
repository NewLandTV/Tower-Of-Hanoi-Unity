#ifndef __STACK_H__
#define __STACK_H__

#define MAX_STACK_SIZE 3

typedef struct _Stack
{
	unsigned char data[MAX_STACK_SIZE];
	unsigned short count;
} Stack;

const Stack MakeStack();
void Push(Stack* stack, unsigned char value);
unsigned char Pop(Stack* stack);

#endif