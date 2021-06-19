#pragma once

#include "Chernobyl/Core/Core.h"
#include "Buffer.h"

#include <glm/glm.hpp>

namespace CH
{
	enum class DrawMode
	{
		None = -1,

		Point			=     0 ,

		LineList		= BIT(1),
		LineStrip		= BIT(2),
		LineIndex		= BIT(3),

		TriangleList	= BIT(4),
		TriangleStrip	= BIT(5),
		TriangleIndex	= BIT(6)
	};

	class RendererAPI
	{
	public:

		virtual void SetClearColor(const float3& color) = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(const float2& size) = 0;
		virtual void Draw(const std::shared_ptr<VertexBuffer>& vb, const std::shared_ptr<IndexBuffer>& ib) = 0;
		virtual void SetMode(DrawMode mode) = 0;

	protected:
		DrawMode m_DrawMode = DrawMode::None;
	};

}