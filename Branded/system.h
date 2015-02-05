#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "input.h"
#include <string>
#include <ObjIdl.h>
#include <gdiplus.h>
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
    VOID draw(HDC);
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
	bool m_done;
	Input* m_input;
	ULONG_PTR gdiPlusToken;
	

private:

};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

VOID OnPaint(HDC hdc);

static System* ApplicationHandle = 0;
