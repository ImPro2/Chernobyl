#include "chpch.hpp"
#include "Application.hpp"

#include "Systems/WindowSystem/WindowSystem.hpp"

namespace CH
{

	Application* Application::sInstance = nullptr;

	Application::Application(ApplicationStartupArguments args)
		: mStartupArgs(args)
	{
		CH_CORE_ASSERT(!sInstance, "Already Initialized Application");
		sInstance = this;

		System::Init();

		mWindow = System::GetSystem(SystemType::Window)->CreateObject<IWindow>();

		System::GetSystem(SystemType::Event)->GetSubsystem<EventManager>()->Subscribe(
		[this](Event& e)
		{
			this->OnEvent(e);
		});

		CH_CORE_LOG(LogSeverity::Info, "Successfully initialized Chernobyl");
	}

	Application::~Application()
	{
		System::Shutdown();

		CH_CORE_LOG(LogSeverity::Info, "Successfully Destroyed Chernobyl");
	}

	void Application::Run()
	{
		this->Init();

		while (mRunning)
		{

			System::GetSystem(SystemType::Time)->GetSubsystem<Time>()->Update();

			// ...
			{
				this->Update();
			}
			// ...

			mWindow->Update();
			System::GetSystem(SystemType::Event)->GetSubsystem<EventManager>()->HandleEvents();
		}
	}

	void Application::Close()
	{
		mRunning = false;
	}

	// events

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		CH_DISPATCH_EVENT_FN(WindowResizeEvent, Event_OnWindowResize);
		CH_DISPATCH_EVENT_FN(WindowCloseEvent,  Event_OnWindowClose);
		CH_DISPATCH_EVENT_FN(AppDestroyEvent,	Event_OnAppDestroy);
	}

	void Application::Event_OnWindowResize(WindowResizeEvent& e)
	{
		// do something in future
	}

	void Application::Event_OnWindowClose(WindowCloseEvent& e)
	{
		// check if the window that is closing is the same as the main window

		if (e.Data.Title == mWindow->GetTitle() &&
			e.Data.Width == mWindow->GetWidth() && e.Data.Height == mWindow->GetHeight() &&
			e.Data.VSync == mWindow->IsVSync())
		{
			// close the main window and exit the Application

			AppDestroyEvent appevent = AppDestroyEvent(ExitCode::Success);
			System::GetSystem(SystemType::Event)->GetSubsystem<EventManager>()->BroadcastEvent((Event*)&appevent);
		}
	}

	void Application::Event_OnAppDestroy(AppDestroyEvent& e)
	{
		mExitCode = e.ReturnCode;

		Close();
	}

}