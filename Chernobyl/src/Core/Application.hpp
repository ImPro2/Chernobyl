#pragma once

#include "ExitCode.hpp"
#include "Core.hpp"

namespace CH
{

	struct ApplicationStartupArguments
	{
		int32 ArgCount;
		char** Arguments;
	};

	class Application
	{
	public:
		Application(ApplicationStartupArguments args);
		~Application();

		void Run();
		void Close();

	public:
		// getters

		static Application* Get() { return sInstance; }

		ApplicationStartupArguments GetStartupArguments() const { return mStartupArgs; }
		bool IsRunning()		const { return mRunning;  }
		ExitCode GetExitCode()	const { return mExitCode; }

	private:
		static Application* sInstance;
		ApplicationStartupArguments mStartupArgs;
		bool mRunning = true;
		ExitCode mExitCode = ExitCode::Success;
	};

	// Defined in Client

	extern Application* CreateApplication(ApplicationStartupArguments args);

}