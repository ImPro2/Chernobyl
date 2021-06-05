#pragma once

#include "Chernobyl/Core/Core.h"

#include <glm/glm.hpp>

namespace CH
{

	class RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec3& color) = 0;
		virtual void Clear() = 0;
	};

}