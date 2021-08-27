#include "chpch.hpp"
#include "Time.hpp"

#include "Core/Application.hpp"

#include <chrono>

namespace CH
{

	Time* Time::Create()
	{
		CH_PROFILE_FUNCTION();

		return new Time();
	}

	static std::chrono::time_point<std::chrono::high_resolution_clock> sLastFrameTime;

	void Time::Update()
	{
		CH_PROFILE_FUNCTION();

		// in seconds
		float timestep = std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now() - sLastFrameTime
			).count() * 0.001f * 0.001f * 0.001f;

		sLastFrameTime = std::chrono::high_resolution_clock::now();

		mTimestep = Timestep(timestep);
		mFPS = 1 / mTimestep;
	}

}