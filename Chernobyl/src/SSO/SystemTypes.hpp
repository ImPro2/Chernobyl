#pragma once

namespace CH
{

	enum class SystemType
	{
		Unknown = -1,
		Window = 0,
		Event = 1,
		Renderer = 2,
		Physics = 3,
		Audio = 4
	};

	constexpr const char* SystemTypeToStr(SystemType type)
	{
		switch (type)
		{
			case SystemType::Window:	return "Window";
			case SystemType::Event:		return "Event";
			case SystemType::Renderer:	return "Renderer";
			case SystemType::Physics:	return "Physics";
			case SystemType::Audio:		return "Audio";
		}

		CH_CORE_LOG(LogSeverity::Info, "Unknown system type");

		return "";
	}

	//constexpr const char* StrToSystemType(SystemType type)
	//{
	//	switch (type)
	//	{
	//		case "Window":		return SystemType::Window;
	//		case "Input":		return SystemType::Input;
	//		case "Renderer":	return SystemType::Renderer;
	//		case "Physics":		return SystemType::Physics;
	//		case "Audio":		return SystemType::Audio;
	//	}
	//
	//	CH_CORE_LOG(LogSeverity::Info, "Unknown system type");
	//
	//	return SystemType::Unknown;
	//}

}