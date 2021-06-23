#pragma once

#include "Chernobyl/Core/Core.h"

namespace CH
{

	enum class ShaderLoadMode
	{
		Source,
		Path
	};

	enum class ShaderType
	{
		Vertex,
		Pixel,
		Fragment = Pixel
	};

	struct ShaderParseResult
	{
		String VertexSrc;
		String PixelSrc;
	};

	enum class ShaderDataType
	{
		None   =     0,
		Float  =     1,
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
	
	uint32 ShaderDataTypeToSize(ShaderDataType type);

}