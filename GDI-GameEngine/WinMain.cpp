// Unnamed Desktop Project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Window.hpp"
#include "Graphics.hpp"
#include "Clock.hpp"
#include "RectangleShape.hpp"
#include "EllipseShape.hpp"
#include "CircleShape.hpp"
#include <sstream>


// Global Variables:
HWND hMainWnd;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	Window someWindow;

	Graphics gfx(someWindow.getWindowHandle());
	Clock clock;
	double dt;

	RectangleShape rect, otherRect;

	rect.setPosition(100, 100);
	rect.setSize(100, 100);
	rect.setFillColor(0, 255, 0);
	rect.setOutlineThickness(50);
	rect.setOutlineColor(0, 0, 255);

	otherRect.setPosition(200, 200);
	otherRect.setSize(200, 200);
	otherRect.setFillColor(255, 0, 0);

	EllipseShape ellipse;

	ellipse.setSize(100, 100);
	ellipse.setPosition(500, 0);
	ellipse.setFillColor(0, 255, 255);
	ellipse.setOutlineColor(255, 255, 0);
	ellipse.setOutlineThickness(20);

	CircleShape circle;

	circle.setPosition(650, 0);
	circle.setRadius(33.33);
	circle.setFillColor(255, 0, 255);
	circle.setOutlineColor(128, 255, 128);
	circle.setOutlineThickness(20);

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
			gfx.draw(ellipse);
			gfx.draw(circle);
			gfx.display();

			std::wstring wstr = std::to_wstring(dt);
			SetWindowText(someWindow.getWindowHandle(), wstr.c_str());
			//rect.move(int(1000 * dt), 0);
		}
    }

    return (int) msg.wParam;
}