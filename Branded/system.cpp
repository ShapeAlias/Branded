#include "system.h"

System::System()
{}

System::~System()
{}

bool System::init()
{
	int screenWidth = 0, screenHeight = 0;
	bool result;
	m_done = false;
	m_input = new Input;
	GdiplusStartupInput gdiplusStartupInput;

	GdiplusStartup(&gdiPlusToken, &gdiplusStartupInput, NULL);

	initWindows(screenWidth, screenHeight, true);
	m_input->init();
	int blank;
	//init button
	m_button = new Button(32, 32, 100, 24, Color(255, 255, 0, 0), Color(255, 0, 255, 0), L"Click me",24);
	m_FPS = 60;
	return true;

}

void System::shutDown()
{
	shutDownWindows();
	GdiplusShutdown(gdiPlusToken);
}

void System::run()
{
	MSG msg;
	bool  result;
	ZeroMemory(&msg, sizeof(MSG));
	unsigned long startTime = GetTickCount();
	while (!m_done)
	{
		if (GetTickCount()-startTime >  (1000/m_FPS))
		{
			startTime = GetTickCount();
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT)
			{
				m_done = true;
			}
			else
			{
				result = frame();
				if (!result)
				{
					m_done = true;
				}
			}
		}
	}

}

bool System::frame()
{
	m_button->Update(*m_input);
	if (m_input->isKeyDown(VK_ESCAPE)) m_done = true;
	/*if (m_input->isMouseLeftClicked())
	{
		string message = "Clicked at (" + to_string(m_input->getMouseX()) + "," +
			to_string(m_input->getMouseY()) + ")";
		wstring wMessage = wstring(message.begin(), message.end());
		LPCWSTR actualMessage = wMessage.c_str();
		MessageBox(m_hwnd, actualMessage, L"Message:Clicked", MB_OK);
		m_input->mouseLClick(false);
	}*/
	//Redraw the window
	RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE);
	if (m_button->isClicked())
	{
		MessageBox(m_hwnd, L"Click the button", L"Click", MB_OK);
		m_input->mouseLClick(false);
	}
	return true;
}

LRESULT CALLBACK System::messageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_KEYDOWN:
	{
		m_input->keyDown((unsigned int)wparam);
		return 0;
	}
	case WM_KEYUP:
	{
		m_input->keyUp((unsigned int)wparam);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		m_input->mouseMove(lparam);
		return 0;
	}
	case  WM_LBUTTONDOWN:
	{
		m_input->mouseLClick(true);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		m_input->mouseLClick(false);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		m_input->mouseRClcik(true);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		m_input->mouseRClcik(false);
		return 0;
	}
	//case WM_SYNCPAINT:
	//{
	//	HDC hdc;
	//	PAINTSTRUCT ps;
	//	hdc = BeginPaint(hwnd, &ps);
	//	ApplicationHandle->draw(hdc);
	//	EndPaint(hwnd, &ps);
	//	return 0;
	//}
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}

void System::initWindows(int& screenWidth, int& screenHeight, bool fullScreen)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Branded";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	m_fullScreen = fullScreen;
	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (fullScreen)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(true);
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_posX = posX;
	m_posY = posY;

	return;
}

void System::shutDownWindows()
{
	ShowCursor(true);

	if (m_fullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	ApplicationHandle = NULL;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		ApplicationHandle->draw(hdc);
		EndPaint(hwnd, &ps);
		return 0;
	}


	default:
	{
		return ApplicationHandle->messageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}

VOID System::draw(HDC hdc)
{
	//draw button
	Bitmap bmp(GAME_RES_WIDTH, GAME_RES_HEIGHT);

	m_button->draw(bmp);
	Graphics* g = Graphics::FromImage(&bmp);

	//draw the updated image
	//SolidBrush brush(Color(255, 255, 255, 255));
	Graphics graphics(hdc);
	graphics.DrawImage(&bmp, m_posX, m_posY, m_screenWidth, m_screenHeight);
;
}