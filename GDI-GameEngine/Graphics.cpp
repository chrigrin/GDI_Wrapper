#include "stdafx.h"
#include "Graphics.hpp"

Graphics::Graphics(const HWND hWnd)
	:
	hWnd(hWnd)
{
	// Retrieve the client rect
	GetClientRect(hWnd, &clientRect);

	// Get the device context for the window
	HDC winDC = GetDC(hWnd);
	// Create a compatible backbuffer
	backBuffer = CreateCompatibleDC(winDC);
	// Create a bitmap, compatible with the window DC (Making it compatible 
	// with the backbuffer returns a monochrome bitmap, with only black and white)
	hBmp = CreateCompatibleBitmap(winDC, clientRect.right, clientRect.bottom);
	// Select the bitmap into the backbuffer, and store the old bitmap in a handle (needed for deletion)
	hBmpOld = (HBITMAP)SelectObject(backBuffer, hBmp);
	// Make the backbuffer use the DC's pen color and brush color
	SelectObject(backBuffer, GetStockObject(DC_PEN));
	SelectObject(backBuffer, GetStockObject(DC_BRUSH));
	// BitBlit a black screen to the window
	BitBlt(winDC, clientRect.left, clientRect.top, clientRect.right, clientRect.bottom,
		nullptr, 0, 0, BLACKNESS);
	// Release the device context to prevent leaks
	ReleaseDC(hWnd, winDC);
}

Graphics::~Graphics()
{
	// Select the old bitmap into the backbuffer to make the created bitmap deletable
	SelectObject(backBuffer, hBmpOld);
	// Delete the created bitmap to prevent leaks
	DeleteObject(hBmp);
	// Delete the backbuffer created to prevent leaks
	DeleteDC(backBuffer);
}

void Graphics::clear()
{
	// Check if there are any objects not cleared
	while (m_objects.size() > 0)
	{
		// Draw a black rectangle over the last object in the vector
		FillRect(backBuffer, &m_objects.back(), CreateSolidBrush(BLACK_BRUSH));
		// Pop the last object in the vector
		m_objects.pop_back();
	}
}

void Graphics::display()
{
	// Get the device context for the window
	HDC winDC = GetDC(hWnd);

	// BitBlit the backbuffer to the window DC
	BitBlt(winDC, clientRect.left, clientRect.top, clientRect.right, clientRect.bottom,
		backBuffer, 0, 0, SRCCOPY);

	// Release the device context to prevent leaks
	ReleaseDC(hWnd, winDC);
}

void Graphics::draw(Shape & shape)
{
	// Save the state of the backbuffer (Pens, brushes, etc.)
	savedDC = SaveDC(backBuffer);

	// Push back a copy of the rect that will be drawn
	m_objects.push_back(shape.getRect());
	// Draw the shape to the backbuffer
	shape.draw(backBuffer);

	// Restore the state of the backbuffer
	RestoreDC(backBuffer, savedDC);
}
