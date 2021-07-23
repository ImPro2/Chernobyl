#pragma once

#include <sstream>

#include "Event.hpp"

#include "Core/StartupArgs.hpp"
#include "Core/ExitCode.hpp"

namespace CH
{

	struct AppCreateEvent : public Event
	{
		static EventType GetStaticType() { return EventType::AppCreate; }

		AppCreateEvent(const ApplicationStartupArguments& args)
			: Event(EventType::AppCreate), AppStartupArgs(args)
		{
		}

		ApplicationStartupArguments AppStartupArgs;

		// overridden methods

		const String& ToString() override
		{
			std::ostringstream oss;
			oss << "[Event]: {(Brief: App Created), (Type: AppCreate), (Category: App)}:" << "\n"
				<< "Argument Count: " << AppStartupArgs.ArgCount << "\n"
				<< "Arguments: " << AppStartupArgs.Arguments;

			mToStrBuffer = oss.str();
			return mToStrBuffer;
		}
	};

	struct AppDestroyEvent : public Event
	{
		static EventType GetStaticType() { return EventType::AppDestroy; }

		AppDestroyEvent(ExitCode code)
			: Event(EventType::AppDestroy), ReturnCode(code)
		{
		}

		ExitCode ReturnCode;

		// overridden methods

		const String& ToString() override
		{
			std::ostringstream oss;
			oss << "[Event]: {(Brief: App Destroyed), (Type: AppDestroy), (Category: App)}:" << "\n"
				<< "Return Code: " << (int32)ReturnCode;

			mToStrBuffer = oss.str();
			return mToStrBuffer;
		}
	};

	struct AppUpdateEvent : public Event
	{
		static EventType GetStaticType() { return EventType::AppUpdate; }
	
		AppUpdateEvent()
			: Event(EventType::AppUpdate)
		{
		}

		// overridden methods

		const String& ToString() override
		{
			std::ostringstream oss;
			oss << "[Event]: {(Brief: App Updated), (Type: AppUpdate), (Category: App)}:";

			mToStrBuffer = oss.str();
			return mToStrBuffer;
		}
	};

	struct AppRenderEvent : public Event
	{
		static EventType GetStaticType() { return EventType::AppRender; }

		AppRenderEvent()
			: Event(EventType::AppRender)
		{
		}

		// overridden methods

		const String& ToString() override
		{
			std::ostringstream oss;
			oss << "[Event]: {(Brief: App Rendered), (Type: AppRender), (Category: App)}:";

			mToStrBuffer = oss.str();
			return mToStrBuffer;
		}
	};

}