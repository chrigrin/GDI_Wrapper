// Unnamed Desktop Project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <sstream>
#include <vector>
#include <algorithm>

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
	Window someWindow;

	Graphics gfx(someWindow.getWindowHandle());
	Clock clock;
	double dt;

	std::vector<std::unique_ptr<Shape>> myShapes;

	{
		auto rect = std::make_unique<RectangleShape>(100, 100, 100, 100);
		rect->setFillColor({ 0, 255, 0 });
		rect->setOutlineThickness(1);
		rect->setOutlineColor({0, 0, 255});
		
		myShapes.push_back(std::move(rect));
	}
	{
		auto rect = std::make_unique<RectangleShape>(200, 200, 200, 200);
		rect->setFillColor({ 255, 0, 0 });

		myShapes.push_back(std::move(rect));
	}
	EllipseShape *myEllipse = nullptr;
	{
		auto ellipse = std::make_unique<EllipseShape>();

		ellipse->setSize(200, 100);
		ellipse->setPosition(500, 0);
		ellipse->setFillColor({ 0, 255, 255 });
		ellipse->setOutlineColor({ 255, 255, 0 });
		ellipse->setOutlineThickness(3);

		myEllipse = ellipse.get();
		myShapes.push_back(std::move(ellipse));
	}
	{
		auto circle = std::make_unique<CircleShape>();
		circle->setPosition(650, 0);
		circle->setRadius(33.33);
		circle->setFillColor({ 0, 255, 255 });
		circle->setOutlineColor({255, 255, 0});
		circle->setOutlineThickness(1);

		myShapes.push_back(std::move(circle));
	}

    // Main message loop:
    while (someWindow.isOpen())
    {
		someWindow.processMessage();

		dt = clock.getElapsedTime();

		gfx.clear({ 0, 0, 0 });

		for (auto &shape : myShapes)
		{
			gfx.draw((*shape.get()));
		}

		gfx.display();

		myEllipse->move(1, 1);

		std::wstring wstr = std::to_wstring(dt);
		SetWindowText(someWindow.getWindowHandle(), wstr.c_str());
		//rect.move(1, 0);
		//ellipse.move(0, 1);
    }

	return static_cast<int>(someWindow.getWParam());
}