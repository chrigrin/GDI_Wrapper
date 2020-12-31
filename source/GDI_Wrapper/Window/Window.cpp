#include <GDI_Wrapper/Window/Window.hpp>

namespace gw
{
	// Initialize the windowclass at compile time to make the linker happy
	Window::WindowClass Window::WindowClass::wndClass;

	const wchar_t *Window::WindowClass::getName()
	{
		return wndClassName;
	}

	HINSTANCE Window::WindowClass::getInstance()
	{
		return wndClass.hInst;
	}

	Window::WindowClass::WindowClass()
		:
		// Set the HINSTANCE to the instance of the program
		hInst(GetModuleHandle(nullptr))
	{
		// Initialize a windowclass and set all members empty
		WNDCLASSEXW wc = { 0 };
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

		// Register the windowclass
		RegisterClassExW(&wc);
	}

	Window::WindowClass::~WindowClass()
	{
		// Unregister the window class
		UnregisterClassW(wndClassName, hInst);
	}

	Window::Window()
		:
		Window(L"GDI_Wrapper", CW_USEDEFAULT, 0)
	{
	}

	Window::Window(const std::wstring &name)
		:
		Window(name, CW_USEDEFAULT, 0)
	{
	}

	Window::Window(double width, double height)
		:
		Window(L"GDI_Wrapper", width, height)
	{
	}

	Window::Window(const std::wstring &name, double width, double height)
		:
		m_ps{ 0 }
	{

		RECT desiredRect = { 0 };

		desiredRect.right = width;
		desiredRect.bottom = height;

		if (width != CW_USEDEFAULT)
			AdjustWindowRect(&desiredRect, WS_CAPTION, FALSE);

		// Create a window and store a pointer to this class in the lpParam
		m_hWnd = CreateWindowW(WindowClass::getName(), name.c_str(), WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT, 0, desiredRect.right - desiredRect.left, desiredRect.bottom - desiredRect.top, nullptr, nullptr, WindowClass::getInstance(), this);

		// Show the window and update it
		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);

		GetMessageW(&m_msg, nullptr, 0, 0);

		// Debugging code
		/*RECT rect, windowRect;
		GetWindowRect(m_hWnd, &windowRect);
		GetClientRect(m_hWnd, &rect);
		SetWindowTextW(m_hWnd, std::to_wstring(rect.bottom - rect.top).c_str());*/
	}

	Window::~Window()
	{
		DestroyWindow(m_hWnd);
	}

	HWND Window::getWindowHandle() const
	{
		return m_hWnd;
	}

	bool Window::isOpen() const
	{
		return m_msg.message != WM_QUIT;
	}

	bool Window::processMessage()
	{
		if (PeekMessageW(&m_msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_msg);
			DispatchMessageW(&m_msg);
			return true;
		}
		return false;
	}

	WPARAM Window::getWParam() const
	{
		return m_msg.wParam;
	}

	LRESULT Window::handleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_NCCREATE)
		{
			// Create a pointer to the createstruct in WM_NCCREATE's LPARAM
			const CREATESTRUCT *const pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
			// Create a pointer to the window from the pCreate's lpParams
			Window *pWnd = reinterpret_cast<Window *>(pCreate->lpCreateParams);
			// Set the userdata of the window to a pointer of the window
			SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			// Set the window procedure to the handleMessageThunk
			SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::handleMessageThunk));
			// Call the messageHandler
			return pWnd->handleMessage(hWnd, msg, wParam, lParam);
		}
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	LRESULT Window::handleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// Retrieve a pointer to the window
		Window *const pWnd = reinterpret_cast<Window *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		// Call the messageHandler
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
		case WM_PAINT:
		{
			BeginPaint(hWnd, &m_ps);

			EndPaint(hWnd, &m_ps);
		}
		break;
		case WM_CREATE:
		{
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
}