#pragma once
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "console.h"
#include "pushImage.h"
#include "MouseInput.h"
#include "startGame.h"
#include "howToGame.h"
#include "continueGame.h"

extern int WIDTH;
extern int HEIGHT;

char startPage[30] = "startPage.bmp";

#pragma comment(lib,"winmm.lib")

void displayStartPage() // �̾��ϱ�, �����ϱ�, ���Ӽ����� ����ְ�, ����ڰ� ������ ���� �����Ű�� �Լ�
{
	PlaySound(TEXT("invertMusic.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	int input;
	gotoxy(WIDTH / 2 - 4, HEIGHT / 2 - 10);
	printf("�̾��ϱ� [1]");
	Sleep(10);
	gotoxy(WIDTH / 2 - 4, HEIGHT / 2);
	printf("�����ϱ� [2]");
	Sleep(10);
	gotoxy(WIDTH / 2 - 4, HEIGHT / 2 + 10);
	printf("���Ӽ��� [3]");
	Sleep(10);
	input = _getch();
	if (input == '1' || input == '2' || input == '3')
	{
		if (input == '1')
		{
			system("cls");
			continueGame();
			displayStartPage();
		}
		else if (input == '2')
		{
			system("cls");
			startGame(1, 300);
			displayStartPage();
		}
		else if (input == '3')
		{
			system("cls");
			howToGame();
			displayStartPage();
		}
	}
	else
		displayStartPage();
}

void displayStart() // '����� ����'������ ���̴� ó�� ��ŸƮ ȭ���� �����ִ� �Լ�
{
	PlaySound(TEXT("startMusic.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	enableMouseInput();
	while (!(isMouseClicked() == 1))
	{
		pushImage(startPage, WIDTH * 5.1, HEIGHT * 2, 3);

	}

	system("cls");
	PlaySound(NULL, 0, 0);
	Sleep(10);
	displayStartPage();
}


