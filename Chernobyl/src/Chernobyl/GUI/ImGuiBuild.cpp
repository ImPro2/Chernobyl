#include "chpch.h"

#ifdef CH_PLATFORM_WINDOWS
#include "backends/imgui_impl_win32.cpp"
#endif

#if CH_RENDERER_API CH_DIRECT3D
#include "backends/imgui_impl_dx11.cpp"
#endif