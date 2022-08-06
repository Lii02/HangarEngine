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
			os.getenv("VULKAN_SDK") .. "/Include/"
		}
		libdirs {
			os.getenv("VULKAN_SDK") .. "/Lib/"
		}
		links {
			"vulkan-1",
			"shaderc_combined",
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