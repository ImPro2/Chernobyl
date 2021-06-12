#include "chpch.h"
#include "WindowInterface.h"

#ifdef CH_PLATFORM_WINDOWS
#include "Chernobyl/Platform/Windows/WindowsWindow.h"
#endif

namespace CH
{

	std::unique_ptr<Window> Window::Create(WindowData data)
	{
#ifdef CH_PLATFORM_WINDOWS
		return std::make_unique<WindowsWindow>(data);
#endif
	}

}