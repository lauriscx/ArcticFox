workspace "ArcticFox"
	architecture "x64"

	startproject "ArcticFox"
	
	configurations {
		"Debug",
		"Release"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GLFW"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"GLFW/include/GLFW/glfw3.h",
		"GLFW/include/GLFW/glfw3native.h",
		"GLFW/src/glfw_config.h",
		"GLFW/src/context.c",
		"GLFW/src/init.c",
		"GLFW/src/input.c",
		"GLFW/src/monitor.c",
		"GLFW/src/vulkan.c",
		"GLFW/src/window.c"
	}
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			"GLFW/src/x11_init.c",
			"GLFW/src/x11_monitor.c",
			"GLFW/src/x11_window.c",
			"GLFW/src/xkb_unicode.c",
			"GLFW/src/posix_time.c",
			"GLFW/src/posix_thread.c",
			"GLFW/src/glx_context.c",
			"GLFW/src/egl_context.c",
			"GLFW/src/osmesa_context.c",
			"GLFW/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"GLFW/src/win32_init.c",
			"GLFW/src/win32_joystick.c",
			"GLFW/src/win32_monitor.c",
			"GLFW/src/win32_time.c",
			"GLFW/src/win32_thread.c",
			"GLFW/src/win32_window.c",
			"GLFW/src/wgl_context.c",
			"GLFW/src/egl_context.c",
			"GLFW/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "AppFrame"
	location "AppFrame"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/%{prj.name}/src/**.h",
		"%{prj.name}/%{prj.name}/src/**.hpp",
		"%{prj.name}/%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/Libraries/AL/include/",
		"%{prj.name}/Libraries/Entt/include/GL/",
		"%{prj.name}/Libraries/glew/include/GL/",
		"%{prj.name}/Libraries/glfw/include/",
		"%{prj.name}/Libraries/glm/glm/",
		"%{prj.name}/Libraries/spdlog/include/",
		"%{prj.name}/Libraries/stb/include/",
		"%{prj.name}/%{prj.name}/src/"
	}
	libdirs {
		"%{prj.name}/Vendor/AL/lib/Win64/",
		"%{prj.name}/Vendor/glew/lib/Win64/"
	}

	links {
		"GLFW",
		"OpenAL32",
		"glew32",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			""
		}
		
		postbuildcommands {
			("")
		}

		filter "configurations:Debug"
			defines "DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "RELEASE"
			optimize "On"

		filter "configurations:Distribution"
			defines "DISTRIBUTION"
			optimize "On"

project "ArcticFox"
	location "ArcticFox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/**.h",
		"%{prj.name}/**.hpp",
		"%{prj.name}/**.cpp"
	}

	includedirs {
		"AppFrame/Libraries/AL/include/",
		"AppFrame/Libraries/Entt/include/GL/",
		"AppFrame/Libraries/glew/include/GL/",
		"AppFrame/Libraries/glfw/include/",
		"AppFrame/Libraries/glm/",
		"AppFrame/Libraries/spdlog/include/",
		"AppFrame/Libraries/stb/include/",
		"AppFrame/AppFrame/src/",
		"ArcticFox/"
	}

	links {
		"AppFrame"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			""
		}

		filter "configurations:Debug"
			defines "DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "RELEASE"
			optimize "On"

		filter "configurations:Distribution"
			defines "DISTRIBUTION"
			optimize "On"
