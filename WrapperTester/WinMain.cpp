// Unnamed Desktop Project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include "Snake.hpp"

namespace {

	class BrushGuard
	{
		HBRUSH m_brush;

	public:
		BrushGuard(HBRUSH brush) : m_brush(brush) {}

		~BrushGuard()
		{
			DeleteObject(static_cast<HGDIOBJ>(m_brush));
		}

		HBRUSH get() const
		{
			return m_brush;
		}
	};
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	gw::Window someWindow;

	gw::Graphics gfx(someWindow.getWindowHandle());
	gw::Clock clock;
	gw::Time dt;

	Snake snake;

    // Main message loop:
    while (someWindow.isOpen())
    {
		someWindow.processMessage();

		dt = clock.getElapsedTime();

		///////////////////////////////
		// Update loop here
		// 
		
		snake.update(dt);

		///////////////////////////////

		gfx.clear({ 0, 0, 0 });

		// Draw here
		snake.draw(gfx);

		gfx.display();

		//std::wstring wstr = std::to_wstring(dt.asNanoseconds());
		//SetWindowTextW(someWindow.getWindowHandle(), wstr.c_str());
		//rect.move(1, 0);
		//ellipse.move(0, 1);
    }

	return static_cast<int>(someWindow.getWParam());
}