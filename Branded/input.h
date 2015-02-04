#ifndef _INPUT_H_
#define _INPUT_H_
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib, "x86/dinput8.lib")
#pragma comment(lib, "x86/dxguid.lib")
#include "Include\dinput.h"
class Input
{
public:
	Input();
	~Input();

	bool init(HINSTANCE, HWND, int, int);
	void shutDown();
	bool frame();

	void RecordMouse(int& mouseX, int& mouseY, bool& leftClick, bool& rightClick);

private:
	bool readKeyboard();
	bool readMouse();
	void processInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};
#endif