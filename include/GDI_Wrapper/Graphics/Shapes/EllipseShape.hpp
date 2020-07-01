#pragma once
#include "Shape.hpp"

class GDIWRAPPER_API EllipseShape : public Shape
{
public:
	EllipseShape();
	EllipseShape(double width, double height);
	EllipseShape(std::pair<double, double> size);
	EllipseShape(double x, double y, double width, double height);
	EllipseShape(std::pair<double, double> pos, std::pair<double, double> size);
	EllipseShape(RECT rect);

	void setFillColor(Color color) override;
	void setOutlineColor(Color color) override;
	void setOutlineThickness(int outlineThickness) override;

	void setPosition(double x, double y) override;
	void setPosition(std::pair<double, double> pos) override;
	void setSize(double width, double height) override;
	void setSize(std::pair<double, double> size) override;
	void setRect(RECT rect) override;

	void move(double x, double y) override;
	void move(std::pair<double, double> distance) override;

	std::pair<double, double> getPosition() const override;
	std::pair<double, double> getSize() const override;
	RECT getRect() const override;
	RECT getTotalRect() const override;

	void draw(HDC hDC) const override;

private:
	RECT getOutlinedRect(RECT rect) const override;
	void drawOutline(HDC hDC, RECT outlineRect) const;

private:
	double m_x, m_y;
	double m_width, m_height;
	int m_outlineThickness;
	COLORREF m_fillColor, m_outlineColor;
};