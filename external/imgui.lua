project "ImGui"
	kind "StaticLib"
	language "C"
	architecture "x86_64"

	targetdir ("../bin/%{cfg.buildcfg}")
	objdir ("../obj/%{cfg.buildcfg}")
	
	includedirs {
		"imgui/",
		"glad/include",
		"glfw/include/"
	}

	-- Include all core ImGui .cpp files and selected backends
	files {
		"imgui/*.cpp",
		"imgui/backends/imgui_impl_glfw.cpp",
		"imgui/backends/imgui_impl_opengl3.cpp",
		"imgui/*.h",
		"imgui/backends/imgui_impl_glfw.h",
		"imgui/backends/imgui_impl_opengl3.h"
	}

	defines { "IMGUI_IMPL_OPENGL_LOADER_GLAD" }

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"
		defines { "_IMGUI_X11" }

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
		defines {
			"_IMGUI_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"