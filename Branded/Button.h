#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <ObjIdl.h>
#include <gdiplus.h>
#include "input.h"
using namespace Gdiplus;
class Button
{
public:
	Button(int x, int y, int width, int height, Color argb1, Color argb2, LPCWSTR text,int fontSize);

	~Button();
	bool isClicked();
	VOID draw(Bitmap& bmp);
	void Update(Input input);

private:
	bool m_highlighted;
	bool m_clicked;
	Color m_color1, m_color2;
	int m_x, m_y;
	int m_width, m_height;
	int m_fontSize;
	LPCWSTR m_text;

};
#endif
