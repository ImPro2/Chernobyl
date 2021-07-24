#pragma once

#include "SSO/SSO.hpp"
#include "Systems/EventSystem/Data/Codes.hpp"

#ifdef CH_PLATFORM_WINDOWS
namespace CH { class WindowsInputManager; }
#define CH_NATIVE_CLASS_INPUTMANAGER WindowsInputManager
#endif

namespace CH
{

	// implemented natively

	class InputManager : public ISubsystem
	{
	public:
		using NativeClass = CH_NATIVE_CLASS_INPUTMANAGER;
		static SubsystemType GetStaticType() { return SubsystemType::InputManager; }

	public:
		virtual bool IsKeyDown(KeyCode key) = 0;

		virtual bool IsMouseButtonDown(MouseCode code) = 0;
		virtual int2 GetMousePosition() = 0;
		int32 GetMouseX() { return GetMousePosition().x; }
		int32 GetMouseY() { return GetMousePosition().y; }

	public:
		static InputManager* Create();
	};

}