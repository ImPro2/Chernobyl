#pragma once

#include "Event.hpp"

namespace CH
{

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e)
			: mEvent(e)
		{
		}

		template<typename T, typename F>
		void Dispatch(const F& fn)
		{
			if (mEvent.GetType() == T::GetStaticType())
			{
				fn(static_cast<T&>(mEvent));
			}
		}

	private:
		Event& mEvent;
	};

}

#define CH_BIND_EVENT_FN(fn) [this](auto&& ... args) -> decltype(auto) { this->fn(std::forward<decltype(args)>(args)...); }
#define CH_DISPATCH_EVENT_FN(type, fn) dispatcher.Dispatch<type>(CH_BIND_EVENT_FN(fn));