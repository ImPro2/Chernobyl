workspace "Chernobyl"
    architecture "x64"
    startproject "Sandbox"


    ----------
    --------------------------------------------------------------------------------------
    --  Public Variables (or fields idk what they're called)
    --------------------------------------------------------------------------------------

    configurations
    {
    --  name        -- long name   - performance     - logging severity                  - description

        "Dev",      -- Development - Slow runtime    - trace   + info  + warning + error - adding new features
        "Test",     -- Test        - Faster runtime  - warning + error                   - test performance
        "Dist"      -- Distribute  - Fastest runtime - none                              - deploy games with it
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    warnings = { "4267", "4244",  "4302", "4311", "4312", "4067", "26495", "26451", "26812" }   -- i hate warnings with a passion

    --------------------------------------------------------------------------------------
    ---------


    ----------
    --------------------------------------------------------------------------------------
    --  Directories
    --------------------------------------------------------------------------------------

    -------------------------
    -- Useful Directories
    -------------------------

    -- Directories

    Directory = {}
    Directory["Root"]                       = ".."
    Directory["Chernobyl"]                  = "%{Directory.Root}/Chernobyl"
    Directory["Sandbox"]                    = "%{Directory.Root}/Sandbox"
    Directory["Dependencies"]               = "%{Directory.Root}/Dependencies"

    -------------------------
    -- Include Directories
    -------------------------

    -- Dependency Include Directories

    IncludeDir = {}
    IncludeDir["GLFW"]                      = "../Dependencies/GLFW/include"
    IncludeDir["Glad"]                      = "../Dependencies/Glad/include"
    IncludeDir["ImGui"]                     = "../Dependencies/imgui"
    IncludeDir["spdlog"]                    = "../Dependencies/spdlog/include"
    IncludeDir["glm"]                       = "../Dependencies/glm"
    IncludeDir["stb_image"]                 = "../Dependencies/stb_image/include"

    --------------------------------------------------------------------------------------
    ---------

    -- Dependencies

    group "Dependencies"
        include "../Dependencies/GLFW"
        include "../Dependencies/Glad"
        include "../Dependencies/imgui"
    group ""
    
    -- Engine
    include "Chernobyl/premake5.lua"
    include "Sandbox/premake5.lua"