#pragma once
#include <stdio.h> 
#include <Windows.h>

HWND WINDOW_HANDLE;
HANDLE CONSOLE_INPUT;

inline void enableMouseInput() { // ���콺 �ʱⰪ ����
	WINDOW_HANDLE = GetConsoleWindow();
	CONSOLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);

	DWORD mode;
	GetConsoleMode(CONSOLE_INPUT, &mode);
	SetConsoleMode(CONSOLE_INPUT, mode | ENABLE_MOUSE_INPUT);
}

inline int hasInput() { // ���콺 Ŭ���ߴ��� �˷��ִ� �Լ�
	INPUT_RECORD input_record;
	DWORD input_count;

	PeekConsoleInput(CONSOLE_INPUT, &input_record, 1, &input_count);
	return input_count;
}

INPUT_RECORD rec;
DWORD dwNOER;
inline int isMouseClicked() { // ���콺 ���� ��ư, ������ ��ư �� �� ��� ��ư�� ���ȴ��� �˷��ִ� �Լ�
	ReadConsoleInput(CONSOLE_INPUT, &rec, 1, &dwNOER);
	if (rec.EventType == MOUSE_EVENT) {
		const DWORD buttonState = rec.Event.MouseEvent.dwButtonState;
		if (buttonState & FROM_LEFT_1ST_BUTTON_PRESSED)	return 1;
		else if (buttonState & RIGHTMOST_BUTTON_PRESSED) return 2;
	}
	return 0;
}

inline COORD getMousePosition() {
	POINT cursorPosition;
	GetCursorPos(&cursorPosition);
	ScreenToClient(WINDOW_HANDLE, &cursorPosition);
	return (COORD) { (SHORT)cursorPosition.x*2, (SHORT)cursorPosition.y*2};
}