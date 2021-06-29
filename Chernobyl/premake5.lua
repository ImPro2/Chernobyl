project "Chernobyl"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    disablewarnings { warnings }

    pchheader "chpch.h"
    pchsource "src/chpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }
    
    includedirs
    {
	    "src",
        "%{IncludeDir.spdlog}",
	    "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "HeaderOnlyDependencies"
    }

    filter "system:windows"
        systemversion "latest"

        links
        {
            "d3d11.lib",
            "D3DCompiler.lib"
        }

        defines
        {
            "CH_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "CH_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "CH_RELEASE"
        runtime "Release"
        optimize "On"
    
    filter "configurations:Dist"
        defines "CH_DIST"
        runtime "Release"
        optimize "On"