#pragma once

#include "SystemTypes.hpp"

namespace CH
{

	enum class ObjectType
	{
		Unknown,

		// Window system
		Window,

		// Event system

		EventListener,

		// Renderer system

		VertexBuffer,
		IndexBuffer,
		VertexArray,
		Pipeline,
		ShaderBuffer

		// Physics system



		// Audio system



	};

	constexpr const char* ObjectTypeToStr(ObjectType type)
	{
		switch (type)
		{
			case ObjectType::Window:		return "Window";
			case ObjectType::EventListener:	return "EventListener";
			case ObjectType::VertexBuffer:	return "VertexBuffer";
			case ObjectType::IndexBuffer:	return "IndexBuffer";
			case ObjectType::VertexArray:	return "VertexArray";
			case ObjectType::Pipeline:		return "Pipeline";
			case ObjectType::ShaderBuffer:	return "ShaderBuffer";
		}
		
		return "";
	}

	constexpr SystemType SystemTypeOfObjectType(ObjectType type)
	{
		switch (type)
		{
			case ObjectType::Window:		return SystemType::Window;
			case ObjectType::EventListener:	return SystemType::Event;
			case ObjectType::VertexBuffer:	return SystemType::Renderer;
			case ObjectType::IndexBuffer:	return SystemType::Renderer;
			case ObjectType::VertexArray:	return SystemType::Renderer;
			case ObjectType::Pipeline:		return SystemType::Renderer;
			case ObjectType::ShaderBuffer:	return SystemType::Renderer;
		}

		return SystemType::Unknown;
	}

}