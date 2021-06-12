#include "chpch.h"
#include "WindowsWindow.h"

#include "Chernobyl/Core/Application.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace CH
{

	WindowsWindow::WindowsWindow(WindowData data)
	{
		m_Data.Width = data.Width;
		m_Data.Height = data.Height;
		m_Data.Title = data.Title;
		m_Data.VSyncEnabled = data.VSyncEnabled;

		m_Data.IsOpen = true;

		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = ::GetModuleHandle(nullptr);
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = TEXT("Main_Window_Class");
		wc.hIconSm = nullptr;

		CH_ASSERT(SUCCEEDED(::RegisterClassEx(&wc)), "Failed to register window class {0}", "Main_Window_Class");

		Init();
	}

	void WindowsWindow::Init()
	{
		CH_CORE_INFO("Creating window {0}: Size: ({1}, {2}), VSyncEnabled: ({3})", m_Data.Title, m_Data.Width, m_Data.Height, m_Data.VSyncEnabled);

		m_Handle = ::CreateWindowExA(
			WS_EX_OVERLAPPEDWINDOW,
			"Main_Window_Class", m_Data.Title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			m_Data.Width, m_Data.Height,
			nullptr, nullptr, nullptr,
			&m_Data
		);

		CH_ASSERT(m_Handle, "Failed to initialize window {0}", m_Data.Title);

		::SetWindowLongPtr(m_Handle, GWLP_USERDATA, (LONG_PTR)(&m_Data));

		::ShowWindow(m_Handle, SW_SHOW);

		m_Context = Context::Create(m_Handle);
		m_Context->Init();
	}

	WindowsWindow::~WindowsWindow()
	{
		::DestroyWindow(m_Handle);
	}

	void WindowsWindow::Update()
	{
		m_Data.FirstEventIteration = true;
		MSG msg;
		while (::PeekMessage(&msg, m_Handle, 0, 0, PM_REMOVE) > 0)
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		m_Context->SwapBuffers(m_Data.VSyncEnabled);
	}

	LRESULT CALLBACK WindowsWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindowData* data = (WindowsWindowData*)(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		switch (uMsg)
		{
		case WM_CLOSE:
		{
			AppCloseEvent e(0);
			data->EventCallback(e);
			data->IsOpen = false;
			CH_CORE_INFO("Closing window {0}", data->Title);
			break;
		}
		case WM_SIZE:
		{
			if (Application::Get()->GetStats().FrameCount == 0) break;

			int width, height;
			width = (int)LOWORD(lParam);
			height = (int)HIWORD(lParam);

			data->Width = width;
			data->Height = height;
			data->EventCallback(WindowResizeEvent(width, height));
			break;
		}

		case WM_MOUSEMOVE:
		{
			POINTS pt = MAKEPOINTS(lParam);

			//data->EventCallback(MouseMoveEvent(pt.x, pt.y));
			//
			//if (pt.x < 0 || pt.x > data->Width || pt.y < 0 || pt.y > data->Height)
			//	::SetCapture(hWnd);

			// mouse in client region
			if (pt.x > 0 && pt.x < data->Width && pt.y > 0 && pt.y < data->Height)
			{
				data->EventCallback(MouseMoveEvent(pt.x, pt.y));

				if (pt.x != data->LastMouseX && pt.y != data->LastMouseY)
					::SetCapture(hWnd);
			}
			else // not in client region
			{
				if (wParam & (MK_LBUTTON | MK_RBUTTON | MK_MBUTTON))
					data->EventCallback(MouseMoveEvent(pt.x, pt.y));
				else
					::ReleaseCapture();
			}

			data->LastMouseX = pt.x;
			data->LastMouseY = pt.y;

			break;
		}
		case WM_LBUTTONDOWN:
		{
			MouseButtonClickEvent e(VK_LBUTTON);
			data->EventCallback(e);
			break;
		}
		case WM_LBUTTONUP:
		{
			MouseButtonReleaseEvent e(VK_LBUTTON);
			data->EventCallback(e);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			data->EventCallback(MouseButtonClickEvent(VK_RBUTTON));
			break;
		}
		case WM_RBUTTONUP:
		{
			data->EventCallback(MouseButtonReleaseEvent(VK_RBUTTON));
			break;
		}
		case WM_MBUTTONDOWN:
		{
			data->EventCallback(MouseButtonClickEvent(VK_MBUTTON));
			break;
		}
		case WM_MBUTTONUP:
		{
			data->EventCallback(MouseButtonReleaseEvent(VK_MBUTTON));
			break;
		}
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			int repeatCount = (lParam & 0xffff);
			data->EventCallback(KeyPressEvent((int8)wParam));
			break;
		}
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			data->EventCallback(KeyReleaseEvent((int8)wParam));
			break;
		}
		case WM_CHAR:
		{
			data->EventCallback(KeyTypeEvent((int8)wParam));
			break;
		}
		default:
		{
			if (Application::Get()->GetStats().FrameCount == 1 && data->FirstEventIteration)
				data->EventCallback(AppCreateEvent());
		}
		}
		if (Application::Get()->GetStats().FrameCount > 0)
			data->FirstEventIteration = false;

		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

}