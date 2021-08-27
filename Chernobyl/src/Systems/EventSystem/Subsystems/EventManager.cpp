#include "chpch.hpp"
#include "EventManager.hpp"

namespace CH
{

	EventManager* EventManager::Create()
	{
		CH_PROFILE_FUNCTION();

		return new EventManager();
	}

	void EventManager::Subscribe(IEventListener* listener)
	{
		CH_PROFILE_FUNCTION();

		mEventListeners.push_back(listener);
	}

	void EventManager::Subscribe(EventCallbackFn fn)
	{
		CH_PROFILE_FUNCTION();

		mEventCallbacks.push_back(fn);
	}

#define CH_HANDLE_EVENT(type, var)\
	while (!mEventBus.var.empty())\
	{\
		type e = mEventBus.var.front();\
		mEventBus.var.pop();\
		BroadcastEvent(e);\
	}

	void EventManager::HandleEvents()
	{
		CH_PROFILE_FUNCTION();

		CH_HANDLE_EVENT(AppCreateEvent,    AppCreateEvents);
		CH_HANDLE_EVENT(AppDestroyEvent,   AppDestroyEvents);
		CH_HANDLE_EVENT(AppUpdateEvent,    AppUpdateEvents);
		CH_HANDLE_EVENT(AppRenderEvent,    AppRenderEvents);

		CH_HANDLE_EVENT(WindowCreateEvent, WindowCreateEvents);
		CH_HANDLE_EVENT(WindowCloseEvent,  WindowCloseEvents);
		CH_HANDLE_EVENT(WindowMoveEvent,   WindowMoveEvents);
		CH_HANDLE_EVENT(WindowResizeEvent, WindowResizeEvents);

		CH_HANDLE_EVENT(MouseClickEvent,   MouseClickEvents);
		CH_HANDLE_EVENT(MouseReleaseEvent, MouseReleaseEvents);
		CH_HANDLE_EVENT(MouseMoveEvent,    MouseMoveEvents);
		CH_HANDLE_EVENT(MouseScrollEvent,  MouseScrollEvents);

		CH_HANDLE_EVENT(KeyPressEvent,     KeyPressEvents);
		CH_HANDLE_EVENT(KeyReleaseEvent,   KeyReleaseEvents);
		CH_HANDLE_EVENT(KeyTypeEvent,      KeyTypeEvents);
	}

#	define CALL_EVENTLISTENER_METHOD(type, method)\
	{\
		type e = static_cast<type>(e);\
		listener->method(e);\
		break;\
	}

	template<class T>
	void EventManager::BroadcastEvent(T e)
	{
		CH_PROFILE_FUNCTION();

		for (IEventListener* listener : mEventListeners)
		{
			switch (e.GetType())
			{
				switch (e.GetType())
				{
					case EventType::AppCreate:
					{
						AppCreateEvent e = static_cast<AppCreateEvent>(e);
						listener->Event_OnAppCreate(e);

						break;
					}
					case EventType::AppDestroy:   CALL_EVENTLISTENER_METHOD(AppDestroyEvent,   Event_OnAppDestroy);
					case EventType::AppUpdate:    CALL_EVENTLISTENER_METHOD(AppUpdateEvent,    Event_OnAppUpdate);
					case EventType::AppRender:    CALL_EVENTLISTENER_METHOD(AppRenderEvent,    Event_OnAppRender);

					case EventType::WindowCreate: CALL_EVENTLISTENER_METHOD(WindowCreateEvent, Event_OnWindowCreate);
					case EventType::WindowClose:  CALL_EVENTLISTENER_METHOD(WindowCloseEvent,  Event_OnWindowClose);
					case EventType::WindowResize: CALL_EVENTLISTENER_METHOD(WindowResizeEvent, Event_OnWindowResize);
					case EventType::WindowMove:	  CALL_EVENTLISTENER_METHOD(WindowMoveEvent,   Event_OnWindowMove);

					case EventType::MouseClick:   CALL_EVENTLISTENER_METHOD(MouseClickEvent,   Event_OnMouseClick);
					case EventType::MouseRelease: CALL_EVENTLISTENER_METHOD(MouseReleaseEvent, Event_OnMouseRelease);
					case EventType::MouseMove:    CALL_EVENTLISTENER_METHOD(MouseMoveEvent,    Event_OnMouseMove);
					case EventType::MouseScroll:  CALL_EVENTLISTENER_METHOD(MouseScrollEvent,  Event_OnMouseScroll);

					case EventType::KeyPress:     CALL_EVENTLISTENER_METHOD(KeyPressEvent,     Event_OnKeyPress);
					case EventType::KeyRelease:   CALL_EVENTLISTENER_METHOD(KeyReleaseEvent,   Event_OnKeyRelease);
					case EventType::KeyType:      CALL_EVENTLISTENER_METHOD(KeyTypeEvent,      Event_OnKeyType);
				}
			}
		}

		for (EventCallbackFn fn : mEventCallbacks)
		{
			fn(static_cast<Event&>(e));
		}

		//for (IEventListener* listener : mEventListeners)
		//{
		//	listener->Event_OnEvent(static_cast<Event>(e));
		//
		//	switch (e.GetType())
		//	{
		//		case EventType::AppCreate:      listener->Event_OnAppCreate(   static_cast<AppCreateEvent>(e));     break;
		//		case EventType::AppDestroy:     listener->Event_OnAppDestroy(  static_cast<AppDestroyEvent>(e));     break;
		//		case EventType::AppUpdate:      listener->Event_OnAppUpdate(   static_cast<AppUpdateEvent>(e));     break;
		//		case EventType::AppRender:      listener->Event_OnAppRender(   static_cast<AppRenderEvent>(e));     break;
		//
		//		case EventType::WindowCreate:   listener->Event_OnWindowCreate(static_cast<WindowCreateEvent>(e));     break;
		//		case EventType::WindowClose:    listener->Event_OnWindowClose( static_cast<WindowCloseEvent>(e));     break;
		//		case EventType::WindowResize:   listener->Event_OnWindowResize(static_cast<WindowResizeEvent>(e));     break;
		//		case EventType::WindowMove:	    listener->Event_OnWindowMove(  static_cast<WindowMoveEvent>(e));     break;
		//
		//		case EventType::MouseClick:     listener->Event_OnMouseClick(  static_cast<MouseClickEvent>(e));     break;
		//		case EventType::MouseRelease:   listener->Event_OnMouseRelease(static_cast<MouseReleaseEvent>(e));     break;
		//		case EventType::MouseMove:      listener->Event_OnMouseMove(   static_cast<MouseMoveEvent>(e));     break;
		//		case EventType::MouseScroll:    listener->Event_OnMouseScroll( static_cast<MouseScrollEvent>(e));     break;
		//
		//		case EventType::KeyPress:		listener->Event_OnKeyPress(    static_cast<KeyPressEvent>(e));     break;
		//		case EventType::KeyRelease:		listener->Event_OnKeyRelease(  static_cast<KeyReleaseEvent>(e));     break;
		//		case EventType::KeyType:		listener->Event_OnKeyType(     static_cast<KeyTypeEvent>(e));     break;
		//	}
		//}
		//
		//for (EventCallbackFn fn : mEventCallbacks)
		//{
		//	fn(static_cast<Event>(e));
		//}
	}

}