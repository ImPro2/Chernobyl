#include "chpch.h"
#include "Renderer.h"

namespace CH {


	Renderer::SceneData Renderer::s_SceneData;

	struct ShaderData
	{
		glm::mat4 ViewProj;
		glm::mat4 Transform;
	};
	
	void Renderer::Init()
	{
		OnResize();

		s_SceneData.SysShaderBuffer = ShaderBuffer::Create(sizeof(ShaderData));
	}

	void Renderer::OnResize()
	{
		float2 size = float2(Application::Get()->GetWindow()->GetWidth(), Application::Get()->GetWindow()->GetHeight());
		RenderCommand::SetViewport(size);
		Application::Get()->GetWindow()->GetContext()->Resize(size);
	}

	void Renderer::BeginScene(const glm::mat4& viewProjMat)
	{
		s_SceneData.ViewProjectionMatrix = viewProjMat;
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<Pipeline>& pipeline, const glm::mat4& transform)
	{
		shader->Bind();
		pipeline->Bind();

		ShaderData data;
		data.ViewProj = s_SceneData.ViewProjectionMatrix;
		data.Transform = transform;

		s_SceneData.SysShaderBuffer->SetData(&data, sizeof(ShaderData), ShaderType::Vertex, 1);

		RenderCommand::Draw(pipeline->GetVertexBuffer(), pipeline->GetIndexBuffer());
	}

	void Renderer::EndScene()
	{
	}

}