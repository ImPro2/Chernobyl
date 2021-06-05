#pragma once

#include "Chernobyl/Core/Core.h"

namespace CH
{

	enum class EventType
	{
		None = -1,
		AppCreate, AppClose, AppTick,
		WindowResize, WindowMove,

		MouseMove, MouseScroll,
		MouseClick, MouseRelease,

		KeyPress, KeyRelease, KeyType
	};

	enum EventCategory
	{
		EventCategory_None = -1,
		EventCategory_App = 0,
		EventCategory_Window,

		EventCategory_Mouse,
		EventCategory_Keyboard
	};

#define EVENT_CLASS_TYPE(type)	virtual EventType GetType() override { return EventType::type; }\
								virtual const char* ToString() override { return #type; }\
								static EventType GetStaticType() { return EventType::type; }

#define EVENT_CLASS_CATEGORY(category) virtual EventCategory GetCategoryFlags() override { return category;}

	class Event
	{
	public:
		virtual EventType GetType() { return EventType::None; }
		virtual EventCategory GetCategoryFlags() { return EventCategory_None; }
		virtual const char* ToString() { return ""; }

		static EventType GetStaticType() { return EventType::None; }

		bool IsInCategory(EventCategory category) { return (GetCategoryFlags() & category); }

	public:
		bool Handled = false;
	};

	class WindowEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory_Window)
	};

	class WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(int32 width, int32 height) : m_Width(width), m_Height(height) {}

		int32 GetWidth() const { return m_Width; }
		int32 GetHeight() const { return m_Height; }

		float2 GetSize() const { return float2(m_Width, m_Height); }

		EVENT_CLASS_TYPE(WindowResize)

	private:
		int32 m_Width, m_Height;
	};
	class WindowMoveEvent : public WindowEvent
	{
	public:
		WindowMoveEvent(int32 x, int32 y) : m_X(x), m_Y(y) {}

		int32 GetX() const { return m_X; }
		int32 GetY() const { return m_Y; }

		EVENT_CLASS_TYPE(WindowMove)

	private:
		int32 m_X, m_Y;
	};

	class AppEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory_App)
	};

	class AppCreateEvent : public AppEvent
	{
	public:
		AppCreateEvent() {}

		EVENT_CLASS_TYPE(AppCreate)
	};
	class AppCloseEvent : public AppEvent
	{
	public:
		AppCloseEvent(int returnCode) : m_ReturnCode(returnCode) {}

		int32 GetReturnCode() const { return m_ReturnCode; }

		EVENT_CLASS_TYPE(AppClose)

	private:
		int32 m_ReturnCode;
	};
	class AppTickEvent : public AppEvent
	{
	public:
		EVENT_CLASS_TYPE(AppTick)
	};

	class MouseEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory_Mouse)
	};

	class MouseMoveEvent : public MouseEvent
	{
	public:
		MouseMoveEvent(int32 x, int32 y) : m_X(x), m_Y(y) {}

		int32 GetX() const { return m_X; }
		int32 GetY() const { return m_Y; }
		float2 GetPos() const { return float2(m_X, m_Y); }

		EVENT_CLASS_TYPE(MouseMove)

	private:
		int m_X, m_Y;
	};
	class MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(int32 offset) : m_Offset(offset) {}

		int32 GetOffset() const { return m_Offset; }

		EVENT_CLASS_TYPE(MouseScroll)

	private:
		int32 m_Offset;
	};

	class MouseButtonEvent : public MouseEvent
	{
	public:
		MouseButtonEvent(int8 button) : m_Button(button) {}

		int8 GetButton() const { return m_Button; }

	private:
		int8 m_Button;
	};
	class MouseButtonClickEvent : public MouseButtonEvent
	{
	public:
		MouseButtonClickEvent(int button) : MouseButtonEvent(button) {}

		EVENT_CLASS_TYPE(MouseClick)
	};
	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(int button) : MouseButtonEvent(button) {}

		EVENT_CLASS_TYPE(MouseRelease)
	};

	class KeyEvent : public Event
	{
	public:
		KeyEvent(int8 key) : m_Key(key) {}

		int8 GetKey() const { return m_Key; }

		EVENT_CLASS_CATEGORY(EventCategory_Keyboard)

	protected:
		int8 m_Key;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int8 key) : KeyEvent(key) {}

		bool IsDown(int8 key) { return key == m_Key; }

		EVENT_CLASS_TYPE(KeyPress)
	};
	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int8 key) : KeyEvent(key) {}

		bool IsUp(int8 key) { return key == m_Key; }

		EVENT_CLASS_TYPE(KeyRelease)
	};
	class KeyTypeEvent : public KeyEvent
	{
	public:
		KeyTypeEvent(int8 key) : KeyEvent(key) {}

		EVENT_CLASS_TYPE(KeyType)
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : m_Event(e) {}

		template<typename T, typename F>
		bool Dispatch(const F& fn)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				m_Event.Handled = fn(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

}