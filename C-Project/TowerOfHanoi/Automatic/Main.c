#include <stdio.h>
#include <memory.h>
#include <Windows.h>

#define CONSOLE_WIDTH 40
#define CONSOLE_HEIGHT 10
#define MAX_STACK_SIZE 5
#define SPEED 100

#define Gotoxy(x, y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){ x - 1, y })
#define Wait() Sleep(SPEED)

// Structs
typedef struct _Stack
{
	unsigned char data[MAX_STACK_SIZE];
	unsigned short count;
} Stack;

// Global variables
unsigned char cursorIndex;
unsigned char selectedDisk;
unsigned long long moveCount;

Stack diskStacks[3];

// Functions
const Stack MakeStack();
void Push(Stack* stack, unsigned char value);
unsigned char Pop(Stack* stack);

void Init();
void DrawCursor(unsigned char newCursorIndex);
void DrawDisk();
void MoveCursor(unsigned char to);
void MoveOrSelectDisk();
void Auto(unsigned short number, unsigned short from, unsigned short middle, unsigned short to);

int main(void)
{
	Init();
	Auto(MAX_STACK_SIZE, 0, 1, 2);

	return 0;
}

// Functions
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

void Init()
{
	// Setup console
	system("title Tower of Hanoi - Auto");
	system("mode con cols=40 lines=10");

	// Hide cursor
	CONSOLE_CURSOR_INFO consoleCursorInfo;

	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);

	// Initialize global variables and function calling
	diskStacks[0] = MakeStack();
	diskStacks[1] = MakeStack();
	diskStacks[2] = MakeStack();

	for (unsigned short i = MAX_STACK_SIZE; i > 0; i--)
	{
		Push(&diskStacks[0], i);
	}

	DrawCursor(0);
	DrawDisk();

	Gotoxy(1, 0);

	printf("Move Count : 0");
}

void DrawCursor(unsigned char newCursorIndex)
{
	unsigned short offsetX = CONSOLE_WIDTH >> 2;

	Gotoxy((cursorIndex + 1) * offsetX, 8);

	printf("  ");

	Gotoxy((newCursorIndex + 1) * offsetX, 8);

	printf("бу");

	cursorIndex = newCursorIndex;
}

void DrawDisk()
{
	unsigned short offsetX = CONSOLE_WIDTH >> 2;

	for (unsigned char i = 3; i < 3 + MAX_STACK_SIZE; i++)
	{
		for (unsigned char j = offsetX - 6; j < offsetX * 3 + 6; j++)
		{
			Gotoxy(j, i);

			printf(" ");
		}
	}

	for (unsigned char i = 0; i < 3; i++)
	{
		for (unsigned char j = 0, index = MAX_STACK_SIZE - 1; j < MAX_STACK_SIZE; j++, index--)
		{
			Gotoxy((i + 1) * offsetX, j + 3);

			printf("бс");

			if (diskStacks[i].data[index] == 0)
			{
				continue;
			}

			Gotoxy((i + 1) * offsetX - diskStacks[i].data[index], j + 3);

			for (unsigned char k = 0; k < diskStacks[i].data[index]; k++)
			{
				printf("-");
			}

			printf("бс");

			for (unsigned char k = 0; k < diskStacks[i].data[index]; k++)
			{
				printf("-");
			}
		}
	}
}

void MoveCursor(unsigned char to)
{
	if (to == cursorIndex)
	{
		return;
	}

	if (to > cursorIndex)
	{
		DrawCursor(cursorIndex + 1);

		Wait();

		MoveCursor(to);
	}
	if (to < cursorIndex)
	{
		DrawCursor(cursorIndex - 1);

		Wait();

		MoveCursor(to);
	}
}

void MoveOrSelectDisk()
{
	// Select disk
	if (selectedDisk == 0)
	{
		if (diskStacks[cursorIndex].count == 0)
		{
			return;
		}

		selectedDisk = Pop(&diskStacks[cursorIndex]);

		DrawDisk();

		return;
	}

	// Move disk
	if (diskStacks[cursorIndex].data[diskStacks[cursorIndex].count - 1] != 0 && diskStacks[cursorIndex].data[diskStacks[cursorIndex].count - 1] < selectedDisk)
	{
		return;
	}

	Push(&diskStacks[cursorIndex], selectedDisk);
	DrawDisk();

	selectedDisk = 0;
	
	Gotoxy(1, 0);

	printf("Move Count : %llu", ++moveCount);
}

void Auto(unsigned short number, unsigned short from, unsigned short middle, unsigned short to)
{
	Wait();

	if (number == 1)
	{
		if (cursorIndex != from)
		{
			MoveCursor(from);
		}

		MoveOrSelectDisk();

		Wait();

		MoveCursor(to);
		MoveOrSelectDisk();

		Wait();

		return;
	}

	Auto(number - 1, from, to, middle);

	if (cursorIndex != from)
	{
		MoveCursor(from);
	}

	MoveOrSelectDisk();

	Wait();

	MoveCursor(to);
	MoveOrSelectDisk();
	Auto(number - 1, middle, from, to);
}