#pragma once
#include <stdio.h>
#include "console.h"
#include "pushImage.h"
#include "MouseInput.h"

extern int WIDTH, HEIGHT;
extern int saveRoom;
extern int saveCurTime;

int saveFile;
int saveTime;

void loadSavefile() // ���̺����� �ҷ����� �Լ�
{
	FILE* sf1, *sf2;
	sf1 = fopen("���̺�����1.txt", "r");
	fscanf(sf1, "%d", &saveFile);
	fclose(sf1);
	sf2 = fopen("���̺�����2.txt", "r");
	fscanf(sf2, "%d", &saveTime);
	fclose(sf2);
	saveRoom = saveFile;
	saveCurTime = saveTime;
	enableMouseInput();
	if (saveRoom == 1 && saveCurTime == 300)
	{
		while (!(isMouseClicked() == 1))
		{
			pushImage("emptySavefile.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
		}
		startGame(1, 300);
	}
	else
	{
		while (!(isMouseClicked() == 1))
		{
			pushImage("loadSavefile.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
		}
	}
}