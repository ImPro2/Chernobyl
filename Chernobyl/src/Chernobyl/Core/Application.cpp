#include "chpch.h"
#include "Application.h"

#include "Chernobyl/Renderer/RenderCommand.h"
#include "Chernobyl/Renderer/Renderer.h"
#include "Chernobyl/Module/ModuleStack.h"
#include "Time.h"
#include "UUID.h"

namespace CH
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		CH_ASSERT(s_Instance == nullptr, "Already initialized Application!");
		s_Instance = this;

		Log::Init();
		m_Window = Window::Create();
		m_Window->SetEventCallback([this](Event& e) { this->OnEvent(e); });

		Renderer::Init();

		m_ImGuiModule = new ImGuiModule();
		ModuleStack::PushOverlay(m_ImGuiModule);
	}

	void Application::SetStartupArguments(int argc, char** argv)
	{
		m_StartupArguments.Count = argc;

		for (int i = 0; i < argc; i++)
		{
			m_StartupArguments.Args.push_back(argv[i]);
		}

		// do some extra formatting here
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
				for (std::vector<Module*>::iterator it = ModuleStack::begin(); it != ModuleStack::end(); it++)
				{
					(*it)->OnUpdate();
					if (!m_Running) break;
				}

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

	void Application::Exit(ExitCode code)
	{
		m_Window->GetEventCallback()(AppCloseEvent((int32)code));
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
		
		RenderCommand::SetViewport(e.GetSize());
		
		return true;
	}

}