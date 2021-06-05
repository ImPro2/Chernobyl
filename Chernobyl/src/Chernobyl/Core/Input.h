#pragma once

#include "Core.h"
#include <glm/glm.hpp>

namespace CH
{

	class Input
	{
	public:
		static bool IsKeyPressed(int8 key) { return s_Instance->IsKeyPressedImpl(key); }
		static bool IsMouseButtonPressed(int8 button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static float2 GetMousePos() { return s_Instance->GetMousePosImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	private:
		virtual bool IsKeyPressedImpl(int8 key) = 0;
		virtual bool IsMouseButtonPressedImpl(int8 button) = 0;
		virtual float2 GetMousePosImpl() = 0;
		float GetMouseXImpl() { return GetMousePosImpl().x; }
		float GetMouseYImpl() { return GetMousePosImpl().y; }

	private:
		static Input* s_Instance;
	};

}