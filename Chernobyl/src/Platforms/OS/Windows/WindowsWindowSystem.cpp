#include "chpch.hpp"
#include "WindowsWindowSystem.hpp"

#include "SSO/System.hpp"

#include "WindowClasses.hpp"

#include <Windows.h>
#include <winuser.h>
#include <windowsx.h>

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

namespace CH
{
	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

static LRESULT CALLBACK FirstWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)CH::MainWndProc);
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

namespace CH
{
	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		CH::WindowData* data = (CH::WindowData*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));

#define EVENT_MANAGER System::GetSystem(SystemType::Event)->GetSubsystem<EventManager>()

		switch (msg)
		{

		///////////////////////////////
		// Window Events
		///////////////////////////////

		case WM_CLOSE:
		{
			EVENT_MANAGER->AddEvent<WindowCloseEvent>(WindowCloseEvent(*data));
			break;
		}
		case WM_SIZE:
		{
			data->Width = LOWORD(lParam);
			data->Height = HIWORD(lParam);

			EVENT_MANAGER->AddEvent<WindowResizeEvent>(WindowResizeEvent(data->Width, data->Height));

			break;
		}
		case WM_MOVE:
		{
			EVENT_MANAGER->AddEvent<WindowMoveEvent>(WindowMoveEvent(LOWORD(lParam), HIWORD(lParam)));

			break;
		}

		///////////////////////////////
		// Mouse Events
		///////////////////////////////

		// click

		case WM_LBUTTONDOWN:
		{
			Button<MouseCode> button;
			button.Code = Mouse::Left;
			button.ControlPressed = wParam & MK_CONTROL;
			button.ShiftPressed = wParam & MK_SHIFT;

			EVENT_MANAGER->AddEvent<MouseClickEvent>(MouseClickEvent(button));

			break;
		}
		case WM_RBUTTONDOWN:
		{
			Button<MouseCode> button;
			button.Code = Mouse::Right;
			button.ControlPressed = wParam & MK_CONTROL;
			button.ShiftPressed = wParam & MK_SHIFT;

			EVENT_MANAGER->AddEvent<MouseClickEvent>(MouseClickEvent(button));

			break;
		}
		case WM_MBUTTONDOWN:
		{
			Button<MouseCode> button;
			button.Code = Mouse::Middle;
			button.ControlPressed = wParam & MK_CONTROL;
			button.ShiftPressed = wParam & MK_SHIFT;

			EVENT_MANAGER->AddEvent<MouseClickEvent>(MouseClickEvent(button));

			break;
		}
		
		// release

		case WM_LBUTTONUP:
		{
			Button<MouseCode> button;
			button.Code = Mouse::Left;
			button.ControlPressed = wParam & MK_CONTROL;
			button.ShiftPressed = wParam & MK_SHIFT;

			EVENT_MANAGER->AddEvent<MouseReleaseEvent>(MouseReleaseEvent(button));

			break;
		}
		case WM_RBUTTONUP:
		{
			Button<MouseCode> button;
			button.Code = Mouse::Right;
			button.ControlPressed = wParam & MK_CONTROL;
			button.ShiftPressed = wParam & MK_SHIFT;

			EVENT_MANAGER->AddEvent<MouseReleaseEvent>(MouseReleaseEvent(button));

			break;
		}
		case WM_MBUTTONUP:
		{
			Button<MouseCode> button;
			button.Code = Mouse::Middle;
			button.ControlPressed = wParam & MK_CONTROL;
			button.ShiftPressed = wParam & MK_SHIFT;

			EVENT_MANAGER->AddEvent<MouseReleaseEvent>(MouseReleaseEvent(button));

			break;
		}

		// other

		case WM_MOUSEMOVE:
		{
			int32 xpos = GET_X_LPARAM(lParam);
			int32 ypos = GET_Y_LPARAM(lParam);

			EVENT_MANAGER->AddEvent<MouseMoveEvent>(MouseMoveEvent(xpos, ypos));

			break;
		}
		case WM_MOUSEWHEEL:
		{
			int32 offset = (float)GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
			EVENT_MANAGER->AddEvent<MouseScrollEvent>(MouseScrollEvent(offset));
		}

		///////////////////////////////
		// Keyboard Events
		///////////////////////////////

		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			Button<KeyCode> key;
			key.Code = wParam;
			key.ControlPressed = (GetAsyncKeyState(VK_CONTROL) & 0x8000);
			key.ShiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000);
			
			EVENT_MANAGER->AddEvent<KeyPressEvent>(KeyPressEvent(key));

			break;
		}
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			Button<KeyCode> key;
			key.Code = wParam;
			key.ControlPressed = (GetAsyncKeyState(VK_CONTROL) & 0x8000);
			key.ShiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000);

			EVENT_MANAGER->AddEvent<KeyReleaseEvent>(KeyReleaseEvent(key));

			break;
		}
		case WM_CHAR:
		{
			char c = (char)wParam;

			EVENT_MANAGER->AddEvent<KeyTypeEvent>(KeyTypeEvent(c));

			break;
		}

		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

}