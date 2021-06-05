#include "RenderCommand.h"

#ifdef CH_PLATFORM_WINDOWS
#include "Chernobyl/Platform/DX11/DX11RendererAPI.h"
#endif

namespace CH
{

#ifdef CH_PLATFORM_WINDOWS
	RendererAPI* RenderCommand::s_API = new DX11RendererAPI();
#endif

}