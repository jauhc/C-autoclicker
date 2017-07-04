#include "stdafx.h"
#include <Windows.h>

#define HITKEY VK_XBUTTON2
#define ENDKEY VK_SHIFT

void __fastcall clickFunction(INPUT* input)
{
	if (!GetAsyncKeyState(ENDKEY) && GetAsyncKeyState(HITKEY))
	{
		input->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
		SendInput(1, input, sizeof(INPUT));
		Sleep(17);

		input->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
		SendInput(1, input, sizeof(INPUT));
		Sleep(17);
	}
	if (GetAsyncKeyState(ENDKEY))
		exit(0);
}


void main()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dx = 0;
	input.mi.dy = 0;
	input.mi.mouseData = 0;
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	input.mi.time = 0;
	input.mi.dwExtraInfo = 0;
	printf("%s\n", "[clickenings intensifies]\n");
	while (1)
		clickFunction(&input);
}
