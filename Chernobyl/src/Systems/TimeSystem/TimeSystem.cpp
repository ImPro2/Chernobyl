#include "chpch.hpp"
#include "TimeSystem.hpp"

#ifdef CH_PLATFORM_WINDOWS
#include "Platforms/OS/Windows/WindowsTimeSystem.hpp"
#endif

namespace CH
{

	TimeSystem* TimeSystem::Create()
	{
		return new NativeClass();
	}

}