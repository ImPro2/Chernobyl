#include "sandboxpch.hpp"
#include "EventSystemTest.hpp"

namespace CH::Sandbox::Test
{

	EventSystemTest::EventSystemTest()
		: ITest("EventSystemTest")
	{
	}

	EventSystemTest::~EventSystemTest()
	{
	}

	void EventSystemTest::OnInit()
	{
		System::GetSystem(SystemType::Event)->GetSubsystem<EventManager>()->Subscribe(this);
	}

	void EventSystemTest::OnDestroy()
	{
	}

	void EventSystemTest::OnUpdate()
	{
	}

	// events

	void EventSystemTest::Event_OnEvent(const Event& e)
	{
		
	}

	void EventSystemTest::Event_OnMouseClick(MouseClickEvent e)
	{
		String str = e.ToString();
		CH_CLIENT_LOG(LogSeverity::Info, "{1}", str);
	}

	void EventSystemTest::Event_OnMouseRelease(MouseReleaseEvent e)
	{
		String str = e.ToString();
		CH_CLIENT_LOG(LogSeverity::Info, "{1}", str);
	}

	void EventSystemTest::Event_OnMouseMove(MouseMoveEvent e)
	{
		const char* str = e.ToString().c_str();
		CH_CLIENT_LOG(LogSeverity::Info, "{1}", str);
	}

	void EventSystemTest::Event_OnMouseScroll(MouseScrollEvent e)
	{
		String str = e.ToString();
		CH_CLIENT_LOG(LogSeverity::Info, "{1}", str);
	}

	void EventSystemTest::Event_OnKeyPress(KeyPressEvent e)
	{
		String str = e.ToString();
		CH_CLIENT_LOG(LogSeverity::Info, "{1}", str);
	}

	void EventSystemTest::Event_OnKeyRelease(KeyReleaseEvent e)
	{
		String str = e.ToString();
		CH_CLIENT_LOG(LogSeverity::Info, "{1}", str);
	}

	void EventSystemTest::Event_OnKeyType(KeyTypeEvent e)
	{
		String str = e.ToString();
		CH_CLIENT_LOG(LogSeverity::Info, "{1}", str);
	}


}