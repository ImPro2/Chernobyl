#include "chpch.hpp"
#include "System.hpp"

namespace CH
{

	System::Map System::sSystems;

	void System::Init()
	{
		sSystems[SystemType::Window] = WindowSystem::Create();
		sSystems[SystemType::Window]->Init();

		sSystems[SystemType::Event] = EventSystem::Create();
		sSystems[SystemType::Event]->Init();

		sSystems[SystemType::Input] = InputSystem::Create();
		sSystems[SystemType::Input]->Init();

		sSystems[SystemType::Time] = TimeSystem::Create();
		sSystems[SystemType::Time]->Init();
	}

	void System::Shutdown()
	{
		sSystems[SystemType::Window]->Shutdown();
		delete sSystems[SystemType::Window];
		sSystems[SystemType::Window] = nullptr;

		sSystems[SystemType::Event]->Shutdown();
		delete sSystems[SystemType::Event];
		sSystems[SystemType::Event] = nullptr;

		sSystems[SystemType::Input]->Shutdown();
		delete sSystems[SystemType::Input];
		sSystems[SystemType::Input] = nullptr;

		sSystems[SystemType::Time]->Shutdown();
		delete sSystems[SystemType::Time];
		sSystems[SystemType::Time] = nullptr;
	}

}