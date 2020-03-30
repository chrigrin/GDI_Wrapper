#pragma once
#include "../GDI-Wrapper/framework.h"
#include <Wrapper/Export/Export.hpp>
#include <Wrapper/Graphics/Shapes/Shape.hpp>
#include <vector>

class GDIWRAPPER_API Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics();

	void clear(COLORREF color);
	void clear(unsigned char r, unsigned char g, unsigned char b);
	void display() const;

	void draw(const Shape &shape);

private:
	HWND m_hWnd;

	HDC m_backBuffer;
	int m_savedDC;
	HBITMAP m_hBmp, m_hBmpOld;
	RECT m_clientRect;
	std::vector<RECT> m_shapes;
};