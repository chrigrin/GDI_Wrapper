#pragma once
#include "EllipseShape.hpp"

class CircleShape : public EllipseShape
{
public:
	CircleShape();
	CircleShape(double radius);
	CircleShape(double radius, int x, int y);
	CircleShape(double radius, std::pair<int, int> pos);

	void setRadius(double radius);

	const double getRadius() const;

private:
	using EllipseShape::setSize;
	using EllipseShape::setRect;

private:
	double m_radius;
};