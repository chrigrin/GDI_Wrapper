#pragma once
#include "Shape.hpp"

class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics();

	void clear();
	void display() const;

	void draw(const Shape &shape);

private:
	HWND m_hWnd;

	HDC m_backBuffer;
	int m_savedDC;
	HBITMAP m_hBmp, m_hBmpOld;
	RECT m_clientRect;
	std::vector<RECT> m_objects;
};