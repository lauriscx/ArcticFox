project "ImGuizmo"
	kind "StaticLib"
	language "C++"

	targetdir ("../../Build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../../Build/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"ImGuizmo.h",
		"ImGuizmo.cpp"
	}

	includedirs
	{
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"
