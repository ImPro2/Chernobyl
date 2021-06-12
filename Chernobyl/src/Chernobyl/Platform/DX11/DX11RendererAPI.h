#pragma once

#include "Chernobyl/Renderer/RendererAPI.h"

namespace CH
{

	class DX11RendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const float3& color) override;
		void Clear() override;

	private:
		float3 m_ClearColor;
	};

}