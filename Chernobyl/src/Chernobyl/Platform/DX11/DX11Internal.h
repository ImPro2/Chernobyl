#pragma once

#include <d3d11.h>
#include <Windows.h>

#include <wrl.h>

#include "Chernobyl/Core/Core.h"

namespace CH
{

	namespace DXInternal {

		void Init(HWND handle);

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