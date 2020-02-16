#pragma once
#include "Shape.hpp"

class Graphics
{
public:
	Graphics(const HWND &hWnd);
	~Graphics();

	void clear();
	void display();

	void draw(Shape &shape);

private:
	HWND hWnd;

	HDC backBuffer;
	int savedDC;
	HBITMAP hBmp, hBmpOld;
	RECT clientRect;
	std::vector<RECT> m_objects;
};