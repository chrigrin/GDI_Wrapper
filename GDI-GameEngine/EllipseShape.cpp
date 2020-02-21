#include "stdafx.h"
#include "EllipseShape.hpp"

EllipseShape::EllipseShape()
	:
	m_fillColor(RGB(255, 255, 255)),
	m_outlineColor(RGB(0, 0, 0))
{
}

EllipseShape::EllipseShape(double radius)
	:
	m_radius(radius),
	m_width(static_cast<int>(radius * 2)),
	m_height(static_cast<int>(radius * 2))
{
	EllipseShape();
}

EllipseShape::EllipseShape(int width, int height)
	:
	m_radius(0),
	m_width(width),
	m_height(height)
{
	EllipseShape();
}

EllipseShape::EllipseShape(std::pair<int, int> size)
{
	EllipseShape(size.first, size.second);
}

EllipseShape::EllipseShape(double radius, int x, int y)
	:
	m_x(x),
	m_y(y)
{
	EllipseShape(static_cast<double>(radius));
}

EllipseShape::EllipseShape(double radius, std::pair<int, int> pos)
{
	EllipseShape(radius, pos.first, pos.second);
}

EllipseShape::EllipseShape(int width, int height, int x, int y)
	:
	m_x(x),
	m_y(y)
{
	EllipseShape(width, height);
}

EllipseShape::EllipseShape(std::pair<int, int> size, std::pair<int, int> pos)
{
	EllipseShape(size.first, size.second, pos.first, pos.second);
}

EllipseShape::EllipseShape(RECT rect)
{
	int width, height;
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	EllipseShape(rect.left, rect.top, width, height);
}

void EllipseShape::setFillColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_fillColor = RGB(r, g, b);
}

void EllipseShape::setOutlineColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_outlineColor = RGB(r, g, b);
}

void EllipseShape::setOutlineThickness(int outlineThickness)
{
	m_outlineThickness = outlineThickness;
}

void EllipseShape::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void EllipseShape::setPosition(std::pair<int, int> pos)
{
	setPosition(pos.first, pos.second);
}

void EllipseShape::setSize(int width, int height)
{
	if (width == height)
		m_radius = static_cast<double>(width / 2);
	else
		m_radius = 0;

	m_width = width;
	m_height = height;
}

void EllipseShape::setSize(std::pair<int, int> size)
{
	setSize(size.first, size.second);
}

void EllipseShape::setRect(RECT & rect)
{
	int width, height;
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	setPosition(rect.left, rect.top);
	setSize(width, height);
}

void EllipseShape::setRadius(double radius)
{
	m_radius = radius;
	m_width = static_cast<int>(radius * 2);
	m_height = static_cast<int>(radius * 2);
}

void EllipseShape::move(int x, int y)
{
	m_x += x;
	m_y += y;
}

void EllipseShape::move(std::pair<int, int> distance)
{
	move(distance.first, distance.second);
}

const std::pair<int, int> EllipseShape::getPosition() const
{
	return std::pair<int, int>(m_x, m_y);
}

const std::pair<int, int> EllipseShape::getSize() const
{
	return std::pair<int, int>(m_width, m_height);
}

const RECT EllipseShape::getRect() const
{
	RECT rect;
	int width, height;
	width = m_x + m_width;
	height = m_y + m_height;
	SetRect(&rect, m_x, m_y, width, height);
	return rect;
}

const double EllipseShape::getRadius() const
{
	return m_radius;
}

void EllipseShape::draw(HDC & hDC)
{
	// Retrieve the ellipse's rectangle (used in the drawing function)
	RECT ellipseRect = getRect();

	SetDCPenColor(hDC, RGB(255, 0, 255));
	SetDCBrushColor(hDC, m_fillColor);


	// Draw before the outline to support negative outlines
	Ellipse(hDC, ellipseRect.left, ellipseRect.top, ellipseRect.right, ellipseRect.bottom);

	// Draw an outline if it is specified
	if (m_outlineThickness != 0)
	{
		drawOutline(hDC, ellipseRect);
	}
}

void EllipseShape::drawOutline(HDC & hDC, RECT outlineRect)
{
	////////////////////////////////////////////
	// Setup

	// Create a logbrush which is using the the outlinecolor
	// retrieved from the parameter
	LOGBRUSH lBrush = { BS_SOLID, m_outlineColor };
	// Use ExtCreatePen to be able to use PS_JOIN_MITER, which is used
	// to make the outline squared and not round
	HPEN hOutlinePen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID | PS_JOIN_MITER,
		m_outlineThickness, &lBrush, 0, 0);
	// Select the new pen into the DC, and store the old pen
	HPEN hOldPen = (HPEN)SelectObject(hDC, hOutlinePen);
	// Finished setup
	////////////////////////////////////////////

	////////////////////////////////////////////
	// Start drawing the outline

	// Call begin path to start capturing GDI shapes into a path
	BeginPath(hDC);

	// Draw the outline rectangle to the path
	Ellipse(hDC, outlineRect.left, outlineRect.top, outlineRect.right, outlineRect.bottom);

	// End the capturing into the path
	EndPath(hDC);

	// Fill the outline of the outline rectangle (using the pen
	// selected into the DC)
	StrokePath(hDC);

	// Finished drawing the outline
	////////////////////////////////////////////

	////////////////////////////////////////////
	// Deletion

	// Select the old pen to make the created pen deletable
	SelectObject(hDC, hOldPen);
	// Delete the created pen
	DeleteObject(hOutlinePen);
	// Finished deletion
	////////////////////////////////////////////
}
