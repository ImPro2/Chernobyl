#include "chpch.hpp"
#include "WindowsInputManager.hpp"

#include <Windows.h>
#include <WinUser.h>

namespace CH
{

	bool WindowsInputManager::IsKeyDown(KeyCode key)
	{
		auto state = ::GetAsyncKeyState(static_cast<int32>(key));
		return (state & 0x8000);
	}

	bool WindowsInputManager::IsMouseButtonDown(MouseCode code)
	{
		auto state = ::GetAsyncKeyState(static_cast<int32>(code));
		return (state & 0x8000);
	}

	int2 WindowsInputManager::GetMousePosition()
	{
		POINT pt;
		::GetCursorPos(&pt);
		return { pt.x, pt.y };
	}

}