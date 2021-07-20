#pragma once

#include <unordered_map>

#include "ISystem.hpp"
#include "ISubsystem.hpp"

#include "SSO.hpp"
#include "SystemTypes.hpp"

#include "Systems/WindowSystem/WindowSystem.hpp"
#include "Systems/WindowSystem/Objects/Window.hpp"

namespace CH
{

	class System
	{
	public:
		// mapped as	                     type    -   system
		using Map = std::unordered_map<SystemType, ISystem*>;

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