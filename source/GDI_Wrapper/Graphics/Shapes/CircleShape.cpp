#include <GDI_Wrapper/Graphics/Shapes/CircleShape.hpp>

CircleShape::CircleShape()
	:
	CircleShape(0, 0, 0)
{
}

CircleShape::CircleShape(double radius)
	:
	CircleShape(0, 0, radius)
{
}

CircleShape::CircleShape(double x, double y, double radius)
	:
	EllipseShape(x, y, radius * 2, radius * 2),
	m_radius(radius)
{
}

CircleShape::CircleShape(std::pair<double, double> pos, double radius)
	:
	CircleShape(pos.first, pos.second, radius)
{
}

void CircleShape::setRadius(double radius)
{
	m_radius = radius;
	double width, height;
	width = radius * 2;
	height = radius * 2;

	EllipseShape::setSize(width, height);
}

const double CircleShape::getRadius() const
{
	return m_radius;
}
