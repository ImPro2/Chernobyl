#pragma once

#include "Chernobyl/Module/Module.h"

namespace CH
{

	class ImGuiModule : public Module
	{
	public:
		ImGuiModule();
		~ImGuiModule();

		void OnAttach() override;
		void OnEvent(Event& e) override;

		void BeginFrame();
		void EndFrame();

	private:
		void SetDarkThemeColors();
		void SetLightThemeColors();

	private:
		bool m_BlockEvents = true;
	};

}