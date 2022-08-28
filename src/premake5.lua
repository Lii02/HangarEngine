project "hangar"
	kind "ConsoleApp"
	files { "**.cpp", "**.h", "../main/**.cpp", "../main/**.h" }
	pchsource "precompiled.cpp"
	pchheader "precompiled.h"