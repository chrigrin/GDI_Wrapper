#pragma once
#include "../GDI-Wrapper/framework.h"
#include <Wrapper/Export/Export.hpp>

class GDIWRAPPER_API Window
{
private:
	class GDIWRAPPER_API WindowClass
	{
	public:
		static const wchar_t *getName();
		static HINSTANCE getInstance();
	private:
		WindowClass();
		~WindowClass();

		WindowClass(const WindowClass&) = delete;
		WindowClass operator=(const WindowClass&) = delete;

		static constexpr const wchar_t *wndClassName = L"MainClass";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window();
	~Window();

	HWND getWindowHandle() const;

private:
	static LRESULT CALLBACK handleMessageSetup(HWND m_hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK handleMessageThunk(HWND m_hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK handleMessage(HWND m_hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HWND m_hWnd;
	PAINTSTRUCT m_ps;
};