#pragma once
#include "EllipseShape.hpp"

class GDIWRAPPER_API CircleShape : public EllipseShape
{
public:
	CircleShape();
	CircleShape(double radius);
	CircleShape(double x, double y, double radius);
	CircleShape(std::pair<double, double> pos, double radius);

	void setRadius(double radius);

	const double getRadius() const;

private:
	using EllipseShape::setSize;
	using EllipseShape::setRect;

private:
	double m_radius;
};