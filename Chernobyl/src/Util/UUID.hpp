#pragma once

#include <sstream>

#include "Random.hpp"

namespace CH
{

	class UUID
	{
	public:
		UUID()
		{
			Regenerate();
		}

		void Regenerate()
		{
			std::stringstream ss;

			ss << std::hex;

			for (int32 i = 0; i < 8; i++)
			{
				ss << Random::Ranged<int32>(0, 15);
			}

			ss << "-";

			for (int32 i = 0; i < 4; i++)
			{
				ss << Random::Ranged<int32>(0, 15);
			}

			ss << "-4";

			for (int32 i = 0; i < 3; i++)
			{
				ss << Random::Ranged<int32>(0, 15);
			}

			ss << "-";
			ss << Random::Ranged<int32>(8, 11);

			for (int32 i = 0; i < 3; i++)
			{
				ss << Random::Ranged<int32>(8, 11);
			}

			ss << "-";

			for (int32 i = 0; i < 12; i++)
			{
				ss << Random::Ranged<int32>(0, 15);
			}

			mUUID = ss.str();
		}

	public:
		const String& Get() const { return mUUID; }

	private:
		String mUUID;
	};

}