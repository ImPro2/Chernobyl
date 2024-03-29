#pragma once

// system

#include "Systems/WindowSystem/WindowSystem.hpp"

// objects

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

			CH_CORE_BREAK_S("Invalid object type '{0}' referenced in {1}", ObjectTypeToStr(type), __FUNCTION__);

			return nullptr;
		}
	};

}