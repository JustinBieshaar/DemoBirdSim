group "Core/Debug"

    createStaticLib { -- ImGui window system to create automatic inspectable objects
        name = "ImGuiWindow",
        path = "../core/debug/ImGuiWindow",
        includes = { "../external/imgui/"  },
        links = { "ImGui" }
    }

    createStaticLib { -- ImGui-Utils
        name = "ImGui-Utils",
        path = "../core/debug/ImGui-Utils",
        includes = { "../external/imgui/", "../external/nlohmann/" },
        links = { "ImGui" },
        debugDefines = '_SOLUTIONDIR=R"(%{os.getcwd()})"'
    }
    
    createStaticLib { -- Console
        name = "Console",
        path = "../core/debug/Console",
        includes = { 
            "../external/imgui/", 
            "../external/nlohmann/",
            "../core/debug/ImGuiWindow"
             },
        links = { "ImGui", "ImGuiWindow", },
        debugDefines = '_SOLUTIONDIR=R"(%{os.getcwd()})"'
    }

group ""