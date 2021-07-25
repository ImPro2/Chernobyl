#pragma once

#include "TimePoint.hpp"

#include <chrono>

namespace CH
{

	class Clock
	{
	public:
		Clock(bool startOnCreation = true)
		{
			if (startOnCreation)
				Reset();
		}

	public:
		void Reset()
		{
			mStart = std::chrono::high_resolution_clock::now();
		}

		TimePoint GetElapsedTime()
		{
			float seconds = std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::high_resolution_clock::now() - mStart
			).count() * 0.001f * 0.001f * 0.001f;

			return TimePoint(seconds);
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> mStart;
	};

}