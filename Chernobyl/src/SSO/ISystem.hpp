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
		virtual void Init()     = 0;
		virtual void Shutdown() = 0;

		template<class T>
		Ref<T> CreateObject(void* props = nullptr);

		virtual ISubsystem* GetSubsystem(SubsystemType type) = 0;

	protected:
		// mapped as:	   type	    -     subsystem 
		std::unordered_map<SubsystemType, ISubsystem*> mSubsystems;
	};

}

// it can't be implemented in cpp file :(

#include "ISystem.inl"