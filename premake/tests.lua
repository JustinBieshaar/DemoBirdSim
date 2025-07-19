group "Core/Tests"

project "SignalTests"
    location "../core/tests/SignalsTests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/CoreTests")
    objdir ("../obj/" .. outputdir .. "/CoreTests")

    files { "../core/tests/SignalsTests/**.cpp", "../core/tests/SignalsTests/**.h" }

    includedirs {
        "../external/googletest/googletest/include",
        "../external/googletest/googletest",

        "../core/Signals",
    }

    links { "gtest", "gtest_main", "Signals" }

    files {
    	"googletest/src/gtest-all.cc",
    	"googletest/src/gtest_main.cc"
	}

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "_RELEASE" }
        optimize "On"

group ""