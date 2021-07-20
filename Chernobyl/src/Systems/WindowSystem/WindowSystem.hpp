#pragma once

#include "SSO/SSO.hpp"

namespace CH
{

	class WindowSystem : public ISystem
	{
	public:
		static SystemType GetStaticType() { return SystemType::Window; }

	public:
		static WindowSystem* Create();
	};

#ifdef CH_PLATFORM_WINDOWS
#	define CH_NATIVE_CLASS_WINDOWSYSTEM WindowsWindowSystem
#endif

}