#include "chpch.h"
#include "ShaderBuffer.h"

#if CH_RENDERER_API CH_DIRECT3D
#include "Chernobyl/Platform/DX11/DX11ShaderBuffer.h"
#endif

namespace CH {



	Ref<ShaderBuffer> ShaderBuffer::Create(Size size)
	{
#if CH_RENDERER_API CH_DIRECT3D
		return CreateRef<DX11ShaderBuffer>(size);
#endif
	}

}