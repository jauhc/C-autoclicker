#include "stdafx.h"
#include <Windows.h>

#define HITKEY VK_XBUTTON2
#define ENDKEY VK_SHIFT
#define SLEEP 14
#define mode 0

//typedef enum bool {false=0, true=1} bool;
static unsigned char fState = 0;
// 0 = default, nothing happening
// 1 = about to go on 
// 2 = on
// 3 = about to go off

void __fastcall sendClick(INPUT* input)
{
	input->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, input, sizeof(INPUT));
	Sleep(SLEEP);

	input->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, input, sizeof(INPUT));
	Sleep(SLEEP);
}

void __fastcall clickFunction(INPUT* input)
{
	if ( !mode && !GetAsyncKeyState(ENDKEY) && GetAsyncKeyState(HITKEY) )
		sendClick(input);

	// Toggle logic
	if ( mode && GetAsyncKeyState(HITKEY) && fState == 0 )
		fState = 1;
	if ( mode && !GetAsyncKeyState(HITKEY) && fState == 1 )
		fState = 2;
	if ( mode && GetAsyncKeyState(HITKEY) && fState == 2 )
		fState = 3;
	if ( mode && !GetAsyncKeyState(HITKEY) && fState == 3 )
		fState = 0;
	if ( mode && fState == 2 )
		sendClick(input);

	if (GetAsyncKeyState(ENDKEY))
		exit(0);
}

void main( int argc, char *argv[] )
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dx = 0;
	input.mi.dy = 0;
	input.mi.mouseData = 0;
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	input.mi.time = 0;
	input.mi.dwExtraInfo = 0;
	//printf("%s\n", "[clickenings intensifies]\n");
	while (1)
		clickFunction(&input);
}
