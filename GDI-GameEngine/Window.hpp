#pragma once

class Window
{
private:
	class WindowClass
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

	const HWND getWindowHandle() const;

private:
	static LRESULT CALLBACK handleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK handleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK handleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HWND hWnd;
	PAINTSTRUCT ps;
};