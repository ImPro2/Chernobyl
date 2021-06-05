#pragma once

#include "Log.h"

#include <functional>

#ifdef CH_PLATFORM_WINDOWS

	#ifdef CH_DEBUG
		#define CH_ENABLE_ASSERTS 1
	#else
		#define CH_ENABLE_ASSERTS 0
#endif

#if CH_ENABLE_ASSERTS 1
	
	#define ASSERT_CON(condition)\
	if (!(condition))\
	{\
		ERROR("Assertion failed: [FILE]: ({0}), [LINE]: ({1})", __FILE__, __LINE__);\
		__debugbreak();\
	}

	#define ASSERT(condition, ...)\
	if (!(condition))\
	{\
		ERROR("Assertion failed: [FILE]: ({0}), [LINE]: ({1})", __FILE__, __LINE__);\
		ERROR(__VA_ARGS__);\
		__debugbreak();\
	}

	#define CORE_ASSERT(condition, ...)\
	if (!(condition))\
	{\
		CORE_ERROR("Assertion failed: [FILE]: ({0}), [LINE]: ({1})", __FILE__, __LINE__);\
		CORE_ERROR(__VA_ARGS__);\
		__debugbreak();\
	}

#else
	#define ASSERT_CON(condition)
	#define ASSERT(condition, ...)
	#define CORE_ASSERT(condition, ...)
#endif

#endif

#define CH_BIND_EVENT_FN(fn) [this](auto&&... args)->decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define CH_DISPATCH_EVENT_FN(type, fn) dispatcher.Dispatch<type>(CH_BIND_EVENT_FN(fn))

#include "Types.h"