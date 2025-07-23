workspace "Demo-Bird-Simulator"
    architecture "x64"
    configurations { "Debug", "Release" }    
    startproject "Demo-Bird-Simulator"

    flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

---------- MAIN ----------

project "Demo-Bird-Simulator"
    location "game/src"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    includedirs { 
        "include/", 

        --- External
        "external/glad/include/", 
        "external/glfw/include/", 
        "external/glm/", 
        "external/imgui/", 
        "external/imgui/examples" ,

        --- Core
        "core/Shader/",
        "core/ECS/",
        "core/SimpleDI/",
        "core/Scenes/",
        "core/Rendering/",
        "core/Signals/",
        "core/Utils/",
        "core/debug/Console/",

        -- Debug
        "core/debug/ImGuiWindow/",

        --- Tools
        "tools/BirdsFactory"
    }

    files 
    { 
        -- Files
        "game/src/**.cpp", 
        "game/src/**.h",
    }

    links { "GLFW", "GLM", "GLAD", "ImGui", "Shader", "ECS", "SimpleDI", "Scenes", "Rendering", "Signals", "ImGuiWindow", "Utils", "Console" }

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "_RELEASE" }
        optimize "On"    

---------- OTHERS ----------

-- Check premake/ for all other premake scripts

include "premake/external.lua"
include "premake/core.lua"
include "premake/debug.lua"
include "premake/tools.lua"
include "premake/tests.lua"