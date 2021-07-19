#pragma once

#include "Log.hpp"
#include "Types/Types.hpp"

#ifdef CH_BUILD_STATIC
#	define CH_API	extern
#else
#	define CH_API	__declspec(dllexport)
#endif

#ifdef CH_DEV

#	define CH_CORE_ASSERT(condition, ...)\
	if (!(condition))\
	{\
		CH_CORE_LOG(CH::LogSeverity::Error, "Assertion Failed ({0}, {1}) in {2}.\n Reason:\n", __FILE__, __LINE__, __FUNCTION__);\
		CH_CORE_LOG(CH::LogSeverity::Error, __VA_ARGS__); \
		__debugbreak(); \
	}

#	define CH_CLIENT_ASSERT(condition, ...)\
	if (!(condition))\
	{\
		CH_CLIENT_LOG(CH::LogSeverity::Error, "Assertion Failed ({0}, {1}) in {2}.\n Reason:\n", __FILE__, __LINE__, __FUNCTION__);\
		CH_CLIENT_LOG(CH::LogSeverity::Error, __VA_ARGS__);\
		__debugbreak();\
	}

#elif CH_TEST

#	define CH_CORE_ASSERT(condition, ...)\
	if (!(condition))\
	{\
		// TODO: Show a message box
		while (true); \
	}

#	define CH_CLIENT_ASSERT(condition, ...)\
	if (!(condition))\
	{\
		// TODO: Show a message box
		while (true); \
	}

#else
#	define CH_CORE_ASSERT(condition, ...)
#	define CH_CLIENT_ASSERT(condition, ...)
#endif