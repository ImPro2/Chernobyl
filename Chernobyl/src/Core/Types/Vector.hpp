#pragma once

#include <vector>

#if CH_USE_STL_VECTOR 1

template<class T>
using Vector = std::vector<T>;

#else

class Vector
{
public:
	// TODO: Implement own vector class
};

#endif