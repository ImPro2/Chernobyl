#pragma once

// All types for the engine

#define CH_USE_STL_STR 1
#define CH_USE_STL_VECTOR 1
#define CH_USE_STL_INTEGERS 0
#define CH_USE_STL_PAIR 0
#define CH_USE_STL_SMART_PTR 1
#define CH_USE_STL_UNORDERED_MAP 1

#include "String.hpp"
#include "Vector.hpp"
#include "Integers.hpp"
#include "Pair.hpp"
#include "SmartPtr.hpp"
#include "UnorderedMap.hpp"

namespace CH
{

	template<class T>
	struct vec2
	{
		T x, y;

		vec2()
			: x(0), y(0)
		{
		}

		vec2(T X, T Y)
			: x(X), y(Y)
		{
		}
	};

	template<class T>
	struct vec3
	{
		union { T x; T r; };
		union { T y; T g; };
		union { T z; T b; };

		vec3()
			: x(0), y(0), z(0)
		{
		}

		vec3(T X, T Y, T Z)
			: x(X), y(Y), z(Z)
		{
		}
	};

	template<class T>
	struct vec4
	{
		union { T x; T r; };
		union { T y; T g; };
		union { T z; T b; };
		union { T w; T a; };

		vec4()
			: x(0), y(0), z(0), w(0)
		{
		}

		vec4(T X, T Y, T Z, T W)
			: x(X), y(Y), z(Z), w(W)
		{
		}
	};

	using int2 = vec2<int32>;
	using int3 = vec3<int32>;
	using int4 = vec4<int32>;

	using float2 = vec2<float>;
	using float3 = vec3<float>;
	using float4 = vec4<float>;

}