#pragma once

#include "TimePoint.hpp"

namespace CH
{

	class Timestep
	{
	public:
		Timestep(float seconds)
			: mTimePoint(seconds)
		{
		}

		operator float() const
		{
			return (float)mTimePoint;
		}

	private:
		TimePoint mTimePoint;
	};

}