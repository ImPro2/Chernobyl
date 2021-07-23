#pragma once

#include <unordered_map>

#include "Core/Core.hpp"

#include "ISubsystem.hpp"

#include "SystemTypes.hpp"
#include "SubsystemTypes.hpp"
#include "ObjectTypes.hpp"

namespace CH
{

	class ISystem
	{
	public:
		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		template<class T>
		Ref<T> CreateObject(void* props = nullptr);

		template<class T>
		T* GetSubsystem();

	protected:
		// mapped as:	   type	    -     subsystem 
		UnorderedMap<SubsystemType, ISubsystem*> mSubsystems;
	};

}

// it can't be implemented in cpp file :(

#include "ISystem.inl"