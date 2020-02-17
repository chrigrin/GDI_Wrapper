#include "stdafx.h"
#include "Graphics.hpp"

Graphics::Graphics(const HWND hWnd)
	:
	hWnd(hWnd)
{
	GetClientRect(hWnd, &clientRect);

	HDC frontBuffer = GetDC(hWnd);
	backBuffer = CreateCompatibleDC(frontBuffer);
	hBmp = CreateCompatibleBitmap(frontBuffer, clientRect.right, clientRect.bottom);
	hBmpOld = (HBITMAP)SelectObject(backBuffer, hBmp);
	SelectObject(backBuffer, GetStockObject(DC_PEN));
	SelectObject(backBuffer, GetStockObject(DC_BRUSH));
	BitBlt(frontBuffer, clientRect.left, clientRect.top, clientRect.right, clientRect.bottom,
		nullptr, 0, 0, BLACKNESS);
	ReleaseDC(hWnd, frontBuffer);
}

Graphics::~Graphics()
{
	SelectObject(backBuffer, hBmpOld);
	DeleteObject(hBmp);
	DeleteDC(backBuffer);
}

void Graphics::clear()
{
	while (m_objects.size() > 0)
	{
		FillRect(backBuffer, &m_objects.back(), CreateSolidBrush(BLACK_BRUSH));
		m_objects.pop_back();
	}
}

void Graphics::display()
{
	HDC frontBuffer = GetDC(hWnd);

	SelectObject(backBuffer, hBmp);

	BitBlt(frontBuffer, clientRect.left, clientRect.top, clientRect.right, clientRect.bottom,
		backBuffer, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, frontBuffer);
}

void Graphics::draw(Shape & shape)
{
	savedDC = SaveDC(backBuffer);

	m_objects.push_back(shape.getRect());
	shape.draw(backBuffer);

	RestoreDC(backBuffer, savedDC);
}
