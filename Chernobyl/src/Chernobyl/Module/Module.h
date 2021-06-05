#pragma once

#include "Chernobyl/Core/Core.h"
#include "Chernobyl/Core/Events.h"

namespace CH
{

	class Module
	{
	public:
		Module(const char* name) : m_ModuleIndex(0), m_DebugName(name) {}
		virtual ~Module() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender() {}

	public:
		const char* GetDebugName() const { return m_DebugName; }
		int32 GetIndex() const { return m_ModuleIndex; }

	private:
		int32 m_ModuleIndex;
		const char* m_DebugName;

	private:
		friend class ModuleStack;
	};

}