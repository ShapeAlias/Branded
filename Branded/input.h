#ifndef _INPUT_H_
#define _INPUT_H_
#include <Windows.h>
#include <windowsx.h>
class Input
{
public:
	Input();
	~Input();

	void init();

	void keyUp(unsigned int);
	void keyDown(unsigned int);
	void mouseMove(LPARAM);
	void mouseLClick(bool);
	void mouseRClcik(bool);
	int getMouseX();
	int getMouseY();
	bool isMouseLeftClicked();
	bool isMouseRightClicked();

	bool isKeyDown(unsigned int );
	bool isKeyUp(unsigned int key) { return !isKeyUp(key); }
private:
	bool m_keys[256];
	int m_mouseX;
	int m_mouseY;
	bool m_LMButton;
	bool m_RMButton;

};
#endif