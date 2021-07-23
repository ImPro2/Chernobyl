#pragma once

#include "EventTypesAndCategories.hpp"
#include "Codes.hpp"

namespace CH
{

	struct Event
	{
	public:
		Event(EventType type)
			: mType(type), mCategory(EventTypeToEventCategory(mType)) 
		{
		}

	public:
		static EventType GetStaticType() { return EventType::None; }
		EventType GetType() const { return mType; }
		EventCategory GetCategory() const { return mCategory; }
		virtual const String& ToString() = 0;

	protected:
		EventType mType;
		EventCategory mCategory;
		String mToStrBuffer;	// avoid dangling strings
	};

	template<typename CodeType>
	struct Button
	{
		CodeType Code;
		
		bool ShiftPressed;
		bool ControlPressed;
		bool AltPressed;

		Button()
			: Code(0), ShiftPressed(false), ControlPressed(0), AltPressed(0)
		{
		}

		Button(CodeType buttonCode, bool shift = false, bool control = false, bool alt = false)
			: Code(buttonCode), ShiftPressed(shift),
			  ControlPressed(control), AltPressed(alt)
		{
		}
	};

	using EventCallbackFn = std::function<void(Event&)>;

}