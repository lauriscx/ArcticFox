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
	
--Gets from windows propertie enviroments path to installed vulkan/spirv sdk(located in c:\VulkanSDK\1.2.170.0) from there we get include folder.
VULKAN_SDK = os.getenv("VULKAN_SDK")--Can be copied and added to vendor folder. Then no need for vulkan sdk installation.
MONO_SDK = os.getenv("MONO_PROJECT")--Can be copied and added to vendor folder. Then no need for MONO Project sdk installation.
	
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
IncludeDir["optick"] = "%{wks.location}/vendor/optick/include"
IncludeDir["assimp"] = "%{wks.location}/vendor/assimp/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/include" --Getting includes from c:\VulkanSDK\1.2.170.0\include
IncludeDir["Mono"] = "%{MONO_SDK}/include/mono-2.0" --Getting includes from C:\Program Files\Mono

LibraryDir = {}
LibraryDir["AL"] = "%{wks.location}/vendor/AL/lib/Win64/"
LibraryDir["glew"] = "%{wks.location}/vendor/glew/lib/x64/"
LibraryDir["GLFW"] = "%{wks.location}/vendor/GLFW/lib/"
LibraryDir["assimp"] = "%{wks.location}/vendor/assimp/lib/x64/"
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/vendor/SPIRV/Lib"
LibraryDir["VulkanSDK_DebugDLL"] = "%{wks.location}/vendor/SPIRV/Bin"
LibraryDir["MonoSDK"] = "%{MONO_SDK}/lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

group "Dependencies"
	include "vendor/yaml-cpp"
	include "vendor/optick"
group ""
include "AppFrame"
include "ArcticFox"
include "ArcticFoxRuntime"
include "ArcticFoxEditor"
include "GameScript"