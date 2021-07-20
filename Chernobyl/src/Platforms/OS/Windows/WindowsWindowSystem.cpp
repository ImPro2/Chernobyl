#include "chpch.hpp"
#include "WindowsWindowSystem.hpp"

#include "WindowClasses.hpp"

#include <Windows.h>

static LRESULT CALLBACK FirstWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace CH
{

	void WindowsWindowSystem::Init()
	{
		/*
			UINT      cbSize;
			UINT      style;
			WNDPROC   lpfnWndProc;
			int       cbClsExtra;
			int       cbWndExtra;
			HINSTANCE hInstance;
			HICON     hIcon;
			HCURSOR   hCursor;
			HBRUSH    hbrBackground;
			LPCWSTR   lpszMenuName;
			LPCWSTR   lpszClassName;
			HICON     hIconSm;
		*/

		// initialize all window classes (so that other windows don't have to do that)

		{

			WNDCLASSEXA wc = {};
			wc.cbSize = sizeof(wc);
			wc.style = CS_OWNDC;
			wc.lpfnWndProc = FirstWndProc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = ::GetModuleHandle(nullptr);
			wc.hIcon = nullptr;
			wc.hCursor = nullptr;
			wc.hbrBackground = nullptr;
			wc.lpszMenuName = nullptr;
			wc.lpszClassName = CH_MAIN_WINDOW_CLASS;
			wc.hIconSm = nullptr;

			if (FAILED(RegisterClassExA(&wc)))
				CH_CORE_BREAK_S("Failed to initialize main window class");
		}

		// setup subsystems

		{

			// not any subsystems at the moment

		}

	}

	void WindowsWindowSystem::Shutdown()
	{
	}

}
static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static LRESULT CALLBACK FirstWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)MainWndProc);
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CH::WindowData* data = (CH::WindowData*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (msg)
	{
	case WM_CREATE:		break;
	case WM_CLOSE:		break;
	case WM_SIZE:
	{
		data->Width = LOWORD(lParam);
		data->Height = HIWORD(lParam);

		break;
	}
	case WM_MOVE:
	{
		CH_CORE_LOG(CH::LogSeverity::Trace, "Window position: {0}, {1}", LOWORD(lParam), HIWORD(lParam));
		break;
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}