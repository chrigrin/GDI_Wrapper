#include <Wrapper/Graphics/Shapes/EllipseShape.hpp>

EllipseShape::EllipseShape()
	:
	EllipseShape(0, 0, 0, 0)
{
}

EllipseShape::EllipseShape(int width, int height)
	:
	EllipseShape(0, 0, width, height)
{
}

EllipseShape::EllipseShape(std::pair<int, int> size)
	:
	EllipseShape(0, 0, size.first, size.second)
{
}

EllipseShape::EllipseShape(int x, int y, int width, int height)
	:
	m_width(width),
	m_height(height),
	m_x(x),
	m_y(y),
	m_outlineThickness(0),
	m_fillColor(RGB(255, 255, 255)),
	m_outlineColor(RGB(0, 0, 0))
{
}

EllipseShape::EllipseShape(std::pair<int, int> pos, std::pair<int, int> size)
	:
	EllipseShape(pos.first, pos.second, size.first, size.second)
{
}

EllipseShape::EllipseShape(RECT rect)
	:
	EllipseShape(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top)
{
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
	m_width = width;
	m_height = height;
}

void EllipseShape::setSize(std::pair<int, int> size)
{
	setSize(size.first, size.second);
}

void EllipseShape::setRect(RECT rect)
{
	int width, height;
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	setPosition(rect.left, rect.top);
	setSize(width, height);
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

std::pair<int, int> EllipseShape::getPosition() const
{
	return std::pair<int, int>(m_x, m_y);
}

std::pair<int, int> EllipseShape::getSize() const
{
	return std::pair<int, int>(m_width, m_height);
}

RECT EllipseShape::getRect() const
{
	RECT rect;
	int width, height;
	width = m_x + m_width;
	height = m_y + m_height;
	SetRect(&rect, m_x, m_y, width, height);
	return rect;
}

RECT EllipseShape::draw(HDC hDC) const
{
	// Retrieve the ellipse's rectangle (used in the drawing function)
	RECT ellipseRect = getRect();

	SetDCPenColor(hDC, m_fillColor);
	SetDCBrushColor(hDC, m_fillColor);

	// Draw before the outline to support negative outlines
	Ellipse(hDC, ellipseRect.left, ellipseRect.top, ellipseRect.right, ellipseRect.bottom);

	// Draw an outline if it is specified
	if (m_outlineThickness != 0)
	{
		RECT outlineRect = getOutlineRect();
		drawOutline(hDC, outlineRect);

		// Return the outlineRect to be able to clear the outline every frame
		// Add a pixel in evry direction to be sure to clear the outline too
		// The getOutline() function is only semi good, and returns a pixel too small
		// to be there are no gaps between the circle and the outline
		outlineRect.left -= 1;
		outlineRect.top -= 1;
		outlineRect.right += 1;
		outlineRect.bottom += 1;
		return outlineRect;
	}
	else
	{
		// Return the ellipseRect when there is no outline
		return ellipseRect;
	}
}

void EllipseShape::drawOutline(HDC hDC, RECT outlineRect) const
{
	////////////////////////////////////////////
	// Setup

	// Create a logbrush which is using the the outlinecolor
	// retrieved from the parameter (needed in ExtCreatePen)
	LOGBRUSH lBrush = { BS_SOLID, m_outlineColor };
	// Use ExtCreatePen to be able to use PS_JOIN_MITER, which is used
	// to make the outline squared and not round (which is default)
	HPEN hOutlinePen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID | PS_JOIN_MITER,
		m_outlineThickness, &lBrush, 0, 0);
	// Select the new pen into the DC, and store the old pen
	HPEN hOldPen = (HPEN)SelectObject(hDC, hOutlinePen);
	// Finished setup
	////////////////////////////////////////////

	////////////////////////////////////////////
	// Start drawing the outline

	Arc(hDC, outlineRect.left, outlineRect.top, outlineRect.right, outlineRect.bottom,
		outlineRect.left, outlineRect.top, outlineRect.left, outlineRect.top);

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

RECT EllipseShape::getOutlineRect() const
{
	RECT outlineRect = getRect();
	int offset = 0;

	// Only semi good solution. Framing a circle without overlapping the
	// edge of the circle isn't possible (as far as I know).
	// Only one pixel is being currently overlapped, when using outlines
	if (m_outlineThickness == int(1 || -1))
	{
		offset = m_outlineThickness - 1;
	}
	else
	{
		if (m_outlineThickness % 2)
		{
			offset = m_outlineThickness / 2;
		}
		else
		{
			offset = m_outlineThickness - 1;
		}
	}

	outlineRect.left -= offset;
	outlineRect.top -= offset;
	outlineRect.right += offset;
	outlineRect.bottom += offset;

	return outlineRect;
}
