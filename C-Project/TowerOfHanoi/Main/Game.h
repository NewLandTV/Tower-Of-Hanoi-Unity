#ifndef __GAME_H__
#define __GAME_H__

#include <Windows.h>

#define CONSOLE_WIDTH 40
#define CONSOLE_HEIGHT 10

#define Gotoxy(x, y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){ x - 1, y });

void Init();
void Update();

void DrawCursor(unsigned char newCursorIndex);
void DrawDisk();
void MoveCursor();
void MoveDisk();

#endif