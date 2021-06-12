#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/async_logger.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/common.h>
#include <spdlog/formatter.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace CH
{

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// avoid error...
#undef ERROR

#define CH_CORE_TRACE(...)		CH::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CH_CORE_INFO(...)		CH::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CH_CORE_WARN(...)		CH::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CH_CORE_ERROR(...)		CH::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CH_CORE_CRITICAL(...)	CH::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define CH_TRACE(...)			CH::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CH_INFO(...)			CH::Log::GetClientLogger()->info(__VA_ARGS__)
#define CH_WARN(...)			CH::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CH_ERROR(...)			CH::Log::GetClientLogger()->error(__VA_ARGS__)
#define CH_CRITICAL(...)		CH::Log::GetClientLogger()->critical(__VA_ARGS__)