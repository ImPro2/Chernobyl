#include "chpch.hpp"
#include "WindowsTimeSystem.hpp"

namespace CH
{

	void WindowsTimeSystem::Init()
	{
		CH_PROFILE_FUNCTION();

		mSubsystems[SubsystemType::Time] = Time::Create();
	}

	void WindowsTimeSystem::Shutdown()
	{
		CH_PROFILE_FUNCTION();

		delete mSubsystems[SubsystemType::Time];
		mSubsystems[SubsystemType::Time] = nullptr;
	}

}