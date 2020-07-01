#include "framework.h"
#include "GDI_Wrapper/Graphics/Color.hpp"

Color::Color()
	:
	r(0),
	g(0),
	b(0)
{
}

Color::Color(unsigned char r, unsigned char g, unsigned char b)
	:
	r(r),
	g(g),
	b(b)
{
}

Color::~Color()
{
}
