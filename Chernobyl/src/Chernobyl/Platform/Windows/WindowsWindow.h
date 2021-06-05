#pragma once

#include "Chernobyl/Window/WindowInterface.h"
#include "Chernobyl/Renderer/Context.h"

#include <Windows.h>

namespace CH
{

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(WindowData data);
		~WindowsWindow();

		virtual int32                 GetWidth()         const override { return m_Data.Width; }
		virtual int32                 GetHeight()        const override { return m_Data.Height; }
		virtual const char*           GetTitle()         const override { return m_Data.Title; }
		virtual bool                  IsVSync()          const override { return m_Data.VSyncEnabled; }
		virtual void*                 GetHandle()        const override { return m_Handle; }
		virtual bool		          IsOpen()           const override { return m_Data.IsOpen; }
		virtual WindowEventCallbackFn GetEventCallback() const override { return m_Data.EventCallback; }

		void SetEventCallback(WindowEventCallbackFn fn) override { m_Data.EventCallback = fn; }

		void Init() override;
		void Update() override;

	private:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		struct WindowsWindowData
		{
			int32 Width, Height;
			bool VSyncEnabled;
			const char* Title;
			WindowEventCallbackFn EventCallback;
			bool IsOpen;

			float LastMouseX = 0, LastMouseY = 0;

			bool FirstEventIteration = true;
		};

	private:
		HWND m_Handle;
		WindowsWindowData m_Data;
		std::unique_ptr<Context> m_Context;
	};

}