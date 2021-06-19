#pragma once

#include "RenderingResource.h"
#include "Buffer.h"
#include "Shader.h"

#include "RenderCommand.h"
#include "RendererAPISwitch.h"

#include "Chernobyl/Core/Application.h"

namespace CH {

	class Renderer
	{
	public:
		static void Init();
		static void OnResize();
		
		static void BeginScene(/*const Ref<OrthographicCamera2D>& camera*/);
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vb);
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vb, const std::shared_ptr<IndexBuffer>& ib);
		static void EndScene();
	};

}