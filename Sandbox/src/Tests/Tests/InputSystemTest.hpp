#pragma once

#include "../Test.hpp"

namespace CH::Sandbox::Test
{

	class InputSystemTest : public ITest
	{
	public:
		InputSystemTest();
		~InputSystemTest();

		void OnInit() override;
		void OnUpdate() override;

	public:
		// events

		void Event_OnMouseClick(MouseClickEvent e) override;
		void Event_OnMouseRelease(MouseReleaseEvent e) override;
		void Event_OnMouseMove(MouseMoveEvent e) override;
		void Event_OnMouseScroll(MouseScrollEvent e) override;
		void Event_OnKeyPress(KeyPressEvent e) override;
		void Event_OnKeyRelease(KeyReleaseEvent e) override;
	};

}