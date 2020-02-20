#pragma once
#include "Shape.hpp"

class Graphics
{
public:
	Graphics(const HWND m_hWnd);
	~Graphics();

	void clear();
	void display();

	void draw(Shape &shape);

private:
	HWND m_hWnd;

	HDC m_backBuffer;
	int m_savedDC;
	HBITMAP m_hBmp, m_hBmpOld;
	RECT m_clientRect;
	std::vector<RECT> m_objects;
};