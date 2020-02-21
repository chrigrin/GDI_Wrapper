#pragma once

class Shape
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	virtual void setFillColor(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void setOutlineColor(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void setOutlineThickness(int outlineThickness) = 0;

	virtual void setPosition(int x, int y) = 0;
	virtual void setPosition(std::pair<int, int> pos) = 0;
	virtual void setSize(int x, int y) = 0;
	virtual void setSize(std::pair<int, int> size) = 0;
	virtual void setRect(RECT &rect) = 0;

	virtual void move(int x, int y) = 0;
	virtual void move(std::pair<int, int> distance) = 0;

	virtual const std::pair<int, int> getPosition() const = 0;
	virtual const std::pair<int, int> getSize() const = 0;
	virtual const RECT getRect() const = 0;

	virtual void draw(HDC &hDC) = 0;

protected:
	virtual void drawOutline(HDC &hDC, RECT outlineRect) = 0;
};