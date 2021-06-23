#pragma once
#include "chpch.h"
#include "ShaderTypes.h"

namespace CH {

	uint32 ShaderDataTypeToSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return sizeof(float);
		case ShaderDataType::Float2:	return sizeof(float2);
		case ShaderDataType::Float3:	return sizeof(float3);
		case ShaderDataType::Float4:	return sizeof(float4);
		case ShaderDataType::Int:		return sizeof(int32);
		case ShaderDataType::Int2:		return sizeof(int2);
		case ShaderDataType::Int3:		return sizeof(int3);
		case ShaderDataType::Int4:		return sizeof(int4);
		case ShaderDataType::Bool:		return sizeof(bool);
		case ShaderDataType::Mat3:		return sizeof(float3) * 3;
		case ShaderDataType::Mat4:		return sizeof(float4) * 4;
		}

		CH_CORE_WARN("Unknown shader data type");
		return 0;
	}

}