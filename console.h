#pragma once
#include <stdio.h>
#include <windows.h>
#include "fullscreenConsole.h"

extern int WIDTH;
extern int HEIGHT;

void gotoxy(int x, int y) // ��ǥ�̵� �Լ�, gotoxy
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clearCursor() //Ŀ�� ����
{
	CONSOLE_CURSOR_INFO c;
	c.bVisible = FALSE;
	c.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

void backgroundSetting() //�⺻ ����
{
	fullscreenConsole();
	WIDTH = bufSize.X;
	HEIGHT = bufSize.Y;
	clearCursor();
}