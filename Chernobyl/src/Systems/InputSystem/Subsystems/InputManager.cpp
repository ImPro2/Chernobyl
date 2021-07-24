#include "chpch.hpp"
#include "InputManager.hpp"

#ifdef CH_PLATFORM_WINDOWS
#	include "Platforms/OS/Windows/WindowsInputManager.hpp"
#endif

namespace CH
{

	InputManager* InputManager::Create()
	{
		return new NativeClass();
	}

}