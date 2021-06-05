#include "DX11RendererAPI.h"

#include "DX11Internal.h"

#include "Chernobyl/Core/Application.h"

namespace CH
{

	void DX11RendererAPI::SetClearColor(const glm::vec3& color)
	{
		m_ClearColor = color;
	}

	void DX11RendererAPI::Clear()
	{
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
	}

}