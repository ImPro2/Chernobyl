#pragma once

#include "Chernobyl/Core/Core.h"
#include "Module.h"

namespace CH
{

	class ModuleStack
	{
	public:
		static void Push(Module* module);
		static void PushOverlay(Module* module);
		static void Pop(Module* module);
		static void PopOverlay(Module* module);
		static void Clear();

		static Module* GetModuleAtIndex(int32 index);
		static Module* GetModuleAtDebugName(const char* name);

		static std::vector<Module*>::iterator begin() { return m_ModuleStack.begin(); }
		static std::vector<Module*>::iterator end() { return m_ModuleStack.end(); }

		static std::vector<Module*> Get() { return m_ModuleStack; }

	private:
		static std::vector<Module*> m_ModuleStack;

		static int32 m_InsertIndex;
	};

}