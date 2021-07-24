#pragma once

#include "SSO/SSO.hpp"

#ifdef CH_PLATFORM_WINDOWS
namespace CH { class WindowsWindowSystem; }
#	define CH_NATIVE_CLASS_WINDOWSYSTEM WindowsWindowSystem
#endif

namespace CH
{

	class WindowSystem : public ISystem
	{
	public:
		using NativeClass = CH_NATIVE_CLASS_WINDOWSYSTEM;
		static SystemType GetStaticType() { return SystemType::Window; }

	public:
		static WindowSystem* Create();
	};

}