#pragma once

#include "SSO/SSO.hpp"

namespace CH
{

	struct WindowData
	{
		int32 Width, Height;
		String Title;
		bool VSync;

		WindowData(int32 width = 800, int32 height = 600, const String& title = "Chernobyl Engine", bool vsync = false)
			: Width(width), Height(height), Title(title), VSync(vsync)
		{
		}
	};

	using WindowHandle = void*;

	class IWindow
	{
	public:
		static ObjectType GetStaticType() { return ObjectType::Window; }

	public:
		virtual void Show() = 0;
		virtual void Update() = 0;
		virtual void Close() = 0;

	public:
		// getters/setters

		virtual WindowHandle	GetHandle()			const	= 0;
		virtual int32			GetWidth()			const	= 0;
		virtual int32			GetHeight()			const	= 0;
		virtual const String&	GetTitle()			const	= 0;
		virtual bool			IsVSync()			const	= 0;
		virtual WindowData		GetData()			const	= 0;

		virtual void SetSize(int32 width, int32 height)		= 0;
		virtual void SetTitle(const String& title)			= 0;
		virtual void SetVSync(bool vsync)					= 0;
	};

}