#include "stdafx.h"
#include "RectangleShape.hpp"

RectangleShape::RectangleShape()
	:
	m_outlineThickness(0)
{
	m_fillColor = RGB(255, 255, 255);
	m_outlineColor = RGB(0, 0, 0);
}

RectangleShape::RectangleShape(int width, int height)
	:
	m_width(width),
	m_height(height)
{
	RectangleShape();
}

RectangleShape::RectangleShape(int x, int y, int width, int height)
	:
	m_x(x),
	m_y(y)
{
	RectangleShape(width, height);
}

RectangleShape::RectangleShape(std::pair<int, int> pos, std::pair<int, int> size)
{
	RectangleShape(pos.first, pos.second, size.first, size.second);
}

RectangleShape::RectangleShape(RECT & rect)
{
	int width, height;
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	RectangleShape(rect.left, rect.top, width, height);
}

RectangleShape::~RectangleShape()
{
}

void RectangleShape::setFillColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_fillColor = RGB(r, g, b);
}

void RectangleShape::setOutlineColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_outlineColor = RGB(r, g, b);
}

void RectangleShape::setOutlineThickness(int outlineThickness)
{
	m_outlineThickness = outlineThickness;
}

void RectangleShape::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void RectangleShape::setPosition(std::pair<int, int> pos)
{
	setPosition(pos.first, pos.second);
}

void RectangleShape::setSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void RectangleShape::setSize(std::pair<int, int> size)
{
	setSize(size.first, size.second);
}

void RectangleShape::setRect(RECT & rect)
{
	int width, height;
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	setPosition(rect.left, rect.top);
	setSize(width, height);
}

void RectangleShape::move(int x, int y)
{
	m_x += x;
	m_y += y;
}

void RectangleShape::move(std::pair<int, int> distance)
{
	move(distance.first, distance.second);
}

std::pair<int, int> RectangleShape::getPosition()
{
	return std::pair<int, int>(m_x, m_y);
}

std::pair<int, int> RectangleShape::getSize()
{
	return std::pair<int, int>(m_width, m_height);
}

RECT RectangleShape::getRect()
{
	RECT rect;
	int width, height;
	width = m_x + m_width;
	height = m_y + m_height;
	SetRect(&rect, m_x, m_y, width, height);
	return rect;
}

void RectangleShape::draw(HDC &hDC)
{
	// Get the rectangle to draw
	RECT rect = getRect();

	// Variables used for error checks on setting DC pen and brush
	COLORREF returnPen, returnBrush;

	// Set pen color (outer points of the rectangle)
	returnPen = SetDCPenColor(hDC, RGB(255, 0, 0));
	// Set brush color (fill color of the rectangle)
	returnBrush = SetDCBrushColor(hDC, m_fillColor);

	// Error checks
	if (returnPen == CLR_INVALID)
		MessageBox(nullptr, L"Could not set pen color", L"Error", MB_ICONERROR);
	if (returnBrush == CLR_INVALID)
		MessageBox(nullptr, L"Could not set brush color", L"Error", MB_ICONERROR);

	// Draw the rectangle before the outline (makes negative outlines possible)
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

	// If an outline is specified create a custom outline for the rectangle
	if (m_outlineThickness != 0)
	{
		RECT outlineRect = getRect();
		int offset;
		if (m_outlineThickness == int(1 || -1))
		{
			// (1 / 2) on an int would be 0, therefore set the offset
			// to the outlineThickness
			offset = m_outlineThickness;
			outlineRect.left -= offset;
			outlineRect.top -= offset;
		}
		else
		{
			offset = m_outlineThickness / 2;
			outlineRect.right += offset;
			outlineRect.bottom += offset;

			// Odd numbers
			if (m_outlineThickness % 2)
			{
				outlineRect.left -= (offset + 1);
				outlineRect.top -= (offset + 1);
			}
			// Even numbers
			else
			{
				outlineRect.left -= offset;
				outlineRect.top -= offset;
			}
		}

		// Create pen, select it into the HDC and store the old pen (needed
		// for deletion)
		HPEN hOutlinePen = CreatePen(PS_SOLID, m_outlineThickness, m_outlineColor);
		HPEN hOldPen = (HPEN)SelectObject(hDC, hOutlinePen);

		// Points of the outline rectangle
		POINT outlinePoints[5];
		outlinePoints[0] = { outlineRect.left, outlineRect.top };
		outlinePoints[1] = { outlineRect.left, outlineRect.bottom };
		outlinePoints[2] = { outlineRect.right, outlineRect.bottom };
		outlinePoints[3] = { outlineRect.right, outlineRect.top };
		outlinePoints[4] = { outlineRect.left, outlineRect.top };

		// Drawing of the outline
		Polyline(hDC, outlinePoints, 5);

		// Select the old pen to make the created pen deletable
		SelectObject(hDC, hOldPen);
		// Delete the created pen
		DeleteObject(hOutlinePen);
	}
}
