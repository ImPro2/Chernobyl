#include "chpch.h"
#include "DX11Context.h"
#include "DX11Internal.h"
#include "Chernobyl/Renderer/RenderCommand.h"

namespace CH
{

	DX11Context::DX11Context(void* handle)
		: m_WindowHandle(static_cast<HWND>(handle))
	{
		CH_ASSERT(m_WindowHandle != nullptr, "Invalid window handle!");
	}

	void DX11Context::Init()
	{
		DXInternal::Init(m_WindowHandle);
	}

	void DX11Context::SwapBuffers(bool vsync)
	{
		DXInternal::GetSwapChain()->Present((vsync ? 1 : 0), NULL);
	}

	void DX11Context::Resize(const float2& size)
	{
		DXInternal::Resize(size);
	}

}