#pragma once

#include "Chernobyl/Core/Core.h"
#include "Chernobyl/Core/Events.h"
#include "Chernobyl/Renderer/Context.h"

#include <memory>

// interface for a desktop system sort of window

namespace CH
{

	using WindowEventCallbackFn = std::function<void(Event&)>;

	struct WindowData
	{
		int32 Width, Height;
		bool VSyncEnabled;
		const char* Title;

		WindowData(int32 width = 1366, int32 height = 768, bool vsync = false, const char* title = "Chernobyl Engine")
			: Width(width), Height(height), VSyncEnabled(vsync), Title(title) {}
	};

	class Window
	{
	public:

		static std::unique_ptr<Window> Create(WindowData data = WindowData());

		virtual int32                 GetWidth()         const = 0;
		virtual int32                 GetHeight()        const = 0;
		virtual const char*           GetTitle()         const = 0;
		virtual bool                  IsVSync()          const = 0;
		virtual void*                 GetHandle()        const = 0;
		virtual bool		          IsOpen()	         const = 0;
		virtual WindowEventCallbackFn GetEventCallback() const = 0;
		virtual Context*              GetContext()       const = 0;

		virtual void SetEventCallback(WindowEventCallbackFn fn) = 0;
		virtual void SetHandle(void* handle)                    = 0;

		virtual void Init() = 0;
		virtual void Update() = 0;
	};

}