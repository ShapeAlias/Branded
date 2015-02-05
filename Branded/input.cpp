#include "Input.h"
Input::Input()
{}

Input::~Input()
{}

void Input::init()
{
	//zero out the keys
	for (int i = 0; i < 256; i++) m_keys[i] = false;
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