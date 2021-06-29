#pragma once

#include "Chernobyl/Renderer/Texture.h"
#include "DX11Internal.h"

namespace CH
{

	class DX11Texture2D : public Texture2D
	{
	public:
		DX11Texture2D(const String& path);

		void Bind() override;

	private:
		ComPtr<ID3D11Texture2D> m_Texture;
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
		ComPtr<ID3D11SamplerState> m_Sampler;
	};

}