#define CH_API_ENTRY 1
#include "Chernobyl.h"
#include "sandboxpch.h"

#include "imgui.h"

class ModuleTest : public CH::Module
{
public:
	ModuleTest() : Module("TestModule") {}

	void OnAttach() override
	{
	}

	void OnUpdate() override
	{
		if (CH::Input::IsKeyPressed('S'))
			CH::Application::Get()->Exit(CH::ExitCode::Success);

		CH::RenderCommand::SetClearColor(m_ClearColor);
		CH::RenderCommand::Clear();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Stats");

		float fps = CH::Time::GetTimestep();

		ImGui::Columns(2);
		ImGui::NextColumn();
		ImGui::SetColumnWidth(0, 130.0f);
		ImGui::PlotLines("##FPS", &fps, 1);
		ImGui::Columns(1);
		
		ImGui::Text("Timestep (s):      %fs ",     CH::Time::GetTimestep());
		ImGui::Text("Timestep (ms):     %fms",     CH::Time::GetDeltaTime().AsMilliSeconds());
		ImGui::Text("Timestep (micros): %fmicros", CH::Time::GetDeltaTime().AsMicroSeconds());
		ImGui::Text("Timestep (ns):     %fns",     CH::Time::GetDeltaTime().AsNanoSeconds());
		ImGui::Text("Frames Per Second (FPS): %f", CH::Time::GetFrameTime());
		ImGui::End();

		ImGui::Begin("Debug");
		ImGui::ColorEdit3("Clear Color", &m_ClearColor.x, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_Float);
		ImGui::End();
	}

private:
	CH::float3 m_ClearColor;
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