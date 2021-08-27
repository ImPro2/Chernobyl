#include "chpch.hpp"
#include "System.hpp"


namespace CH
{

	static ISystem* SystemTypeToISystem(SystemType type)
	{
		CH_PROFILE_FUNCTION();

		switch (type)
		{
			case SystemType::Window:	return WindowSystem::Create();
			case SystemType::Event:		return EventSystem::Create();
			case SystemType::Input:		return InputSystem::Create();
			case SystemType::Time:		return TimeSystem::Create();
			case SystemType::Renderer:	CH_CORE_BREAK_S("Unsupported system!"); return nullptr;
			case SystemType::Physics:	CH_CORE_BREAK_S("Unsupported system!"); return nullptr;
			case SystemType::Audio:		CH_CORE_BREAK_S("Unsupported system!"); return nullptr;
		}

		CH_CORE_BREAK_S("Unsupported system!");
		return nullptr;
	}

	System::Map System::sSystems;

	void System::Init()
	{
		CH_PROFILE_FUNCTION();

		for (int32 i = 0; i < CH_SYSTEM_TYPE_LAST; i++)
		{
			sSystems[(SystemType)i] = SystemTypeToISystem((SystemType)i);
			sSystems[(SystemType)i]->Init();
		}
	}

	void System::Shutdown()
	{
		CH_PROFILE_FUNCTION();

		for (int32 i = 0; i < CH_SYSTEM_TYPE_LAST; i++)
		{
			SystemType type = (SystemType)i;
			sSystems[type]->Shutdown();
			delete sSystems[type];
			sSystems[type] = nullptr;
		}
	}

}