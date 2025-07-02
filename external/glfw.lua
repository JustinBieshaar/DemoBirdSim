project "glfw"
	kind "StaticLib"
	language "C"
	architecture "x86_64"

	targetdir ("../bin/%{cfg.buildcfg}")
	objdir ("../obj/%{cfg.buildcfg}")
	
	includedirs { "glfw/include/" }

	-- Include all .c and .h files in the src directory
	files { "glfw/src/**.c", "glfw/src/**.h" }

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"
		defines { "_GLFW_X11" }

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
		defines {
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"