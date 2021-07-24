#pragma once

#include "Systems/InputSystem/Subsystems/InputManager.hpp"

namespace CH
{

	class WindowsInputManager : public InputManager
	{
	public:
		bool IsKeyDown(KeyCode key) override;

		bool IsMouseButtonDown(MouseCode code) override;
		int2 GetMousePosition() override;
	};

}