#include <GDI_Wrapper/Graphics/Shapes/RectangleShape.hpp>

RectangleShape::RectangleShape()
	:
	RectangleShape(0, 0, 0, 0)
{
}

RectangleShape::RectangleShape(double width, double height)
	:
	RectangleShape(0, 0, width, height)
{
}

RectangleShape::RectangleShape(std::pair<double, double> size)
	:
	RectangleShape(0,0, size.first, size.second)
{
}

RectangleShape::RectangleShape(double x, double y, double width, double height)
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

RectangleShape::RectangleShape(std::pair<double, double> pos, std::pair<double, double> size)
	:
	RectangleShape(pos.first, pos.second, size.first, size.second)
{
}

RectangleShape::RectangleShape(RECT rect)
	:
	RectangleShape(rect.left,
		rect.top,
		static_cast<double>(rect.right) - static_cast<double>(rect.left),
		static_cast<double>(rect.bottom) - static_cast<double>(rect.top))
{
}

RectangleShape::~RectangleShape()
{
}

void RectangleShape::setFillColor(Color color)
{
	m_fillColor = RGB(color.r, color.g, color.b);
}

void RectangleShape::setOutlineColor(Color color)
{
	m_outlineColor = RGB(color.r, color.g, color.b);
}

void RectangleShape::setOutlineThickness(int outlineThickness)
{
	m_outlineThickness = outlineThickness;
}

void RectangleShape::setPosition(double x, double y)
{
	m_x = x;
	m_y = y;
}

void RectangleShape::setPosition(std::pair<double, double> pos)
{
	setPosition(pos.first, pos.second);
}

void RectangleShape::setSize(double width, double height)
{
	m_width = width;
	m_height = height;
}

void RectangleShape::setSize(std::pair<double, double> size)
{
	setSize(size.first, size.second);
}

void RectangleShape::setRect(RECT rect)
{
	int width, height;
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	setPosition(rect.left, rect.top);
	setSize(width, height);
}

void RectangleShape::move(double x, double y)
{
	m_x += x;
	m_y += y;
}

void RectangleShape::move(std::pair<double, double> distance)
{
	move(distance.first, distance.second);
}

std::pair<double, double> RectangleShape::getPosition() const
{
	return std::pair<double, double>(m_x, m_y);
}

std::pair<double, double> RectangleShape::getSize() const
{
	return std::pair<double, double>(m_width, m_height);
}

RECT RectangleShape::getRect() const
{
	return RECT{
		static_cast<LONG>(m_x),
		static_cast<LONG>(m_y),
		static_cast<LONG>(m_x + m_width),
		static_cast<LONG>(m_y + m_height)
	};
}

RECT RectangleShape::getTotalRect() const
{
	RECT rect = getRect();
	RECT outlineRect = getOutlinedRect(rect);
	RECT totalRect = getOutlinedRect(outlineRect);

	if (m_outlineThickness % 2 == 0)
	{
		totalRect.left -= 1;
		totalRect.top -= 1;
		totalRect.right += 1;
		totalRect.bottom += 1;
	}

	return totalRect;
}

void RectangleShape::draw(HDC hDC) const
{
	// Retrieve the rectangle to draw
	RECT rect = getRect();

	// Variables used for error checks on setting DC pen and brush
	COLORREF returnPen, returnBrush;

	// Set pen color (outer points of the rectangle)
	returnPen = SetDCPenColor(hDC, m_fillColor);
	// Set brush color (fill color of the rectangle)
	returnBrush = SetDCBrushColor(hDC, m_fillColor);

	// Error checks
	if (returnPen == CLR_INVALID)
		MessageBox(nullptr, L"Could not set pen color", L"Error", MB_ICONERROR);
	if (returnBrush == CLR_INVALID)
		MessageBox(nullptr, L"Could not set brush color", L"Error", MB_ICONERROR);

	// Draw the rectangle before the outline to support negative outlines
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

	// If an outline is specified create a an outline for the rectangle
	if (m_outlineThickness != 0)
	{
		RECT outlineRect = getOutlinedRect(rect);
		drawOutline(hDC, outlineRect);
	}
}

RECT RectangleShape::getOutlinedRect(RECT rect) const
{
	// Retrieve the rectangle to be outlined
	RECT outlinedRect = rect;

	int offset = 0;
	if (m_outlineThickness == int(1 || -1))
	{
		// (1 / 2) of an int would be 0, therefore set the offset
		// to the outlineThickness
		offset = m_outlineThickness;
		outlinedRect.left -= offset;
		outlinedRect.top -= offset;
		outlinedRect.right += offset;
		outlinedRect.bottom += offset;
	}
	else
	{
		offset = m_outlineThickness / 2;
		outlinedRect.right += (offset + 1);
		outlinedRect.bottom += (offset + 1);

		// Odd numbers
		if (m_outlineThickness % 2)
		{
			outlinedRect.left -= (offset + 1);
			outlinedRect.top -= (offset + 1);
		}
		// Even numbers
		else
		{
			outlinedRect.left -= offset;
			outlinedRect.top -= offset;
		}
	}
	return outlinedRect;
}

void RectangleShape::drawOutline(HDC hDC, RECT outlineRect) const
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

	// Call begin path to start capturing GDI shapes into a path
	BeginPath(hDC);

	// Draw the outline rectangle to the path
	Rectangle(hDC, outlineRect.left, outlineRect.top, outlineRect.right, outlineRect.bottom);
	
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
