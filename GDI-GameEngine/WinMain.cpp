// Unnamed Desktop Project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Window.hpp"
#include "Graphics.hpp"
#include "Clock.hpp"
#include "RectangleShape.hpp"
#include <sstream>


// Global Variables:
HWND hMainWnd;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

	Window someWindow;

	Graphics gfx(someWindow.getWindowHandle());
	Clock clock;
	double dt;

	RectangleShape rect, otherRect;

	rect.setPosition(0, 0);
	rect.setSize(100, 100);
	rect.setFillColor(0, 255, 0);

	otherRect.setPosition(200, 200);
	otherRect.setSize(200, 200);
	otherRect.setFillColor(255, 0, 0);

    MSG msg;
	GetMessage(&msg, nullptr, 0, 0);

    // Main message loop:
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			dt = clock.restart();

			gfx.clear();
			gfx.draw(rect);
			gfx.draw(otherRect);
			gfx.display();

			rect.move(int(1000 * dt), 0);
		}
    }

    return (int) msg.wParam;
}