#include "chpch.h"
#include "ImGuiModule.h"

#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"

#include "Chernobyl/Core/Application.h"

#include <d3d11.h>
#include <wrl.h>

#ifdef CH_PLATFORM_WINDOWS
#include "Chernobyl/Platform/DX11/DX11Internal.h"
#endif

namespace CH
{

	ImGuiModule::ImGuiModule()
		: Module("ImGuiModule")
	{
	}

	ImGuiModule::~ImGuiModule()
	{
	}

	void ImGuiModule::OnAttach()
	{
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

#ifdef CH_PLATFORM_WINDOWS
		ImGui_ImplDX11_Init(DXInternal::GetDevice(), DXInternal::GetDeviceContext());
#endif

#if CH_RENDERER_API CH_DIRECT3D
		ImGui_ImplWin32_Init(Application::Get()->GetWindow()->GetHandle());
#endif
	}

	void ImGuiModule::OnEvent(Event& e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategory_Mouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategory_Keyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiModule::BeginFrame()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(Application::Get()->GetWindow()->GetWidth(), Application::Get()->GetWindow()->GetHeight());

#if CH_RENDERER_API CH_DIRECT3D
		ImGui_ImplDX11_NewFrame();
#endif
		
#ifdef CH_PLATFORM_WINDOWS
		ImGui_ImplWin32_NewFrame();
#endif

		ImGui::NewFrame();
	}

	void ImGuiModule::EndFrame()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Render();

#if CH_RENDERER_API CH_DIRECT3D
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif

#ifdef CH_PLATFORM_WINDOWS
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
#endif
	}

}