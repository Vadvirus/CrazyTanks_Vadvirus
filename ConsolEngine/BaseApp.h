#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

class BaseApp
{
private:
	HANDLE mConsole;
	HANDLE mConsoleIn;

	CHAR_INFO* mChiBuffer;
	COORD mDwBufferSize;
	COORD mDwBufferCoord;
	SMALL_RECT mLpWriteRegion;

	void Render();

public:
	// the size of the output area horizontally and vertically in the characters
	const int X_SIZE;
	const int Y_SIZE;

	// arguments are the sizes of the output area horizontally and vertically in the symbols
	BaseApp(int xSize=100, int ySize=80);
	virtual ~BaseApp();

	// runs the game loop
	void Run();

	// you can fill the x, y-character of the screen with a specific character, or read it
	void SetChar(int x, int y, wchar_t c);
	wchar_t GetChar(int x, int y);

	/ * this function is called every game iteration, it can be redefined, in the class heir.
deltaTime arrives in it - the time difference between the previous iteration and this, in seconds * /
	virtual void UpdateF (float deltaTime){}
	/ * this function is called when a key is pressed on the keyboard, the key code comes to it - btnCode.
if you use arrows or function keys, then there will come a common number for them, for example 224, and the next after it -
the code of the key itself will already be directly, it can be obtained by calling the getch () method.
The KeyPressed method can also be redefined in the successor * /
	virtual void KeyPressed (int btnCode){}
};
