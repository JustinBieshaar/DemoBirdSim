project "GLM"
	kind "None"
    language "C++"
    cppdialect "C++20"
	architecture "x86_64"

	targetdir ("../bin/%{cfg.buildcfg}")
	objdir ("../obj/%{cfg.buildcfg}")
	
	includedirs { "glm/" }

	-- Include all GLM headers (no .cpp files since it's header-only)
	files { "glm/glm/**.hpp", "glm/glm/**.inl" }

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"
		defines { "_GLM_X11" }

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
		defines {
			"_GLM_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"