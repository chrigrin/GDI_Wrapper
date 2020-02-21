#pragma once
#include "Shape.hpp"

class EllipseShape : public Shape
{
public:
	EllipseShape();
	EllipseShape(double radius);
	EllipseShape(int width, int height);
	EllipseShape(std::pair<int, int> size);
	EllipseShape(double radius, int x, int y);
	EllipseShape(double radius, std::pair<int, int> pos);
	EllipseShape(int width, int height, int x, int y);
	EllipseShape(std::pair<int, int> size, std::pair<int, int> pos);
	EllipseShape(RECT rect);

	void setFillColor(unsigned char r, unsigned char g, unsigned char b) override;
	void setOutlineColor(unsigned char r, unsigned char g, unsigned char b) override;
	void setOutlineThickness(int outlineThickness) override;

	void setPosition(int x, int y) override;
	void setPosition(std::pair<int, int> pos) override;
	void setSize(int width, int height) override;
	void setSize(std::pair<int, int> size) override;
	void setRect(RECT &rect) override;
	void setRadius(double radius);

	void move(int x, int y) override;
	void move(std::pair<int, int> distance) override;

	const std::pair<int, int> getPosition() const override;
	const std::pair<int, int> getSize() const override;
	const RECT getRect() const override;
	// If the width and height are different, getRadius()
	// returns 0
	const double getRadius() const;

	void draw(HDC &hDC) override;

private:
	void drawOutline(HDC &hDC, RECT outlineRect);

private:
	int m_x, m_y;
	int m_width, m_height;
	double m_radius;
	int m_outlineThickness;
	COLORREF m_fillColor, m_outlineColor;
};