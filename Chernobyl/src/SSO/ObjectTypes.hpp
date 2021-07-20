#pragma once

#include "SystemTypes.hpp"

namespace CH
{

	enum class ObjectType
	{
		Unknown,

		// Window system
		Window,

		// Input system

		

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
			case ObjectType::VertexBuffer:	return "VertexBuffer";
			case ObjectType::IndexBuffer:	return "IndexBuffer";
			case ObjectType::VertexArray:	return "VertexArray";
			case ObjectType::Pipeline:		return "Pipeline";
			case ObjectType::ShaderBuffer:	return "ShaderBuffer";
		}

		return "";
	}

	//constexpr ObjectType StrToObjectType(const char* str)
	//{
	//	switch (type)
	//	{
	//		case "Window":			return ObjectType::Window;
	//		case "VertexBuffer":	return ObjectType::VertexBuffer;
	//		case "IndexBuffer":		return ObjectType::IndexBuffer;
	//		case "VertexArray":		return ObjectType::VertexArray;
	//		case "Pipeline":		return ObjectType::Pipeline;
	//		case "ShaderBuffer":	return ObjectType::ShaderBuffer;
	//	}
	//
	//	return ObjectType::Unknown;
	//}

	constexpr SystemType SystemTypeOfObjectType(ObjectType type)
	{
		switch (type)
		{
			case ObjectType::Window:		return SystemType::Window;
			case ObjectType::VertexBuffer:	return SystemType::Renderer;
			case ObjectType::IndexBuffer:	return SystemType::Renderer;
			case ObjectType::VertexArray:	return SystemType::Renderer;
			case ObjectType::Pipeline:		return SystemType::Renderer;
			case ObjectType::ShaderBuffer:	return SystemType::Renderer;
		}

		return SystemType::Unknown;
	}

}