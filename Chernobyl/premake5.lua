----------
----------------------------------------------------------------
-- Chernobyl Project
----------------------------------------------------------------

project "Chernobyl"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    -- Output

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    -- Warnings

    disablewarnings { warnings }

    -- PCH

    pchheader "chpch.hpp"
    pchsource "src/chpch.cpp"

    -- Files

    files
    {
        -- Engine

        "src/**.hpp",
        "src/**.cpp",

        -- Header-Only Dependencies

        "%{Directory.Dependencies/glm/glm/**.hpp",
        "%{Directory.Dependencies/glm/glm/**.inl",

        "%{Directory.Dependencies}/stb_image/include/stb_image/stb_image.h",
        "%{Directory.Dependencies}/stb_image/include/stb_image/stb_image.cpp"
    }

    -- IncludeDir

    includedirs
    {
        -- Engine

        "src",

        -- Dependencies

        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    -- Links (only the libs)

    links
    {
        "GLFW",
        "Glad",
        "ImGui"
    }

    defines
    {
        "CH_BUILD_STATIC",
        "_CRT_SECURE_NO_WARNINGS"
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

---------------------------------------------------------------
----------