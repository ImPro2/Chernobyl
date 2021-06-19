#pragma once

#include "RendererAPI.h"


namespace CH
{

	class RenderCommand
	{
	public:
		inline static void SetClearColor(const float3& color)
		{
			s_API->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_API->Clear();
		}

		inline static void SetViewport(const float2& size)
		{
			s_API->SetViewport(size);
		}

		inline static void SetDrawMode(DrawMode mode)
		{
			s_API->SetMode(mode);
		}

		inline static void Draw(const std::shared_ptr<VertexBuffer>& vb, const std::shared_ptr<IndexBuffer>& ib = nullptr)
		{
			s_API->Draw(vb, ib);
		}

	private:
		static RendererAPI* s_API;
	};

}