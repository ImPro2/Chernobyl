workspace "Chernobyl"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
warnings = { "4267", "4244",  "4302", "4311", "4312", "4067", "26495", "26451", "26812" }

IncludeDir = {}
IncludeDir["GLFW"]  = "../ExternalLibs/GLFW/include"
IncludeDir["Glad"]  = "../ExternalLibs/Glad/include"
IncludeDir["ImGui"] = "../ExternalLibs/imgui"
IncludeDir["glm"]   = "../ExternalLibs/glm"


group "Dependencies"
    include "ExternalLibs/GLFW"
    include "ExternalLibs/Glad"
    include "ExternalLibs/imgui"
group ""

include "Chernobyl"
include "Sandbox"