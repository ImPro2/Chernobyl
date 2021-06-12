#include "chpch.h"
#include "APIEntry.h"

#ifdef CH_DEBUG
#include "ExitCode.h"
#endif

int main(int argc, char** argv)
{
	CH::Application* app = CreateApplication();
	app->SetStartupArguments(argc, argv);

	int code = app->Run();
	delete app;

#ifdef CH_DEBUG
	switch (code)
	{
	case (int)CH::ExitCode::Success:
		CH_CORE_INFO("Exit success");
		break;
	default:
		CH_CORE_ERROR("Exit failure");
	}
#endif

	return code;
}