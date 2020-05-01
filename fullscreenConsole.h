#pragma once
#include <stdio.h>
#include <Windows.h>

COORD bufSize;

void fullscreenConsole() { // �ܼ�â ȭ�� �ִ������ ���� �Լ�
	system("cls");

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(hCon, CONSOLE_FULLSCREEN_MODE, NULL);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hCon, &info); // �ܼ�â�� ������ ���´�.

	

	//�ܼ�â�� �ִ� ����� �޾ƿ´�.
	bufSize.X = info.dwMaximumWindowSize.X;
	bufSize.Y = info.dwMaximumWindowSize.Y;

	int ret = 0;

	//�ܼ�â�� ����� �ٲ��ش�.
	ret = SetConsoleScreenBufferSize(hCon, bufSize);

	if (ret == 0) //�����ϸ� �����Ѵ�.
		abort();
}