
-- Create static library
function createStaticLib(params)
    project(params.name)
        location(params.path)
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("../bin/" .. outputdir .. "/" .. params.name)
        objdir ("../obj/" .. outputdir .. "/" .. params.name)

        files { params.path .. "/**.h", params.path .. "/**.cpp" }
        includedirs { params.path }

        if params.includes then
            includedirs(params.includes)
        end

        if params.links then
            links(params.links)
        end

        filter "configurations:Debug"
            defines { "_DEBUG" }
            if params.debugDefines then
                defines { params.debugDefines }
            end
            symbols "On"

        filter "configurations:Release"
            defines { "_RELEASE" }
            if params.releaseDefines then
                defines { params.releaseDefines }
            end
            optimize "On"
end

group "Core"
    createStaticLib { -- Simple dependency injection
        name = "SimpleDI",
        path = "../core/SimpleDI"
    }
    createStaticLib { -- Utilities
        name = "Utils",
        path = "../core/Utils",
        debugDefines = '_SOLUTIONDIR=R"(%{os.getcwd()})"'
    }
    createStaticLib { -- Signal handling to observe and pass events
        name = "Signals",
        path = "../core/Signals"
    }
    createStaticLib { -- Shader
        name = "Shader",
        path = "../core/Shader",
        includes = 
            { 
                "../external/glad/include/",
                "../external/glfw/include/",
                "../external/glm/",
                "../core/Utils" -- for path manager
            },
        links = { "GLFW", "GLM", "GLAD" },
        debugDefines = '_SOLUTIONDIR=R"(%{os.getcwd()})"'
    }
    createStaticLib { -- Rendering, for reading obj files and defining vao, vbo and ebo.
        name = "Rendering",
        path = "../core/Rendering",
        includes = 
            {
                "../external/glad/include/",
                "../external/glfw/include/",
                "../external/glm/",
                "../external/stb/",
                "../core/Shader",
                "../core/Utils" 
            },
        links = { "GLFW", "GLM", "GLAD", "Shader" }
    }
    createStaticLib { -- Entity component system
        name = "ECS",
        path = "../core/ECS",
        includes = 
            { 
                "../external/glad/include/",
                "../external/glfw/include/",
                "../external/glm/",

                "../core/Shader",
                "../core/Rendering",
                "../core/Utils", -- TODO: add utils to imgui window to add a method to get the name of the object for fields.
                "../core/debug/ImGuiWindow", -- inspector
                "../external/imgui/" -- ^
            },
        links = { "GLFW", "GLM", "GLAD", "Shader", "Rendering", "ImGuiWindow", "ImGui", "Utils" }
    }
    createStaticLib { -- Scenes
        name = "Scenes",
        path = "../core/Scenes",
        includes = 
            { 
                "../external/glad/include/",
                "../external/glfw/include/",
                "../external/glm/",

                "../core/Shader",
                "../core/ECS", -- includes ECS as a scene is also a ECS registry
                "../core/Rendering", -- rendering for the loader
                "../core/Utils", -- TODO: add utils to imgui window to add a method to get the name of the object for fields.
                "../core/debug/ImGuiWindow", -- inspector
                "../external/imgui/", -- ^

                "../core/debug/Console", -- inspector
            }, 
        links = { "GLFW", "GLM", "GLAD", "ECS", "Shader", "Rendering", "ImGuiWindow", "Console", "ImGui", "Utils" }
    }

group ""