#include "chpch.h"
#include "DX11RendererAPI.h"

#include "DX11Internal.h"

#include "Chernobyl/Core/Application.h"

#include <d3dcompiler.h>

namespace CH
{

	void DX11RendererAPI::SetClearColor(const float3& color)
	{
		m_ClearColor = color;
	}
	
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	void DX11RendererAPI::Clear()
	{
		// TEMPORARY CODE TO DRAW TRIANGLE

		ComPtr<ID3D11Buffer> pVertexBuffer;

		float vertices[]
		{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.0f,  0.5f
		};

		// vertex buffer creation

		D3D11_BUFFER_DESC buffDesc = {};
		buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buffDesc.ByteWidth = sizeof(vertices);
		buffDesc.CPUAccessFlags = 0;
		buffDesc.MiscFlags = 0;
		buffDesc.StructureByteStride = sizeof(float) * 2;
		buffDesc.Usage = D3D11_USAGE_DEFAULT;
		
		D3D11_SUBRESOURCE_DATA sbd = {};
		sbd.pSysMem = vertices;

		DXInternal::GetDevice()->CreateBuffer(&buffDesc, &sbd, &pVertexBuffer);

		uint32 stride = sizeof(float) * 2;
		uint32 offset = 0;

		DXInternal::GetDeviceContext()->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);

		// shaders

		ComPtr<ID3D11VertexShader> pVertexShader;
		ComPtr<ID3D11PixelShader>  pPixelShader;

		ComPtr<ID3DBlob> pVSBlob;
		ComPtr<ID3DBlob> pPSBlob;
		ComPtr<ID3DBlob> pErrBlob;

		const char* vertexSrc = R"(
		float4 main(float2 position)
		{
			return float4(position, 0, 1);
		})";

		const char* fragmentSrc = R"(
		float4 main() : SV_TARGET
		{
			return float4(1.0, 0, 0, 1.0);
		})";

		HRESULT hr;
		hr = D3DCompile(vertexSrc, sizeof(vertexSrc), nullptr, nullptr, nullptr, "main", "vs_4_0", D3DCOMPILE_DEBUG, 0, &pVSBlob, &pErrBlob);
		if (FAILED(hr))
		{
			const char* errMsg = (char*)pErrBlob->GetBufferPointer();
			CH_CORE_ASSERT(false, errMsg);
		}

		hr = D3DCompile(fragmentSrc, sizeof(fragmentSrc), nullptr, nullptr, nullptr, "main", "ps_4_0", D3DCOMPILE_DEBUG, 0, &pPSBlob, &pErrBlob);
		if (FAILED(hr))
		{
			const char* errMsg = (char*)pErrBlob->GetBufferPointer();
			CH_CORE_ASSERT(false, errMsg);
		}

		DXInternal::GetDevice()->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &pVertexShader);
		DXInternal::GetDevice()->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &pPixelShader);
		
		DXInternal::GetDeviceContext()->VSSetShader(pVertexShader.Get(), nullptr, 0);
		DXInternal::GetDeviceContext()->PSSetShader(pPixelShader.Get() , nullptr, 0);

		ComPtr<ID3D11InputLayout> pInputLayout;
		D3D11_INPUT_ELEMENT_DESC ieds[]
		{
			{ "Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		DXInternal::GetDevice()->CreateInputLayout(ieds, 1, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &pInputLayout);
		DXInternal::GetDeviceContext()->IASetInputLayout(pInputLayout.Get());

		// END TEMPORARY CODE

		int width = Application::Get()->GetWindow()->GetWidth();
		int height = Application::Get()->GetWindow()->GetHeight();

		D3D11_VIEWPORT vp = {};
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.MinDepth = 0;
		vp.MaxDepth = 1;
		vp.Width = width;
		vp.Height = height;

		DXInternal::GetDeviceContext()->RSSetViewports(1, &vp);

		float clearColor[4]{ m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 0 };

		DXInternal::GetDeviceContext()->OMSetRenderTargets(1, DXInternal::GetRTVAsComptr().GetAddressOf(), nullptr);
		DXInternal::GetDeviceContext()->ClearRenderTargetView(DXInternal::GetRTV(), clearColor);

		// DRAWING CODE

		DXInternal::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DXInternal::GetDeviceContext()->Draw(3, 0);

		// END DRAWING CODE
	}

}