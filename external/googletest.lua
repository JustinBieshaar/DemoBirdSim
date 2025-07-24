project "GoogleTest"
	kind "StaticLib"
    language "C++"
    cppdialect "C++20"
	architecture "x86_64"
    staticruntime "on"

	targetdir "../bin/%{cfg.buildcfg}"
	objdir "../obj/%{cfg.buildcfg}"
    
    includedirs {
        "googletest/googletest/include",
        "googletest/googletest/"
    }

    files {
	    "googletest/googletest/src/gtest-all.cc",
	    "googletest/googletest/src/gtest_main.cc"
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