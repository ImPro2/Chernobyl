#include "chpch.h"
#include "RenderCommand.h"

#ifdef CH_PLATFORM_WINDOWS
#include "Chernobyl/Platform/DX11/DX11RendererAPI.h"
#endif

namespace CH
{

#if CH_RENDERER_API CH_DIRECT3D
	RendererAPI* RenderCommand::s_API = new DX11RendererAPI();
#endif

}