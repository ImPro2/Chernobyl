#include "chpch.hpp"
#include "WindowsWindow.hpp"

#include "WindowClasses.hpp"

namespace CH
{

	WindowsWindow::WindowsWindow(WindowData data)
		: mData(data)
	{
		CH_PROFILE_FUNCTION();

		CH_CORE_LOG(LogSeverity::Info, "Creating window {} [{}:{}]", mData.Title.c_str(), mData.Width, mData.Height);

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
		CH_PROFILE_FUNCTION();

		DestroyWindow(mHandle);
	}

	void WindowsWindow::Show()
	{
		CH_PROFILE_FUNCTION();

		ShowWindow(mHandle, SW_SHOW);
	}

	void WindowsWindow::Update()
	{
		CH_PROFILE_FUNCTION();

		MSG msg;
		while (PeekMessage(&msg, mHandle, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowsWindow::Close()
	{
		CH_PROFILE_FUNCTION();

		DestroyWindow(mHandle);
	}

	void WindowsWindow::SetSize(int32 width, int32 height)
	{
		CH_PROFILE_FUNCTION();

		mData.Width = width;
		mData.Height = height;
		::SetWindowPos(mHandle, HWND_TOP, CW_USEDEFAULT, CW_USEDEFAULT, width, height, SWP_NOMOVE);
	}

	void WindowsWindow::SetTitle(const String& title)
	{
		CH_PROFILE_FUNCTION();

		mData.Title = title;
		SetWindowTextA(mHandle, title.c_str());
	}

	void WindowsWindow::SetVSync(bool vsync)
	{
		CH_PROFILE_FUNCTION();
		// TODO: Set VSync
	}

}