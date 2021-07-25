#pragma once

namespace CH
{

	class TimePoint
	{
	public:
		TimePoint()
			: mTime(0.0f)
		{
		}

		TimePoint(float seconds)
			: mTime(seconds)
		{
		}

		~TimePoint() = default;

	public:
		operator float() const
		{
			return mTime;
		}

	public:
		float Seconds()      { return mTime; }
		float MilliSeconds() { return mTime * 1000.0f; }
		float MicroSeconds() { return MilliSeconds() * 1000.0f; }
		float NanoSeconds()  { return MicroSeconds() * 1000.0f; }

	private:
		float mTime; // in seconds
	};

}