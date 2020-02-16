#include "stdafx.h"
#include "RectangleShape.hpp"

RectangleShape::RectangleShape()
{
	m_fillColor = RGB(255, 255, 255);
	m_outlineColor = RGB(0, 0, 0);
}

RectangleShape::RectangleShape(int width, int height)
	:
	m_width(width),
	m_height(height)
{
	m_fillColor = RGB(255, 255, 255);
	m_outlineColor = RGB(0, 0, 0);
}

RectangleShape::RectangleShape(int x, int y, int m_width, int m_height)
	:
	m_x(m_x),
	m_y(m_y),
	m_width(m_width),
	m_height(m_height)
{
	m_fillColor = RGB(255, 255, 255);
	m_outlineColor = RGB(0, 0, 0);
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
	COLORREF returnPen, returnBrush;

	returnPen = SetDCPenColor(hDC, m_outlineColor);
	returnBrush = SetDCBrushColor(hDC, m_fillColor);

	if (returnPen == CLR_INVALID)
		MessageBox(nullptr, L"Could not set pen color", L"Error", MB_ICONERROR);
	if (returnBrush == CLR_INVALID)
		MessageBox(nullptr, L"Could not set brush color", L"Error", MB_ICONERROR);

	int width, height;
	width = m_x + m_width;
	height = m_y + m_height;

	Rectangle(hDC, m_x, m_y, width, height);
}
