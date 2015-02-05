#include "Input.h"
Input::Input()
{}

Input::~Input()
{}

void Input::init()
{
	//zero out the keys
	for (int i = 0; i < 256; i++) m_keys[i] = false;
	m_LMButton = false;
	m_RMButton = false;
}

void Input::keyUp(unsigned int key)
{
	m_keys[key] = false;
}

void Input::keyDown(unsigned int key)
{
	m_keys[key] = true;
	int x;
}

bool Input::isKeyDown(unsigned int key)
{
	return m_keys[key];
}

void Input::mouseMove(LPARAM lparam)
{
	m_mouseX = GET_X_LPARAM(lparam);
	m_mouseY = GET_Y_LPARAM(lparam);
}

void Input::mouseLClick(bool state)
{
	m_LMButton = state;
}

void Input::mouseRClcik(bool state)
{
	m_RMButton = state;
}

int Input::getMouseX()
{
	return m_mouseX;
}

int Input::getMouseY()
{
	return m_mouseY;
}

bool Input::isMouseLeftClicked()
{
	return m_LMButton;
}

bool Input::isMouseRightClicked()
{
	return m_RMButton;
}