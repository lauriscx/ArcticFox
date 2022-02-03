workspace "ArcticFox"
	architecture "x64"
	configurations {
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	startproject "ArcticFoxEditor"
	
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["AL"] = "%{wks.location}/vendor/AL/include"
IncludeDir["glew"] = "%{wks.location}/vendor/glew/include/GL"
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"
IncludeDir["spdlog"] = "%{wks.location}/vendor/spdlog/include"
IncludeDir["stb"] = "%{wks.location}/vendor/stb/include"
IncludeDir["entt"] = "%{wks.location}/vendor/entt/include"
IncludeDir["yaml"] = "%{wks.location}/vendor/yaml-cpp/include"

LibraryDir = {}
LibraryDir["AL"] = "%{wks.location}/vendor/AL/lib/Win64/"
LibraryDir["glew"] = "%{wks.location}/vendor/glew/lib/x64/"
LibraryDir["GLFW"] = "%{wks.location}/vendor/GLFW/lib/"

group "Dependencies"
	include "vendor/yaml-cpp"
group ""
include "AppFrame"
include "ArcticFox"
include "Game"
include "ArcticFoxEditor"