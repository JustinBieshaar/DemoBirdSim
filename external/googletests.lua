project "GoogleTests"
	kind "StaticLib"
    language "C++"
    cppdialect "C++20"
	architecture "x86_64"

	targetdir "../bin/%{cfg.buildcfg}"
	objdir "../obj/%{cfg.buildcfg}"
    
    includedirs {
        "googletests/include",
        "googletests/googletest"
    }

    files {
	    "googletests/src/gtest-all.cc",
	    "googletests/src/gtest_main.cc"
	}

    filter "system:linux"
        pic "On"
        systemversion "latest"

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"