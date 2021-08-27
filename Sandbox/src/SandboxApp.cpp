#include "sandboxpch.hpp"

#define CH_API_ENTRY
#include "Chernobyl.hpp"

#include "Tests/Tests/EventSystemTest.hpp"
#include "Tests/Tests/InputSystemTest.hpp"
#include "Tests/Tests/TimeSystemTest.hpp"

namespace CH::Sandbox
{

	class SandboxApp : public Application
	{
	public:
		SandboxApp(ApplicationStartupArguments args)
			: Application(args)
		{
		}

		~SandboxApp() = default;

	public:
		void Init() override
		{
			Tests::AddTest(new Test::EventSystemTest());
			Tests::AddTest(new Test::InputSystemTest());
			Tests::AddTest(new Test::TimeSystemTest());

			//Tests::SetCurrentTest("TimeSystemTest");
		}

		void Update() override
		{
			Tests::Update();
		}
	};

}

CH::Application* CH::CreateApplication(CH::ApplicationStartupArguments args)
{
	return new CH::Sandbox::SandboxApp(args);
}