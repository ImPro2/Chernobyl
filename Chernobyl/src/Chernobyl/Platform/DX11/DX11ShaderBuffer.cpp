#include "chpch.h"
#include "DX11ShaderBuffer.h"

namespace CH {

#define MINIMUM_CONSTANT_BUFFER_SIZE 16

	DX11ShaderBuffer::DX11ShaderBuffer(Size size)
	{
		if (size < MINIMUM_CONSTANT_BUFFER_SIZE)
			size = MINIMUM_CONSTANT_BUFFER_SIZE;

		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = size;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		
		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = new uint8[desc.ByteWidth];

		DXInternal::GetDevice()->CreateBuffer(&desc, &data, &m_ConstantBuffer);
	}

	void DX11ShaderBuffer::SetData(void* data, Size size, ShaderType type, uint32 slot)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		DXInternal::GetDeviceContext()->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		memcpy(msr.pData, data, size);
		DXInternal::GetDeviceContext()->Unmap(m_ConstantBuffer.Get(), 0);

		switch (type)
		{
			case ShaderType::Vertex:	DXInternal::GetDeviceContext()->VSSetConstantBuffers(slot, 1, m_ConstantBuffer.GetAddressOf());	break;
			case ShaderType::Pixel:		DXInternal::GetDeviceContext()->PSSetConstantBuffers(slot, 1, m_ConstantBuffer.GetAddressOf());	break;
			default:					CH_CORE_WARN("Unknown shader type!");
		}

		Bind();
	}

	void DX11ShaderBuffer::Bind()
	{
		m_Binded = true;
	}

}