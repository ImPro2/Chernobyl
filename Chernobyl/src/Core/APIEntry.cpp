#include "chpch.hpp"
#include "APIEntry.hpp"
#include "Log.hpp"
#include "ExitCode.hpp"
#include "Core.hpp"

CH::int32 main(CH::int32 argc, char* argv[])
{
	CH::ExitCode exitcode;

	{
		CH::Log::Init();
	}

	{

		CH::ApplicationStartupArguments args{ argc, argv };

		CH::Application* app = CH::CreateApplication(args);
		app->Run();

		exitcode = app->GetExitCode();

		delete app;
		app = nullptr;
	}

	return (CH::int32)exitcode;
}