// file for template implementations

#include "Systems/WindowSystem/WindowSystem.hpp"

#ifdef CH_PLATFORM_WINDOWS
#include "Platforms/OS/Windows/WindowsWindowSystem.hpp"
#endif

namespace CH
{

	template<class T>
	Ref<T> ISystem::CreateObject(void* props)
	{
		CH_PROFILE_FUNCTION();

		ObjectType type = T::GetStaticType();

		switch (CH::SystemTypeOfObjectType(type))
		{
			case SystemType::Window:	return static_cast<CH_NATIVE_CLASS_WINDOWSYSTEM*>(this)->CreateObject<T>(type, props);
		}

		CH_CORE_BREAK_S("Unsupported object '{0}'.", ObjectTypeToStr(type));
		return nullptr;
	}

	template<class T>
	T* ISystem::GetSubsystem()
	{
		CH_PROFILE_FUNCTION();

		SubsystemType type = T::GetStaticType();
		ISubsystem* subsystem = mSubsystems[type];
		return static_cast<T*>(subsystem);
	}

}