#pragma once
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "console.h"

int currentTime;
int isTiming = 0; // 0 ���� 1 �簳
int pTime;
char timerShow[6];

void startTime(int time) // �ð��� �Ű������� �����Ͽ� �� �ð� ��ŭ Ÿ�̸Ӹ� ���� �� �����ϴ� �Լ�
{
	currentTime = time;
	isTiming = 1;
}

void stopTime() // Ÿ�̸Ӹ� ���ߴ� �Լ�
{
	isTiming = 0;
}

void processTime() // ����� ���� �ð��� �����Ͽ� Ÿ�̸��� �ð��� ���̴� �Լ�
{
	int cTime;
	cTime = (int)time(NULL) % 60;
	if (pTime != cTime) currentTime--;
	pTime = cTime;
	sprintf(timerShow, "%02d:%02d", currentTime / 60, currentTime % 60);
}