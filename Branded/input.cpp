#include "Input.h"
bool mouseClicked = false;
Input::Input()
{
	m_directInput = NULL;
	m_keyboard = NULL;
	m_mouse = NULL;
	m_mouseX = NULL;
	m_mouseY = NULL;
	m_screenHeight = NULL;
	m_screenWidth = NULL;
}

Input::~Input()
{
	shutDown();
}

bool Input::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;

	//Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	//init the mouse location
	m_mouseX = 0;
	m_mouseY = 0;

	//init the main direct input interface
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the keyboard.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}


	//Set the data format. In this case since it is a keyboard we can use the predefined data format.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	//Set the cooperative level of the keyboard to not share with other programs.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	//now aquire the keyboard.
	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		//	return false;
	}

	//init the direct input interface for the mouse
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	//Set the cooperative level of the mouse to share with other programs.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	//Acquire the mouse
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		//return false;
	}

	return true;
}

void Input::shutDown()
{
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = NULL;
	}

	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_mouse->Release();
		m_mouse = NULL;
	}

	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = NULL;
	}
}

bool Input::frame()
{
	bool result;

	result = readKeyboard();
	if (!result)
	{
		return false;
	}

	result = readMouse();
	if (!result)
	{
		return false;
	}

	processInput();

	return true;
}

bool Input::readKeyboard()
{
	HRESULT result;

	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		if ((result == DIERR_INCOMPLETEEFFECT) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Input::readMouse()
{
	HRESULT result;

	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}
	if (m_mouseState.rgbButtons[0] && 0x80)
	{
		MessageBox(NULL, L"Mouse clicked", L"mouseClicked", MB_OK);
	}
	if (m_mouseState.rgbButtons[1] && 0x80)
	{
		MessageBox(NULL, L"Mouse Clicked", L"Clicked", MB_OK);
	}
	return true;
}

void Input::processInput()
{
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	if (m_mouseX < 0)m_mouseX = 0;
	if (m_mouseY < 0)m_mouseY = 0;

	if (m_mouseX > m_screenWidth)m_mouseX = m_screenWidth;
	if (m_mouseY > m_screenHeight)m_mouseY = m_screenHeight;
}

void Input::RecordMouse(int& mouseX, int& mouseY, bool& leftClick, bool& rightClick)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
	leftClick = (m_mouseState.rgbButtons[0] & 0x80);

	rightClick = (m_mouseState.rgbButtons[1] & 0x80);
}