#pragma once
#include <stdio.h>
#include <math.h>
#include "pushImage.h"
#include "MouseInput.h"
#include "displayEnding.h"
#include "timeCount.h"

//���콺 �Է��� 2���� ������ ������ �޾ҽ��ϴ�. �ϳ��� ĳ���� �̵��� ���� �Է¹��� ���콺���� �� �����߰�, 
//checkB_�� ���� �� ĳ������ �� ���⸦ ���� �������� ���� ���콺���� �޾ҽ��ϴ�.

extern int WIDTH;
extern int HEIGHT;
extern int backG_imageX;
extern int backG_imageY;
extern int backG_imageZ;
extern int backG_imageR;
extern int checkB_imageX;
extern int checkB_imageY;
extern int checkB_imageZ;
extern int checkB_imageR;

int flag = 0;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int cnt = 0;
int cnt1 = 0;
int cnt2 = 0;
int clearEnding = 0;
int roomNum = 0;

double nowX = 1800; //�̹��� ���� x��ǥ
double nowY = 810;  //�̹��� ���� y��ǥ
double checkB_nowX = 0, checkB_nowY = 0;

char mainRoom1[30] = "mainRoom1.bmp";
char mainRoom2[30] = "mainRoom2.bmp";
char mainRoom3[30] = "mainRoom3.bmp";
char imageFront[30] = "characterFront.bmp";
char imageBack[30] = "characterBack.bmp";
char imageRight[30] = "characterRight.bmp";
char imageLeft[30] = "characterLeft.bmp";

extern char timerShow[6]; //���� ���� �ð� ���ڿ�
extern int isTiming; // �ð��� ��� �ִ°�
extern int currentTime; //���� ���� �ð�
/*
moveImage �Լ� ����:
���콺 �������� ��ǥ���� �޾� �� ��ġ�� ĳ���͸� �̵���Ű��,
�߰��� �ٽ� ���콺 �Է��� �ִٸ� �ٽ� �Էµ� ��ġ�� ĳ���͸� �̵���Ű�� �Լ��Դϴ�.
ĳ���Ͱ� ���� �������� �ϸ�, �� �ൿ�� �����ϴ�.
����, ���ѽð��� 5���� ���� ���� �����ݴϴ�.
�ð� ������ ���� ���̺긦 �� ���� �����ϵ��� �Ͽ����ϴ�.
����� �ִ� ����ⱸ�� ���� �ִ� Ź�� ���� �ݰ� �տ� ����, �ܼ��� ���� �� �ֵ��� �Ͽ����ϴ�.
ù��°�� �ι�° �濡���� �ܼ��� ���� ���� �� �ܼ��� ���� �˰� �� ��й�ȣ�� �Է��ϸ� ���� ���������� �Ѿ���� �Ͽ���,
�ڷΰ���(back)�� ���� b�Ǵ� B��ư�� ������ �ܼ��� ���������� �Ͽ����ϴ�.
�繰���� �߰��� �� �ִ� ����̳� �� ���� �ܼ��� ���� ǥ���Ͽ� ��й�ȣ�� �� �� �ֵ��� �Ͽ����ϴ�.
�����Ե� �ѹ� �غ��ø� ���� �� �����ϴ�. 
������ �ſ� ������ ��й�ȣ�� ������ ��� �����ôٸ� 1404�����, 1407�����쿡�� �� �ֽø� ģ���ϰ� �����ص帮�ڽ��ϴ�.
������ �濡��, ĳ���Ͱ� �� �տ� ����, ���� ������ �����ϵ��� �Ͽ����ϴ�.
���� ���� ������ �����ִ� �Լ��� ȣ���մϴ�.
*/


void moveImage(int saveNum, int saveCurTime) {
	roomNum = saveNum;
	ImageLayer layer = DEFAULT_IMAGE_LAYER;
	layer.initialize(&layer);
	layer.imageCount = 2;

	Image images[2] = {
	   {mainRoom1, WIDTH * 5.1, HEIGHT * 2, 3} ,
	   {imageFront, nowX, nowY, 1}
	};
	layer.images = images;
	if (roomNum == 1)
		layer.images->fileName = mainRoom1;
	else if (roomNum == 2)
		layer.images->fileName = mainRoom2;
	else if (roomNum == 3)
		layer.images->fileName = mainRoom3;
	layer.renderAll(&layer);
	enableMouseInput();
	double speed_penguin = 5;

	int penguinDestX = nowX, penguinDestY = nowY;
	int checkB_DestX = 0, checkB_DestY = 0;
	double x_move = 0, y_move = 0;
	double checkB_x_move = 0, checkB_y_move = 0;
	while (1) {
		if (isTiming) processTime();
		gotoxy(0, 0);
		printf("%s", timerShow);
		if (currentTime == 0)
		{
			stopTime();
			flag3 = 1;
			break;
		}
		if (hasInput() && isMouseClicked() == 2) {

			COORD pos = getMousePosition();

			penguinDestX = pos.X * 0.9;
			penguinDestY = pos.Y * 0.8;
			checkB_DestX = pos.X;
			checkB_DestY = pos.Y;

			if (penguinDestX == layer.images[1].x && penguinDestY == layer.images[1].y) break;
			nowX = layer.images[1].x;
			nowY = layer.images[1].y;
			checkB_nowX = layer.images[1].x;
			checkB_nowY = layer.images[1].y;

			double dis = sqrt(pow(pos.X * 0.9 - layer.images[1].x, 2) + pow(pos.Y * 0.8 - layer.images[1].y, 2));
			double checkB_dis = sqrt(pow(pos.X - layer.images[1].x, 2) + pow(pos.Y - layer.images[1].y, 2));

			x_move = (double)(pos.X * 0.9 - layer.images[1].x) / dis * speed_penguin;
			y_move = (double)(pos.Y * 0.8 - layer.images[1].y) / dis * speed_penguin;
			checkB_x_move = (double)(pos.X - layer.images[1].x) / checkB_dis * speed_penguin;
			checkB_y_move = (double)(pos.Y - layer.images[1].y) / checkB_dis * speed_penguin;
		}
		while (penguinDestX != layer.images[1].x || penguinDestY != layer.images[1].y)
		{
			if (isTiming) processTime();
			gotoxy(0, 0);
			printf("%s", timerShow);
			if (currentTime == 0)
			{
				stopTime();
				flag3 = 1;
				break;
			}
			if (1630 <= checkB_imageX + 50 && checkB_imageX + 50 <= 1820 && 580 <= checkB_imageY + 50 && checkB_imageY + 50 <= 600 && roomNum == 3)
			{
				if (flag == 0 && cnt == 0)
				{
					flag = 1;
					break;
				}
			}
			else cnt = 0;
			
			if (1855 <= checkB_imageX + 50 && checkB_imageX + 50 <= 2045 && 580 <= checkB_imageY + 50 && checkB_imageY + 50 <= 600)
			{
				if (flag1 == 0 && cnt1 == 0)
				{
					flag1 = 1;
					break;
				}
			}
			else cnt1 = 0;
			if (1288 <= checkB_imageX && checkB_imageX <= 1436 && 844 <= checkB_imageY && checkB_imageY <= 900 && cnt == 0)
			{
				if (flag2 == 0 && cnt2 == 0)
				{
					flag2 = 1;
					break;
				}
			}
			else cnt2 = 0;

			if (hasInput() && isMouseClicked() == 2) {
				COORD pos = getMousePosition();

				penguinDestX = pos.X * 0.9;
				penguinDestY = pos.Y * 0.8;
				checkB_DestX = pos.X;
				checkB_DestY = pos.Y;

				if (penguinDestX == layer.images[1].x && penguinDestY == layer.images[1].y) break;


				nowX = layer.images[1].x;
				nowY = layer.images[1].y;

				checkB_nowX = layer.images[1].x;
				checkB_nowY = layer.images[1].y;

				double dis = sqrt(pow(pos.X * 0.9 - layer.images[1].x, 2) + pow(pos.Y * 0.8 - layer.images[1].y, 2));
				double checkB_dis = sqrt(pow(pos.X - layer.images[1].x, 2) + pow(pos.Y - layer.images[1].y, 2));

				x_move = (double)(pos.X * 0.9 - layer.images[1].x) / dis * speed_penguin;
				y_move = (double)(pos.Y * 0.8 - layer.images[1].y) / dis * speed_penguin;
				checkB_x_move = (double)(pos.X - layer.images[1].x) / checkB_dis * speed_penguin;
				checkB_y_move = (double)(pos.Y - layer.images[1].y) / checkB_dis * speed_penguin;
			}
			if (abs(penguinDestX - layer.images[1].x) > abs(penguinDestY - layer.images[1].y))
			{
				if ((penguinDestX - layer.images[1].x) > 0)
				{
					layer.images[1].fileName = imageLeft;
					layer.renderAll(&layer);
				}
				else
				{
					layer.images[1].fileName = imageRight;
					layer.renderAll(&layer);
				}
			}
			else if (abs(penguinDestX - layer.images[1].x) < abs(penguinDestY - layer.images[1].y))
			{
				if ((penguinDestY - layer.images[1].y) > 0)
				{
					layer.images[1].fileName = imageFront;
					layer.renderAll(&layer);
				}
				else
				{
					layer.images[1].fileName = imageBack;
					layer.renderAll(&layer);
				}
			}

			if (!(backG_imageX < (int)(checkB_nowX + checkB_x_move) && (int)(checkB_nowX + checkB_x_move ) + 132 < backG_imageZ
				&& backG_imageY < (int)(checkB_nowY + checkB_y_move) && (int)(checkB_nowY + checkB_y_move) + 145 < backG_imageR))
			{
				if (backG_imageX >= (int)(checkB_nowX + checkB_x_move)) layer.images[1].x++;
				if (backG_imageZ <= (int)(checkB_nowX + checkB_x_move) + 132) layer.images[1].x--;
				if (backG_imageY >= (int)(checkB_nowY + checkB_y_move)) layer.images[1].y = backG_imageY++;
				if (backG_imageR <= (int)(checkB_nowY + checkB_y_move) + 145) layer.images[1].y = backG_imageR--;

				penguinDestX = layer.images[1].x;
				penguinDestY = layer.images[1].y;
				checkB_DestX = layer.images[1].x;
				checkB_DestY = layer.images[1].y;

				nowX = layer.images[1].x;
				nowY = layer.images[1].y;
				checkB_nowX = layer.images[1].x;
				checkB_nowY = layer.images[1].y;
				break;
			}
			nowX += x_move;
			nowY += y_move;
			checkB_nowX += checkB_x_move;
			checkB_nowY += checkB_y_move;
			layer.images[1].x = (int)nowX;
			layer.images[1].y = (int)nowY;
			checkB_imageX = (int)checkB_nowX;
			checkB_imageY = (int)checkB_nowY;
			checkB_imageZ = checkB_imageX + 132;
			checkB_imageR = checkB_imageY + 145;
			layer.renderAll(&layer);

			double nextX = nowX + x_move, nextY = nowY + y_move;
			if (
				((nowX <= penguinDestX && penguinDestX < nextX) || (nowX >= penguinDestX && penguinDestX > nextX))
				|| ((nowY <= penguinDestY && penguinDestY < nextY) || (nowY >= penguinDestY && penguinDestY > nextY))
				) {
				nowX = penguinDestX;
				nowY = penguinDestY;
				checkB_nowX = checkB_DestX;
				checkB_nowY = checkB_DestY;

				layer.images[1].x = (int)nowX;
				layer.images[1].y = (int)nowY;
				checkB_imageX = (int)checkB_nowX;
				checkB_imageY = (int)checkB_nowY;
				checkB_imageZ = checkB_imageX + 132;
				checkB_imageR = checkB_imageY + 145;
				layer.renderAll(&layer);
				break;
			}
		}
		if ((flag == 1 && cnt == 0) || (flag1 == 1 && cnt1 == 0) || (flag2 == 1 && cnt2==0) || flag3 == 1)
				break;
	}
	if (flag3 == 1)
	{
		Sleep(50);
		clearEnding = 0;
		system("cls");
		displayEnding();
		return;
	}
	if (flag == 1) //��
	{
		Sleep(30);
		pushImage("door1.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
		Sleep(20);
		pushImage("door2.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
		int input = 0;
		while (input != 'Y' || input != 'y' || input != 'N' || input != 'n')
		{
			input = _getch();
			if (input == 'Y' || input == 'y')
			{
			R_SOLVE:
				Sleep(20);
				pushImage("door3.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
				int a, b, c, d;
				a = _getch();
				b = _getch();
				c = _getch();
				d = _getch();
				if (a == '1' && b == '0' && c == '0' && d == '3')
				{
					clearEnding = 1;
					displayEnding();
					break;
				}
				else if (a == 'B' || a == 'b')
				{
					flag = 0;
					cnt = 1;
					Sleep(20);
					moveImage(3, currentTime);
				}
				else
				{
					Sleep(20);
					pushImage("door4.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
					int solveTry = 0;
					while (solveTry != 'Y' || solveTry != 'y' || solveTry != 'N' || solveTry == 'n')
					{
						solveTry = _getch();
						if (solveTry == 'Y' || solveTry == 'y')
						{
							goto R_SOLVE;
						}
						else if (solveTry == 'N' || solveTry == 'n')
						{
							flag = 0;
							cnt = 1;
							Sleep(20);
							moveImage(3, currentTime);
						}
					}
				}
				goto R_SOLVE;
			}
			else if (input == 'N' || input == 'n')
			{
				flag = 0;
				cnt = 1;
				Sleep(20);
				moveImage(3, currentTime);
			}
		}
	}
	if (flag1 == 1)//�ð�
	{
		Sleep(30);
		if(roomNum == 1)
			pushImage("clock1.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
		else if(roomNum == 2)
			pushImage("clock2.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
		else if (roomNum == 3)
			pushImage("clock3.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
		int input = 0;
		while (input != 'Y' || input != 'y' || input != 'N' || input != 'n')
		{
			input = _getch();
			if (input == 'Y' || input == 'y')
			{
				pushSavefile(roomNum, currentTime);
				flag1 = 0;
				cnt1 = 1;
				Sleep(20);
				moveImage(roomNum, currentTime);
			}
			else if (input == 'N' || input == 'n')
			{
				flag1 = 0;
				cnt1 = 1;
				Sleep(20);
				moveImage(roomNum, currentTime);
			}
		}
	}
	if (flag2 == 1) //����Ʈ
	{
		int tryQuest = 0;
	R_RETRY:
		tryQuest = 0;
		Sleep(30);
		while (1)
		{
			if(roomNum == 1)
				pushImage("solve1.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
			else if(roomNum == 2)
				pushImage("solve2.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
			else if (roomNum == 3)
				pushImage("solve3.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
			if (_kbhit && roomNum == 3)
			{
				tryQuest = 1;
				break;
			}
			if (_kbhit && roomNum != 3)
			{
				tryQuest = 1;
				if (roomNum == 1)
					pushImage("solve1.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
				else if (roomNum == 2)
					pushImage("solve2.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
				else if (roomNum == 3)
					pushImage("solve3.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
				break;
			}
		}
		if (tryQuest == 1 && roomNum == 3)
		{
			int a;
		R_WRONG:
			a = _getch();
			if (a == 'B' || a == 'b')
			{
				flag2 = 0;
				cnt2 = 1;
				moveImage(roomNum, currentTime);
			}
			else goto R_WRONG;
		}
		if (tryQuest == 1)
		{
			Sleep(20);
			int a, b, c, d;
			a = _getch();
			if (a == 'B' || a == 'b')
			{
				flag2 = 0;
				cnt2 = 1;
				moveImage(roomNum, currentTime);
			}
			b = _getch();
			c = _getch();
			d = _getch();
			if (roomNum == 1)
			{
				if (a == '3' && b == '1' && c == '2' && d == '2')
				{
					roomNum++;
					layer.images->fileName = mainRoom2;
					flag2 = 0;
					cnt2 = 1;
					moveImage(roomNum, currentTime);
				}
				else
				{
					Sleep(20);
					if (roomNum == 1)
						pushImage("wrongSolve1.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
					else if (roomNum == 2)
						pushImage("wrongSolve2.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
					Sleep(500);
					tryQuest = 0;
					goto R_RETRY;
				}
			}
			else if (roomNum == 2)
			{
				if (a == '6' && b == '8' && c == '2' && d == '2')
				{
					roomNum++;
					layer.images->fileName = mainRoom3;
					flag2 = 0;
					cnt2 = 1;
					moveImage(roomNum, currentTime);
				}
				else
				{
					Sleep(20);
					if (roomNum == 1)
						pushImage("wrongSolve1.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
					else if (roomNum == 2)
						pushImage("wrongSolve2.bmp", WIDTH * 5.1, HEIGHT * 2, 3);
					Sleep(500);
					tryQuest = 0;
					goto R_RETRY;
				}
			}
		}
		flag2 = 0;
		cnt2 = 1;
		moveImage(roomNum, currentTime);
	}

}