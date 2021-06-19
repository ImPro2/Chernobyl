#pragma once

#include "Chernobyl/Renderer/RendererAPI.h"

namespace CH
{

	class DX11RendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const float3& color) override;
		void Clear() override;
		void SetViewport(const float2& size) override;
		void SetMode(DrawMode mode) override;
		void Draw(const std::shared_ptr<VertexBuffer>& vb, const std::shared_ptr<IndexBuffer>& ib) override;

	private:
		float3 m_ClearColor;
	};

}