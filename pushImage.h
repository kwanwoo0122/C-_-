#pragma once
#include <stdio.h>
#include "ImageLayer.h"

void pushImage(char *imageName, double x, double y, double scale) { // �̹��� ����ϴ� �Լ�
	Sleep(500);

	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ

	Image images[2] = {

		{imageName, x, y, scale}, //{�̹��� �̸�, ���� x��ǥ, ���� y��ǥ, ũ�� ����(���� ������ �⺻���� 16�� ��)} 
		//{"characterFront.bmp", 800, 92, 1} //���ڿ� �տ�  L�� �� �ٿ���� �Ѵ�.
		//{L"sample.bmp", 200, 200}
	}; //�迭�� ù ���Ұ� ���� �Ʒ� �׷�����.

	imageLayer.imageCount = 2; //images �迭�� ũ�⺸�� �۰ų� ���ƾ� �Ѵ�.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}