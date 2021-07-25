#pragma once

#include "SSO/SSO.hpp"

#include "Subsystems/Time.hpp"

#ifdef CH_PLATFORM_WINDOWS
namespace CH { class WindowsTimeSystem; }
#define CH_NATIVE_CLASS_TIMESYSTEM WindowsTimeSystem;
#endif

namespace CH
{

	class TimeSystem : public ISystem
	{
	public:
		using NativeClass = CH_NATIVE_CLASS_TIMESYSTEM;
		static SystemType GetStaticType() { return SystemType::Time; }

	public:
		static TimeSystem* Create();
	};

}