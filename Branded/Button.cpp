#include "Button.h"

Button::Button(int x, int y, int width, int height, Color argb1, Color argb2, LPCWSTR text,int fontSize)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_color1 = argb1;
	m_color2 = argb2;
	m_text = text;
	m_highlighted = false;
	m_clicked = false;
	m_fontSize = fontSize;
}

VOID Button::draw(HDC hdc)
{
	Graphics g(hdc);
	if (m_highlighted)
	{
		SolidBrush brush( m_color2);
		g.FillRectangle(&brush, m_x, m_y, m_width, m_height);
		//draw text
		FontFamily fontFamily(L"Times New Roman");
		SolidBrush brushf(m_color1);
		Font font(&fontFamily, m_fontSize, FontStyleRegular, UnitPixel);
		PointF pointf(m_x + (m_width / 2) - (font.GetHeight(&g)*sizeof(m_text) / 2), m_y );
		g.DrawString(m_text, -1, &font, pointf, &brushf);
		
	}
	else
	{
		SolidBrush brush(m_color1);
		g.FillRectangle(&brush, m_x, m_y, m_width, m_height);
		//draw text
		FontFamily fontFamily(L"Times New Roman");
		SolidBrush brushf(m_color2);
		Font font(&fontFamily, m_fontSize, FontStyleRegular, UnitPixel);
		PointF pointf(m_x + (m_width / 2) - (font.GetHeight(&g)*sizeof(m_text) / 2), m_y);
		g.DrawString(m_text, -1, &font, pointf, &brushf);
	}
}

bool Button::isClicked()
{
	return m_clicked;
}

void Button::Update(Input input)
{
	//check to see if the mouse is over the button
	if ((input.getMouseX() > m_x && input.getMouseX() < m_x + m_width) &&
		(input.getMouseY ()> m_y && input.getMouseY() < m_y + m_height))
		m_highlighted = true;
	else 
		m_highlighted = false;

	if (m_highlighted && input.isMouseLeftClicked()) m_clicked = true;
	else m_clicked = false;
}