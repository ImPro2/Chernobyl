project "HeaderOnlyDependencies"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    disablewarnings { warnings }

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp"
	}

	defines
	{
		"SPDLOG_COMPILED_LIB"
	}

	includedirs
	{
		"src/glm",
		"src/spdlog/include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
       runtime "Debug"
       symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
    
    filter "configurations:Dist"
        runtime "Release"
        optimize "On"