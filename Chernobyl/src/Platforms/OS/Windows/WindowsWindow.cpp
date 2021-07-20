#include "chpch.hpp"
#include "WindowsWindow.hpp"

#include "WindowClasses.hpp"

namespace CH
{

	WindowsWindow::WindowsWindow(WindowData data)
		: mData(data)
	{
		CH_CORE_LOG(LogSeverity::Info, "Creating window {1} [{2}:{3}]", mData.Title.c_str(), mData.Width, mData.Height);

		mHandle = CreateWindowExA(
			WS_EX_OVERLAPPEDWINDOW,
			CH_MAIN_WINDOW_CLASS, mData.Title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			mData.Width, mData.Height,
			nullptr, nullptr, nullptr,
			&mData
		);

		CH_CORE_ASSERT(mHandle != NULL, "Failed to create window!");

		SetWindowLongPtrA(mHandle, GWLP_USERDATA, (LONG_PTR)(&mData));

		Show();
	}

	WindowsWindow::~WindowsWindow()
	{
		DestroyWindow(mHandle);
	}

	void WindowsWindow::Show()
	{
		ShowWindow(mHandle, SW_SHOW);
	}

	void WindowsWindow::Update()
	{
		MSG msg;
		while (PeekMessage(&msg, mHandle, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowsWindow::Close()
	{
		DestroyWindow(mHandle);
	}

	void WindowsWindow::SetSize(int32 width, int32 height)
	{
		mData.Width = width;
		mData.Height = height;
		::SetWindowPos(mHandle, HWND_TOP, CW_USEDEFAULT, CW_USEDEFAULT, width, height, SWP_NOMOVE);
	}

	void WindowsWindow::SetTitle(const String& title)
	{
		mData.Title = title;
		SetWindowTextA(mHandle, title.c_str());
	}

	void WindowsWindow::SetVSync(bool vsync)
	{
		// TODO: Set VSync
	}

}