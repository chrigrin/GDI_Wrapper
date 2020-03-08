#include <Wrapper/Graphics/Shapes/CircleShape.hpp>

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

CircleShape::CircleShape(int x, int y, double radius)
	:
	EllipseShape(x, y, static_cast<int>(radius * 2), static_cast<int>(radius * 2)),
	m_radius(radius)
{
}

CircleShape::CircleShape(std::pair<int, int> pos, double radius)
	:
	CircleShape(pos.first, pos.second, radius)
{
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
