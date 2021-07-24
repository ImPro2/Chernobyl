#pragma once

#include "Systems/InputSystem/InputSystem.hpp"

namespace CH
{

	class WindowsInputSystem : public InputSystem
	{
	public:
		void Init() override;
		void Shutdown() override;
	};

}