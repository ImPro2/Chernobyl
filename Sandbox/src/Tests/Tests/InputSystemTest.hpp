#pragma once

#include "../Test.hpp"

namespace CH::Sandbox::Test
{

	class InputSystemTest : public ITest, public IEventListener
	{
	public:
		InputSystemTest();
		~InputSystemTest();

		void OnInit() override;
		void OnUpdate() override;
	};

}