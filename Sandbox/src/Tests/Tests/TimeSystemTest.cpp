#include "sandboxpch.hpp"
#include "TimeSystemTest.hpp"

namespace CH::Sandbox::Test
{

	TimeSystemTest::TimeSystemTest()
		: CH::Sandbox::ITest("TimeSystemTest")
	{
	}

	void TimeSystemTest::OnUpdate()
	{
		Timestep ts = System::GetSystem(SystemType::Time)->GetSubsystem<Time>()->GetTimestep();
		float fps = System::GetSystem(SystemType::Time)->GetSubsystem<Time>()->GetFPS();
		TimePoint time = System::GetSystem(SystemType::Time)->GetSubsystem<Time>()->GetGlobalClock().GetElapsedTime().Seconds();
		
		CH_CLIENT_LOG(LogSeverity::Info, "Timestep: {1}, FPS: {2}, Current Time: {3}", (float)ts, fps, time.Seconds());
	}

}