#include "chpch.h"
#include "DX11Texture.h"

#include "stb_image.h"

namespace CH
{

	DX11Texture2D::DX11Texture2D(const String& path)
		: Texture2D(path)
	{
		// flip the file vertically if needed (some texture formats like PNG would be upside down otherwise)

		String fileExtension = path.substr(path.find_last_of('.'));

		if (fileExtension == ".png")
			stbi_set_flip_vertically_on_load(1);

		// load file

		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		CH_CORE_ASSERT(data != nullptr, "Invalid file path!");

		// set members

		m_Width = width;
		m_Height = height;

		// set subresource data

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = data;
		initData.SysMemPitch = 4 * m_Width;
		initData.SysMemSlicePitch = m_Width * m_Height * 4;

		D3D11_SUBRESOURCE_DATA* pInitData = nullptr;
		pInitData = &initData;

		// create texture
		
		D3D11_TEXTURE2D_DESC texDesc = {};
		texDesc.Width = width;
		texDesc.Height = height;
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.CPUAccessFlags = 0;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texDesc.MiscFlags = 0;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		
		
		HRESULT hr = DXInternal::GetDevice()->CreateTexture2D(&texDesc, pInitData, &m_Texture);
		CH_CORE_ASSERT(SUCCEEDED(hr), "Failed to create texture 2D!");
		
		// create view

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = texDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;

		hr = DXInternal::GetDevice()->CreateShaderResourceView(m_Texture.Get(), &srvDesc, &m_ShaderResourceView);
		CH_CORE_ASSERT(SUCCEEDED(hr), "Failed to create shader resource view!");
		
		// create sampler

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		
		hr = DXInternal::GetDevice()->CreateSamplerState(&samplerDesc, &m_Sampler);
		CH_CORE_ASSERT(SUCCEEDED(hr), "Failed to create sampler state!");

		stbi_image_free(data);
	}

	void DX11Texture2D::Bind()
	{
		DXInternal::GetDeviceContext()->PSSetSamplers(m_Slot, 1, m_Sampler.GetAddressOf());
		DXInternal::GetDeviceContext()->PSSetShaderResources(m_Slot, 1, m_ShaderResourceView.GetAddressOf());
		m_Binded = true;
	}

}