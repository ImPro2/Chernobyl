#pragma once

#include "Chernobyl/Renderer/ShaderBuffer.h"
#include "DX11Internal.h"

namespace CH {

	class DX11ShaderBuffer : public ShaderBuffer
	{
	public:
		DX11ShaderBuffer(Size size);

		void SetData(void* data, Size size, ShaderType type, uint32 slot) override;
		void Bind() override;
		
	private:
		ComPtr<ID3D11Buffer> m_ConstantBuffer;
	};

}