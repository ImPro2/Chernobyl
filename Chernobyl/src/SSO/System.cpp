#include "chpch.hpp"
#include "System.hpp"

namespace CH
{

	System::Map System::sSystems;

	void System::Init()
	{
		sSystems[SystemType::Window] = WindowSystem::Create();
		sSystems[SystemType::Window]->Init();
	}

	void System::Shutdown()
	{
		
	}

}