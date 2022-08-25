workspace "hangar"
	architecture "x64"
	startproject "Sandbox"
	cppdialect "c++latest"
	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }
	defines {
		"UNICODE",
	}
	includedirs {
		"%{wks.location}/src",
	}
	targetdir ("%{wks.location}/build")
	objdir ("%{wks.location}/intermediates/%{prj.name}_%{cfg.buildcfg}_%{cfg.system}/")
	filter "system:windows"
		staticruntime "off"
		systemversion "latest"
        	defines { "WIN32" }
		links {
			"d3d11",
			"dxgi",
			"d3dcompiler"
		}
	filter "configurations:Debug"
		symbols "on"
		defines {  "_DEBUG", }
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "on"
		symbols "on"

	include "src"
	include "sandbox"