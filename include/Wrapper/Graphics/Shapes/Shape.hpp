#pragma once
#include "../GDI-Wrapper/framework.h"
#include <Wrapper/Export/Export.hpp>
#include <Windows.h>
#include <utility>

class GDIWRAPPER_API Shape
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	virtual void setFillColor(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void setOutlineColor(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void setOutlineThickness(int outlineThickness) = 0;

	virtual void setPosition(double x, double y) = 0;
	virtual void setPosition(std::pair<double, double> pos) = 0;
	virtual void setSize(double x, double y) = 0;
	virtual void setSize(std::pair<double, double> size) = 0;
	virtual void setRect(RECT rect) = 0;

	virtual void move(double x, double y) = 0;
	virtual void move(std::pair<double, double> distance) = 0;

	virtual std::pair<double, double> getPosition() const = 0;
	virtual std::pair<double, double> getSize() const = 0;
	virtual RECT getRect() const = 0;
	virtual RECT getTotalRect() const = 0;

	virtual void draw(HDC hDC) const = 0;

protected:
	virtual RECT getOutlinedRect(RECT rect) const = 0;
	virtual void drawOutline(HDC hDC, RECT outlineRect) const = 0;
};