#pragma once

#include <fmt/core.h>
#include <fmt/color.h>

#include <memory>
#include <string>

#include "Core/Types/String.hpp"

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
		static void SetClientLogProfile(const String& profile);

		static bool IsInitialized() { return sIsInitialized; }

	public:
		inline static fmt::color LogSeverityToFmtColor(LogSeverity severity)
		{
			switch (severity)
			{
				case CH::LogSeverity::Trace:		return fmt::color::white;	break;
				case CH::LogSeverity::Info:			return fmt::color::green;	break;
				case CH::LogSeverity::Warn:			return fmt::color::yellow;	break;
				case CH::LogSeverity::Error:		return fmt::color::red;		break;
				case CH::LogSeverity::Critical:		return fmt::color::red;		break;
			}

			return (fmt::color)-1;
		}

		template<typename ... Args>
		static void CoreLog(LogSeverity severity, const char* fmt, const Args& ... args)
		{
			fmt::print(fg(fmt::color::dark_blue), "[Engine]: ");

			switch (severity)
			{
				case LogSeverity::Trace:		CoreTrace(   fmt, args...);		break;
				case LogSeverity::Info:			CoreInfo(    fmt, args...);		break;
				case LogSeverity::Warn:			CoreWarn(    fmt, args...);		break;
				case LogSeverity::Error:		CoreError(   fmt, args...);		break;
				case LogSeverity::Critical:		CoreCritical(fmt, args...);		break;
			}

			putc('\n', stdout);
		}

		template<typename ... Args>
		static void ClientLog(LogSeverity severity, const char* fmt, const Args& ... args)
		{
			fmt::print(fg(fmt::color::forest_green), "[Client]: ");
			switch (severity)
			{
				case LogSeverity::Trace:		ClientTrace(	fmt, args...);		break;
				case LogSeverity::Info:			ClientInfo(		fmt, args...);		break;
				case LogSeverity::Warn:			ClientWarn(		fmt, args...);		break;
				case LogSeverity::Error:		ClientError(	fmt, args...);		break;
				case LogSeverity::Critical:		ClientCritical(	fmt, args...);		break;
			}
		
			putc('\n', stdout);
		}

		template<typename ... Args>
		static void CoreTrace(const char* fmt, const Args& ... args)
		{
			fmt::print(fg(LogSeverityToFmtColor(LogSeverity::Trace)), fmt, args...);
		}
		template<typename ... Args>
		static void CoreInfo(const char* fmt, const Args& ... args)
		{
			fmt::print(fg(LogSeverityToFmtColor(LogSeverity::Info)), fmt, args...);
		}
		template<typename ... Args>
		static void CoreWarn(const char* fmt, const Args& ... args)
		{
			fmt::print(fg(LogSeverityToFmtColor(LogSeverity::Warn)), fmt, args...);
		}
		template<typename ... Args>
		static void CoreError(const char* fmt, const Args& ... args)
		{
			fmt::print(fg(LogSeverityToFmtColor(LogSeverity::Error)), fmt, args...);
		}
		template<typename ... Args>
		static void CoreCritical(const char* fmt, const Args& ... args)
		{
			fmt::print(fg(LogSeverityToFmtColor(LogSeverity::Critical)), fmt, args...);
		}

		template<typename ... Args>
		static void ClientTrace(const char* fmt, const Args& ... args)
		{
			fmt::print(fg(LogSeverityToFmtColor(LogSeverity::Trace)), fmt, args...);
		}
		template<typename ... Args>
		static void ClientInfo(const char* fmt, const Args& ... args)
		{
			fmt::print(fg(LogSeverityToFmtColor(LogSeverity::Info)), fmt, args...);
		}
		template<typename ... Args>
		static void ClientWarn(const char* fmt, const Args& ... args)
		{
			fmt::print(fg(LogSeverityToFmtColor(LogSeverity::Warn)), fmt, args...);
		}
		template<typename ... Args>
		static void ClientError(const char* fmt, const Args& ... args)
		{
			fmt::print(fg(LogSeverityToFmtColor(LogSeverity::Error)), fmt, args...);
		}
		template<typename ... Args>
		static void ClientCritical(const char* fmt, const Args& ... args)
		{
			fmt::print(fg(LogSeverityToFmtColor(LogSeverity::Trace)) | bg(LogSeverityToFmtColor(LogSeverity::Critical)), fmt, args...);
		}

	private:
		static bool sIsInitialized;
		static String mClientProfile;
	};

}

#if defined(CH_DEV) || defined(CH_TEST)

#	define CH_CORE_LOG(/*CH::LogSeverity*/ severity, /*const char* fmt, ...*/ ...)\
	CH::Log::CoreLog((CH::LogSeverity)severity, __VA_ARGS__)

#	define CH_CLIENT_LOG(/*CH::LogSeverity*/ severity, /*const char* fmt, ...*/ ...)\
	CH::Log::ClientLog((CH::LogSeverity)severity, __VA_ARGS__)
#else
// do nothing
#	define CH_CORE_LOG(/*CH::LogSeverity*/ severity, /*const char* fmt, ...*/ ...)
#	define CH_CLIENT_LOG(/*CH::LogSeverity*/ severity, /*const char* fmt, ...*/ ...)
#endif