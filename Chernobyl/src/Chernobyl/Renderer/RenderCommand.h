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

	private:
		static RendererAPI* s_API;
	};

}