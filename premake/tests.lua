-- Create static library
function createUnitTestProject(params)
    project(params.name)
        location(params.path)
	    kind "ConsoleApp"
	    language "C++"
	    cppdialect "C++20"
	    staticruntime "on"

	    targetdir ("../bin/" .. outputdir .. "/CoreTests")
	    objdir ("../obj/" .. outputdir .. "/CoreTests")

        files { params.path .. "/**.h", params.path .. "/**.cpp" }

	    includedirs {
	        "../external/googletest/googletest/include",
	        "../external/googletest/googletest/",

	        params.includes
	    }

	    links { "GoogleTest", params.links }

	    filter "configurations:Debug"
	        defines { "_DEBUG" }
	        symbols "On"

	    filter "configurations:Release"
	        defines { "_RELEASE" }
	        optimize "On"
end

group "Core/Tests"
	createUnitTestProject {
		name = "Signals_Tests",
		path = "../core/tests/Signals_Tests",
		includes = { "../core/Signals" },
		links = { "Signals" }
	}

	createUnitTestProject {
		name = "SimpleDI_Tests",
		path = "../core/tests/SimpleDI_Tests",
		includes = { "../core/SimpleDI" },
		links = { "SimpleDI" }
	}

group ""