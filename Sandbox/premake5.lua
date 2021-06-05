project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    disablewarnings { warnings }

    files
    {
        "src/**.h",
        "src/**.cpp"
    }
    
    includedirs
    {
        "../ExternalLibs/spdlog/include",
        "../Chernobyl/src",
        "../ExternalLibs/imgui",
        "../ExternalLibs/Glad/include",
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