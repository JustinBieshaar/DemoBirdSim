project "ImGuiFileDialog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("../bin/%{cfg.buildcfg}")
	objdir ("../obj/%{cfg.buildcfg}")

	includedirs {
		"ImGuiFileDialog",
		"imgui/",
		"glad/include",
		"glfw/include/"
	}

	files {
		"ImGuiFileDialog/ImGuiFileDialog.cpp",
		"ImGuiFileDialog/ImGuiFileDialog.h"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"