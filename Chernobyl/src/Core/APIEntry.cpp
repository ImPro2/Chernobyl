#include "chpch.hpp"
#include "APIEntry.hpp"
#include "Log.hpp"
#include "ExitCode.hpp"
#include "Core.hpp"

#include "Debug/Allocation/Allocations.hpp"

CH::int32 main(CH::int32 argc, char* argv[])
{
	CH::ExitCode exitcode;
	CH::Log::Init();

	CH::Allocations::ReportLiveAllocations();

	CH_PROFILE_BEGIN_SESSION("Chernobyl Startup", "data/ch-startup.json");
		CH::ApplicationStartupArguments args{ argc, argv };
		CH::Application* app = CH::CreateApplication(args);
	CH_PROFILE_END_SESSION();

	CH::Allocations::ReportLiveAllocations();

	CH_PROFILE_BEGIN_SESSION("Chernobyl Runtime", "data/ch-runtime.json");
		app->Run();
	CH_PROFILE_END_SESSION();

	CH::Allocations::ReportLiveAllocations();

	exitcode = app->GetExitCode();

	CH_PROFILE_BEGIN_SESSION("Chernobyl Shutdown", "data/ch-shutdown.json");
		delete app;
		app = nullptr;
	CH_PROFILE_END_SESSION();


	return (CH::int32)exitcode;
}