#pragma once

#if CH_USE_STL_PAIR 1

#include <pair>

namespace CH
{

	template<class T1, class T2>
	using Pair = std::pair<T1, T2>

}

#else

namespace CH
{

	template<class T1, class T2>
	struct Pair
	{
		T1 First;
		T2 Second;
	};

}

#endif