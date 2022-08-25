project "hangar"
	kind "StaticLib"
	files { "**.cpp", "**.h", "**.hpp" }
	pchsource "Precompiled.cpp"
	pchheader "Precompiled.h"