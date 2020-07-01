#pragma once
#include "../GDI_Wrapper/framework.h"
#include <GDI_Wrapper/Export/Export.hpp>

namespace gw
{
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

			WindowClass(const WindowClass &) = delete;
			WindowClass operator=(const WindowClass &) = delete;

			static constexpr const wchar_t *wndClassName = L"MainClass";
			static WindowClass wndClass;
			HINSTANCE hInst;
		};
	public:
		Window();
		~Window();

		HWND getWindowHandle() const;

		bool isOpen() const;

		// Needed to handle any messages to the window
		bool processMessage();

		WPARAM getWParam() const;

	private:
		static LRESULT CALLBACK handleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK handleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK handleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_hWnd;
		PAINTSTRUCT m_ps;
		MSG m_msg;
	};
}