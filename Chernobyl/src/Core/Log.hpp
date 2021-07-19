#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#pragma pop

#include <memory>

#include "Core.hpp"

namespace CH
{

	enum class LogSeverity
	{
		Trace,
		Info,
		Warn,
		Error,
		Critical
	};

	class Log
	{
	public:
		static void Init();

		template<typename ... Args>
		static void CoreLog(LogSeverity severity, const char* fmt, const Args& ... args)
		{
			switch (severity)
			{
				case LogSeverity::Trace:		CoreTrace(   fmt, args...);		break;
				case LogSeverity::Info:			CoreInfo(    fmt, args...);		break;
				case LogSeverity::Warn:			CoreWarn(    fmt, args...);		break;
				case LogSeverity::Error:		CoreError(   fmt, args...);		break;
				case LogSeverity::Critical:		CoreCritical(fmt, args...);		break;
			}
		}

		template<typename ... Args>
		static void ClientLog(LogSeverity severity, const char* fmt, const Args& ... args)
		{
			switch (severity)
			{
				case LogSeverity::Trace:		Trace(	 fmt, args...);		break;
				case LogSeverity::Info:			Info(	 fmt, args...);		break;
				case LogSeverity::Warn:			Warn(	 fmt, args...);		break;
				case LogSeverity::Error:		Error(	 fmt, args...);		break;
				case LogSeverity::Critical:		Critical(fmt, args...);		break;
			}
		}


		template<typename ... Args>
		static void CoreTrace(const char* fmt, const Args& ... args)
		{
			sCoreLogger->trace(fmt, spdlog::level::info, args...);
		}
		template<typename ... Args>
		static void CoreInfo(const char* fmt, const Args& ... args)
		{
			sCoreLogger->info(fmt, spdlog::level::info, args...);
		}
		template<typename ... Args>
		static void CoreWarn(const char* fmt, const Args& ... args)
		{
			sCoreLogger->warn(fmt, spdlog::level::info, args...);
		}
		template<typename ... Args>
		static void CoreError(const char* fmt, const Args& ... args)
		{
			sCoreLogger->error(fmt, spdlog::level::info, args...);
		}
		template<typename ... Args>
		static void CoreCritical(const char* fmt, const Args& ... args)
		{
			sCoreLogger->critical(fmt, spdlog::level::info, args...);
		}

		template<typename ... Args>
		static void ClientTrace(const char* fmt, const Args& ... args)
		{
			sClientLogger->trace(fmt, spdlog::level::info, args...);
		}
		template<typename ... Args>
		static void ClientInfo(const char* fmt, const Args& ... args)
		{
			sClientLogger->info(fmt, spdlog::level::info, args...);
		}
		template<typename ... Args>
		static void ClientWarn(const char* fmt, const Args& ... args)
		{
			sClientLogger->warn(fmt, spdlog::level::info, args...);
		}
		template<typename ... Args>
		static void ClientError(const char* fmt, const Args& ... args)
		{
			sClientLogger->error(fmt, spdlog::level::info, args...);
		}
		template<typename ... Args>
		static void ClientCritical(const char* fmt, const Args& ... args)
		{
			sClientLogger->critical(fmt, spdlog::level::info, args...);
		}

	private:
		static std::shared_ptr<spdlog::logger> sCoreLogger;
		static std::shared_ptr<spdlog::logger> sClientLogger;
	};

}

#ifdef CH_DEV

#	define CH_CORE_LOG(/*CH::LogSeverity*/ severity, /*const char* fmt, ...*/ ...)\
	CH::Log::CoreLog((CH::LogSeverity)severity, __VA_ARGS__)

#	define CH_CLIENT_LOG(/*CH::LogSeverity*/ severity, /*const char* fmt, ...*/ ...)\
	CH::Log::ClientLog((CH::LogSeverity)severity, __VA_ARGS__)

#elif defined(CH_TEST)

// TODO: show msg box

#else

// do nothing

#endif