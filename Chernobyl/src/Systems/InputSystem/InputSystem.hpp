#pragma once

#include "SSO/SSO.hpp"

#include "Subsystems/InputManager.hpp"

#ifdef CH_PLATFORM_WINDOWS
namespace CH { class WindowsInputSystem; }
#define CH_NATIVE_CLASS_INPUTSYSTEM WindowsInputSystem
#endif

namespace CH
{

	class InputSystem : public ISystem
	{
	public:
		using NativeClass = CH_NATIVE_CLASS_INPUTSYSTEM;
		static SystemType GetStaticType() { return SystemType::Input; }

	public:
		static InputSystem* Create();
	};

}