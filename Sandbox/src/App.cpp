#define CH_API_ENTRY 1
#include "Chernobyl.h"
#include "sandboxpch.h"

#include "imgui.h"

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
			CH::float3 col;
		};

		Vertex vertices[]
		{
			{ CH::float2( 0.0f,  0.5f), CH::float3(1, 0, 0) },
			{ CH::float2( 0.5f, -0.5f), CH::float3(0, 1, 0) },
			{ CH::float2(-0.5f, -0.5f), CH::float3(0, 0, 1) }
		}; 

		CH::u16 indices[] = { 0, 1, 2 };

		m_VB = CH::VertexBuffer::Create(vertices, 3, sizeof(vertices), sizeof(Vertex));
		m_IB = CH::IndexBuffer::Create(indices, 3, sizeof(indices));

		m_VB->SetLayout({
			CH::BufferElement("Position", CH::ShaderDataType::Float2, false),
			CH::BufferElement("Color",    CH::ShaderDataType::Float3, false)
		});

		m_Shader = CH::Shader::Create("../Chernobyl/assets/BasicShader.hlsl", CH::Shader::Load::Path);

		m_Pipeline = CH::Pipeline::Create();
		m_Pipeline->AddVertexBuffer(m_VB, m_Shader);
	}

	void OnUpdate() override
	{
		CH::RenderCommand::SetClearColor(m_ClearColor);
		CH::RenderCommand::Clear();
		
		if (CH::Input::IsKeyPressed('S'))
			CH::Application::Get()->Exit(CH::ExitCode::Success);

		m_Pipeline->Bind();

		CH::Renderer::BeginScene();
		{
			CH::RenderCommand::SetDrawMode(CH::DrawMode::TriangleIndex);
			CH::Renderer::Submit(m_Shader, m_VB, m_IB);
		}
		CH::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Stats");

		float fps = CH::Time::GetTimestep();
		
		ImGui::Text("Timestep: %fs ",     CH::Time::GetTimestep());
		ImGui::Text("Timestep: %fms",     CH::Time::GetDeltaTime().AsMilliSeconds());
		ImGui::Text("Timestep: %fmicros", CH::Time::GetDeltaTime().AsMicroSeconds());
		ImGui::Text("Timestep: %fns",     CH::Time::GetDeltaTime().AsNanoSeconds());
		ImGui::Text("FPS: %f", CH::Time::GetFrameTime());
		ImGui::End();

		ImGui::Begin("Debug");
		ImGui::ColorEdit3("Clear Color", &m_ClearColor.x, ImGuiColorEditFlags_PickerHueWheel/* | ImGuiColorEditFlags_Float*/);
		ImGui::End();
	}

private:
	CH::float3 m_ClearColor;
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