#pragma once

#include <cstdlib>
#include <string>
#include <vector>

// std lib types

namespace CH
{

	using String = std::string;

	template<typename T>
	using Vector = std::vector<T>;

	// signed integers

	using i8 = __int8;
	using i16 = __int16;
	using i32 = __int32;
	using i64 = __int64;

	using int8 = i8;
	using int32 = i32;
	using int64 = i64;

	// unsigned integers

	using u8 = unsigned __int8;
	using u16 = unsigned __int16;
	using u32 = unsigned __int32;
	using u64 = unsigned __int64;

	using uint8 = u8;
	using uint32 = u32;
	using uint64 = u64;

	// extra

	//using byte = u16;

	// vectors

	template<typename T>
	struct vec2
	{
		union { T x, r; };
		union { T y, g; };

		// constructor/destructor

		vec2() : x((T)0), y((T)0) {}
		vec2(T x, T y) : x((T)x), y((T)y) {}

		// overloaded operators

		vec2 operator+(vec2 other)
		{
			vec2 v;
			v.x = this->x + other.x;
			v.y = this->y + other.y;
			return v;
		}
		vec2 operator-(vec2 other)
		{
			vec2 v;
			v.x = x - other.x;
			v.y = y - other.y;
			return v;
		}
		vec2 operator*(vec2 other)
		{
			vec2 v;
			v.x = x * other.x;
			v.y = y * other.y;
			return v;
		}
		vec2 operator/(vec2 other)
		{
			vec2 v;
			v.x = x / other.x;
			v.y = y / other.y;
			return v;
		}
		void operator+=(vec2 other)
		{
			x += other.x;
			y += other.y;
		}
		void operator-=(vec2 other)
		{
			x -= other.x;
			y -= other.y;
		}
		void operator*=(vec2 other)
		{
			x *= other.x;
			y *= other.y;
		}
		void operator/=(vec2 other)
		{
			x /= other.x;
			y /= other.y;
		}
	};

	template<typename T>
	struct vec3
	{
		union { T x, r; };
		union { T y, g; };
		union { T z, b; };

		// constructor/destructor

		vec3() : x((T)0), y((T)0), z((T)0) {}
		vec3(T x, T y, T z) : x((T)x), y((T)y), z((T)z) {}

		// overloaded operators

		vec3 operator+(vec3 other)
		{
			vec3 v;
			v.x = this->x + other.x;
			v.y = this->y + other.y;
			v.z = this->z + other.z;
			return v;
		}
		vec3 operator-(vec3 other)
		{
			vec3 v;
			v.x = x - other.x;
			v.y = y - other.y;
			v.z = z - other.z;
			return v;
		}
		vec3 operator*(vec3 other)
		{
			vec3 v;
			v.x = x * other.x;
			v.y = y * other.y;
			v.z = z * other.z;
			return v;
		}
		vec3 operator/(vec3 other)
		{
			vec3 v;
			v.x = x / other.x;
			v.y = y / other.y;
			v.z = z / other.z;
			return v;
		}
		void operator+=(vec3 other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}
		void operator-=(vec3 other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}
		void operator*=(vec3 other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
		}
		void operator/=(vec3 other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
		}
	};

	template<typename T>
	struct vec4
	{
		union { T x, r; };
		union { T y, g; };
		union { T z, b; };
		union { T w, a; };

		// constructor/destructor

		vec4() : x((T)0), y((T)0), z((T)0), w((T)0) {}
		vec4(T x, T y, T z, T w) : x((T)x), y((T)y), z((T)z), w((T)w) {}

		// overloaded operators

		vec4 operator+(vec4 other)
		{
			vec4 v;
			v.x = this->x + other.x;
			v.y = this->y + other.y;
			v.z = this->z + other.z;
			v.w = this->w + other.w;
			return v;
		}
		vec4 operator-(vec4 other)
		{
			vec4 v;
			v.x = x - other.x;
			v.y = y - other.y;
			v.z = z - other.z;
			v.w = w - other.w;
			return v;
		}
		vec4 operator*(vec4 other)
		{
			vec4 v;
			v.x = x * other.x;
			v.y = y * other.y;
			v.z = z * other.z;
			v.w = w * other.w;
			return v;
		}
		vec4 operator/(vec4 other)
		{
			vec4 v;
			v.x = x / other.x;
			v.y = y / other.y;
			v.z = z / other.z;
			v.w = w / other.w;
			return v;
		}
		void operator+=(vec4 other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
		}
		void operator-=(vec4 other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
		}
		void operator*=(vec4 other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
		}
		void operator/=(vec4 other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
		}
	};

	using float2 = vec2<float>;
	using float3 = vec3<float>;
	using float4 = vec4<float>;

	//using byte2 = vec2<u16>;
	//using byte3 = vec3<u16>;
	//using byte4 = vec4<u16>;

	using int2 = vec2<int32>;
	using int3 = vec3<int32>;
	using int4 = vec4<int32>;

}