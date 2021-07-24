#include "chpch.hpp"
#include "WindowsInputSystem.hpp"

namespace CH
{

	void WindowsInputSystem::Init()
	{
		mSubsystems[SubsystemType::InputManager] = InputManager::Create();
	}

	void WindowsInputSystem::Shutdown()
	{
	}

}