/*
민승현의 이미지 레이어를 사용하였습니다.
*/
#pragma once
#pragma comment (lib, "Msimg32.lib")
#include <Windows.h>
#include "ImageLayer.h"

#define CONSOLE_WIDTH 200
#define CONSOLE_HEIGHT 70

#define DEFAULT_RESOLUTION_SCALE 16
double RESOLUTION_MULTIPLIER = 1;
int WINDOW_WIDTH = 0;
int WINDOW_HEIGHT = 0;

typedef struct {
	int width, height;
}Size;

inline int getDPI(HWND hWnd) { //화면의 dpi값을 반환
	const HANDLE user32 = GetModuleHandle(TEXT("user32"));
	const FARPROC func = GetProcAddress(user32, "GetDpiForWindow");
	if (func == NULL)
		return 96;
	return ((UINT(__stdcall*)(HWND))func)(hWnd);
}

inline Size getBitmapSize(HBITMAP bitmap) {//비트맵의 크기를 반환
	BITMAP tmpBitmap;
	GetObject(bitmap, sizeof(BITMAP), &tmpBitmap);
	const Size bitmapSize = { tmpBitmap.bmWidth, tmpBitmap.bmHeight };
	return bitmapSize;
}

inline HDC createNewBackDC(HDC compatibleDC) { //검정색의 새DC를 반환
	const HDC backDC = CreateCompatibleDC(compatibleDC);
	const HBITMAP backBitmap = CreateCompatibleBitmap(compatibleDC, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(backDC, backBitmap);
	DeleteObject(backBitmap);
	return backDC;
}

inline void putBitmapToBackDC(HDC backDC, Image image, UINT transparentColor) { //DC에 이미지를 넣어줌
	const HDC bitmapDC = CreateCompatibleDC(backDC);
	const HBITMAP bitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)image.fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(bitmapDC, bitmap);

	double scale = image.scale;
	if (scale == 0) scale = DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER;

	const int x = (int)(image.x * RESOLUTION_MULTIPLIER);
	const int y = (int)(image.y * RESOLUTION_MULTIPLIER);
	const Size bitmapSize = getBitmapSize(bitmap);
	const int width = (int)(bitmapSize.width * scale);
	const int height = (int)(bitmapSize.height * scale);
	TransparentBlt(backDC, x, y, width, height,
		bitmapDC, 0, 0, bitmapSize.width, bitmapSize.height, transparentColor);

	DeleteObject(bitmap);
	DeleteDC(bitmapDC);
}

inline void applyToDC(HDC dstDC, HDC srcDC) { //목표DC에 소스DC를 복사함
	BitBlt(dstDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		srcDC, 0, 0, SRCCOPY);
}

inline void _initialize(ImageLayer* self) {//이미지 레이어를 초기화 해줌
	self->_windowHandle = GetConsoleWindow();
	self->_consoleDC = GetDC(self->_windowHandle);

	const int dpi = getDPI(self->_windowHandle);
	RESOLUTION_MULTIPLIER = dpi / 192.0;
	WINDOW_WIDTH = (int)(CONSOLE_WIDTH * DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER);
	WINDOW_HEIGHT = (int)(CONSOLE_HEIGHT * 2 * DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER);
}

inline HDC getRenderedBackDC(ImageLayer* self) {//모든 이미지들이 들어간 DC를 반환
	const HDC backDC = createNewBackDC(self->_consoleDC);

	for (int i = 0; i < self->imageCount; i++) {
		putBitmapToBackDC(backDC, self->images[i], self->transparentColor);
	}
	return backDC;
}

inline void _renderAll(ImageLayer* self) {//화면에 이미지 레이어를 출력해줌
	const HDC backDC = getRenderedBackDC(self);
	applyToDC(self->_consoleDC, backDC);
	DeleteDC(backDC);
}

inline BLENDFUNCTION getBlendFunction() {//새로운 BLENDFUNCTION을 만들어서 반환
	BLENDFUNCTION bf;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = 0;
	return bf;
}

inline void _renderAndFadeIn(ImageLayer* self, void(*applyToBackDC)(HDC)) {//이미지가 점점 밝아지는 효과를 생성
	const HDC consoleDC = self->_consoleDC;
	const HDC backDC = getRenderedBackDC(self);
	if (applyToBackDC != NULL) applyToBackDC(backDC);

	const HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(consoleDC, blackBrush);

	BLENDFUNCTION bf = getBlendFunction();
	bf.SourceConstantAlpha = 12;

	Rectangle(consoleDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	for (int i = 0; i < 20; i++) {
		AlphaBlend(consoleDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			backDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, bf);
	}
	applyToDC(consoleDC, backDC);
	DeleteObject(blackBrush);
	DeleteDC(backDC);
}

//이미지가 점점 어두워지는 효과를 생성
inline void _renderAndFadeOut(ImageLayer* self, void(*applyToBackDC)(HDC)) {
	const HDC consoleDC = self->_consoleDC;
	const HDC backDC = getRenderedBackDC(self);
	if (applyToBackDC != NULL) applyToBackDC(backDC);
	applyToDC(consoleDC, backDC);

	const HDC blackDC = createNewBackDC(consoleDC);
	BLENDFUNCTION bf = getBlendFunction();

	for (int i = 255; i >= 0; i -= 20) {
		bf.SourceConstantAlpha = i;
		applyToDC(consoleDC, blackDC);
		AlphaBlend(consoleDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			backDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, bf);
		Sleep(100);
	}
	applyToDC(consoleDC, blackDC);

	DeleteDC(backDC);
	DeleteDC(blackDC);
}