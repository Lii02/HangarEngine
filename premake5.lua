workspace "Hangar Engine"
	architecture "x64"
	startproject "Sandbox"
	cppdialect "c++latest"
	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }
	defines {
		"UNICODE",
		"_CRT_SECURE_NO_WARNINGS",
		"STB_IMAGE_IMPLEMENTATION",
		"STB_IMAGE_WRITE_IMPLEMENTATION",
		"STB_TRUETYPE_IMPLEMENTATION"
	}
	includedirs {
		"%{wks.location}/Vendor",
	}
	targetdir ("%{wks.location}/Build")
	objdir ("%{wks.location}/Intermediates/%{prj.name}_%{cfg.buildcfg}_%{cfg.system}/")
	filter "system:windows"
		staticruntime "off"
		systemversion "latest"
        	defines { "WIN32" }
		includedirs {
		}
		libdirs {
		}
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

	include "Hangar"
	include "Sandbox"