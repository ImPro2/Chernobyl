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
	}

	Application::~Application()
	{
		System::Shutdown();

		delete sInstance;
		sInstance = nullptr;

		CH_CORE_LOG(LogSeverity::Info, "Successfully Destroyed Chernobyl");
	}

	void Application::Run()
	{
		while (mRunning)
		{
			mWindow->Update();
		}
	}

	void Application::Close()
	{
		mWindow->Close();

		mRunning  = false;
		mExitCode = ExitCode::CustomExit;
	}

}
