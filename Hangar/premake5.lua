project "Hangar"
	kind "StaticLib"
	files { "**.cpp", "**.h", "**.hpp" }
	includedirs {
		"%{wks.location}",
		"%{wks.location}/Hangar"
	}
	pchsource "Precompiled.cpp"
	pchheader "Precompiled.h"