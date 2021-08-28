----------
--------------------------------------------------------------------------------------
--  Sandbox Project
--------------------------------------------------------------------------------------

project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    -- Output

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    -- Warnings

    disablewarnings { warnings }

    -- PCH

    pchheader "sandboxpch.hpp"
    pchsource "src/sandboxpch.cpp"

    -- Files

    files
    {
        "src/**.hpp",
        "src/**.cpp"
    }
    
    -- IncludeDirs

    includedirs
    {
        "src",
        "..\\Chernobyl\\src",

        -- I'm going to use these dependencies in the project

        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.fmt}"
    }

    -- Links

    links
    {
        "Chernobyl"
    }

    -- Platforms the engine is able to buid on

    filter "system:windows"
        systemversion "latest"
        
        defines
        {
            "CH_PLATFORM_WINDOWS"
        }

    -- Configurations

    filter "configurations:Dev"
        defines "CH_DEV"
        runtime "Debug"
        symbols "On"

    filter "configurations:Test"
        defines "CH_TEST"
        runtime "Release"
        optimize "On"
    
    filter "configurations:Dist"
        defines "CH_DIST"
        runtime "Release"
        optimize "On"

--------------------------------------------------------------------------------------
---------