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
	
	#define CH_ASSERT_CON(condition)\
	if (!(condition))\
	{\
		CH_ERROR("Assertion failed: [FILE]: ({0}), [LINE]: ({1})", __FILE__, __LINE__);\
		__debugbreak();\
	}

	#define CH_ASSERT(condition, ...)\
	if (!(condition))\
	{\
		CH_ERROR("Assertion failed: [FILE]: ({0}), [LINE]: ({1})", __FILE__, __LINE__);\
		CH_ERROR(__VA_ARGS__);\
		__debugbreak();\
	}

	#define CH_CORE_ASSERT(condition, ...)\
	if (!(condition))\
	{\
		CH_CORE_ERROR("Assertion failed: [FILE]: ({0}), [LINE]: ({1})", __FILE__, __LINE__);\
		CH_CORE_ERROR(__VA_ARGS__);\
		__debugbreak();\
	}

#else
	#define CH_ASSERT_CON(condition)
	#define CH_ASSERT(condition, ...)
	#define CH_CORE_ASSERT(condition, ...)
#endif

#endif

#define CH_BIND_EVENT_FN(fn) [this](auto&&... args)->decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define CH_DISPATCH_EVENT_FN(type, fn) dispatcher.Dispatch<type>(CH_BIND_EVENT_FN(fn))

#define BIT(x) 1 << x

#include "Types.h"