workspace "XuanWu"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "XuanWu/vendor/GLFW/include"
IncludeDir["Glad"] = "XuanWu/vendor/Glad/include"
IncludeDir["ImGui"] = "XuanWu/vendor/imgui"
IncludeDir["glm"] = "XuanWu/vendor/glm"

group "Dependencies"
	include "XuanWu/vendor/GLFW"
	include "XuanWu/vendor/Glad"
	include "XuanWu/vendor/imgui"
group ""

project "XuanWu"
	location "XuanWu"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "xwpch.h"
	pchsource "XuanWu/src/xwpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"IMGUI_API=__declspec(dllexport)",
			"XW_PLATFORM_WINDOWS",
			"XW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
	
	filter "configurations:Debug"
		defines "XW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "XW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "XW_DIST"
		runtime "Release"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"XuanWu/vendor/spdlog/include",
		"XuanWu/src",
		"XuanWu/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"XuanWu"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"IMGUI_API=__declspec(dllimport)",
			"XW_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "XW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "XW_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "XW_DIST"
		runtime "Release"
		optimize "On"