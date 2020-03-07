#include "stdafx.h"
#include "Graphics/Shapes/CircleShape.hpp"

CircleShape::CircleShape()
{
	EllipseShape();
}

CircleShape::CircleShape(double radius)
	:
	m_radius(radius)
{
	int width, height;
	width = static_cast<int>(radius * 2);
	height = static_cast<int>(radius * 2);
	EllipseShape(width, height);
}

CircleShape::CircleShape(double radius, int x, int y)
{
	CircleShape(static_cast<double>(radius));
	EllipseShape::setPosition(x, y);
}

CircleShape::CircleShape(double radius, std::pair<int, int> pos)
{
	CircleShape(radius, pos.first, pos.second);
}

void CircleShape::setRadius(double radius)
{
	m_radius = radius;
	int width, height;
	width = static_cast<int>(radius * 2);
	height = static_cast<int>(radius * 2);

	EllipseShape::setSize(width, height);
}

const double CircleShape::getRadius() const
{
	return m_radius;
}
