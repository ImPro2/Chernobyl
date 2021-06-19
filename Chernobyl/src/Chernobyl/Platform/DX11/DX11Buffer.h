#pragma once
#include "Chernobyl/Core/Core.h"
#include "Chernobyl/Renderer/Buffer.h"

#include "DX11Internal.h"

namespace CH {

	class DX11VertexBuffer : public VertexBuffer
	{
	public:
		DX11VertexBuffer(void* vertices, int32 vertexCount, int32 size, int32 vertexSize);
		void Bind() override;

	private:
		ComPtr<ID3D11Buffer> m_VertexBuffer;
	};

	class DX11IndexBuffer : public IndexBuffer
	{
	public:
		DX11IndexBuffer(u16* indices, int32 count, int32 size);
		void Bind() override;

	private:
		ComPtr<ID3D11Buffer> m_IndexBuffer;
	};

}