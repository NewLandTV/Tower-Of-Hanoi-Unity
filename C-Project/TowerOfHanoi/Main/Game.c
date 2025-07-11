#include <stdio.h>
#include "Game.h"
#include "Input.h"
#include "Stack.h"

// Global variables
unsigned char cursorIndex;
unsigned char selectedDisk;

Stack diskStacks[3];

// Functions
void Init()
{
	// Setup console
	system("title Tower of Hanoi");
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

	Push(&diskStacks[0], 3);
	Push(&diskStacks[0], 2);
	Push(&diskStacks[0], 1);
	DrawCursor(0);
	DrawDisk();
}

void Update()
{
	MoveCursor();
	MoveDisk();
	Sleep(50);
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

	for (unsigned char i = 3; i < 6; i++)
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

void MoveCursor()
{
	if (GetKey(KC_LeftArrow) && cursorIndex - 1 >= 0)
	{
		DrawCursor(cursorIndex - 1);
	}
	if (GetKey(KC_RightArrow) && cursorIndex + 1 < 3)
	{
		DrawCursor(cursorIndex + 1);
	}
}

void MoveDisk()
{
	if (GetKey(KC_Return))
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
	}
}