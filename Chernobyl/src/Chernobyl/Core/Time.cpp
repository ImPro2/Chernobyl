#include "Time.h"

namespace CH
{

	DeltaTime Time::s_DeltaTime;
	std::chrono::steady_clock::time_point Time::s_Last = std::chrono::steady_clock::now();

	void Time::Update()
	{
		auto old = s_Last;
		s_Last = std::chrono::steady_clock::now();

		std::chrono::duration<float> frameTime = s_Last - old;
		s_DeltaTime = frameTime.count();
	}

}