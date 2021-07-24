#include "chpch.hpp"
#include "InputSystem.hpp"

#ifdef CH_PLATFORM_WINDOWS
#	include "Platforms/OS/Windows/WindowsInputSystem.hpp"
#endif

namespace CH
{

	InputSystem* InputSystem::Create()
	{
		return new NativeClass();
	}

}