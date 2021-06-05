#define CH_API_ENTRY
#include "Chernobyl.h"

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
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Stats");
		ImGui::Text("Timestep: %fms, FPS: %fs", CH::Time::GetDeltaTime().AsMilliSeconds(), CH::Time::GetFrameTime());
		ImGui::End();
	}
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