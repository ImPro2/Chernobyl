#pragma once

#include <sstream>

#include "Event.hpp"

namespace CH
{

	struct WindowCreateEvent : public Event
	{
		static EventType GetStaticType() { return EventType::WindowCreate; }

		WindowCreateEvent(const WindowData& data)
			: Event(EventType::WindowCreate), Data(data)
		{
		}

		WindowData Data;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Window Created), (Type: WindowCreate), (Category: Window)}:" << "\n"
				<< "Window Title: " << Data.Title << "\n"
				<< "Window Size: " << Data.Width << ", " << Data.Height << "\n"
				<< "VSync Enabled: " << Data.VSync;

			return oss.str();
		}
	};

	struct WindowCloseEvent : public Event
	{
		static EventType GetStaticType() { return EventType::WindowClose; }

		WindowCloseEvent(const WindowData& data)
			: Event(EventType::WindowClose), Data(data)
		{
		}

		WindowData Data;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Window Closed), (Type: WindowClose), (Category: Window)}:" << "\n"
				<< "Window Title: " << Data.Title << "\n"
				<< "Window Size: " << Data.Width << ", " << Data.Height << "\n"
				<< "VSync Enabled: " << Data.VSync;

			return oss.str();
		}
	};

	struct WindowResizeEvent : public Event
	{
		static EventType GetStaticType() { return EventType::WindowResize; }

		WindowResizeEvent(int32 width, int32 height)
			: Event(EventType::WindowResize), Width(width), Height(height)
		{
		}

		int32 Width, Height;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Window Resized), (Type: WindowClose), (Category: Window)}:" << "\n"
				<< "Window Size: (" << Width << ", " << Height << ")";

			return oss.str();
		}
	};

	struct WindowMoveEvent : public Event
	{
		static EventType GetStaticType() { return EventType::WindowMove; }

		WindowMoveEvent(int32 x, int32 y)
			: Event(EventType::WindowMove), XPos(x), YPos(y)
		{
		}

		int32 XPos, YPos;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Window Moved), (Type: WindowMove), (Category: Window)}:" << "\n"
				<< "Window Position: " << XPos << ", " << YPos;

			return oss.str();
		}
	};

}