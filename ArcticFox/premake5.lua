project "ArcticFox"
	kind "StaticLib"
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
		"%{prj.location}/src/",
		"%{IncludeDir.AL}",
		"%{IncludeDir.glew}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}", 
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.Mono}"
	}

	libdirs {
		"%{LibraryDir.assimp}"
	}

	links {
		"AppFrame",
		"assimp.lib"
	}

	filter "system:windows"
		--staticruntime "On"
		systemversion "latest"

		defines {
			--"ENGINE_PLATFORM_WINDOWS",
			--"_MBCS"
			--"IMGUI_API=__declspec(dllimport)"
		}

		filter { "configurations:Debug" }
			runtime "Debug"
			defines "DEBUG"
			symbols "On"
			links {
				"%{Library.ShaderC_Debug}",
				"%{Library.SPIRV_Cross_Debug}",
				"%{Library.SPIRV_Cross_GLSL_Debug}"
			}

		filter { "configurations:Release" }
			runtime "Release"
			defines "RELEASE"
			optimize "On"
			
			links {
				"%{Library.ShaderC_Release}",
				"%{Library.SPIRV_Cross_Release}",
				"%{Library.SPIRV_Cross_GLSL_Release}"
			}