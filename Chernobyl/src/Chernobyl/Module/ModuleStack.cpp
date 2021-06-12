#include "chpch.h"
#include "ModuleStack.h"

namespace CH
{

	std::vector<Module*> ModuleStack::m_ModuleStack;
	int32 ModuleStack::m_InsertIndex = 0;

	void ModuleStack::Push(Module* module)
	{
		module->m_ModuleIndex = m_InsertIndex;
		module->OnAttach();

		m_ModuleStack.emplace(m_ModuleStack.begin() + m_InsertIndex, module);
		m_InsertIndex++;
	}

	void ModuleStack::PushOverlay(Module* module)
	{
		module->m_ModuleIndex = m_InsertIndex;
		module->OnAttach();

		m_ModuleStack.push_back(module);
	}

	void ModuleStack::Pop(Module* module)
	{
		auto it = std::find(m_ModuleStack.begin(), m_ModuleStack.end(), module);
		if (it != m_ModuleStack.end())
		{
			m_ModuleStack.erase(it);
			m_InsertIndex--;
			module->OnDetach();
		}
	}

	void ModuleStack::PopOverlay(Module* module)
	{
		auto it = std::find(m_ModuleStack.begin(), m_ModuleStack.end(), module);
		if (it != m_ModuleStack.end())
		{
			m_ModuleStack.erase(it);
			module->OnDetach();
		}
	}

	void ModuleStack::Clear()
	{
		for (Module* module : m_ModuleStack)
		{
			module->OnDetach();
			delete module;
		}

		m_ModuleStack.clear();
	}

	Module* ModuleStack::GetModuleAtIndex(int32 index)
	{
		for (Module* module : m_ModuleStack)
		{
			if (index == module->GetIndex())
				return module;
		}
		return nullptr;
	}

	Module* ModuleStack::GetModuleAtDebugName(const char* name)
	{
		for (Module* module : m_ModuleStack)
		{
			if (name == module->GetDebugName())
				return module;
		}
		return nullptr;
	}

}