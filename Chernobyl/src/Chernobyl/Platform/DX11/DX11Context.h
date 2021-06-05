#pragma once

#include "Chernobyl/Renderer/Context.h"

namespace CH
{

	class DX11Context : public Context
	{
	public:
		DX11Context(void* handle);

		void Init() override;
		void SwapBuffers(bool vsync) override;

	private:
		HWND m_WindowHandle;
	};

}