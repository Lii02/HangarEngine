workspace "Hangar Engine"
	architecture "x64"
	startproject "Sandbox"
	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }
	defines {
		"UNICODE",
		"_CRT_SECURE_NO_WARNINGS",
	}
	cppdialect "c++20"
	targetdir ("%{wks.location}/Build")
	objdir ("%{wks.location}/Intermediates/%{prj.name}_%{cfg.buildcfg}_%{cfg.system}/")
	filter "system:windows"
		staticruntime "off"
		systemversion "latest"
        	defines { "WIN32" }
		includedirs {
			os.getenv("VULKAN_SDK") .. "/Include/"
		}
		libdirs {
			os.getenv("VULKAN_SDK") .. "/Lib/"
		}
		links {
			"vulkan-1",
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