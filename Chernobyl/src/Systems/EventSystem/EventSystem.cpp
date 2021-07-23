#include "chpch.hpp"
#include "EventSystem.hpp"

#ifdef CH_PLATFORM_WINDOWS
#	include "Platforms/OS/Windows/WindowsEventSystem.hpp"
#endif

namespace CH
{

	EventSystem* EventSystem::Create()
	{
		return new NativeClass();
	}

}