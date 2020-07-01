#pragma once
#include <GDI_Wrapper/Export/Export.hpp>

namespace gw
{
	class GDIWRAPPER_API Color
	{
	public:
		Color();
		Color(unsigned char r, unsigned char g, unsigned char b);
		~Color();

		unsigned char r, g, b;
	};
}