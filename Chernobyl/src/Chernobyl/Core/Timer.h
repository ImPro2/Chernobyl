#pragma once
#include <chrono>

#include "Core.h"

namespace CH {

	class Timer
	{
	public:
		Timer()
		{
			Reset();
		}

		Timer Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
			return *this;
		}

	public:
		// getters
		float ElapsedSeconds()      const 
		{ 
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
		}
		float ElapsedMilliSeconds() const { return ElapsedSeconds()      * 1000.0f; }
		float ElapsedMicroSeconds() const { return ElapsedMilliSeconds() * 1000.0f; }
		float ElapsedNanoSeconds()  const { return ElapsedMicroSeconds() * 1000.0f; }

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};

}