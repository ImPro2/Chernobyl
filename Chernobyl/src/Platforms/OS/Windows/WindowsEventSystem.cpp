#include "chpch.hpp"
#include "WindowsEventSystem.hpp"

namespace CH
{

	void WindowsEventSystem::Init()
	{
		mSubsystems[SubsystemType::EventManager] = EventManager::Create();
	}

	void WindowsEventSystem::Shutdown()
	{
		delete mSubsystems[SubsystemType::EventManager];
		mSubsystems[SubsystemType::EventManager] = nullptr;
	}

}