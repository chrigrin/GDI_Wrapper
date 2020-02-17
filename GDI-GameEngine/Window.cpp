#include "stdafx.h"
#include "Window.hpp"

Window::WindowClass Window::WindowClass::wndClass;

const wchar_t * Window::WindowClass::getName()
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::getInstance()
{
	return wndClass.hInst;
}

Window::WindowClass::WindowClass()
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = nullptr;
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hInstance = hInst;
	wc.lpfnWndProc = handleMessageSetup;
	wc.lpszClassName = wndClassName;
	wc.lpszMenuName = nullptr;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, hInst);
}

Window::Window()
{
	hWnd = CreateWindow(WindowClass::getName(), L"Desktop", WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, WindowClass::getInstance(), this);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
}

const HWND Window::getWindowHandle() const
{
	return hWnd;
}

LRESULT Window::handleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window *pWnd = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handleMessageThunk));
		pWnd->handleMessage(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::handleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->handleMessage(hWnd, msg, wParam, lParam);
}

LRESULT Window::handleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		}
	}
	break;
	case WM_ERASEBKGND:
		return TRUE;
		break;
	case WM_PAINT:
	{
		BeginPaint(hWnd, &ps);

		//BitBlt(dcBuffer, 0, 0, clientRect.right, clientRect.bottom, nullptr, 0, 0, BLACKNESS);
		//BitBlt(hDC, 0, 0, clientRect.right, clientRect.bottom, nullptr, 0, 0, BLACKNESS);

		//FillRect(dcBuffer, &someRect, CreateSolidBrush(RGB(0, 255, 0)));

		//BitBlt(ps.hdc, 0, 0, clientRect.right, clientRect.bottom, dcBuffer, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
		break;
	case WM_CREATE:
	{
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
