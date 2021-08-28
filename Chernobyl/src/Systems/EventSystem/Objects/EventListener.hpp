#pragma once

#include "SSO/SSO.hpp"

#include "Systems/EventSystem/Data/Events.hpp"

namespace CH
{

	struct Event;

	// classes can inherit from this class and receive events

	class IEventListener
	{
	public:
		static ObjectType GetStaticType() { return ObjectType::EventListener; }

	public:

		// all events

		virtual void Event_OnEvent(const Event& e)						{ }

		// app events

		virtual void Event_OnAppCreate(AppCreateEvent e)				{ }
		virtual void Event_OnAppDestroy(AppDestroyEvent e)				{ }
		virtual void Event_OnAppUpdate(AppUpdateEvent e)				{ }
		virtual void Event_OnAppRender(AppRenderEvent e)				{ }

		// window events

		virtual void Event_OnWindowCreate(WindowCreateEvent e)			{ }
		virtual void Event_OnWindowClose(WindowCloseEvent e)			{ }
		virtual void Event_OnWindowResize(WindowResizeEvent e)			{ }
		virtual void Event_OnWindowMove(WindowMoveEvent e)				{ }

		// mouse events

		virtual void Event_OnMouseClick(MouseClickEvent e)				{ }
		virtual void Event_OnMouseRelease(MouseReleaseEvent e)			{ }
		virtual void Event_OnMouseMove(MouseMoveEvent e)				{ }
		virtual void Event_OnMouseScroll(MouseScrollEvent e)			{ }

		// keyboard events

		virtual void Event_OnKeyPress(KeyPressEvent e)					{ }
		virtual void Event_OnKeyRelease(KeyReleaseEvent e)				{ }
		virtual void Event_OnKeyType(KeyTypeEvent e)					{ }
	};

}