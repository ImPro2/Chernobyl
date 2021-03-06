#include "chpch.h"
#include "Shader.h"
#include "ShaderBuffer.h"

#if CH_RENDERER_API CH_DIRECT3D
#include "Chernobyl/Platform/DX11/DX11Shader.h"
#endif

namespace CH {

	Ref<Shader> Shader::Create(const String& str, ShaderLoadMode mode)
	{
#if CH_RENDERER_API CH_DIRECT3D
		std::shared_ptr<Shader> shader = std::make_shared<DX11Shader>(str, mode);
		RendererVault::Submit(shader);
		return shader;
#endif
	}

}