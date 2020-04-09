#pragma once
#include "Shape.hpp"

class GDIWRAPPER_API RectangleShape : public Shape
{
public:
	RectangleShape();
	RectangleShape(double width, double height);
	RectangleShape(std::pair<double, double> size);
	RectangleShape(double x, double y, double width, double height);
	RectangleShape(std::pair<double, double> pos, std::pair<double, double> size);
	RectangleShape(RECT rect);
	virtual ~RectangleShape();

	void setFillColor(unsigned char r, unsigned char g, unsigned char b) override;
	void setOutlineColor(unsigned char r, unsigned char g, unsigned char b) override;
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
	void drawOutline(HDC hDC, RECT outlineRect) const override;

private:
	double m_x, m_y;
	double m_width, m_height;
	int m_outlineThickness;
	COLORREF m_fillColor, m_outlineColor;
};