#include "chpch.h"
#include "DX11RendererAPI.h"

#include "DX11Internal.h"

#include "Chernobyl/Core/Application.h"
#include "Chernobyl/Renderer/Renderer.h"
#include "Chernobyl/Renderer/Buffer.h"
#include "Chernobyl/Renderer/Shader.h"
#include "Chernobyl/Renderer/Pipeline.h"
#include "DX11Shader.h"
#include <d3dcompiler.h>

#include <fstream>

namespace CH
{

	namespace Utils
	{
		String DrawModeToStr(DrawMode mode)
		{
			switch (mode)
			{
				case DrawMode::Point:			return "Point";
				case DrawMode::LineList:		return "LineList";
				case DrawMode::LineStrip:		return "LineStrip";
				case DrawMode::LineIndex:		return "LineIndex";
				case DrawMode::TriangleList:	return "TriangleList";
				case DrawMode::TriangleStrip:	return "TriangleStrip";
				case DrawMode::TriangleIndex:	return "TriangleIndex";
			}

			return "None";
		}

		D3D_PRIMITIVE_TOPOLOGY DrawModeToPrimitiveTopology(DrawMode mode)
		{
			switch (mode)
			{
				case DrawMode::Point:			return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
				case DrawMode::LineList:		return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
				case DrawMode::LineStrip:		return D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
				case DrawMode::LineIndex:		return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
				case DrawMode::TriangleList:	return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
				case DrawMode::TriangleStrip:	return D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
				case DrawMode::TriangleIndex:	return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			}

			return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
		}
	}

	void DX11RendererAPI::SetClearColor(const float3& color)
	{
		m_ClearColor = color;
	}
	
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	void DX11RendererAPI::Clear()
	{
		float clearColor[4]{ m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 0 };

		DXInternal::SetRenderTargets();
		DXInternal::GetDeviceContext()->ClearRenderTargetView(DXInternal::GetRTV(), clearColor);

		/*

		// TEMPORARY CODE TO DRAW TRIANGLE

		// vertices + indices

		struct Vertex
		{
			float x;
			float y;
			float r;
			float g;
			float b;
		};
		
		Vertex vertices[] =
		{
			{ 0.0f,0.5f,1.0f,0.0f,0.0f },
			{ 0.5f,-0.5f,0.0f,1.0f,0.0f },
			{ -0.5f,-0.5f,0.0f,0.0f,1.0f },
		};

		u16 indices[] = { 0, 1, 2 };

		// vertex + index buffers

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, 3, sizeof(vertices), sizeof(Vertex));
		Ref<IndexBuffer>  indexBuffer =  IndexBuffer::Create( indices,  3, sizeof(indices));

		vertexBuffer->SetLayout({
			BufferElement("Position", ShaderDataType::Float2, false),
			BufferElement("Color",    ShaderDataType::Float3, false)
		});

		// shaders

		Ref<Shader> shader = Shader::Create("C:/Users/User/Documents/dev/LearnRenderAPIs/Chernobyl/Chernobyl/assets/BasicShader.hlsl", Shader::Load::Path);
		
		// pipeline

		Ref<Pipeline> pipeline = Pipeline::Create();
		pipeline->AddVertexBuffer(vertexBuffer, shader);

		DXInternal::SetRenderTargets();

		// draw

		Renderer::BeginScene();
		{
			RenderCommand::SetDrawMode(DrawMode::TriangleIndex);
			Renderer::Submit(shader, vertexBuffer, indexBuffer);
		}
		Renderer::EndScene();

		// END TEMPORARY CODE

		*/
	}

	void DX11RendererAPI::SetViewport(const float2& size)
	{
		D3D11_VIEWPORT vp;
		vp.Width = size.x;
		vp.Height = size.y;
		vp.MinDepth = 0;
		vp.MaxDepth = 1;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		DXInternal::GetDeviceContext()->RSSetViewports(1, &vp);
	}

	void DX11RendererAPI::SetMode(DrawMode mode)
	{
		m_DrawMode = mode;
		DXInternal::GetDeviceContext()->IASetPrimitiveTopology(Utils::DrawModeToPrimitiveTopology(mode));
	}

	void DX11RendererAPI::Draw(const std::shared_ptr<VertexBuffer>& vb, const std::shared_ptr<IndexBuffer>& ib)
	{
		switch (m_DrawMode)
		{
			case DrawMode::Point:			DXInternal::GetDeviceContext()->Draw(        vb->GetVertexCount(),  0       );	return;
			case DrawMode::LineList:		DXInternal::GetDeviceContext()->Draw(        vb->GetVertexCount(),  0       );	return;
			case DrawMode::LineStrip:		DXInternal::GetDeviceContext()->Draw(        vb->GetVertexCount(),  0       );	return;
			case DrawMode::LineIndex:		DXInternal::GetDeviceContext()->DrawIndexed( ib->GetCount(),        0, NULL );	return;
			case DrawMode::TriangleList:	DXInternal::GetDeviceContext()->Draw(        vb->GetVertexCount(),  0       );	return;
			case DrawMode::TriangleStrip:	DXInternal::GetDeviceContext()->Draw(        vb->GetVertexCount(),  0       );	return;
			case DrawMode::TriangleIndex:	DXInternal::GetDeviceContext()->DrawIndexed( ib->GetCount(),        0, NULL );	return;
		}

		CH_CORE_WARN("DrawMode::{0} not currently supported", Utils::DrawModeToStr(m_DrawMode));
	}

}