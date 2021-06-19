#include "chpch.h"
#include "DX11Internal.h"

namespace CH
{

	namespace DXInternal {

		static ComPtr<ID3D11Device> pDevice;
		static ComPtr<ID3D11DeviceContext> pContext;
		static ComPtr<IDXGISwapChain> pSwapChain;

		static ComPtr<ID3D11RenderTargetView> pRTV;

		ID3D11Device* GetDevice() { return pDevice.Get(); }
		ID3D11DeviceContext* GetDeviceContext() { return pContext.Get(); }
		IDXGISwapChain* GetSwapChain() { return pSwapChain.Get(); }
		ID3D11RenderTargetView* GetRTV() { return pRTV.Get(); }

		Microsoft::WRL::ComPtr<ID3D11Device>				GetDeviceAsComptr() { return pDevice; }
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>			GetDeviceContextAsComptr() { return pContext; }
		Microsoft::WRL::ComPtr<IDXGISwapChain>				GetSwapChainAsComptr() { return pSwapChain; }
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		GetRTVAsComptr() { return pRTV; }

		void Init(HWND handle)
		{
			DXGI_SWAP_CHAIN_DESC sd = {};
			// set it to zero so that d3d can set it itself
			sd.BufferDesc.Width = 0;
			sd.BufferDesc.Height = 0;

			sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;

			// set to zero so that d3d can set it itself
			sd.BufferDesc.RefreshRate.Numerator = 0;
			sd.BufferDesc.RefreshRate.Denominator = 0;

			sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;

			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.BufferCount = 1;

			sd.OutputWindow = handle;
			sd.Windowed = TRUE;

			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			sd.Flags = 0;

			uint32_t createFlags = 0;
#ifdef _DEBUG
			createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

			HRESULT hr;

			if (FAILED(D3D11CreateDeviceAndSwapChain(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				createFlags,
				nullptr,
				0,
				D3D11_SDK_VERSION,
				&sd,
				&pSwapChain,
				&pDevice,
				nullptr,
				&pContext
			)))
				CH_ASSERT(false, "Failed to initialize d3d11");

			ComPtr<ID3D11Resource> pBackBuffer = nullptr;
			hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
			CH_ASSERT(SUCCEEDED(hr), "Failed to get back buffer");
			hr = pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pRTV);
			CH_ASSERT(SUCCEEDED(hr), "Failed to create rtv");

			DXInternal::SetRenderTargets();
		}

		void Resize(const float2& size)
		{
			pRTV.ReleaseAndGetAddressOf();
			
			pSwapChain->ResizeBuffers(1, size.x, size.y, DXGI_FORMAT_B8G8R8A8_UNORM, 0);
			
			ComPtr<ID3D11Texture2D> pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pRTV);
			
			DXInternal::SetRenderTargets();
		}

		void SetRenderTargets()
		{
			pContext->OMSetRenderTargets(1, pRTV.GetAddressOf(), /*pDPS*/nullptr);
		}
	}


}