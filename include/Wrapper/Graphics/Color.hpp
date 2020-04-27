#pragma once
#include <Wrapper/Export/Export.hpp>

class GDIWRAPPER_API Color
{
public:
	Color();
	Color(unsigned char r, unsigned char g, unsigned char b);
	~Color();

	unsigned char r, g, b;
};