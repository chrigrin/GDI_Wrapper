#include <GDI_Wrapper/Graphics/Shapes/EllipseShape.hpp>

EllipseShape::EllipseShape()
	:
	EllipseShape(0, 0, 0, 0)
{
}

EllipseShape::EllipseShape(double width, double height)
	:
	EllipseShape(0, 0, width, height)
{
}

EllipseShape::EllipseShape(std::pair<double, double> size)
	:
	EllipseShape(0, 0, size.first, size.second)
{
}

EllipseShape::EllipseShape(double x, double y, double width, double height)
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

EllipseShape::EllipseShape(std::pair<double, double> pos, std::pair<double, double> size)
	:
	EllipseShape(pos.first, pos.second, size.first, size.second)
{
}

EllipseShape::EllipseShape(RECT rect)
	:
	EllipseShape(rect.left,
		rect.top,
		static_cast<double>(rect.right) - static_cast<double>(rect.left),
		static_cast<double>(rect.bottom) - static_cast<double>(rect.top))
{
}

void EllipseShape::setFillColor(Color color)
{
	m_fillColor = RGB(color.r, color.g, color.b);
}

void EllipseShape::setOutlineColor(Color color)
{
	m_outlineColor = RGB(color.r, color.g, color.b);
}

void EllipseShape::setOutlineThickness(int outlineThickness)
{
	m_outlineThickness = outlineThickness;
}

void EllipseShape::setPosition(double x, double y)
{
	m_x = x;
	m_y = y;
}

void EllipseShape::setPosition(std::pair<double, double> pos)
{
	setPosition(pos.first, pos.second);
}

void EllipseShape::setSize(double width, double height)
{
	m_width = width;
	m_height = height;
}

void EllipseShape::setSize(std::pair<double, double> size)
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

void EllipseShape::move(double x, double y)
{
	m_x += x;
	m_y += y;
}

void EllipseShape::move(std::pair<double, double> distance)
{
	move(distance.first, distance.second);
}

std::pair<double, double> EllipseShape::getPosition() const
{
	return std::pair<double, double>(m_x, m_y);
}

std::pair<double, double> EllipseShape::getSize() const
{
	return std::pair<double, double>(m_width, m_height);
}

RECT EllipseShape::getRect() const
{
	return RECT{	
		static_cast<LONG>(m_x), 
		static_cast<LONG>(m_y), 
		static_cast<LONG>(m_x + m_width), 
		static_cast<LONG>(m_y + m_height) 
	};
}

RECT EllipseShape::getTotalRect() const
{
	RECT rect = getRect();
	RECT outlineRect = getOutlinedRect(rect);
	RECT totalRect = getOutlinedRect(outlineRect);

	if (m_outlineThickness % 2)
	{
		totalRect.left -= 1;
		totalRect.top -= 1;
		totalRect.right += 1;
		totalRect.bottom += 1;
	}

	return totalRect;
}

void EllipseShape::draw(HDC hDC) const
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
		RECT outlineRect = getOutlinedRect(ellipseRect);
		drawOutline(hDC, outlineRect);
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

RECT EllipseShape::getOutlinedRect(RECT rect) const
{
	RECT outlineRect = rect;
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
