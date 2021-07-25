#pragma once

#include "SSO.hpp"
#include "SystemTypes.hpp"

#include "Systems/WindowSystem/WindowSystem.hpp"
#include "Systems/EventSystem/EventSystem.hpp"
#include "Systems/InputSystem/InputSystem.hpp"
#include "Systems/TimeSystem/TimeSystem.hpp"

namespace CH
{

	class System
	{
	public:
		// mapped as	         type    -   system
		using Map = UnorderedMap<SystemType, ISystem*>;

	public:
		static void Init();
		static void Shutdown();

		template<class T>
		static ISystem* GetSystem()
		{
			SystemType type = T::GetStaticType();
			return sSystems[type];
		}

		static ISystem* GetSystem(SystemType type)
		{
			return sSystems[type];
		}

	private:
		static Map sSystems;
	};

}