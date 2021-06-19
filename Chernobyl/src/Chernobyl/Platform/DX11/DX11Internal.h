#pragma once

#include <d3d11.h>
#include <Windows.h>

#include <wrl.h>

#include "Chernobyl/Core/Core.h"

namespace CH
{

	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	namespace DXInternal {

		void Init(HWND handle);
		void Resize(const float2& size);
		void SetRenderTargets();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		IDXGISwapChain* GetSwapChain();
		ID3D11RenderTargetView* GetRTV();

		Microsoft::WRL::ComPtr<ID3D11Device>				GetDeviceAsComptr();
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>			GetDeviceContextAsComptr();
		Microsoft::WRL::ComPtr<IDXGISwapChain>				GetSwapChainAsComptr();
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		GetRTVAsComptr();
	}

}