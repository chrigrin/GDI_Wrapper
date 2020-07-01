#pragma once
#include "../GDI_Wrapper/framework.h"
#include <GDI_Wrapper/Export/Export.hpp>
#include <GDI_Wrapper/Graphics/Shapes/Shape.hpp>
#include "Color.hpp"
#include <vector>
#include <memory>

namespace gw
{
	class GDIWRAPPER_API Graphics
	{
	public:
		Graphics(HWND hWnd);
		~Graphics();

		Graphics(const Graphics &) = delete;
		Graphics operator=(const Graphics &) = delete;

		void clear(COLORREF color);
		void clear(Color color);
		void display() const;

		void draw(const Shape &shape);

	private:
		HWND m_hWnd;

		HDC m_backBuffer;
		int m_savedDC;
		HBITMAP m_hBmp, m_hBmpOld;
		RECT m_clientRect;
	};
}