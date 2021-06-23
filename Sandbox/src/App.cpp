#define CH_API_ENTRY 1
#include "Chernobyl.h"
#include "sandboxpch.h"

#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

struct ShaderBuffer
{
	CH::float4 col;
};

class ModuleTest : public CH::Module
{
public:
	ModuleTest()
		: Module("TestModule"),
		  m_ClearColor({ 0.1f, 0.1f, 0.1f })
	{
	}

	void OnAttach() override
	{
		struct Vertex
		{
			CH::float2 pos;
		};

		Vertex vertices[]
		{
			{ CH::float2(-0.5f,  0.5f) },
			{ CH::float2( 0.5f,  0.5f) },
			{ CH::float2( 0.5f, -0.5f) },
			{ CH::float2(-0.5f, -0.5f) }
		}; 

		CH::u16 indices[] = { 0, 1, 2,
							  2, 3, 0 };

		m_VB = CH::VertexBuffer::Create(vertices, CHCountOf(vertices), sizeof(vertices), sizeof(Vertex));
		m_IB = CH::IndexBuffer::Create( indices,  CHCountOf(indices ), sizeof(indices));

		m_VB->SetLayout({
			CH::BufferElement("Position", CH::ShaderDataType::Float2, false)
		});

		m_Shader = CH::Shader::Create("../Chernobyl/assets/BasicShader.hlsl", CH::ShaderLoadMode::Path);
		m_Shader->SetBuffer(sizeof(m_ShaderBufferData));
		m_Shader->GetBuffer()->SetData(&m_ShaderBufferData, sizeof(m_ShaderBufferData), CH::ShaderType::Pixel);

		m_Pipeline = CH::Pipeline::Create();
		m_Pipeline->SetVertexBuffer(m_VB, m_Shader);
		m_Pipeline->SetIndexBuffer(m_IB);
	}

	void OnUpdate() override
	{
		CH::RenderCommand::SetClearColor(m_ClearColor);
		CH::RenderCommand::Clear();

		m_Pipeline->Bind();

		CH::int2 size = CH::int2(CH::Application::Get()->GetWindow()->GetWidth(), CH::Application::Get()->GetWindow()->GetHeight());

		static glm::vec3 pos;

		if (CH::Input::IsKeyPressed('A'))
			pos.x -= 0.01f;
		if (CH::Input::IsKeyPressed('W'))
			pos.y += 0.01f;
		if (CH::Input::IsKeyPressed('S'))
			pos.y -= 0.01f;
		if (CH::Input::IsKeyPressed('D'))
			pos.x += 0.01f;

		glm::mat4 proj = glm::ortho(-1.6f, 1.6f, -0.9f, 0.9f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2));

		m_Shader->GetBuffer()->SetData(&m_ShaderBufferData, sizeof(m_ShaderBufferData), CH::ShaderType::Pixel);

		CH::Renderer::BeginScene(view * proj);
		{
			CH::RenderCommand::SetDrawMode(CH::DrawMode::TriangleIndex);
			CH::Renderer::Submit(m_Shader, m_Pipeline, model);
		}
		CH::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Stats");
		
		static float updateFPS = 0.5f;

		ImGui::Text("Timestep: %fs ",     CH::Time::GetTimestep());
		ImGui::Text("Timestep: %fms",     CH::Time::GetDeltaTime().AsMilliSeconds());
		ImGui::Text("Timestep: %fmicros", CH::Time::GetDeltaTime().AsMicroSeconds());
		ImGui::Text("Timestep: %fns",     CH::Time::GetDeltaTime().AsNanoSeconds());
		
		static float fps;
		if (m_Timer.ElapsedSeconds() >= updateFPS)
		{
			m_Timer.Reset();
			fps = CH::Time::GetFrameTime(); 
		}
		ImGui::Text("FPS: %f", fps);
		
		ImGui::End();


		ImGui::Begin("Debug");
		ImGui::ColorEdit3("Clear Color", &m_ClearColor.x, ImGuiColorEditFlags_PickerHueWheel/* | ImGuiColorEditFlags_Float*/);
		ImGui::ColorEdit3("Triangle Color", &m_ShaderBufferData.col.r, ImGuiColorEditFlags_PickerHueWheel);
		ImGui::SliderFloat("Update FPS", &updateFPS, 0, 5);
		ImGui::End();
	}

private:
	CH::float3 m_ClearColor;
	CH::Timer m_Timer;
	ShaderBuffer m_ShaderBufferData;

	CH::Ref<CH::VertexBuffer> m_VB;
	CH::Ref<CH::IndexBuffer> m_IB;
	CH::Ref<CH::Shader> m_Shader;
	CH::Ref<CH::Pipeline> m_Pipeline;

};

class SandboxApp : public CH::Application
{
public:
	SandboxApp()
	{
		CH::ModuleStack::Push(new ModuleTest());
	}

	~SandboxApp()
	{
	}
};

CH::Application* CreateApplication()
{
	return new SandboxApp();
}