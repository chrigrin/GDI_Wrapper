#pragma once
#include "Shape.hpp"

class RectangleShape : public Shape
{
public:
	RectangleShape();
	RectangleShape(int width, int height);
	RectangleShape(int x, int y, int width, int height);
	RectangleShape(std::pair<int, int> pos, std::pair<int, int> size);
	RectangleShape(RECT &rect);
	virtual ~RectangleShape();

	void setFillColor(unsigned char r, unsigned char g, unsigned char b) override;
	void setOutlineColor(unsigned char r, unsigned char g, unsigned char b) override;
	void setOutlineThickness(int outlineThickness);

	void setPosition(int x, int y) override;
	void setPosition(std::pair<int, int> pos) override;
	void setSize(int width, int height) override;
	void setSize(std::pair<int, int> size) override;
	void setRect(RECT &rect) override;

	void move(int x, int y) override;
	void move(std::pair<int, int> distance) override;

	std::pair<int, int> getPosition() override;
	std::pair<int, int> getSize() override;
	RECT getRect() override;

	void draw(HDC &hDC) override;

private:
	int m_x, m_y;
	int m_width, m_height;
	int m_outlineThickness;
	COLORREF m_fillColor, m_outlineColor;
};