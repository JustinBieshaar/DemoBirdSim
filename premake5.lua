-- OpenGL project
workspace "Demo-Bird-Simulator"
    architecture "x64"
    configurations { "Debug", "Release" }    
    startproject "BoilerPlate-OpenGL"
    
    flags
    {
        "MultiProcessorCompile"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Demo-Bird-Simulator"
    location "src"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    includedirs { 
        "include/", 
        "external/glad/include/", 
        "external/glfw/include/", 
        "external/glm/", 
        "external/imgui/", 
        "external/imgui/examples" ,
        "external/stb/"
    }

    files 
    { 
        -- Files
        "src/**.cpp", 
        "src/**.h",
    }

    links { "GLFW", "GLM", "GLAD", "ImGui" }

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "_RELEASE" }
        optimize "On"

-- Project
group "Dependencies"
    include "external/glfw.lua"
    include "external/glad.lua"
    include "external/glm.lua"
    include "external/imgui.lua"
group ""