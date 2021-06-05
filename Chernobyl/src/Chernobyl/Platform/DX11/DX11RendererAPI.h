#pragma once

#include "Chernobyl/Renderer/RendererAPI.h"

namespace CH
{

	class DX11RendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const glm::vec3& color) override;
		void Clear() override;

	private:
		glm::vec3 m_ClearColor;
	};

}