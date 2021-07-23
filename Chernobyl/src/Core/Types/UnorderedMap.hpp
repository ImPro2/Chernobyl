#pragma once

#ifdef CH_USE_STL_UNORDERED_MAP

#include <unordered_map>

namespace CH
{

	template<class Key, class Value>
	using UnorderedMap = std::unordered_map<Key, Value>;

}

#else

namespace CH
{

	// TODO: [Types] Implement own UnorderedMap class

	template<class Key, class Value>
	class UnorderedMap
	{
	public:
		using Type = Pair<Key, Value>;

	public:
		UnorderedMap() = default;

		Value& operator[](const Key& key)
		{
			
		}

		Value operator[](Key&& key)
		{

		}

	private:
		Vector<Type> mValues;
	};

}

#endif