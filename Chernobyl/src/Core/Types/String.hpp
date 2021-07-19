#pragma once


#if CH_USE_STL_STR 1

#include <string>

namespace CH
{

	using String = std::string;

}

#else

namespace CH
{

	// TODO: Implement String Class
	class String {};

}

#endif