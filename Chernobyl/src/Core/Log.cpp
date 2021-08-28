#include "chpch.hpp"
#include "Log.hpp"

#include <string>

namespace CH
{

	bool Log::sIsInitialized = false;
	String Log::mClientProfile = "Client";

	void Log::Init()
	{
		sIsInitialized = true;
	}

	void Log::SetClientLogProfile(const String& profile)
	{
		mClientProfile = profile;
	}


}