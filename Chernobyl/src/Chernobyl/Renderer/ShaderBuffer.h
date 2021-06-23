#pragma once

// like uniforms in opengl and constant buffers in dx11, just changed the name a little ;)

#include "RenderingResource.h"
#include "ShaderTypes.h"

namespace CH {

	class ShaderBuffer : public RenderingResource
	{
	public:
		static Ref<ShaderBuffer> Create(Size size);

		virtual void SetData(void* data, Size size, ShaderType shaderType, uint32 slot = 0) = 0;
	};

}