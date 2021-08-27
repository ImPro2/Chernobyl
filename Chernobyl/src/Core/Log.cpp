#include "chpch.hpp"
#include "Log.hpp"

namespace CH
{

	std::shared_ptr<spdlog::logger> Log::sCoreLogger;
	std::shared_ptr<spdlog::logger> Log::sClientLogger;
	bool Log::sIsInitialized = false;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%n: (%T)]: %v%$");

		sCoreLogger = spdlog::stdout_color_mt("Chernobyl");
		sCoreLogger->set_level(spdlog::level::trace);

		sClientLogger = spdlog::stdout_color_mt("Client");
		sClientLogger->set_level(spdlog::level::trace);

		sIsInitialized = true;
	}

}