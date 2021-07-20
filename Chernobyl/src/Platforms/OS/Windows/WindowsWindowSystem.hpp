#pragma once

#include "Systems/WindowSystem/WindowSystem.hpp"
#include "WindowsWindow.hpp"

namespace CH
{

	class WindowsWindowSystem : public WindowSystem
	{
	public:
		void Init() override;
		void Shutdown() override;

		template<class T>
		Ref<T> CreateObject(ObjectType type, void* props)
		{
			switch (type)
			{
				case ObjectType::Window:	return CreateRef<WindowsWindow>(props == nullptr ? WindowData() : *(WindowData*)props);
			}

			return nullptr;
		}

		ISubsystem* GetSubsystem(SubsystemType type) override
		{
			// no subsystems yet
			return nullptr;
		}

	};

}