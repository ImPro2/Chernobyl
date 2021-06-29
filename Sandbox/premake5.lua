project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    disablewarnings { warnings }

    pchheader "sandboxpch.h"
    pchsource "src/sandboxpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }
    
    includedirs
    {
        "%{IncludeDir.spdlog}",
        "../Chernobyl/src",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Chernobyl"
    }

    filter "system:windows"
        systemversion "latest"
        
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