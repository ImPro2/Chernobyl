#include "chpch.hpp"
#include "WindowsInputSystem.hpp"

namespace CH
{

	void WindowsInputSystem::Init()
	{
		CH_PROFILE_FUNCTION();

		mSubsystems[SubsystemType::InputManager] = InputManager::Create();
	}

	void WindowsInputSystem::Shutdown()
	{
		CH_PROFILE_FUNCTION();
	}

}