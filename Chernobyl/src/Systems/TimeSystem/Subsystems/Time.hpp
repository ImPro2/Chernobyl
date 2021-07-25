#pragma once

#include "SSO/SSO.hpp"

#include "../Data/TimePoint.hpp"
#include "../Data/Timestep.hpp"
#include "../Data/Clock.hpp"

namespace CH
{

	class Application;

	class Time : public ISubsystem
	{
	public:
		static SubsystemType GetStaticType() { return SubsystemType::Time; }
		static Time* Create();

	public:
		Timestep GetTimestep()    const { return mTimestep; }
		float    GetFPS()         const { return mFPS;      }
		Clock    GetGlobalClock() const { return mClock;    }

	private:
		void Update();

	private:
		Timestep mTimestep = Timestep(0.0f);
		float mFPS = 0.0f;

		Clock mClock = Clock(true);

	private:
		friend class Application;
	};

}