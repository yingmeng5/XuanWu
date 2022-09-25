workspace "XuanWu"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "XuanWu"
	location "XuanWu"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"XW_PLATFORM_WINDOWS",
			"XW_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "XW_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "XW_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "XW_DIST"
		symbols "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

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
		"XuanWu/src"
	}

	links
	{
		"XuanWu"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"XW_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "XW_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "XW_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "XW_DIST"
		symbols "On"
		symbols "On"