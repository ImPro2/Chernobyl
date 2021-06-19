#include "chpch.h"
#include "Buffer.h"
#include "RendererAPISwitch.h"
#include "RenderingResource.h"

#if CH_RENDERER_API CH_DIRECT3D
#include "Chernobyl/Platform/DX11/DX11Buffer.h"
#endif

namespace CH {

	Ref<VertexBuffer> VertexBuffer::Create(void* vertices, int32 vertexCount, int32 size, int32 vertexSize)
	{
#if CH_RENDERER_API CH_DIRECT3D
		std::shared_ptr<VertexBuffer> buffer =  std::make_shared<DX11VertexBuffer>(vertices, vertexCount, size, vertexSize);
		RendererVault::Submit(buffer);
		return buffer;
#endif
	}

	VertexBuffer::VertexBuffer(int32 vertexCount, int32 size, int32 vertexSize)
		: m_VertexCount(vertexCount), m_Size(size), m_VertexSize(vertexSize)
	{
	}

	Ref<IndexBuffer> IndexBuffer::Create(u16* indices, int32 count, int32 size)
	{
#if CH_RENDERER_API CH_DIRECT3D
		return std::make_shared<DX11IndexBuffer>(indices, count, size);
#endif
	}

	IndexBuffer::IndexBuffer(int32 count, int32 size)
		: m_Count(count), m_Size(size)
	{
	}

}