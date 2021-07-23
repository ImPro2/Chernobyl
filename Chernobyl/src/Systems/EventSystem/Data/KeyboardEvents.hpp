#pragma once

#include "Event.hpp"

namespace CH
{ 

	struct KeyPressEvent : public Event
	{
		static EventType GetStaticType() { return EventType::KeyPress; }

		KeyPressEvent(Button<KeyCode> key)
			: Event(EventType::KeyPress), Key(key)
		{
		}

		Button<KeyCode> Key;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Key Pressed), (Type: KeyPress), (Category: Keyboard)}:" << "\n"
				<< "Key Code: " << Key.Code << "\n"
				<< "Control: " << Key.ControlPressed << "\n"
				<< "Shift: " << Key.ShiftPressed << "\n"
				<< "Alt: " << Key.AltPressed << "\n";

			return oss.str();
		}
	};

	struct KeyReleaseEvent : public Event
	{
		static EventType GetStaticType() { return EventType::KeyRelease; }

		KeyReleaseEvent(Button<KeyCode> key)
			: Event(EventType::KeyRelease), Key(key)
		{
		}

		Button<KeyCode> Key;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Key Released), (Type: KeyRelease), (Category: Keyboard)}:" << "\n"
				<< "Key Code: " << Key.Code << "\n"
				<< "Control: " << Key.ControlPressed << "\n"
				<< "Shift: " << Key.ShiftPressed << "\n"
				<< "Alt: " << Key.AltPressed << "\n";

			return oss.str();
		}
	};

	struct KeyTypeEvent : public Event
	{
		static EventType GetStaticType() { return EventType::KeyType; }

		KeyTypeEvent(char character)
			: Event(EventType::KeyType), Character(character)
		{
		}

		char Character;

		// overriden methods

		const String& ToString() override
		{
			std::ostringstream oss;

			oss << "[Event]: {(Brief: Key Typed), (Type: KeyType), (Category: Keyboard)}:" << "\n"
				<< "Character: " << Character;

			return oss.str();
		}
	};

}