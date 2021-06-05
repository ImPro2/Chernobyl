#pragma once

#include <Windows.h>

#include "Chernobyl/Core/Core.h"
#include "Chernobyl/Core/Input.h"

namespace CH
{

	class WindowsInput : public Input
	{
	public:
		bool IsKeyPressedImpl(int8 key) override
		{
			auto state = GetAsyncKeyState(static_cast<int>(key));
			return (state & 0x8000);
		}

		bool IsMouseButtonPressedImpl(int8 button) override
		{
			auto state = ::GetAsyncKeyState(button);
			return (state & 0x8000);
		}

		float2 GetMousePosImpl() override
		{
			POINT pt;
			::GetCursorPos(&pt);
			return float2(pt.x, pt.y);
		}
	};

}