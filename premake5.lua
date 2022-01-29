workspace "ArticFox"
	architecture "x64"
	
	configurations {
		"Debug",
		"Release",
		"Distribution"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "AppFrame"
	location "AppFrame"
	kind "SharedLib"
	language "C++"
	targedir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	file {
		"%{prj.name}/src/**.h"
		"%{prj.name}/src/**.hpp"
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/Libraries/AF/include/"
	}

	filter "system:windows"
		ccpdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		define {
			""
		}
		
		postbuildcommands {
			("")
		}

		filter "configurations:Debug"
			define "DEBUG"
			symbols "On"

		filter "configurations:Release"
			define "RELEASE"
			optimize "On"

		filter "configurations:Distribution"
			define "DISTRIBUTION"
			optimize "On"

project "ArticFox"
	location "ArticFox"
	kind "ConsoleApp"
	language "C++"
	targedir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	file {
		"%{prj.name}/src/**.h"
		"%{prj.name}/src/**.hpp"
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/Libraries/AF/include/",
		""
	}

	links {
		"AppFrame"
	}

	filter "system:windows"
		ccpdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		define {
			""
		}

		filter "configurations:Debug"
			define "DEBUG"
			symbols "On"

		filter "configurations:Release"
			define "RELEASE"
			optimize "On"

		filter "configurations:Distribution"
			define "DISTRIBUTION"
			optimize "On"
