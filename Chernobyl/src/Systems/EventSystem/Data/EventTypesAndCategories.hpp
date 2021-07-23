#pragma once

namespace CH
{

	enum class EventType
	{
		None = -1,

		// App

		AppCreate,
		AppDestroy,
		AppUpdate,
		AppRender,
		
		// Window

		WindowCreate,
		WindowClose,
		WindowResize,
		WindowMove,

		// Mouse

		MouseClick,
		MouseRelease,
		MouseMove,
		MouseScroll,

		// Keyboard

		KeyPress,
		KeyRelease,
		KeyType
	};

	enum class EventCategory
	{
		None		= CH_BIT(0),
		App			= CH_BIT(1),
		Window		= CH_BIT(2),
		Mouse		= CH_BIT(3),
		Keyboard	= CH_BIT(4)
	};

	constexpr const char* EventTypeToStr(EventType type)
	{
		switch (type)
		{
			case EventType::AppCreate:					return 	  "AppCreate";
			case EventType::AppDestroy:					return 	  "AppDestroy";
			case EventType::AppUpdate:					return 	  "AppUpdate";
			case EventType::AppRender:					return 	  "AppRender";

			case EventType::WindowCreate:				return 	  "WindowCreate";
			case EventType::WindowClose:				return 	  "WindowDestroy";
			case EventType::WindowResize:				return 	  "WindowResize";
			case EventType::WindowMove:					return 	  "WindowMove";

			case EventType::MouseClick:					return 	  "MouseClick";
			case EventType::MouseRelease:				return 	  "MouseRelease";
			case EventType::MouseMove:					return 	  "MouseMove";
			case EventType::MouseScroll:				return 	  "MouseScroll";

			case EventType::KeyPress:					return	  "KeyPress";
			case EventType::KeyRelease:					return	  "KeyRelease";
			case EventType::KeyType:					return	  "KeyType";
		}

		return "";
	}

	constexpr EventCategory EventTypeToEventCategory(EventType type)
	{
		switch (type)
		{
			case EventType::AppCreate:					return EventCategory::App;
			case EventType::AppDestroy:					return EventCategory::App;
			case EventType::AppUpdate:					return EventCategory::App;
			case EventType::AppRender:					return EventCategory::App;

			case EventType::WindowCreate:				return EventCategory::Window;
			case EventType::WindowClose:				return EventCategory::Window;
			case EventType::WindowResize:				return EventCategory::Window;
			case EventType::WindowMove:					return EventCategory::Window;

			case EventType::MouseClick:					return EventCategory::Mouse;
			case EventType::MouseRelease:				return EventCategory::Mouse;
			case EventType::MouseMove:					return EventCategory::Mouse;
			case EventType::MouseScroll:				return EventCategory::Mouse;

			case EventType::KeyPress:					return EventCategory::Keyboard;
			case EventType::KeyRelease:					return EventCategory::Keyboard;
			case EventType::KeyType:					return EventCategory::Keyboard;
		}

		CH_CORE_BREAK_S("Unknown EventType '{0}'.", EventTypeToStr(type));

		return EventCategory::None;
	}

}