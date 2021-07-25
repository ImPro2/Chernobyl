#pragma once

namespace CH
{

	enum class SystemType
	{
		Unknown = -1,
		Window = 0,
		Event = 1,
		Input = 2,
		Time = 3,
		Renderer = 4,
		Physics = 5,
		Audio = 6
	};

#define CH_SYSTEM_TYPE_LAST 4

	constexpr const char* SystemTypeToStr(SystemType type)
	{
		switch (type)
		{
			case SystemType::Window:	return "Window";
			case SystemType::Event:		return "Event";
			case SystemType::Input:		return "Input";
			case SystemType::Time:		return "Time";
			case SystemType::Renderer:	return "Renderer";
			case SystemType::Physics:	return "Physics";
			case SystemType::Audio:		return "Audio";
		}

		CH_CORE_LOG(LogSeverity::Info, "Unknown system type");

		return "";
	}

}