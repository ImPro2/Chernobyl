#include "Application.h"

#include "Chernobyl/Renderer/RenderCommand.h"
#include "Chernobyl/Module/ModuleStack.h"
#include "Time.h"

namespace CH
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ASSERT(s_Instance == nullptr, "Already initialized Application!");
		s_Instance = this;

		Log::Init();
		m_Window = Window::Create(WindowData(1366, 768, false));
		m_Window->SetEventCallback([this](Event& e) { this->OnEvent(e); });

		m_ImGuiModule = new ImGuiModule();
		ModuleStack::PushOverlay(m_ImGuiModule);
	}

	void Application::SetStartupArguments(int argc, char** argv)
	{
		m_StartupArguments.Count = argc;

		for (int i = 0; i < argc; i++)
		{
			m_StartupArguments.Args[i] = std::string(argv[i]);
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		CH_DISPATCH_EVENT_FN(AppCreateEvent,    OnAppCreate);
		CH_DISPATCH_EVENT_FN(AppCloseEvent,     OnAppClose);
		CH_DISPATCH_EVENT_FN(WindowResizeEvent, OnWindowResize);

		for (std::vector<Module*>::iterator it = ModuleStack::begin(); it != ModuleStack::end(); it++)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	int32 Application::Run()
	{
		while (m_Running)
		{
			Time::Update();
			
			if (!m_Minimized)
			{
				RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f });
				RenderCommand::Clear();

				for (std::vector<Module*>::iterator it = ModuleStack::begin(); it != ModuleStack::end(); it++)
					(*it)->OnUpdate();

				m_ImGuiModule->BeginFrame();
				for (std::vector<Module*>::iterator it = ModuleStack::begin(); it != ModuleStack::end(); it++)
					(*it)->OnImGuiRender();
				m_ImGuiModule->EndFrame();	
			}

			m_Window->Update();
			
			m_Stats.FrameCount++;
		}

		return m_ExitCode;
	}

	bool Application::OnAppCreate(AppCreateEvent& e)
	{
		return true;
	}

	bool Application::OnAppClose(AppCloseEvent& e)
	{
		m_ExitCode = e.GetReturnCode();
		m_Running = false;

		ModuleStack::Clear();

		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_Minimized = (e.GetWidth() <= 0 && e.GetHeight() <= 0);
		return true;
	}

}