#pragma once
#include "EllipseShape.hpp"

class GDIWRAPPER_API CircleShape : public EllipseShape
{
public:
	CircleShape();
	CircleShape(double radius);
	CircleShape(int x, int y, double radius);
	CircleShape(std::pair<int, int> pos, double radius);

	void setRadius(double radius);

	const double getRadius() const;

private:
	using EllipseShape::setSize;
	using EllipseShape::setRect;

private:
	double m_radius;
};