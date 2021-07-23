#pragma once

#include <sstream>

#include "Event.hpp"

namespace CH
{

	struct MouseClickEvent : public Event
	{
		static EventType GetStaticType() { return EventType::MouseClick; }

		MouseClickEvent(Button<MouseCode> button)
			: Event(EventType::MouseClick), MouseButton(button)
		{
		}
		
		Button<MouseCode> MouseButton;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Mouse Clicked), (Type: MouseClick), (Category: Mouse)}:" << "\n"
				<< "Mouse Button: " << MouseButton.Code << "\n"
				<< "Control: " << MouseButton.ControlPressed << "\n"
				<< "Shift: " << MouseButton.ShiftPressed << "\n"
				<< "Alt: " << MouseButton.AltPressed;

			return oss.str();
		}
	};

	struct MouseReleaseEvent : public Event
	{
		static EventType GetStaticType() { return EventType::MouseRelease; }

		MouseReleaseEvent(Button<MouseCode> button)
			: Event(EventType::MouseRelease), MouseButton(button)
		{
		}

		Button<MouseCode> MouseButton;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Mouse Released), (Type: MouseRelease), (Category: Mouse)}:" << "\n"
				<< "Button Released: " << MouseButton.Code << "\n"
				<< "Control: " << MouseButton.ControlPressed << "\n"
				<< "Shift: " << MouseButton.ShiftPressed << "\n"
				<< "Alt: " << MouseButton.AltPressed;

			return oss.str();
		}
	};

	struct MouseMoveEvent : public Event
	{
		static EventType GetStaticType() { return EventType::MouseMove; }

		MouseMoveEvent(int32 xpos, int32 ypos)
			: Event(EventType::MouseMove), XPos(xpos), YPos(ypos)
		{
		}

		int32 XPos, YPos;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Mouse Moved), (Type: MouseMove), (Category: Mouse)}:" << "\n"
				<< "Mouse Position: " << XPos << ", " << YPos;

			return oss.str();
		}
	};

	struct MouseScrollEvent : public Event
	{
		static EventType GetStaticType() { return EventType::MouseScroll; }

		MouseScrollEvent(int32 offset)
			: Event(EventType::MouseScroll), Offset(offset)
		{
		}

		int32 Offset;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Mouse Scrolled), (Type: MouseScroll), (Category: Mouse)}:" << "\n"
				<< "Mouse Scroll Offset: " << Offset;

			return oss.str();
		}
	};


}