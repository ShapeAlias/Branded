#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "input.h"
#include <string>
#include <ObjIdl.h>
#include <gdiplus.h>
#include "Button.h"
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
using namespace std;
class System
{
public:
	System();
	~System();

	bool init();
	void shutDown();
	void run();
    VOID draw(HDC hdc);
	LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool frame();
	void initWindows(int&, int&, bool);
	
	void shutDownWindows();
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	bool m_fullScreen;
	int m_screenWidth, m_screenHeight;
	int m_posX, m_posY;
	bool m_done;
	Input* m_input;
	ULONG_PTR gdiPlusToken;
	Button* m_button;
	int m_FPS;
	const int GAME_RES_WIDTH = 1920;
	const int GAME_RES_HEIGHT = 1080;
	

private:

};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

VOID OnPaint(HDC hdc);

static System* ApplicationHandle = 0;
