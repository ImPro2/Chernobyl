#pragma once

#if CH_USE_STL_INTEGERS 1

#include <stdint.h>

namespace CH
{
/*
	typedef signed char        int8_t;
	typedef short              int16_t;
	typedef int                int32_t;
	typedef long long          int64_t;
	typedef unsigned char      uint8_t;
	typedef unsigned short     uint16_t;
	typedef unsigned int       uint32_t;
	typedef unsigned long long uint64_t;
*/

	using i8 = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;

	using int32 = i32;

	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;

	using uint32 = u32;

}

#else

namespace CH
{

	using i8  = __int8;
	using i16 = __int16;
	using i32 = __int32;
	using i64 = __int64;

	using int32 = i32;

	using u8  = unsigned __int8;
	using u16 = unsigned __int16;
	using u32 = unsigned __int32;
	using u64 = unsigned __int64;

	using uint32 = u32;

}

#endif