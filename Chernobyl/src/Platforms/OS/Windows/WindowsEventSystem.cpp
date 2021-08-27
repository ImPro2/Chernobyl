#include "chpch.hpp"
#include "WindowsEventSystem.hpp"

namespace CH
{

	void WindowsEventSystem::Init()
	{
		CH_PROFILE_FUNCTION();

		mSubsystems[SubsystemType::EventManager] = EventManager::Create();
	}

	void WindowsEventSystem::Shutdown()
	{
		CH_PROFILE_FUNCTION();

		delete mSubsystems[SubsystemType::EventManager];
		mSubsystems[SubsystemType::EventManager] = nullptr;
	}

}