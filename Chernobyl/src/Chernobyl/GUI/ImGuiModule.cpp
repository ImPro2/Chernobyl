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

		io.Fonts->AddFontFromFileTTF("../Chernobyl/assets/fonts/opensans/OpenSans-Bold.ttf", 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("../Chernobyl/assets/fonts/opensans/OpenSans-Bold.ttf", 18.0f);

		SetDarkThemeColors();
		//SetLightThemeColors();

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
		io.DisplaySize = ImVec2(Application::Get()->GetWindow()->GetWidth(), Application::Get()->GetWindow()->GetHeight());

		ImGui::Render();

#if CH_RENDERER_API CH_DIRECT3D
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif

#ifdef CH_PLATFORM_WINDOWS
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			HWND hWnd = (HWND)Application::Get()->GetWindow()->GetHandle();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			Application::Get()->GetWindow()->SetHandle(hWnd);
		}
#endif
	}

	void ImGuiModule::SetDarkThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg]           = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };
									        
		// Headers					        
		colors[ImGuiCol_Header]             = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered]      = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive]       = ImVec4{ 1.0f, 0.256f, 0.000f, 1.0f };
									        
		// Buttons					        
		colors[ImGuiCol_Button]             = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered]      = ImVec4{ 1.0f, 0.256f, 0.000f, 1.0f };
		colors[ImGuiCol_ButtonActive]       = ImVec4{ 1.0f, 0.256f, 0.000f, 1.0f };
									        
		// Frame BG					        
		colors[ImGuiCol_FrameBg]            = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered]     = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive]      = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
										    
		// Tabs							    
		colors[ImGuiCol_Tab]                = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered]         = ImVec4{ 1.0f, 0.403f, 0.186f, 1.0f };
		colors[ImGuiCol_TabActive]          = ImVec4{ 1.0f, 0.256f, 0.000f, 1.0f };
		colors[ImGuiCol_TabUnfocused]       = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// 1.0f, 0.403f, 0.186f, 1.0f
		// 1.0f, 0.256f, 0.000f, 1.0f

		// Title
		colors[ImGuiCol_TitleBg]            = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive]      = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed]   = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
										    
		colors[ImGuiCol_DockingPreview]     = ImVec4{ 1.0f, 0.403f, 0.186f, 1.0f };
										    
		colors[ImGuiCol_ResizeGrip]         = ImVec4{ 1.0f, 0.403f, 0.186f, 1.0f };
		colors[ImGuiCol_ResizeGripHovered]  = ImVec4{ 1.0f, 0.403f, 0.186f, 1.0f };
		colors[ImGuiCol_ResizeGripActive]   = ImVec4{ 1.0f, 0.256f, 0.000f, 1.0f };
		colors[ImGuiCol_Border]             = ImVec4{ 1.0f, 0.403f, 0.186f, 1.0f };
		colors[ImGuiCol_BorderShadow]       = ImVec4{ 1.0f, 0.403f, 0.186f, 1.0f };
										    
		colors[ImGuiCol_SliderGrab]         = ImVec4{ 1.0f, 0.403f, 0.186f, 1.0f };
		colors[ImGuiCol_SliderGrabActive]   = ImVec4{ 1.0f, 0.256f, 0.000f, 1.0f };
	}

	void ImGuiModule::SetLightThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.9f, 0.895f, 0.89f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.8f, 0.795f, 0.79f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.7f, 0.695f, 0.69f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.85f, 0.8595f, 0.859f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.8f, 0.795f, 0.79f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.7f, 0.695f, 0.69f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.85f, 0.8595f, 0.859f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.8f, 0.795f, 0.79f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.7f, 0.895f, 0.69f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.85f, 0.8595f, 0.859f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.85f, 0.8595f, 0.859f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.62f, 0.6195f, 0.619f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.72f, 0.7195f, 0.719f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.85f, 0.8495f, 0.849f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.8f, 0.795f, 0.79f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.85f, 0.8495f, 0.849f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.85f, 0.8495f, 0.849f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.85f, 0.8495f, 0.859f, 1.0f };

		colors[ImGuiCol_Text] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };
	}

}