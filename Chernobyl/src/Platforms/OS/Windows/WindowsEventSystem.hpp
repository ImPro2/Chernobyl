#pragma once

#include "Systems/EventSystem/EventSystem.hpp"

namespace CH
{ 

	class WindowsEventSystem : public EventSystem
	{
	public:
		void Init() override;
		void Shutdown() override;

		template<class T>
		Ref<T> CreateObject(ObjectType type, void* props)
		{
			switch (type)
			{
				case ObjectType::EventListener:		return CreateRef<T>(props);
			}

			CH_CORE_BREAK_S("Invalid object type '{0}' referenced in {1}", ObjectTypeToStr(type), __FUNCTION__);

			return nullptr;
		}
	};

}