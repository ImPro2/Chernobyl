#pragma once

#include <chrono>

#include "Core.h"

namespace CH
{

	class Application;

	class DeltaTime
	{
	public:
		float AsSeconds()      const { return m_Time;                     }
		float AsMilliSeconds() const { return m_Time * 1000.0f;           }
		float AsMicroSeconds() const { return AsMilliSeconds() * 1000.0f; }
		float AsNanoSeconds()  const { return AsMicroSeconds() * 1000.0f; }

		operator float() { return AsSeconds(); }
		void operator=(float other)
		{
			m_Time = other;
		}

	private:
		float m_Time = 0.0f;
	};

	using Timestep = DeltaTime;

	class Time
	{
	public:
		static DeltaTime GetDeltaTime() { return s_DeltaTime;             }
		static float	 GetTimestep()  { return s_DeltaTime.AsSeconds(); }
		static float	 GetFrameTime() { return 1 / s_DeltaTime;         }

	private:
		static void Update();

	private:
		static DeltaTime s_DeltaTime;
		static std::chrono::steady_clock::time_point s_Last;

	private:
		friend class Application;
	};

}