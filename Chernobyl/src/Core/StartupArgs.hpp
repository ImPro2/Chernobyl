#pragma once

namespace CH
{

	struct ApplicationStartupArguments
	{
		int32 ArgCount;
		char** Arguments;
	};

	struct ApplicationInitData
	{
		ApplicationStartupArguments StartupArgs;
		String ClientLogProfile;
		bool EnableImGui;

		ApplicationInitData(ApplicationStartupArguments args, const String& clientLogProfile, bool enableImGui)
			: StartupArgs(args), ClientLogProfile(clientLogProfile), EnableImGui(enableImGui)
		{
		}
	};

}