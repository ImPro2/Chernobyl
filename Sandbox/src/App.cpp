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
		  m_ClearColor({ 0.1f, 0.1f, 0.1f }), m_Camera(-1.366f, 1.366f, -0.768f, 0.768f)
	{
	}

	void OnAttach() override
	{
		// shaders

		m_Shader = CH::Shader::Create("../Chernobyl/assets/shaders/BasicShader.hlsl", CH::ShaderLoadMode::Path);
		m_Shader->SetBuffer(sizeof(m_ShaderBufferData));
		m_Shader->GetBuffer()->SetData(&m_ShaderBufferData, sizeof(m_ShaderBufferData), CH::ShaderType::Pixel);

		m_TexShader = CH::Shader::Create("../Chernobyl/assets/shaders/TextureShader.hlsl", CH::ShaderLoadMode::Path);

		// data

		struct Vertex
		{
			CH::float2 pos;
			CH::float2 texcoord;
		};

		//Vertex vertices[]
		//{
		//	{ CH::float2(-0.5f,  0.5f), CH::float2(0, 0) },
		//	{ CH::float2( 0.5f,  0.5f), CH::float2(1, 0) },
		//	{ CH::float2( 0.5f, -0.5f), CH::float2(1, 1) },
		//	{ CH::float2(-0.5f, -0.5f), CH::float2(0, 1) }
		//}; 

		float vertices[]
		{
			-0.5f,  0.5f,	0.0f, 0.0f,
			 0.5f,  0.5f,	1.0f, 0.0f,
			 0.5f, -0.5f,	1.0f, 1.0f,
			-0.5f, -0.5f,	0.0f, 1.0f
		};

		CH::u16 indices[] = { 0, 1, 2,
							  2, 3, 0 };
		
		// buffers

		m_Pipeline = CH::Pipeline::Create();

		CH::Ref<CH::VertexBuffer> vb = CH::VertexBuffer::Create(vertices, CHCountOf(vertices), sizeof(vertices), sizeof(Vertex));
		CH::Ref<CH::IndexBuffer> ib = CH::IndexBuffer::Create( indices,  CHCountOf(indices ), sizeof(indices));
		
		vb->SetLayout({
			CH::BufferElement("POSITION", CH::ShaderDataType::Float2, false),
			CH::BufferElement("TEXCOORD", CH::ShaderDataType::Float2, false)
		});
		
		m_Pipeline->SetVertexBuffer(vb, m_Shader);
		m_Pipeline->SetIndexBuffer(ib);

		// texture

		m_Texture2D = CH::Texture2D::Create("../Resources/Branding/Logo.png");
		m_Texture2D->SetSlot(0);
}

	void OnUpdate() override
	{
		// clear screen

		CH::RenderCommand::SetClearColor(m_ClearColor);
		CH::RenderCommand::Clear();

		// local variables

		static CH::float2 campos;
		static float rotation;
		static float camrot = 0;
		float speed = 1;

		// input

		if (CH::Input::IsKeyPressed('A'))
			campos.x -= speed * CH::Time::GetTimestep();
		if (CH::Input::IsKeyPressed('W'))
			campos.y += speed * CH::Time::GetTimestep();
		if (CH::Input::IsKeyPressed('S'))
			campos.y -= speed * CH::Time::GetTimestep();
		if (CH::Input::IsKeyPressed('D'))
			campos.x += speed * CH::Time::GetTimestep();

		if (CH::Input::IsKeyPressed('E'))
			rotation++;

		// update

		m_Camera.SetPosition(campos);
		m_Camera.SetRotation(camrot);
		
		m_Shader->GetBuffer()->SetData(&m_ShaderBufferData, sizeof(m_ShaderBufferData), CH::ShaderType::Pixel);
		
		// maths

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2));

		// render

		CH::Renderer::BeginScene(m_Camera);
		{
			CH::RenderCommand::SetDrawMode(CH::DrawMode::TriangleIndex);

			m_Texture2D->SetSlot(0);
			m_Texture2D->Bind();
			CH::Renderer::Submit(m_TexShader, m_Pipeline, transform);
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

	CH::OrthographicCamera m_Camera;

	CH::Ref<CH::Shader> m_Shader, m_TexShader;
	CH::Ref<CH::Texture2D> m_Texture2D;
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