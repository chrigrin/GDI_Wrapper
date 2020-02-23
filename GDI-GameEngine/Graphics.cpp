#include "stdafx.h"
#include "Graphics.hpp"

Graphics::Graphics(HWND hWnd)
	:
	m_hWnd(hWnd)
{
	// Retrieve the client rect
	GetClientRect(hWnd, &m_clientRect);

	// Get the device context for the window
	HDC wndDC = GetDC(hWnd);
	// Create a compatible backbuffer
	m_backBuffer = CreateCompatibleDC(wndDC);
	// Create a bitmap, compatible with the window DC (Making it compatible 
	// with the backbuffer returns a monochrome bitmap, with only black and white)
	m_hBmp = CreateCompatibleBitmap(wndDC, m_clientRect.right, m_clientRect.bottom);
	// Select the bitmap into the backbuffer, and store the old bitmap in a handle (needed for deletion)
	m_hBmpOld = (HBITMAP)SelectObject(m_backBuffer, m_hBmp);
	// Make the backbuffer use the DC's pen color and brush color
	SelectObject(m_backBuffer, GetStockObject(DC_PEN));
	SelectObject(m_backBuffer, GetStockObject(DC_BRUSH));
	// BitBlit a black screen to the window
	BitBlt(wndDC, m_clientRect.left, m_clientRect.top, m_clientRect.right, m_clientRect.bottom,
		nullptr, 0, 0, BLACKNESS);
	// Release the device context to prevent leaks
	ReleaseDC(hWnd, wndDC);
}

Graphics::~Graphics()
{
	// Select the old bitmap into the backbuffer to make the created bitmap deletable
	SelectObject(m_backBuffer, m_hBmpOld);
	// Delete the created bitmap to prevent leaks
	DeleteObject(m_hBmp);
	// Delete the backbuffer created to prevent leaks
	DeleteDC(m_backBuffer);
}

void Graphics::clear()
{
	// Check if there are any objects not cleared
	while (m_objects.size() > 0)
	{
		// Draw a black rectangle over the last object in the vector
		FillRect(m_backBuffer, &m_objects.back(), CreateSolidBrush(BLACK_BRUSH));
		// Pop the last object in the vector
		m_objects.pop_back();
	}
}

void Graphics::display() const
{
	// Get the device context for the window
	HDC wndDC = GetDC(m_hWnd);

	// BitBlit the backbuffer to the window DC
	BitBlt(wndDC, m_clientRect.left, m_clientRect.top, m_clientRect.right, m_clientRect.bottom,
		m_backBuffer, 0, 0, SRCCOPY);

	// Release the device context to prevent leaks
	ReleaseDC(m_hWnd, wndDC);
}

void Graphics::draw(const Shape & shape)
{
	// Save the state of the backbuffer (Pens, brushes, etc.)
	m_savedDC = SaveDC(m_backBuffer);

	// Push back a copy of the rect that will be drawn
	m_objects.push_back(shape.getRect());
	// Draw the shape to the backbuffer
	shape.draw(m_backBuffer);

	// Restore the state of the backbuffer
	RestoreDC(m_backBuffer, m_savedDC);
}
