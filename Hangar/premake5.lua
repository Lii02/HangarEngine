project "Hangar"
	kind "StaticLib"
	files { "**.cpp", "**.h", "**.hpp" }
	includedirs {
		"%{wks.location}"
	}
	pchsource "Precompiled.cpp"
	pchheader "Precompiled.h"