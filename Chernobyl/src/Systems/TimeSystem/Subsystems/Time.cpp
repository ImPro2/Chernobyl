#include "chpch.hpp"
#include "Time.hpp"

#include "Core/Application.hpp"

#include <chrono>

namespace CH
{

	Time* Time::Create()
	{
		return new Time();
	}

	static std::chrono::time_point<std::chrono::high_resolution_clock> sLastFrameTime;

	void Time::Update()
	{
		// in seconds
		float timestep = std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now() - sLastFrameTime
			).count() * 0.001f * 0.001f * 0.001f;

		sLastFrameTime = std::chrono::high_resolution_clock::now();

		mTimestep = Timestep(timestep);
		mFPS = 1 / mTimestep;
	}

}