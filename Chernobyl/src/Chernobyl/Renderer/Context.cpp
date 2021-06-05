#include "Context.h"

#ifdef CH_PLATFORM_WINDOWS
#include "Chernobyl/Platform/DX11/DX11Context.h"
#endif

namespace CH
{

	std::unique_ptr<Context> Context::Create(void* windowHandle)
	{
#ifdef CH_PLATFORM_WINDOWS
		return std::make_unique<DX11Context>(windowHandle);
#endif
	}

}