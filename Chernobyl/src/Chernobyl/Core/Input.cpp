#include "chpch.h"
#include "Input.h"

#ifdef CH_PLATFORM_WINDOWS
#include "Chernobyl/Platform/Windows/WindowsInput.h"
#endif

namespace CH
{

#ifdef CH_PLATFORM_WINDOWS
	Input* Input::s_Instance = new WindowsInput();
#endif

}