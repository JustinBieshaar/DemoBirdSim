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
        "core/ImGuiWindow/",
        "core/Utils/",

        --- Tools
        "tools/BirdsFactory"
    }

    files 
    { 
        -- Files
        "game/src/**.cpp", 
        "game/src/**.h",
    }

    links { "GLFW", "GLM", "GLAD", "ImGui", "Shader", "ECS", "SimpleDI", "Scenes", "Rendering", "ImGuiWindow", "Utils" }

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "_RELEASE" }
        optimize "On"    

---------- TOOLS (tbc) ----------

group "Tools" 
    project "BirdGenerator"
        location "tools/BirdGenerator/src"
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
            "external/nlohmann/", -- for JSon parsing and reading

            --- Core
            "core/Shader/",
            "core/Rendering/",
            "core/ECS/",
            "core/Utils/",

            --- Tools
            "tools/BirdsFactory"
        }

        files 
        { 
            -- Files
            "tools/BirdGenerator/src/**.cpp", 
            "tools/BirdGenerator/src/**.h",
        }

        links { "GLFW", "GLM", "GLAD", "ImGui", "Shader", "Rendering", "ECS", "Utils", "BirdsFactory" }

        filter "configurations:Debug"
            defines { 
                "_DEBUG",
                '_SOLUTIONDIR=R"(%{wks.location})"'
            }
            symbols "On"

        filter "configurations:Release"
            defines { "_RELEASE" }
            optimize "On"

---------- CORE ----------

-- function to generate core libraries
function createStaticLib(params)
    project(params.name)
        location(params.path)
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("bin/" .. outputdir .. "/" .. params.name)
        objdir ("obj/" .. outputdir .. "/" .. params.name)

        files {
            params.path .. "/**.h",
            params.path .. "/**.cpp"
        }

        includedirs {
            params.path
        }

        if params.includes then
            includedirs(params.includes)
        end

        if params.links then
            links(params.links)
        end

        filter "configurations:Debug"
        if params.debugDefines then
           defines { "_DEBUG", params.debugDefines}
        else
           defines { "_DEBUG" }
        end
            symbols "On"


        filter "configurations:Release"
        if params.releaseDefines then
           defines { "_RELEASE", params.releaseDefines}
        else
           defines { "_RELEASE" }
        end
            optimize "On"
end

---------- STRUCTURE ----------

group "Dependencies"
    include "external/glfw.lua"
    include "external/glad.lua"
    include "external/glm.lua"
    include "external/imgui.lua"

group "Core"
    createStaticLib { -- Simple dependency injection
        name = "SimpleDI",
        path = "core/SimpleDI"
    }
    createStaticLib { -- Utilities
        name = "Utils",
        path = "core/Utils",
        debugDefines = '_SOLUTIONDIR=R"(%{wks.location})"'
    }
    createStaticLib { -- Signal handling to observe and pass events
        name = "Signals",
        path = "core/Signals"
    }
    createStaticLib { -- Shader
        name = "Shader",
        path = "core/Shader",
        includes = 
            { 
                "external/glad/include/",
                "external/glfw/include/",
                "external/glm/" 
            },
        links = { "GLFW", "GLM", "GLAD" }
    }
    createStaticLib { -- Rendering, for reading obj files and defining vao, vbo and ebo.
        name = "Rendering",
        path = "core/Rendering",
        includes = 
            {
                "external/glad/include/",
                "external/glfw/include/",
                "external/glm/",
                "external/stb/",
                "core/Shader" 
            },
        links = { "GLFW", "GLM", "GLAD", "Shader" }
    }
    createStaticLib { -- ImGui window system to create automatic inspectable objects
        name = "ImGuiWindow",
        path = "core/ImGuiWindow",
        includes = { "external/imgui/"  },
        links = { "ImGui" }
    }
    createStaticLib { -- Entity component system
        name = "ECS",
        path = "core/ECS",
        includes = 
            { 
                "external/glad/include/",
                "external/glfw/include/",
                "external/glm/",

                "core/Shader",
                "core/Rendering",
                "core/Utils", -- TODO: add utils to imgui window to add a method to get the name of the object for fields.
                "core/ImGuiWindow", -- inspector
                "external/imgui/" -- ^
            },
        links = { "GLFW", "GLM", "GLAD", "Shader", "Rendering", "ImGuiWindow", "ImGui", "Utils" }
    }
    createStaticLib { -- Scenes
        name = "Scenes",
        path = "core/Scenes",
        includes = 
            { 
                "external/glad/include/",
                "external/glfw/include/",
                "external/glm/",

                "core/Shader",
                "core/ECS", -- includes ECS as a scene is also a ECS registry
                "core/Rendering", -- rendering for the loader
                "core/Utils", -- TODO: add utils to imgui window to add a method to get the name of the object for fields.
                "core/ImGuiWindow", -- inspector
                "external/imgui/" -- ^
            }, 
        links = { "GLFW", "GLM", "GLAD", "ECS", "Shader", "Rendering", "ImGuiWindow", "ImGui", "Utils" }
    }
group "Tools"
    createStaticLib { -- Birds Factory
        name = "BirdsFactory",
        path = "tools/BirdsFactory",
        includes = 
            { 
                "core/Shader",
                "core/ECS", -- includes ECS as a scene is also a ECS registry
                "core/Utils", -- TODO: add utils to imgui window to add a method to get the name of the object for fields.

                "external/nlohmann/" -- for JSon parsing and reading
            }, 
        links = { "ECS", "Shader", "Utils" },
        debugDefines = '_SOLUTIONDIR=R"(%{wks.location})"'
    }
group ""