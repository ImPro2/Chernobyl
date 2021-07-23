#pragma once

#include "../Test.hpp"

namespace CH::Sandbox::Test
{

	class EventSystemTest : public CH::Sandbox::ITest, public CH::IEventListener
	{
	public:
		EventSystemTest();
		~EventSystemTest();

	public:
		void OnInit() override;
		void OnDestroy() override;
		void OnUpdate() override;

	private:
		// Events

		void Event_OnEvent(const Event& e) override;
		void Event_OnMouseClick(MouseClickEvent e) override;
		void Event_OnMouseRelease(MouseReleaseEvent e) override;
		void Event_OnMouseMove(MouseMoveEvent e) override;
		void Event_OnMouseScroll(MouseScrollEvent e) override;
		void Event_OnKeyPress(KeyPressEvent e) override;
		void Event_OnKeyRelease(KeyReleaseEvent e) override;
		void Event_OnKeyType(KeyTypeEvent e) override;
	};

}