project "hangar"
	kind "StaticLib"
	files { "**.cpp", "**.h", "**.hpp" }
	pchsource "precompiled.cpp"
	pchheader "precompiled.h"