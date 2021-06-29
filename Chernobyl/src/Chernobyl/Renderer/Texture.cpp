#include "chpch.h"
#include "Texture.h"

#ifdef CH_RENDERER_API CH_DIRECT3D
#include "Chernobyl/Platform/DX11/DX11Texture.h"
#endif

namespace CH
{

	Ref<Texture2D> Texture2D::Create(const String& path)
	{
#ifdef CH_RENDERER_API CH_DIRECT3D
		return CreateRef<DX11Texture2D>(path);
#endif
	}

	Texture2D::Texture2D(const String& path)
		: m_Path(path)
	{
	}

}