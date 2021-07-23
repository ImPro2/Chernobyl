#pragma once

#include <random>

namespace CH
{

	class Random
	{
		template<typename T>
		static T Ranged(T a, T b)
		{
			static_assert(false);
		}

		template<>
		static int32 Ranged<int32>(int32 a, int32 b)
		{
			std::uniform_int_distribution<> dist(a, b);
			return dist(Engine());
		}

		template<>
		static float Ranged<float>(float a, float b)
		{
			std::uniform_int_distribution<float> dist(a, b);
			return dist(Engine());
		}

		template<>
		static char Ranged<char>(char a, char b)
		{
			std::uniform_int_distribution<char> dist(a, b);
			return dist(Engine());
		}

	private:
		static std::mt19937 Engine()
		{
			static std::random_device rd;
			static std::mt19937 engine(rd());
			return engine;
		}
	};

}