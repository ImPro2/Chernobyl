#include "chpch.h"
#include "DX11Buffer.h"

namespace CH {

	DX11VertexBuffer::DX11VertexBuffer(void* vertices, int32 vertexCount, int32 size, int32 vertexSize)
		: VertexBuffer(vertexCount, size, vertexSize)
	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = size;
		desc.StructureByteStride = vertexSize;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA sbd = {};
		sbd.pSysMem = vertices;

		CH_ASSERT(SUCCEEDED(DXInternal::GetDevice()->CreateBuffer(&desc, &sbd, &m_VertexBuffer)), "Failed to create vertex buffer!");

		Bind();
	}

	void DX11VertexBuffer::Bind()
	{
		UINT stride = m_VertexSize;
		UINT offset = 0;

		DXInternal::GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

		m_Binded = true;
	}

	DX11IndexBuffer::DX11IndexBuffer(u16* indices, int32 count, int32 size)
		: IndexBuffer(count, size)
	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(u16) * count;
		desc.StructureByteStride = sizeof(u16);
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA sbd = {};
		sbd.pSysMem = indices;

		CH_ASSERT(SUCCEEDED(DXInternal::GetDevice()->CreateBuffer(&desc, &sbd, &m_IndexBuffer)), "Failed to create index buffer!");

		Bind();
	}

	void DX11IndexBuffer::Bind()
	{
		DXInternal::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

		m_Binded = true;
	}

}