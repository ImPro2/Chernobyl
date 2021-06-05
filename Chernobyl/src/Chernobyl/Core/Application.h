#pragma once

#include "Chernobyl/Window/WindowInterface.h"
#include "Chernobyl/GUI/ImGuiModule.h"
#include "Core.h"
#include "ExitCode.h"

#include "glm/glm.hpp"

namespace CH
{

	struct ApplicationStats
	{
		uint64 FrameCount = 0;
	};

	struct StartupArguments
	{
		std::vector<char*> Args;
		int32 Count;
	};

	class Application
	{
	public:
		Application();
		~Application() = default;

		int32 Run();

		static Application* Get() { return s_Instance; }

	public:
		ApplicationStats GetStats() { return m_Stats; }
		Window* GetWindow() { return m_Window.get(); }

	public:
		void SetStartupArguments(int argc, char** argv);
		void Exit(ExitCode code);

	private:
		// Events

		void OnEvent(Event& e);
		bool OnAppCreate(AppCreateEvent& e);
		bool OnAppClose(AppCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		int32 m_ExitCode;
		bool m_Running = true;
		bool m_Minimized = false;

		ApplicationStats m_Stats;
		StartupArguments m_StartupArguments;

		ImGuiModule* m_ImGuiModule;
	};

	extern Application* CreateApplication();

}