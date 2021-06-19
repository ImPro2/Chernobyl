#include "chpch.h"
#include "Pipeline.h"

#if CH_RENDERER_API CH_DIRECT3D
#include "Chernobyl/Platform/DX11/DX11Pipeline.h"
#endif

namespace CH {

	Ref<Pipeline> Pipeline::Create()
	{
		return CreateRef<DX11Pipeline>();
	}

	Pipeline::Pipeline()
	{

	}

}