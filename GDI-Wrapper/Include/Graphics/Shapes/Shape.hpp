#pragma once
#include "../../Export/Export.hpp"
#include <utility>

class GDIWRAPPER_API Shape
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
	virtual void setRect(RECT rect) = 0;

	virtual void move(int x, const int y) = 0;
	virtual void move(std::pair<int, int> distance) = 0;

	virtual std::pair<int, int> getPosition() const = 0;
	virtual std::pair<int, int> getSize() const = 0;
	virtual RECT getRect() const = 0;

	virtual void draw(HDC hDC) const = 0;

protected:
	virtual void drawOutline(HDC hDC, RECT outlineRect) const = 0;
};