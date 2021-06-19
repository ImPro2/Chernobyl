#include "chpch.h"
#include "Renderer.h"

namespace CH {

	void Renderer::Init()
	{
		OnResize();
	}

	void Renderer::OnResize()
	{
		float2 size = float2(Application::Get()->GetWindow()->GetWidth(), Application::Get()->GetWindow()->GetHeight());
		RenderCommand::SetViewport(size);
		Application::Get()->GetWindow()->GetContext()->Resize(size);
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vb)
	{
		shader->Bind();
		vb->Bind();

		RenderCommand::Draw(vb);
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vb, const std::shared_ptr<IndexBuffer>& ib)
	{
		shader->Bind();
		vb->Bind();
		ib->Bind();

		RenderCommand::Draw(vb, ib);
	}

	void Renderer::EndScene()
	{
	}

}