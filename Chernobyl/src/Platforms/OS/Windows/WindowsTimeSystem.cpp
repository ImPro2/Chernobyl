#include "chpch.hpp"
#include "WindowsTimeSystem.hpp"

namespace CH
{

	void WindowsTimeSystem::Init()
	{
		mSubsystems[SubsystemType::Time] = Time::Create();
	}

	void WindowsTimeSystem::Shutdown()
	{
		delete mSubsystems[SubsystemType::Time];
		mSubsystems[SubsystemType::Time] = nullptr;
	}

}