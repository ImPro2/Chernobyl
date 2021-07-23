#pragma once

#include "SSO/SSO.hpp"

// subsystems

#include "Subsystems/EventManager.hpp"

#ifdef CH_PLATFORM_WINDOWS
namespace CH { class WindowsEventSystem; }
#	define CH_NATIVE_CLASS_EVENTSYSTEM WindowsEventSystem
#endif

namespace CH
{

	class EventSystem : public ISystem
	{
	public:
		static SystemType GetStaticType() { return SystemType::Event; }
		using NativeClass = CH_NATIVE_CLASS_EVENTSYSTEM;

	public:
		static EventSystem* Create();
	};

}