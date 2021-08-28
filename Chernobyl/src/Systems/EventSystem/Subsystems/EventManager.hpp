#pragma once

#include <queue>

#include "SSO/SSO.hpp"
#include "Systems/EventSystem/Data/Events.hpp"
#include "Systems/EventSystem/Objects/EventListener.hpp"
#include "Core/Types/Types.hpp"

namespace CH
{

	struct EventBus
	{
		std::queue<AppCreateEvent>      AppCreateEvents;
		std::queue<AppDestroyEvent>     AppDestroyEvents;
		std::queue<AppUpdateEvent>      AppUpdateEvents;
		std::queue<AppRenderEvent>      AppRenderEvents;
		
		std::queue<WindowCreateEvent>   WindowCreateEvents;
		std::queue<WindowCloseEvent>    WindowCloseEvents;
		std::queue<WindowMoveEvent>     WindowMoveEvents;
		std::queue<WindowResizeEvent>   WindowResizeEvents;

		std::queue<MouseClickEvent>     MouseClickEvents;
		std::queue<MouseReleaseEvent>   MouseReleaseEvents;
		std::queue<MouseMoveEvent>      MouseMoveEvents;
		std::queue<MouseScrollEvent>    MouseScrollEvents;
		
		std::queue<KeyPressEvent>       KeyPressEvents;
		std::queue<KeyReleaseEvent>     KeyReleaseEvents;
		std::queue<KeyTypeEvent>        KeyTypeEvents;

	};

	class EventManager : public ISubsystem
	{
	public:
		static SubsystemType GetStaticType() { return SubsystemType::EventManager; }
		static EventManager* Create();

	public:

		
		//////////////////
		//////////////////////////////////////////////////////////
		// Add events
		//////////////////////////////////////////////////////////

		template<typename T>
		void AddEvent(T e)
		{
			static_assert(false);
		}
		template<>
		void AddEvent<AppCreateEvent>(AppCreateEvent e)
		{
			mEventBus.AppCreateEvents.push(e);
		}
		template<>
		void AddEvent<AppDestroyEvent>(AppDestroyEvent e)
		{
			mEventBus.AppDestroyEvents.push(e);
		}
		template<>
		void AddEvent<AppUpdateEvent>(AppUpdateEvent e)
		{
			mEventBus.AppUpdateEvents.push(e);
		}
		template<>
		void AddEvent<AppRenderEvent>(AppRenderEvent e)
		{
			mEventBus.AppRenderEvents.push(e);
		}
		template<>
		void AddEvent<WindowCreateEvent>(WindowCreateEvent e)
		{
			mEventBus.WindowCreateEvents.push(e);
		}
		template<>
		void AddEvent<WindowCloseEvent>(WindowCloseEvent e)
		{
			mEventBus.WindowCloseEvents.push(e);
		}
		template<>
		void AddEvent<WindowMoveEvent>(WindowMoveEvent e)
		{
			mEventBus.WindowMoveEvents.push(e);
		}
		template<>
		void AddEvent<WindowResizeEvent>(WindowResizeEvent e)
		{
			mEventBus.WindowResizeEvents.push(e);
		}
		template<>
		void AddEvent<MouseClickEvent>(MouseClickEvent e)
		{
			mEventBus.MouseClickEvents.push(e);
		}
		template<>
		void AddEvent<MouseReleaseEvent>(MouseReleaseEvent e)
		{
			mEventBus.MouseReleaseEvents.push(e);
		}
		template<>
		void AddEvent<MouseMoveEvent>(MouseMoveEvent e)
		{
			mEventBus.MouseMoveEvents.push(e);
		}
		template<>
		void AddEvent<MouseScrollEvent>(MouseScrollEvent e)
		{
			mEventBus.MouseScrollEvents.push(e);
		}
		template<>
		void AddEvent<KeyPressEvent>(KeyPressEvent e)
		{
			mEventBus.KeyPressEvents.push(e);
		}
		template<>
		void AddEvent<KeyReleaseEvent>(KeyReleaseEvent e)
		{
			mEventBus.KeyReleaseEvents.push(e);
		}
		template<>
		void AddEvent<KeyTypeEvent>(KeyTypeEvent e)
		{
			mEventBus.KeyTypeEvents.push(e);
		}

		//////////////////////////////////////////////////////////
		//////////////////


		void Subscribe(IEventListener* listener);		// class that can be subscribed
		void Subscribe(EventCallbackFn fn);				// callback that can be subscribed
		
		void HandleEvents();							// calls all event callbacks

		template<class T>
		void BroadcastEvent(T e);

	private:
		EventBus mEventBus;
		Vector<IEventListener*> mEventListeners;
		Vector<EventCallbackFn> mEventCallbacks;
	};

}