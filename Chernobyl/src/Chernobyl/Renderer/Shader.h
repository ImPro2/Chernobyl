#pragma once

#include "Chernobyl/Core/Core.h"
#include "RenderingResource.h"
#include "RendererAPISwitch.h"

namespace CH {
	
	namespace ShaderDataType
	{
		enum : u16
		{
			None       = 0,
			Float      = 1,
			Float2 = BIT(1),
			Float3 = BIT(2),
			Float4 = BIT(3),
			Int    = BIT(4),
			Int2   = BIT(5),
			Int3   = BIT(6),
			Int4   = BIT(7),
			Bool   = BIT(8),
			Mat3   = BIT(9),
			Mat4   = BIT(10)
		};
	}

	class Shader : public RenderingResource
	{
	public:
		enum class Load
		{
			Source,
			Path
		};

		enum class Type
		{
			Vertex,
			Pixel,
			Fragment = Pixel
		};		

		struct ParseResult
		{
			String VertexSrc;
			String PixelSrc;
		};

		using DataType = u16;

		static uint32 DataTypeToSize(DataType type)
		{
			switch (type)
			{
				case ShaderDataType::Float:		return sizeof(float);
				case ShaderDataType::Float2:	return sizeof(float2);
				case ShaderDataType::Float3:	return sizeof(float3);
				case ShaderDataType::Float4:	return sizeof(float4);
				case ShaderDataType::Int:		return sizeof(int32);
				case ShaderDataType::Int2:		return sizeof(vec2<int32>);
				case ShaderDataType::Int3:		return sizeof(vec3<int32>);
				case ShaderDataType::Int4:		return sizeof(vec4<int32>);
				case ShaderDataType::Bool:		return sizeof(bool);
				case ShaderDataType::Mat3:		return sizeof(float3) * 3;
				case ShaderDataType::Mat4:		return sizeof(float4) * 4;
			}

			CH_CORE_WARN("Unknown shader data type");
			return 0;
		}
		
		static Ref<Shader> Create(const String& str, Load mode);
	};

	
}