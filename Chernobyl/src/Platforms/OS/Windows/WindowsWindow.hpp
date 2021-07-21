#pragma once

#include <Windows.h>

#include "Systems/WindowSystem/Objects/Window.hpp"

namespace CH
{

	class WindowsWindow : public IWindow
	{
	public:
		WindowsWindow(WindowData data = WindowData());
		~WindowsWindow();

		void Show()		override;
		void Update()	override;
		void Close()	override;

	public:		
		virtual WindowHandle	GetHandle()	const override { return (WindowHandle)mHandle;	}
		virtual int32			GetWidth()	const override { return mData.Width;			}
		virtual int32			GetHeight()	const override { return mData.Height;			}
		virtual const String&	GetTitle()	const override { return mData.Title;			}
		virtual bool			IsVSync()	const override { return mData.VSync;			}
		virtual WindowData		GetData()	const override { return mData;					}

		virtual void SetSize(int32 width, int32 height)	override;
		virtual void SetTitle(const String& title)		override;
		virtual void SetVSync(bool vsync)				override;

	private:
		HWND mHandle;
		WindowData mData;
	};

}