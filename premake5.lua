workspace "hangar"
	architecture "x64"
	cppdialect "c++latest"
	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }
	links {
		"SDL2"
	}
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
	filter "configurations:Debug"
		symbols "on"
		defines {  "_DEBUG", }
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "on"
		symbols "on"

	include "src"