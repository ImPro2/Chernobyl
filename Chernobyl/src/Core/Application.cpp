#include "chpch.hpp"
#include "Application.hpp"

namespace CH
{

	Application* Application::sInstance = nullptr;

	Application::Application(ApplicationStartupArguments args)
		: mStartupArgs(args)
	{
		CH_CORE_ASSERT(!sInstance, "Already Initialized Application");
		sInstance = this;

		CH_CORE_LOG(LogSeverity::Info, "Successfully Initialized Chernobyl");
	}

	Application::~Application()
	{
		delete sInstance;
		sInstance = nullptr;

		CH_CORE_LOG(LogSeverity::Info, "Successfully Destroyed Chernobyl");
	}

	void Application::Run()
	{
		while (mRunning);
	}

	void Application::Close()
	{
		mRunning  = false;
		mExitCode = ExitCode::CustomExit;
	}

}
