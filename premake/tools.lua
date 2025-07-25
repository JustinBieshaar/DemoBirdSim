group "Tools"

createStaticLib {
    name = "BirdsFactory",
    path = "../tools/BirdsFactory",
    includes = {
        "../core/Shader",
        "../core/ECS",
        "../core/Utils",
        "../external/nlohmann/"
    },
    links = { "ECS", "Shader", "Utils" },
    debugDefines = '_SOLUTIONDIR=R"(%{os.getcwd()})"'
}

project "BirdGenerator"
    location "../tools/BirdGenerator/src"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir "../bin/tools/%{cfg.buildcfg}"
    objdir "../obj/tools/%{cfg.buildcfg}"

    includedirs {
        "../include/",
        "../external/glad/include/",
        "../external/glfw/include/",
        "../external/glm/",
        "../external/imgui/",
        "../external/imgui/examples",
        "../external/nlohmann/",
        "../external/imguiFileDialog/",

        "../core/Shader/",
        "../core/Rendering/",
        "../core/ECS/",
        "../core/Utils/",
        "../core/Signals/",

        "../core/debug/ImGuiWindow", -- inspector
        "../core/debug/ImGui-Utils/",
        "../external/imgui/", -- ^
        "../core/debug/Console/",

        "../tools/BirdsFactory"
    }

    files { "../tools/BirdGenerator/src/**.cpp", "../tools/BirdGenerator/src/**.h" }

    links { "GLFW", "GLM", "GLAD", "ImGui", "Shader", "Rendering", "ECS", "Utils", "Signals", "ImGui-Utils", "Console", "ImGuiFileDialog", "BirdsFactory" }

    filter "configurations:Debug"
        defines { "_DEBUG", '_SOLUTIONDIR=R"(%{os.getcwd()})"' }
        symbols "On"

    filter "configurations:Release"
        defines { "_RELEASE" }
        optimize "On"

group ""