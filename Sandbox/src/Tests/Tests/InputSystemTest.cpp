#include "sandboxpch.hpp"
#include "InputSystemTest.hpp"

namespace CH::Sandbox::Test
{
	InputSystemTest::InputSystemTest()
		: ITest("InputSystemTest")
	{
	}

	InputSystemTest::~InputSystemTest()
	{
	}

	void InputSystemTest::OnInit()
	{
		System::GetSystem(SystemType::Event)->GetSubsystem<EventManager>()->Subscribe(this);
	}

	void InputSystemTest::OnUpdate()
	{
		InputManager* input = System::GetSystem(SystemType::Input)->GetSubsystem<InputManager>();

		if (input->IsKeyDown(Key::A))
			CH_CLIENT_LOG(LogSeverity::Info, "A key is pressed!");
		if (input->IsKeyDown(Key::W))
			CH_CLIENT_LOG(LogSeverity::Info, "W key is pressed!");
		if (input->IsKeyDown(Key::D))
			CH_CLIENT_LOG(LogSeverity::Info, "D key is pressed!");
		if (input->IsKeyDown(Key::S))
			CH_CLIENT_LOG(LogSeverity::Info, "S key is pressed!");
	}

}
