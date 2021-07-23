#pragma once

#include "SSO/SSO.hpp"

#include "Systems/EventSystem/Data/Events.hpp"

namespace CH
{

	class Event;

	// classes can inherit from this class and receive events

	class IEventListener
	{
	public:
		static ObjectType GetStaticType() { return ObjectType::EventListener; }

	public:

		// all events

		virtual void Event(const Event& e)										{ }

		// app events

		virtual void Event_OnAppCreate(const AppCreateEvent& e)					{ }
		virtual void Event_OnAppDestroy(const AppDestroyEvent& e)				{ }
		virtual void Event_OnAppUpdate(const AppUpdateEvent& e)					{ }
		virtual void Event_OnAppRender(const AppRenderEvent& e)					{ }

		// window events

		virtual void Event_OnWindowCreate(const WindowCreateEvent& e)			{ }
		virtual void Event_OnWindowClose(const WindowCloseEvent& e)				{ }
		virtual void Event_OnWindowResize(const WindowResizeEvent& e)			{ }
		virtual void Event_OnWindowMove(const WindowMoveEvent& e)				{ }

		// mouse events

		virtual void Event_OnMouseClick(const MouseClickEvent& e)				{ }
		virtual void Event_OnMouseRelease(const MouseReleaseEvent& e)			{ }
		virtual void Event_OnMouseMove(const MouseMoveEvent& e)					{ }
		virtual void Event_OnMouseScroll(const MouseScrollEvent& e)				{ }

		// keyboard events

		virtual void Event_OnKeyPress(const KeyPressEvent& e)					{ }
		virtual void Event_OnKeyRelease(const KeyReleaseEvent& e)				{ }
		virtual void Event_OnKeyType(const KeyTypeEvent& e)						{ }
	};

}