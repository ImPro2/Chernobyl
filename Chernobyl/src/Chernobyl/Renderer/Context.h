#pragma once

#include "Chernobyl/Core/Core.h"

namespace CH
{

	class Context
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers(bool vsync) = 0;
		virtual void Resize(const float2& size) = 0;

		static std::unique_ptr<Context> Create(void* windowHandle);
	};

}