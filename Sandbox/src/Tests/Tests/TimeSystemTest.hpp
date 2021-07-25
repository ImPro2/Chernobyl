#pragma once

#include "../Test.hpp"

namespace CH::Sandbox::Test
{

	class TimeSystemTest : public ITest
	{
	public:
		TimeSystemTest();
		~TimeSystemTest() = default;

	public:
		void OnUpdate() override;

	};

}