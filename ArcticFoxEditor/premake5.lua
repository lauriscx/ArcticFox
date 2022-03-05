
project "ArcticFoxEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("../Build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../Build/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.c",
		"src/**.hpp",
		"src/**.cpp"
	}

	includedirs {
		"%{wks.location}/AppFrame/src/",
		"%{wks.location}/ArcticFox/src/",
		"%{prj.location}/src/",
		"%{IncludeDir.AL}",
		"%{IncludeDir.glew}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}", 
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.Mono}"
	}
	
	libdirs {
		"%{LibraryDir.assimp}"
	}

	links {
		"ArcticFox",
		"assimp.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			--"ENGINE_PLATFORM_WINDOWS",
			"_MBCS"
			--"IMGUI_API=__declspec(dllimport)"
		}

		filter { "configurations:Debug" }
			runtime "Debug"
			defines "DEBUG"
			symbols "On"
			postbuildcommands {
				"{COPYDIR} \"%{LibraryDir.VulkanSDK_DebugDLL}\" \"%{cfg.targetdir}\""
			}

		filter { "configurations:Release" }
			runtime "Release"
			defines "RELEASE"
			optimize "On"