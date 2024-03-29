#pragma once

#include "Log.hpp"

#ifdef CH_BUILD_STATIC
#	define CH_API	extern
#else
#	define CH_API	__declspec(dllexport)
#endif

#if defined(CH_DEV) || defined(CH_TEST)

//	core assert

#	define CH_CORE_ASSERT(condition, ...)\
	if (!(condition))\
	{\
		CH_CORE_LOG(CH::LogSeverity::Error, "Assertion Failed ({}, {}) in {}.\n Reason:\n", __FILE__, __LINE__, __FUNCTION__);\
		CH_CORE_LOG(CH::LogSeverity::Error, __VA_ARGS__); \
		__debugbreak(); \
	}

//	core break

#	define CH_CORE_BREAK_C(condition)\
	if (!(condition))\
	{\
		CH_CORE_LOG(CH::LogSeverity::Error, "A break occured. ({}, {}) in {}.\n Reason: Unknown", __FILE__, __LINE__, __FUNCTION__);\
		__debugbreak();\
	}

#	define CH_CORE_BREAK_S(...)\
	do\
	{\
		CH_CORE_LOG(CH::LogSeverity::Error, "A break occured. ({}, {}) in {}.\n Reason:\n", __FILE__, __LINE__, __FUNCTION__);\
		CH_CORE_LOG(CH::LogSeverity::Error, __VA_ARGS__);\
		__debugbreak();\
	}\
	while (0);

//	client assert

#	define CH_CLIENT_ASSERT(condition, ...)\
	if (!(condition))\
	{\
		CH_CLIENT_LOG(CH::LogSeverity::Error, "Assertion Failed ({0}, {1}) in {2}.\n Reason:\n", __FILE__, __LINE__, __FUNCTION__);\
		CH_CLIENT_LOG(CH::LogSeverity::Error, __VA_ARGS__);\
		__debugbreak();\
	}

//	client break

#	define CH_CLIENT_BREAK_C(condition)\
	if (!(condition))\
	{\
		CH_CLIENT_LOG(CH::LogSeverity::Error, "A break occured. ({0}, {1}) in {2}.\n Reason: Unknown", __FILE__, __LINE__, __FUNCTION__);\
		__debugbreak();\
	}

#	define CH_CLIENT_BREAK_S(...)\
	do\
	{\
		CH_CLIENT_LOG(CH::LogSeverity::Error, "A break occured. ({0}, {1}) in {2}.\n Reason:\n", __FILE__, __LINE__, __FUNCTION__);\
		CH_CLIENT_LOG(CH::LogSeverity::Error, __VA_ARGS__);\
		__debugbreak();\
	}\
	while (0);

#else
#	define CH_CORE_ASSERT(condition, ...)
#	define CH_CORE_BREAK_C(condition)
#	define CH_CORE_BREAK_S(...)

#	define CH_CLIENT_ASSERT(condition, ...)
#	define CH_CLIENT_BREAK_C(condition)
#	define CH_CLIENT_BREAK_S(...)
#endif

#define CH_BIT(x) 1 << x

#include "Types/Types.hpp"
#include "Debug/Profiler/Profiler.hpp"