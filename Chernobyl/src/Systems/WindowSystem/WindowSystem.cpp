#include "chpch.hpp"
#include "SSO/SSO.hpp"
#include "WindowSystem.hpp"

#ifdef CH_PLATFORM_WINDOWS
#include "Platforms/OS/Windows/WindowsWindowSystem.hpp"
#endif

namespace CH
{

	WindowSystem* WindowSystem::Create()
	{
		return new NativeClass();
	}

}